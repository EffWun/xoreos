/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/kotor/trigger.cpp
 *  A trigger.
 */

#include "common/util.h"

#include "aurora/gfffile.h"
#include "aurora/2dafile.h"
#include "aurora/2dareg.h"
#include "aurora/resman.h"

#include "aurora/nwscript/ncsfile.h"

#include "graphics/aurora/model.h"

#include "engines/aurora/util.h"

#include "engines/kotor/trigger.h"

#include <fstream>

namespace Engines {

namespace KotOR {

Trigger::Trigger() {
}

void Trigger::load(const Aurora::GFFStruct &trigger) {
	Common::UString temp = trigger.getString("TemplateResRef");

	std::unique_ptr<Aurora::GFFFile> utt;
	if (!temp.empty()) {
		try {
			utt.reset(new Aurora::GFFFile(temp, Aurora::kFileTypeUTT, MKTAG('U', 'T', 'T', ' ')));
		} catch (...) {
			utt.reset();
		}
	}

	Situated::load(trigger, utt ? &utt->getTopLevel() : 0);

	if (!utt)
		warning("Trigger \"%s\" has no blueprint", _tag.c_str());

	auto& x = utt->getTopLevel();
	auto fields = x.getFields();
	//std::ofstream ofs("c:\\tmp\\field_" + std::string(temp.c_str()) + ".txt");
	//for (auto i = fields.begin(); i != fields.end(); ++i) {
	//	//ofs << i->c_str() << ": " << x.getString(*i).c_str() << std::endl;
	//	ofs << i->c_str() << std::endl;
 //   }
	// ofs << "Tag:" << x.getString("Tag").c_str() << std::endl;
	// ofs << "TemplateResRef:" << x.getString("TemplateResRef").c_str() << std::endl;

	auto entryScriptPath = x.getString("ScriptOnEnter");
	auto exitScriptPath = x.getString("ScriptOnExit");

	_ncs.reset(new Aurora::NWScript::NCSFile(ResMan.getResource(entryScriptPath, Aurora::kFileTypeNCS)));
}

void Trigger::hide() {
	leave();

	Situated::hide();
}

void Trigger::loadObject(const Aurora::GFFStruct &gff) {
}

void Trigger::loadAppearance() {
	// const Aurora::TwoDAFile &twoda = TwoDAReg.get("triggers");

	// _modelName = twoda.getRow(_appearanceID).getString("ModelName");
}

void Trigger::enter() {
	highlight(true);
}

void Trigger::leave() {
	highlight(false);
}

void Trigger::highlight(bool enabled) {
	if (_model)
		_model->drawBound(enabled);
}

} // End of namespace KotOR

} // End of namespace Engines
