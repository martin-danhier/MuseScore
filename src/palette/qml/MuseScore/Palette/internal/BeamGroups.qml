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
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import MuseScore.Ui 1.0
import MuseScore.UiComponents 1.0
import MuseScore.Palette 1.0
import MuseScore.CommonScene 1.0
import MuseScore.NotationScene 1.0

StyledGroupBox {
    id: root

    title: qsTrc("palette", "Beam groups")

    BeamGroupsModel {
        id: beamGroupsModel

        score8View: example1View
        score16View: example2View
        score32View: example3View

    }

    Component.onCompleted: {
        beamGroupsModel.load()
    }

    ColumnLayout {
        width: parent.width
        height: parent.height

        Row {
            // Beam selector
            StyledGroupBox {
                title: qsTrc("palette", "Beam selector")

            }


            // "Also change shorter notes" checkbox
            CheckBox {
                id: shorterNotesCheckBox

                text: qsTrc("palette", "Also change shorter notes")
            }

        }

        GridLayout {
            id: grid

            columns: 2

            anchors.margins: 10
            rowSpacing: 5

            property int firstColumnWidth: 50

            Layout.fillWidth: true
            Layout.fillHeight: true

            // 1/8 line
            StyledTextLabel {
                Layout.minimumWidth: grid.firstColumnWidth

                text: qsTrc("palette", "1/8")
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ExamplePaintView {
                    id: example1View
                    anchors.fill: parent
                }
            }

            // 1/16 line
            StyledTextLabel {
                Layout.minimumWidth: grid.firstColumnWidth

                text: qsTrc("palette", "1/16")
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ExamplePaintView {
                    id: example2View
                    anchors.fill: parent
                }
            }

            // 1/32 line
            StyledTextLabel {
                Layout.minimumWidth: grid.firstColumnWidth

                text: qsTrc("palette", "1/32")
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ExamplePaintView {
                    id: example3View
                    anchors.fill: parent
                }
            }
        }

        // Reset button
        FlatButton {
            id: resetButton

            text: qsTrc("palette", "Reset")
        }
    }
}