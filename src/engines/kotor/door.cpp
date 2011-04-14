/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010-2011 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file engines/kotor/door.cpp
 *  KotOR door.
 */

#include "common/util.h"
#include "common/error.h"

#include "aurora/gfffile.h"
#include "aurora/2dafile.h"
#include "aurora/2dareg.h"

#include "graphics/aurora/model.h"

#include "engines/aurora/util.h"

#include "engines/kotor/door.h"

namespace Engines {

namespace KotOR {

Door::Door() : _genericType(Aurora::kFieldIDInvalid) {
}

Door::~Door() {
}

void Door::load(const Aurora::GFFStruct &door) {
	Common::UString temp = door.getString("TemplateResRef");

	Aurora::GFFFile *utd = 0;
	if (!temp.empty()) {
		try {
			utd = loadGFF(temp, Aurora::kFileTypeUTD, MKID_BE('UTD '));
		} catch (...) {
		}
	}

	Situated::load(door, utd ? &utd->getTopLevel() : 0);

	if (!utd)
		warning("Door \"%s\" has no blueprint", _tag.c_str());

	delete utd;
}

void Door::loadObject(const Aurora::GFFStruct &gff) {
	_genericType = gff.getUint("GenericType", _genericType);
}

void Door::loadAppearance() {
	if (_appearanceID == 0) {
		if (_genericType == Aurora::kFieldIDInvalid)
			throw Common::Exception("Door \"%s\" has no appearance ID and no generic type",
			                        _tag.c_str());

		loadAppearance(TwoDAReg.get("genericdoors"), _genericType);
	} else
		loadAppearance(TwoDAReg.get("doortypes"), _appearanceID);
}

void Door::loadAppearance(const Aurora::TwoDAFile &twoda, uint32 id) {
	uint32 column = twoda.headerToColumn("ModelName");
	if (column == Aurora::kFieldIDInvalid)
		column = twoda.headerToColumn("Model");

	_modelName = twoda.getRow(id).getString(column);
}

void Door::hide() {
	leave();

	Situated::hide();
}

void Door::enter() {
	highlight(true);
}

void Door::leave() {
	highlight(false);
}

void Door::highlight(bool enabled) {
	if (_model)
		_model->drawBound(enabled);
}

} // End of namespace KotOR

} // End of namespace Engines