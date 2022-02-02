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

#include "beamgroupsmodel.h"
#include "commonscene/examplepaintview.h"
#include "libmscore/masterscore.h"
#include "libmscore/mcursor.h"
#include "notation/internal/notation.h"
#include "notation/view/notationpaintview.h"

using namespace mu::palette;
using namespace mu::commonscene;

Ms::MasterScore *BeamGroupsModel::createScore(int chordsCount, Ms::TDuration::DurationType duration,
                                              std::vector<Ms::Chord *> *chords)
{
    Ms::MCursor cursor;

    // Setup score properties
    cursor.setTimeSig(m_timeSignature);
    cursor.createScore("");
    cursor.addPart("voice");
    cursor.move(0, Ms::Fraction(0, 1));
    cursor.addKeySig(Ms::Key::C);

    // Add a time signature that overrides the default one
    Ms::TimeSig *newTimeSignature = cursor.addTimeSig(m_timeSignature);
    if (!m_numeratorOverride.isEmpty()) {
        newTimeSignature->setNumeratorString(m_numeratorOverride);
    }
    if (!m_denominatorOverride.isEmpty()) {
        newTimeSignature->setDenominatorString(m_denominatorOverride);
    }

    // Setup groups
    Ms::GroupNode node{0, 0};
    Ms::Groups newGroups;
    newGroups.push_back(node);
    newTimeSignature->setGroups(newGroups);

    // Create and setup new chords
    for (int i = 0; i < chordsCount; ++i) {
        Ms::Chord *chord = cursor.addChord(77, duration);
        Ms::Fraction tick = chord->rtick();
        chord->setBeamMode(m_groups.beamMode(tick.ticks(), duration));
        chord->setStemDirection(Ms::DirectionV::UP);
        chords->push_back(chord);
    }

    // Set score style
    cursor.score()->style().set(Ms::Sid::pageOddLeftMargin, 0.0);
    cursor.score()->style().set(Ms::Sid::pageOddTopMargin, 10.0 / Ms::INCH);
    cursor.score()->style().set(Ms::Sid::startBarlineSingle, true);

    // Setup staff
    Ms::StaffType *staffType = cursor.score()->staff(0)->staffType(Ms::Fraction(0, 1));
    staffType->setLines(1);       // single line only
    staffType->setGenClef(false); // no clef
    //      st->setGenTimesig(false); // don't display time sig since ExampleView is unable to
    //      reflect custom time sig text/symbols TODO

    return cursor.score();
}

void BeamGroupsModel::setTimeSignature(Ms::Fraction newTimeSignature, const Ms::Groups &groups,
                                       const QString &numeratorOverride,
                                       const QString &denominatorOverride)
{
    // Update properties
    m_timeSignature = newTimeSignature;
    m_groups = groups;
    m_numeratorOverride = numeratorOverride;
    m_denominatorOverride = denominatorOverride;

    // Clear old data
    m_chords8.clear();
    m_chords16.clear();
    m_chords32.clear();

    Ms::Fraction f = m_timeSignature.reduced();
    int chordsCount = 0;

    // Create for 8th notes
    if (m_score8View != nullptr) {
        chordsCount = f.numerator() * (8 / f.denominator());
        m_score8View->setScore(
            createScore(chordsCount, Ms::TDuration::DurationType::V_EIGHTH, &m_chords8));
    }

    // Create for 16th notes
    if (m_score16View != nullptr) {
        chordsCount = f.numerator() * (16 / f.denominator());
        m_score16View->setScore(
            createScore(chordsCount, Ms::TDuration::DurationType::V_16TH, &m_chords16));
    }

    // Create for 32nd notes
    if (m_score32View != nullptr) {
        chordsCount = f.numerator() * (32 / f.denominator());
        m_score32View->setScore(
            createScore(chordsCount, Ms::TDuration::DurationType::V_32ND, &m_chords32));
    }
}

void BeamGroupsModel::load()
{
    setTimeSignature(Ms::Fraction(4, 4), Ms::Groups(), "", "");
}

void BeamGroupsModel::setScore8View(QObject *score8View)
{
    m_score8View = static_cast<commonscene::ExamplePaintView *>(score8View);
}
void BeamGroupsModel::setScore16View(QObject *score16View)
{
    m_score16View = static_cast<commonscene::ExamplePaintView *>(score16View);
}
void BeamGroupsModel::setScore32View(QObject *score32View)
{
    m_score32View = static_cast<commonscene::ExamplePaintView *>(score32View);
}