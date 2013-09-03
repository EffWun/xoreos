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

/** @file engines/kotor/script/functions_000.cpp
 *  kotor script functions, 000-099.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"
#include "common/maths.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/variable.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"
#include "aurora/nwscript/ncsfile.h"

#include "engines/kotor/types.h"
#include "engines/kotor/module.h"
#include "engines/kotor/object.h"
#include "engines/kotor/door.h"
#include "engines/kotor/creature.h"

#include "engines/kotor/script/functions.h"
#include "engines/kotor/script/function_template.h"


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

struct Random {
	typedef mpl::vector<int> args;
	typedef mpl::vector<void> defaults;
	typedef int return_type;

	int operator()(int nMaxInteger) const {
		return 0;
    }
};

struct FloatToString {
	typedef mpl::vector<float, int, int> args;
	typedef mpl::vector<void, mpl::int_<18>, mpl::int_<9>> defaults;
	typedef Common::UString return_type;

	Common::UString operator()(float,int,int) const {
		return "";
    }
};

void ScriptFunctions::registerFunctions000(const Defaults &d) {
	FunctionMan.registerFunction("Random", 1,
			run_function<Random>,
			createSignature(1, kTypeInt, kTypeInt));
	FunctionMan.registerFunction("FloatToString", 40,
			run_function<FloatToString>,
			createSignature(4, kTypeString, kTypeFloat, kTypeInt, kTypeInt),
			createDefaults(2, d.int18, d.int9));
}



// 7: Delay aActionToDelay by fSeconds.
// * No return value, but if an error occurs, the log file will contain
//   "DelayCommand failed.".
//void DelayCommand(float fSeconds, action aActionToDelay);
//void ScriptFunctions::delayCommand(Aurora::NWScript::FunctionContext &ctx) {
//	if (!_module)
//		return;
//
//	Common::UString script = ctx.getScriptName();
//	if (script.empty())
//		throw Common::Exception("ScriptFunctions::assignCommand(): Script needed");
//
//	uint32 delay = ctx.getParams()[0].getFloat() * 1000;
//
//	const Aurora::NWScript::ScriptState &state = ctx.getParams()[1].getScriptState();
//
//	_module->delayScript(script, state, ctx.getCaller(), ctx.getTriggerer(), delay);
//}


} // End of namespace KotOR

} // End of namespace Engines
