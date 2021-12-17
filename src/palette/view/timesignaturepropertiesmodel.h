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

public:
//    QString name() const;

    Q_INVOKABLE QString fourFourText() const;
    Q_INVOKABLE QString allaBreveText() const;

    Q_INVOKABLE void load();

//public slots:
//    void setName(const QString &name);

signals:
    void propertiesChanged();

private:
    QString m_name;
};
}

#endif // MU_PALETTE_TIMESIGNATUREPROPERTIESMODEL_H