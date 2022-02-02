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

#ifndef MU_COMMONSCENE_EXAMPLEPAINTVIEW_H
#define MU_COMMONSCENE_EXAMPLEPAINTVIEW_H

#include "notation/view/notationpaintview.h"
#include "modularity/ioc.h"
#include "project/iprojectcreator.h"

class Ms::Score;

namespace mu::commonscene {

// Based on TemplatePaintView, which displays a score from a template file
// The example paint view displays an example score which can be created using a cursor,
// for example.
class ExamplePaintView : public notation::NotationPaintView
{
    Q_OBJECT

    INJECT(commonscene, project::IProjectCreator, notationCreator)

public:
    explicit ExamplePaintView(QQuickItem *parent = nullptr);

    void setScore(Ms::MasterScore *score);

private slots:
    void onViewSizeChanged() override;

private:
    void onNotationSetup() override;

    void adjustCanvas();
    qreal resolveDefaultScaling() const;

    notation::INotationPtr m_notationToSetup = nullptr;
};
}

#endif // MU_COMMONSCENE_EXAMPLEPAINTVIEW_H