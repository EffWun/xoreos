/* eos - A reimplementation of BioWare's Aurora engine
 *
 * eos is the legal property of its developers, whose names can be
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
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/nwn/scriptfuncs.cpp
 *  NWN script functions.
 */

#include "boost/bind.hpp"

#include "common/util.h"
#include "common/error.h"

#include "engines/nwn/scriptfuncs.h"
#include "engines/nwn/object.h"
#include "engines/nwn/creature.h"
#include "engines/nwn/module.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

using Aurora::NWScript::kTypeVoid;
using Aurora::NWScript::kTypeInt;
using Aurora::NWScript::kTypeFloat;
using Aurora::NWScript::kTypeString;
using Aurora::NWScript::kTypeObject;
using Aurora::NWScript::createSignature;

namespace Engines {

namespace NWN {

ScriptFunctions::ScriptFunctions() {
	registerFunctions();
}

ScriptFunctions::~ScriptFunctions() {
	FunctionMan.clear();
}

void ScriptFunctions::setModule(Module *module) {
	_module = module;
}

Aurora::NWScript::Object *ScriptFunctions::getPC() {
	if (!_module)
		return 0;

	return (Aurora::NWScript::Object *) _module->getPC();
}

Object *ScriptFunctions::convertObject(Aurora::NWScript::Object *o) {
	Object *object = dynamic_cast<Object *>(o);
	if (!object || !object->loaded())
		return 0;

	return object;
}

Creature *ScriptFunctions::convertCreature(Aurora::NWScript::Object *o) {
	Creature *creature = dynamic_cast<Creature *>(o);
	if (!creature || !creature->loaded())
		return 0;

	return creature;
}

Creature *ScriptFunctions::convertPC(Aurora::NWScript::Object *o) {
	Creature *pc = dynamic_cast<Creature *>(o);
	if (!pc || !pc->loaded() || !pc->isPC())
		return 0;

	return pc;
}

void ScriptFunctions::registerFunctions() {
	Aurora::NWScript::Signature sig;

	FunctionMan.registerFunction("GetIsObjectValid", 42,
			boost::bind(&ScriptFunctions::getObjectIsValid, this, _1),
			createSignature(2, kTypeInt, kTypeObject));

	FunctionMan.registerFunction("GetLocalInt", 51,
			boost::bind(&ScriptFunctions::getLocalInt, this, _1),
			createSignature(3, kTypeInt, kTypeObject, kTypeString));
	FunctionMan.registerFunction("GetLocalFloat", 52,
			boost::bind(&ScriptFunctions::getLocalFloat, this, _1),
			createSignature(3, kTypeFloat, kTypeObject, kTypeString));
	FunctionMan.registerFunction("GetLocalString", 53,
			boost::bind(&ScriptFunctions::getLocalString, this, _1),
			createSignature(3, kTypeString, kTypeObject, kTypeString));
	FunctionMan.registerFunction("GetLocalObject", 54,
			boost::bind(&ScriptFunctions::getLocalObject, this, _1),
			createSignature(3, kTypeObject, kTypeObject, kTypeString));
	FunctionMan.registerFunction("SetLocalInt", 55,
			boost::bind(&ScriptFunctions::setLocalInt, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeInt));
	FunctionMan.registerFunction("SetLocalFloat", 56,
			boost::bind(&ScriptFunctions::setLocalFloat, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeFloat));
	FunctionMan.registerFunction("SetLocalString", 57,
			boost::bind(&ScriptFunctions::setLocalString, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeString));
	FunctionMan.registerFunction("SetLocalObject", 58,
			boost::bind(&ScriptFunctions::setLocalObject, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeObject));

	FunctionMan.registerFunction("IntToString", 92,
			boost::bind(&ScriptFunctions::intToString, this, _1),
			createSignature(2, kTypeString, kTypeInt));

	FunctionMan.registerFunction("GetPCSpeaker", 238,
			boost::bind(&ScriptFunctions::getPCSpeaker, this, _1),
			createSignature(1, kTypeObject));

	FunctionMan.registerFunction("BeginConversation", 255,
			boost::bind(&ScriptFunctions::beginConversation, this, _1),
			createSignature(3, kTypeVoid, kTypeString, kTypeObject));

	FunctionMan.registerFunction("SendMessageToPC", 374,
			boost::bind(&ScriptFunctions::sendMessageToPC, this, _1),
			createSignature(3, kTypeVoid, kTypeObject, kTypeString));

	FunctionMan.registerFunction("GetFirstPC", 548,
			boost::bind(&ScriptFunctions::getFirstPC, this, _1),
			createSignature(1, kTypeObject));
	FunctionMan.registerFunction("GetNextPC", 549,
			boost::bind(&ScriptFunctions::getNextPC, this, _1),
			createSignature(1, kTypeObject));

}

void ScriptFunctions::getObjectIsValid(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = convertObject(ctx.getParams()[0].getObject()) != 0;
}

void ScriptFunctions::getLocalInt(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		ctx.getReturn() = object->getVariable(params[1].getString(), kTypeInt).getInt();
}

void ScriptFunctions::getLocalFloat(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		ctx.getReturn() = object->getVariable(params[1].getString(), kTypeFloat).getFloat();
}

void ScriptFunctions::getLocalString(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		ctx.getReturn() = object->getVariable(params[1].getString(), kTypeString).getString();
}

void ScriptFunctions::getLocalObject(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		ctx.getReturn() = object->getVariable(params[1].getString(), kTypeObject).getObject();
}

void ScriptFunctions::setLocalInt(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		object->setVariable(params[1].getString(), params[2].getInt());
}

void ScriptFunctions::setLocalFloat(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		object->setVariable(params[1].getString(), params[2].getFloat());
}

void ScriptFunctions::setLocalString(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		object->setVariable(params[1].getString(), params[2].getString());
}

void ScriptFunctions::setLocalObject(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Object *object = convertObject(params[0].getObject());
	if (object)
		object->setVariable(params[1].getString(), params[2].getObject());
}

void ScriptFunctions::intToString(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = Common::UString::sprintf("%d", ctx.getParams()[0].getInt());
}

void ScriptFunctions::getFirstPC(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = (Aurora::NWScript::Object *) getPC();
}

void ScriptFunctions::getNextPC(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = (Aurora::NWScript::Object *) 0;
}

void ScriptFunctions::getPCSpeaker(Aurora::NWScript::FunctionContext &ctx) {
	Object *speaker = 0;
	Object *object  = convertObject(ctx.getCaller());
	if (object)
		speaker = object->getPCSpeaker();

	ctx.getReturn() = (Aurora::NWScript::Object *) speaker;
}

void ScriptFunctions::beginConversation(Aurora::NWScript::FunctionContext &ctx) {
	if (!_module)
		throw Common::Exception("ScriptFunctions::beginConversation(): Module needed");

	const Aurora::NWScript::Parameters &params = ctx.getParams();

	// Get the script object parameters
	Aurora::NWScript::Object *obj1 = ctx.getCaller();
	Aurora::NWScript::Object *obj2 = params[1].getObject();
	if (!obj2)
		obj2 = ctx.getTriggerer();
	if (!obj2)
		obj2 = getPC();

	// Try to convert them to an NWN Creature and Object
	Creature *pc     = convertPC(obj2);
	Object   *object = convertObject(obj1);

	// Try the other way round, if necessary
	if (!pc || !object) {
		pc     = convertPC(obj1);
		object = convertObject(obj2);
	}

	// Fail
	if (!pc || !object)
		throw Common::Exception("ScriptFunctions::beginConversation(): "
		                        "Need one PC and one object");

	if (object->getPCSpeaker())
		throw Common::Exception("ScriptFunctions::beginConversation(): "
		                        "Object already in conversation");

	Common::UString conversation = params[0].getString();
	if (conversation.empty())
		conversation = object->getConversation();

	object->setPCSpeaker(pc);
	_module->startConversation(conversation, *pc, *object);
	object->setPCSpeaker(0);
}

void ScriptFunctions::sendMessageToPC(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Creature *pc = convertPC(params[0].getObject());
	if (!pc)
		return;

	const Common::UString &msg = params[1].getString();

	warning("Send message to PC \"%s\": \"%s\"", pc->getName().c_str(), msg.c_str());
}

} // End of namespace NWN

} // End of namespace Engines