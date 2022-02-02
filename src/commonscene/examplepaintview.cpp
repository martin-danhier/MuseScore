/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "examplepaintview.h"
#include "notation/internal/notation.h"
#include "log.h"

using namespace mu::commonscene;

ExamplePaintView::ExamplePaintView(QQuickItem *parent) : NotationPaintView(parent)
{
    setReadonly(true);
    setAcceptTouchEvents(false);
    setAcceptedMouseButtons(false);
    setAcceptHoverEvents(false);
    setConstraintCanvas(false);
    setBackgroundColorOverride(configuration()->foregroundColor());
}

void ExamplePaintView::setScore(Ms::MasterScore *score)
{
    score->setLayoutMode(engraving::LayoutMode::LINE);


    // Create the notation here. It will handle the destruction of the score.
    m_notationToSetup = std::make_shared<notation::Notation>(score);
    m_notationToSetup->setViewMode(notation::ViewMode::LINE);
    m_notationToSetup->setOpened(true);

    load();
}

void ExamplePaintView::adjustCanvas()
{
    qreal scaling = resolveDefaultScaling();

    if (qFuzzyIsNull(scaling) || scaling < 0) {
        return;
    }

    setScaling(scaling, QPointF());

    // Center vertically and align left horizontally (with a small margin)
    moveCanvasToCenter();
    auto origin = toLogical(PointF(10, 0));
    moveCanvas(origin.x(), -35);
}

qreal ExamplePaintView::resolveDefaultScaling() const
{
    //! NOTE: this value was found experimentally
    constexpr qreal PROPORTION_FACTOR = 0.7;

    RectF notationRect = notationContentRect();

    qreal widthScaling = width() / notationRect.width() / PROPORTION_FACTOR;
    qreal heightScaling = height() / notationRect.height() / PROPORTION_FACTOR;

    return std::min(widthScaling, heightScaling);
}

void ExamplePaintView::onNotationSetup()
{
    if (m_notationToSetup != nullptr) {
        setNotation(m_notationToSetup);

        adjustCanvas();
    }
}

void ExamplePaintView::onViewSizeChanged()
{
    adjustCanvas();
}