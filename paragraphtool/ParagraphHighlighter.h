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

#ifndef PARAGRAPHHIGHLIGHTER_H
#define PARAGRAPHHIGHLIGHTER_H

#include "ParagraphBase.h"

#include <QRectF>

class KCanvasBase;
class KViewConverter;

class QPainter;

/**
 * This tool can be used to highlight a paragraph of text
 */
class ParagraphHighlighter : public ParagraphBase
{
    Q_OBJECT
public:
    explicit ParagraphHighlighter(QObject *parent, KCanvasBase *canvas);
    ~ParagraphHighlighter();

    void paint(QPainter &painter, const KViewConverter &converter);

    QRectF dirtyRectangle();

private:
    QRectF m_storedRepaintRectangle;
};

#endif

