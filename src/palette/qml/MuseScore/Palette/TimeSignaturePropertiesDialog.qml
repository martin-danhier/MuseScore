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
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import MuseScore.Ui 1.0
import MuseScore.UiComponents 1.0
import MuseScore.Palette 1.0

import "internal"

StyledDialogView {
    id: root

    title: qsTrc("palette", "Time Signature Properties")

    contentWidth: 779
    contentHeight: 640
    margins: 12

    TimeSignaturePropertiesModel {
        id: propertiesModel
    }

    Component.onCompleted: {
        propertiesModel.load()
    }

    ColumnLayout {
        width: parent.width
        height: parent.height

        spacing: 10

        // Appearance
        TimeSignatureAppearanceSettings {
            id: appearanceSettings

            timeSignatureModel: propertiesModel
        }

        // Beam groups
        BeamGroups {
            id: beamGroups

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 16
            Layout.bottomMargin: 16

            spacing: 12

            FlatButton {
                text: qsTrc("global", "Cancel")
            }

            FlatButton {
                text: qsTrc("global", "OK")
                accentButton: true
            }
        }
    }
}
