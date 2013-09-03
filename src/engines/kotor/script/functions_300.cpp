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

/** @file engines/kotor/script/functions_300.cpp
 *  kotor script functions, 300-399.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/object.h"
#include "engines/kotor/situated.h"
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

void ScriptFunctions::registerFunctions300(const Defaults &d) {
	FunctionMan.registerFunction("SetIsDestroyable", 323,
			boost::bind(&ScriptFunctions::setIsDestroyable, this, _1),
			createSignature(4, kTypeVoid, kTypeInt, kTypeInt, kTypeInt),
			createDefaults(2, d.int1, d.int0));
}

// 323: Set the destroyable status of the caller.
// - bDestroyable: If this is FALSE, the caller does not fade out on death, but
//   sticks around as a corpse.
// - bRaiseable: If this is TRUE, the caller can be raised via resurrection.
// - bSelectableWhenDead: If this is TRUE, the caller is selectable after death.
// void SetIsDestroyable(int bDestroyable, int bRaiseable = TRUE, int bSelectableWhenDead = FALSE);
void ScriptFunctions::setIsDestroyable(Aurora::NWScript::FunctionContext &ctx) {
	warning("TODO: SetIsDestroyable");
}

} // End of namespace KotOR

} // End of namespace Engines
