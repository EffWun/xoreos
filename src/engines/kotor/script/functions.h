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

/** @file engines/kotor/script/functions.h
 *  Kotor script functions.
 */

#ifndef ENGINES_KOTOR_SCRIPT_FUNCTIONS_H
#define ENGINES_KOTOR_SCRIPT_FUNCTIONS_H

#include "aurora/nwscript/objectcontainer.h"

namespace Aurora {
	namespace NWScript {
		class Variable;
		class Object;
		class FunctionContext;
	}
}

namespace Engines {

namespace KotOR {

class Module;
class Area;

class Object;
class Waypoint;
class Situated;
class Door;
class Creature;

class Location;

class ObjectDistanceSort {
public:
	ObjectDistanceSort(const Object &target);

	bool operator()(Object *a, Object *b);

private:
	float xt, yt, zt;

	float getDistance(Object &a);
};

class ScriptFunctions {
public:
	ScriptFunctions();
	~ScriptFunctions();

	void setModule(Module *module = 0);

private:
	struct Defaults {
		Aurora::NWScript::Variable *int0;
		Aurora::NWScript::Variable *int1;
		Aurora::NWScript::Variable *int100;
		Aurora::NWScript::Variable *int18;
		Aurora::NWScript::Variable *int9;
		Aurora::NWScript::Variable *intm1;
		Aurora::NWScript::Variable *intMale;
		Aurora::NWScript::Variable *intObjectTypeAll;

		Aurora::NWScript::Variable *intACAll;
		Aurora::NWScript::Variable *intACDodge;
		Aurora::NWScript::Variable *intAlignAll;
		Aurora::NWScript::Variable *intAttackMisc;
		Aurora::NWScript::Variable *intCameraSnap;
		Aurora::NWScript::Variable *intClassInvalid;
		Aurora::NWScript::Variable *intCreatureLevel;
		Aurora::NWScript::Variable *intDamageMagical;
		Aurora::NWScript::Variable *intDamageNormal;
		Aurora::NWScript::Variable *intFactionHostile;
		Aurora::NWScript::Variable *intFirstGenericMale;
		Aurora::NWScript::Variable *intIPAmmo;
		Aurora::NWScript::Variable *intMetaMagicAny;
		Aurora::NWScript::Variable *intMissNormal;
		Aurora::NWScript::Variable *intObjectCreature;
		Aurora::NWScript::Variable *intPackageInvalid;
		Aurora::NWScript::Variable *intPersZoneActive;
		Aurora::NWScript::Variable *intProjPathDefault;
		Aurora::NWScript::Variable *intSaveAll;
		Aurora::NWScript::Variable *intSaveNone;
		Aurora::NWScript::Variable *intSpellsGeneral;
		Aurora::NWScript::Variable *intSpellsAll;
		Aurora::NWScript::Variable *intTalk;
		Aurora::NWScript::Variable *intVFXNone;

		Aurora::NWScript::Variable *float0_0;
		Aurora::NWScript::Variable *float1_0;
		Aurora::NWScript::Variable *float2_0;
		Aurora::NWScript::Variable *float30_0;
		Aurora::NWScript::Variable *float40_0;
		Aurora::NWScript::Variable *float180_0;
		Aurora::NWScript::Variable *floatm1_0;

		Aurora::NWScript::Variable *floatMedium;

		Aurora::NWScript::Variable *object0;
		Aurora::NWScript::Variable *stringEmpty;
		Aurora::NWScript::Variable *vector0;

		Defaults();
		~Defaults();
	};

	Module *_module;

	Aurora::NWScript::ObjectContainer::SearchContext _objSearchContext;


	void registerFunctions();
	void registerFunctions000(const Defaults &d);
	void registerFunctions100(const Defaults &d);
	void registerFunctions200(const Defaults &d);
	void registerFunctions300(const Defaults &d);
	void registerFunctions400(const Defaults &d);
	void registerFunctions500(const Defaults &d);
	void registerFunctions600(const Defaults &d);
	void registerFunctions700(const Defaults &d);
	void registerFunctions800(const Defaults &d);

	Common::UString floatToString(float f, int width = 18, int decimals = 9);
	int32 random(int min, int max, int32 n = 1);

	Aurora::NWScript::Object *getPC();

	Common::UString gTag(const Aurora::NWScript::Object *o);

	Module   *convertModule  (Aurora::NWScript::Object *o);
	Area     *convertArea    (Aurora::NWScript::Object *o);
	Object   *convertObject  (Aurora::NWScript::Object *o);
	Waypoint *convertWaypoint(Aurora::NWScript::Object *o);
	Situated *convertSituated(Aurora::NWScript::Object *o);
	Door     *convertDoor    (Aurora::NWScript::Object *o);
	Creature *convertCreature(Aurora::NWScript::Object *o);
	Creature *convertPC      (Aurora::NWScript::Object *o);

	Location *convertLocation(Aurora::NWScript::EngineType *e);

	void jumpTo(Object *object, Area *area, float x, float y, float z);

	void getEnteringObject(Aurora::NWScript::FunctionContext &ctx);
	void getObjectByTag(Aurora::NWScript::FunctionContext &ctx);
	void getLocalBoolean(Aurora::NWScript::FunctionContext &ctx);
	void getPartyLeader(Aurora::NWScript::FunctionContext &ctx);
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_SCRIPT_FUNCTIONS_H
