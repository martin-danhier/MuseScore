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

#ifndef MU_PALETTE_BEAMGROUPSMODEL_H
#define MU_PALETTE_BEAMGROUPSMODEL_H

#include <QObject>

#include "libmscore/groups.h"

namespace mu::commonscene {
class ExamplePaintView;
}

namespace mu::palette {
class BeamGroupsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject *score8View WRITE setScore8View)
    Q_PROPERTY(QObject *score16View WRITE setScore16View)
    Q_PROPERTY(QObject *score32View WRITE setScore32View)

public:
    Q_INVOKABLE void load();
    Q_INVOKABLE void setTimeSignature(Ms::Fraction newTimeSignature, const Ms::Groups &groups,
                                      const QString &numeratorOverride,
                                      const QString &denominatorOverride);

signals:
    void scoresChanged();

public slots:
    void setScore8View(QObject *score8View);
    void setScore16View(QObject *score16View);
    void setScore32View(QObject *score32View);

private:
    // Creates a score with chordsCount chords of the given duration, and stores pointers to the
    // chords in the given vector.
    Ms::MasterScore* createScore(int chordsCount, Ms::TDuration::DurationType duration,
                           std::vector<Ms::Chord *> *chords);

    // Examples data
    std::vector<Ms::Chord *> m_chords8;
    std::vector<Ms::Chord *> m_chords16;
    std::vector<Ms::Chord *> m_chords32;

    // Views
    commonscene::ExamplePaintView *m_score8View = nullptr;
    commonscene::ExamplePaintView *m_score16View = nullptr;
    commonscene::ExamplePaintView *m_score32View = nullptr;

    // Time signature properties
    Ms::Fraction m_timeSignature;
    QString m_numeratorOverride, m_denominatorOverride;

    // Groups
    Ms::Groups m_groups;
};
}

#endif // MU_PALETTE_BEAMGROUPSMODEL_H