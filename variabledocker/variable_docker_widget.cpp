/*
Copyright 2011 Robert Marmorstein <robert@narnia.homeunix.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of 
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "variable_docker_widget.h"

//Qt includes
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QMessageBox>
#include <QtGui/QGridLayout>

//KDE includes

#include <KDE/KLineEdit>
#include <KDE/KComboBox>

//Koffice includes
#include <KCanvasBase.h>
#include <KCanvasObserverBase.h>
#include <KInlineTextObjectManager.h>
#include <KVariableManager.h>
#include <KShapeController.h>
#include <KResourceManager.h>
#include <KOdfText.h>

VariableDockerWidget::VariableDockerWidget(QWidget* parent) : QDockWidget("VariableDocker", parent), KCanvasObserverBase(), m_canvas(NULL), m_vmanager(NULL)
{
	QWidget* mainWidget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(mainWidget);

	setWindowTitle("VariableDocker");
	QLabel* name_label = new QLabel("Name");
	m_name = new KComboBox(true, this);
	QLabel* value_label = new QLabel("Value");
	m_value = new KLineEdit();
	layout->addWidget(name_label, 0, 0);
	layout->addWidget(m_name, 0, 1);
	layout->addWidget(value_label, 1, 0);
	layout->addWidget(m_value, 1, 1);
	m_addbutton = new QPushButton(mainWidget);
	m_addbutton->setText( "Add or Modify" );
	m_addbutton->setToolTip("Create or modify a user-defined variable.");
	layout->addWidget(m_addbutton, 2, 1);
	m_removebutton = new QPushButton(mainWidget);
	m_removebutton->setText("Remove");
	m_removebutton->setToolTip("Remove a variable.");
	layout->addWidget(m_removebutton, 0,2);
	setWidget(mainWidget);
	connect(m_addbutton, SIGNAL(clicked()), this, SLOT(variable_docker_submit()));
	connect(m_removebutton, SIGNAL(clicked()), this, SLOT(variable_remove()));
	connect(m_name, SIGNAL(returnPressed(const QString&)), m_value, SLOT(setFocus()));
	connect(m_value, SIGNAL(editingFinished()), this, SLOT(variable_docker_submit()));
	connect(m_name, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(updateValueField(const QString)));

	m_addbutton->setEnabled(false);
}

VariableDockerWidget::~VariableDockerWidget(){
	delete m_addbutton;
	delete m_value;
	delete m_name;
}

void VariableDockerWidget::variable_remove() {
	if (m_vmanager) {
		QString name = m_name->lineEdit()->text();
		m_vmanager->remove(name);
	}
}

void VariableDockerWidget::variable_docker_submit(){
	if (m_vmanager) {
		QString name = m_name->lineEdit()->text();
		QString value = m_value->text();
		m_vmanager->setValue(name, value);
	}
}

void VariableDockerWidget::updateVariables() {
	m_name->clear();
	m_name->addItems(m_vmanager->variables());
}

void VariableDockerWidget::setCanvas(KCanvasBase* canvas){
	m_canvas = canvas;
	KShapeController* scont = m_canvas->shapeController();
	Q_ASSERT(scont);
	
	KResourceManager* manager = scont->resourceManager();
	Q_ASSERT(manager);
	
	KInlineTextObjectManager* tmanager = qvariant_cast<KInlineTextObjectManager *>(manager->resource(KOdfText::InlineTextObjectManager));
	Q_ASSERT(tmanager);
	
	m_vmanager = tmanager->variableManager();
	Q_ASSERT(m_vmanager);

	connect(m_vmanager, SIGNAL(valueChanged()), this, SLOT(updateVariables()));
	m_addbutton->setEnabled(true);
}

void VariableDockerWidget::updateValueField(const QString text) {
	QString value = m_vmanager->value(text);
	m_value->setText(value);
}
