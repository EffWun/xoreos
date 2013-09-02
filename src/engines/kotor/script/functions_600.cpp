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

/** @file engines/kotor/script/functions_600.cpp
 *  kotor script functions, 600-699.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/talkman.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/object.h"
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

void ScriptFunctions::registerFunctions600(const Defaults &d) {
	FunctionMan.registerFunction("GetLocalBoolean", 679,
			boost::bind(&ScriptFunctions::getLocalBoolean, this, _1),
			createSignature(3, kTypeInt, kTypeObject, kTypeString));
}

// 679. GetLocalBoolean
// This gets a boolean flag on an object
// currently the index is a range between 20 and 63
void ScriptFunctions::getLocalBoolean(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Aurora::NWScript::Object *object = params[0].getObject();
	if (object) {
		ctx.getReturn() = object->getVariable(params[1].getInt(), kTypeInt).getInt();
    }
}

} // End of namespace KotOR

} // End of namespace Engines
