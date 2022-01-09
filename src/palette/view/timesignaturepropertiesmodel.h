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

#ifndef MU_PALETTE_TIMESIGNATUREPROPERTIESMODEL_H
#define MU_PALETTE_TIMESIGNATUREPROPERTIESMODEL_H

#include <QObject>

namespace mu::palette {
class TimeSignaturePropertiesModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentAppearanceType READ currentAppearanceType WRITE setCurrentAppearanceType
                   NOTIFY currentAppearanceTypeChanged)

public:
    // Possible appearance types
    enum TimeSigAppearanceType {
        // Fraction
        NORMAL,
        FOUR_FOUR,
        ALLA_BREVE,
        // Other kinds of time signatures, such as prolations
        OTHER
    };
    Q_ENUM(TimeSigAppearanceType)

    enum OtherTimeSigAppearanceType {
        // tempus perfectum, prol. perfecta
        PROLATION_1,
        // tempus perfectum, prol. imperfecta
        PROLATION_2,
        // tempus perfectum, prol. imperfecta, dimin.
        PROLATION_3,
        // tempus perfectum, prol. perfecta, dimin.
        PROLATION_4,
        // tempus imperf. prol. perfecta
        PROLATION_5,
        // tempus imperf., prol. imperfecta, reversed
        PROLATION_7,
        // tempus imperf., prol. perfecta, dimin.
        PROLATION_8,
        // tempus imperf., prol imperfecta, dimin., reversed
        PROLATION_10,
        // tempus imperf., prol. perfecta, reversed
        PROLATION_11,
    };
    Q_ENUM(OtherTimeSigAppearanceType)

    int currentAppearanceType() const;
    Q_INVOKABLE void load();

public slots:
    void setCurrentAppearanceType(int newType);

signals:
    void currentAppearanceTypeChanged();

private:

    TimeSigAppearanceType m_currentAppearanceType = TimeSigAppearanceType::NORMAL;
    // Used if m_currentAppearanceType == OTHER
    OtherTimeSigAppearanceType m_currentOtherAppearanceType = OtherTimeSigAppearanceType::PROLATION_1;
};
}

#endif // MU_PALETTE_TIMESIGNATUREPROPERTIESMODEL_H