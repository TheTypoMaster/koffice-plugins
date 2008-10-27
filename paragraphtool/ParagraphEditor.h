/* This file is part of the KDE project
 * Copyright (C) 2008 Florian Merz <florianmerz@gmx.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef PARAGRAPHEDITOR_H
#define PARAGRAPHEDITOR_H

#include "ParagraphBase.h"
#include "ParagraphFragment.h"
#include "Ruler.h"

#include <QRectF>
#include <QTextCursor>
#include <QTextBlock>
#include <QVector>

class KoParagraphStyle;
class KoCanvasBase;

class QObject;
class QPainter;
class QTextLayout;

/**
 * This is the tool for editing paragraph formatting
 * It displays all paragraph formatting parameters directly on the canvas
 * and allows to modify them, too.
 */
class ParagraphEditor : public ParagraphBase
{
    Q_OBJECT
public:
    explicit ParagraphEditor(QObject *parent, KoCanvasBase *canvas);
    ~ParagraphEditor();

    void initializeRuler(Ruler &ruler, const QString &name, int options = 0);

    void paint(QPainter &painter, const KoViewConverter &converter);

    QRectF dirtyRectangle();

    void loadRulers();
    void saveRulers();

    // paint a label at the specified position
    void paintLabel(QPainter &painter, const KoViewConverter &converter) const;

    // paint all rulers for a given fragment
    void paintRulers(QPainter &painter, const KoViewConverter &converter, const ParagraphFragment &fragment) const;

    bool createFragments();

    bool hasActiveRuler() const {
        return m_activeRuler != noRuler;
    }
    void activateRuler(RulerIndex ruler, RulerFragment *fragment);
    bool activateRulerAt(const QPointF &point);
    void deactivateRuler();
    void resetActiveRuler();
    void moveActiveRulerTo(const QPointF &point);

    Ruler &focusedRuler() {
        return m_rulers[m_focusedRuler];
    }
    bool hasFocusedRuler() const {
        return m_focusedRuler >= 0 && m_focusedRuler < maxRuler;
    }
    void focusRuler(RulerIndex ruler);

    void focusFirstRuler();
    void focusLastRuler();
    bool focusPreviousRuler();
    bool focusNextRuler();

    void defocusRuler();

    bool hasHighlightedRuler() const {
        return m_highlightedRuler != noRuler;
    }
    void highlightRulerAt(const QPointF &point);
    void dehighlightRuler();

    bool smoothMovement() {
        return m_smoothMovement;
    }
    void toggleSmoothMovement() {
        m_smoothMovement = !m_smoothMovement; emit smoothMovementChanged(m_smoothMovement);
    }

    QTextBlockFormat blockFormat() const {
        return textBlock().blockFormat();
    }
    QTextCharFormat charFormat() const {
        return textBlock().charFormat();
    }
    QTextLayout *textLayout() const {
        return textBlock().layout();
    }

public slots:
    // should be called when the value of any of the rulers changed
    void updateLayout();

    // Apply the parent's style to the active ruler
    // (essentially deletes the setting)
    void applyParentStyleToActiveRuler();

    // if the parargraph style is inherited from a named paragraph style
    // return that name, otherwise return QString()
    QString styleName();

    void setSmoothMovement(bool smoothMovement) {
        m_smoothMovement = smoothMovement;
    }

protected:
    void addShapes();

signals:
    void styleNameChanged(const QString&);
    void smoothMovementChanged(bool smooth);

private:
    KoParagraphStyle *m_paragraphStyle;

    Ruler m_rulers[maxRuler];

    RulerIndex m_activeRuler,
    m_focusedRuler,
    m_highlightedRuler;

    RulerFragment *m_activeRulerFragment;
    RulerFragment *m_highlightedRulerFragment;

    QRectF m_storedRepaintRectangle;

    bool m_smoothMovement;

};

#endif

