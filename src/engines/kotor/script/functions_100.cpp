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

/** @file engines/kotor/script/functions_100.cpp
 *  kotor script functions, 100-199.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/module.h"
#include "engines/kotor/object.h"
#include "engines/kotor/waypoint.h"
#include "engines/kotor/creature.h"

#include "engines/kotor/script/functions.h"

using Aurora::kObjectIDInvalid;

// NWScript
using Aurora::NWScript::kTypeVoid;
using Aurora::NWScript::kTypeInt;
using Aurora::NWScript::kTypeFloat;
using Aurora::NWScript::kTypeString;
using Aurora::NWScript::kTypeObject;
using Aurora::NWScript::kTypeEngineType;
using Aurora::NWScript::kTypeVector;
using Aurora::NWScript::kTypeScriptState;
using Aurora::NWScript::createSignature;
using Aurora::NWScript::createDefaults;

namespace Engines {

namespace KotOR {

void ScriptFunctions::registerFunctions100(const Defaults &d) {
	FunctionMan.registerFunction("GetTag", 168,
			boost::bind(&ScriptFunctions::getTag, this, _1),
			createSignature(2, kTypeString, kTypeObject));
	FunctionMan.registerFunction("EffectVisualEffect", 180,
			boost::bind(&ScriptFunctions::effectVisualEffect, this, _1),
			createSignature(3, kTypeEngineType, kTypeInt, kTypeInt),
			createDefaults(1, d.int0));
}

// 168: Get the Tag of oObject
// * Return value if oObject is not a valid object: ""
//string GetTag(object oObject);
void ScriptFunctions::getTag(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn().getString().clear();

	Aurora::NWScript::Object *object = ctx.getParams()[0].getObject();
	if (object)
		ctx.getReturn() = object->getTag();
}


// 180: * Create a Visual Effect that can be applied to an object.
// - nVisualEffectId
// - nMissEffect: if this is TRUE, a random vector near or past the target will
//   be generated, on which to play the effect
// effect EffectVisualEffect(int nVisualEffectId, int nMissEffect = FALSE);
void ScriptFunctions::effectVisualEffect(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = (Aurora::NWScript::EngineType *) 0;

	int  effectID = ctx.getParams()[0].getInt();
	bool miss     = ctx.getParams()[1].getInt() != 0;

	warning("TODO: EffectVisualEffect: %d, %d", effectID, miss);
}


} // End of namespace KotOR

} // End of namespace Engines
