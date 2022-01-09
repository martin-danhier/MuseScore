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

GridLayout {

    id: root
    property TimeSignaturePropertiesModel timeSignatureModel: null

    columns: 2
    anchors.fill: parent

    RadioButtonGroup {
        id: radioGroup

        Layout.rowSpan: 4
        Layout.fillHeight: true
        Layout.preferredWidth: 60

        orientation: ListView.Vertical

        // Define the items of the list with components defined below
        model: [
            // Fraction
            {
                contentComponent: fractionComponent,
                valueRole: TimeSignaturePropertiesModel.NORMAL
            },
            // Four four
            {
                contentComponent: fourFourComponent,
                valueRole: TimeSignaturePropertiesModel.FOUR_FOUR
            },
            // Alla breve
            {
                contentComponent: allaBreveComponent,
                valueRole: TimeSignaturePropertiesModel.ALLA_BREVE
            },
            // Other
            {
                contentComponent: otherComponent,
                valueRole: TimeSignaturePropertiesModel.OTHER
            },
        ]

        // Wrap each component in a radio button
        delegate: RoundedRadioButton {
            id: timeFractionButton

            checked: root.timeSignatureModel.currentAppearanceType === modelData.valueRole

            // Spacing between the radio button and the text
            spacing: 10

            ButtonGroup.group: radioGroup.radioButtonGroup

            height: 30
            width: parent.width

            contentComponent: modelData.contentComponent

            navigation.row: model.index
            navigation.column: 0

            onToggled: {
                root.timeSignatureModel.currentAppearanceType = modelData.valueRole
            }

            onCheckedChanged: {
                if (checked && !navigation.active) {
                    navigation.requestActive()
                }
            }
        }

        // Define components used in the list

        Component {
            id: fractionComponent

            StyledTextLabel {
                id: fractionLabel

                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideNone
                horizontalAlignment: Text.AlignLeft
                text: qsTrc("palette", "Text:")
            }
        }

        Component {
            id: fourFourComponent

            StyledIconLabel {
                anchors.verticalCenter: parent.verticalCenter
                font.family: ui.theme.musicalFont.family
                font.pixelSize: 20
                horizontalAlignment: Text.AlignLeft
                iconCode: MusicalSymbolCodes.TIMESIG_COMMON
            }
        }

        Component {
            id: allaBreveComponent

            StyledIconLabel {
                anchors.verticalCenter: parent.verticalCenter
                font.family: ui.theme.musicalFont.family
                font.pixelSize: 20
                horizontalAlignment: Text.AlignLeft
                iconCode: MusicalSymbolCodes.TIMESIG_CUT
            }
        }

        Component {
            id: otherComponent

            StyledTextLabel {
                id: otherLabel

                elide: Text.ElideNone
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignLeft
                text: qsTrc("palette", "Other:")
            }
        }

    }

    Row {
        spacing: 5
        height: 30
        Layout.column: 1

        TextInputField {
            height: parent.height
            width: 80
        }

        StyledTextLabel {
            text: "/"
            anchors.verticalCenter: parent.verticalCenter
        }

        TextInputField {
            height: parent.height
            width: 80
        }
    }

    Dropdown {
        id: otherDropdown

        currentIndex: 0
        Layout.column: 1
        Layout.row: 3

        Layout.preferredWidth: 30 + otherDropdown.iconFontPixelSize

        iconFontFamily: ui.theme.musicalFont.family
        iconFontPixelSize: 30
        showLabelText: false

        model: [
            // tempus perfectum, prol. perfecta
            {
                text: qsTrc("palette", "Tempus perfectum, prol. perfecta"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_1,
                value: TimeSignaturePropertiesModel.PROLATION_1
            },
            // tempus perfectum, prol. imperfecta
            {
                text: qsTrc("palette", "Tempus perfectum, prol. imperfecta"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_2,
                value: TimeSignaturePropertiesModel.PROLATION_2
            },
            // tempus perfectum, prol. imperfecta, dimin.
            {
                text: qsTrc("palette", "Tempus perfectum, prol. imperfecta, dimin."),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_3,
                value: TimeSignaturePropertiesModel.PROLATION_3
            },
            // tempus perfectum, prol. perfecta, dimin.
            {
                text: qsTrc("palette", "Tempus perfectum, prol. perfecta, dimin."),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_4,
                value: TimeSignaturePropertiesModel.PROLATION_4
            },
            // tempus imperf. prol. perfecta
            {
                text: qsTrc("palette", "Tempus imperf. prol. perfecta"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_5,
                value: TimeSignaturePropertiesModel.PROLATION_5
            },
            // tempus imperf., prol. imperfecta, reversed
            {
                text: qsTrc("palette", "Tempus imperf., prol. imperfecta, reversed"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_7,
                value: TimeSignaturePropertiesModel.PROLATION_7
            },
            // tempus imperf., prol. perfecta, dimin.
            {
                text: qsTrc("palette", "Tempus imperf., prol. perfecta, dimin."),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_8,
                value: TimeSignaturePropertiesModel.PROLATION_8
            },
            // tempus imperf., prol imperfecta, dimin., reversed
            {
                text: qsTrc("palette", "Tempus imperf., prol imperfecta, dimin., reversed"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_10,
                value: TimeSignaturePropertiesModel.PROLATION_10
            },
            // tempus imperf., prol. perfecta, reversed
            {
                text: qsTrc("palette", "Tempus imperf., prol. perfecta, reversed"),
                icon: MusicalSymbolCodes.MENSURAL_PROLATION_11,
                value: TimeSignaturePropertiesModel.PROLATION_11
            },
        ]

    }
}
