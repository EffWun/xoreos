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
	FunctionMan.registerFunction("SetListening", 175,
			boost::bind(&ScriptFunctions::setListening, this, _1),
			createSignature(3, kTypeVoid, kTypeObject, kTypeInt));
	FunctionMan.registerFunction("SetListenPattern", 176,
			boost::bind(&ScriptFunctions::setListenPattern, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeInt),
			createDefaults(1, d.int0));
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

// 100: Get the total from rolling (nNumDice x d10 dice).
// - nNumDice: If this is less than 1, the value 1 will be used.
//int d10(int nNumDice=1);

// 101: Get the total from rolling (nNumDice x d12 dice).
// - nNumDice: If this is less than 1, the value 1 will be used.
//int d12(int nNumDice=1);

// 102: Get the total from rolling (nNumDice x d20 dice).
// - nNumDice: If this is less than 1, the value 1 will be used.
//int d20(int nNumDice=1);

// 103: Get the total from rolling (nNumDice x d100 dice).
// - nNumDice: If this is less than 1, the value 1 will be used.
//int d100(int nNumDice=1);

// 104: Get the magnitude of vVector; this can be used to determine the
// distance between two points.
// * Return value on error: 0.0f
//float VectorMagnitude(vector vVector);

// 105: Get the metamagic type (METAMAGIC_*) of the last spell cast by the caller
// * Return value if the caster is not a valid object: -1
//int GetMetaMagicFeat();

// 106: Get the object type (OBJECT_TYPE_*) of oTarget
// * Return value if oTarget is not a valid object: -1
//int GetObjectType(object oTarget);

// 107: Get the racial type (RACIAL_TYPE_*) of oCreature
// * Return value if oCreature is not a valid creature: RACIAL_TYPE_INVALID
//int GetRacialType(object oCreature);

// 108: Do a Fortitude Save check for the given DC
// - oCreature
// - nDC: Difficulty check
// - nSaveType: SAVING_THROW_TYPE_*
// - oSaveVersus
// Returns: 0 if the saving throw roll failed
// Returns: 1 if the saving throw roll succeeded
// Returns: 2 if the target was immune to the save type specified
//int FortitudeSave(object oCreature, int nDC, int nSaveType=SAVING_THROW_TYPE_NONE, object oSaveVersus=OBJECT_SELF);

// 109: Does a Reflex Save check for the given DC
// - oCreature
// - nDC: Difficulty check
// - nSaveType: SAVING_THROW_TYPE_*
// - oSaveVersus
// Returns: 0 if the saving throw roll failed
// Returns: 1 if the saving throw roll succeeded
// Returns: 2 if the target was immune to the save type specified
//int ReflexSave(object oCreature, int nDC, int nSaveType=SAVING_THROW_TYPE_NONE, object oSaveVersus=OBJECT_SELF);

// 110: Does a Will Save check for the given DC
// - oCreature
// - nDC: Difficulty check
// - nSaveType: SAVING_THROW_TYPE_*
// - oSaveVersus
// Returns: 0 if the saving throw roll failed
// Returns: 1 if the saving throw roll succeeded
// Returns: 2 if the target was immune to the save type specified
//int WillSave(object oCreature, int nDC, int nSaveType=SAVING_THROW_TYPE_NONE, object oSaveVersus=OBJECT_SELF);

// 111: Get the DC to save against for a spell (5 + spell level + CHA Mod + WIS Mod).
// This can be called by a creature or by an Area of Effect object.
//int GetSpellSaveDC();

// 112: Set the subtype of eEffect to Magical and return eEffect.
// (Effects default to magical if the subtype is not set)
//effect MagicalEffect(effect eEffect);

// 113: Set the subtype of eEffect to Supernatural and return eEffect.
// (Effects default to magical if the subtype is not set)
//effect SupernaturalEffect(effect eEffect);

// 114: Set the subtype of eEffect to Extraordinary and return eEffect.
// (Effects default to magical if the subtype is not set)
//effect ExtraordinaryEffect(effect eEffect);

// 115: Create an AC Increase effect
// - nValue: size of AC increase
// - nModifyType: AC_*_BONUS
// - nDamageType: DAMAGE_TYPE_*
//   * Default value for nDamageType should only ever be used in this function prototype.
//effect EffectACIncrease(int nValue, int nModifyType=AC_DODGE_BONUS, int nDamageType=AC_VS_DAMAGE_TYPE_ALL);

// 116: If oObject is a creature, this will return that creature's armour class
// If oObject is an item, door or placeable, this will return zero.
// - nForFutureUse: this parameter is not currently used
// * Return value if oObject is not a creature, item, door or placeable: -1
//int GetAC(object oObject, int nForFutureUse=0);

// 117: Create an AC Decrease effect
// - nSave: SAVING_THROW_* (not SAVING_THROW_TYPE_*)
// - nValue: size of AC decrease
// - nSaveType: SAVING_THROW_TYPE_*
//effect EffectSavingThrowIncrease(int nSave, int nValue, int nSaveType=SAVING_THROW_TYPE_ALL);

// 118: Create an Attack Increase effect
// - nBonus: size of attack bonus
// - nModifierType: ATTACK_BONUS_*
//effect EffectAttackIncrease(int nBonus, int nModifierType=ATTACK_BONUS_MISC);

// 119: Create a Damage Reduction effect
// - nAmount: amount of damage reduction
// - nDamagePower: DAMAGE_POWER_*
// - nLimit: How much damage the effect can absorb before disappearing.
//   Set to zero for infinite
//effect EffectDamageReduction(int nAmount, int nDamagePower, int nLimit=0);

// 120: Create a Damage Increase effect
// - nBonus: DAMAGE_BONUS_*
// - nDamageType: DAMAGE_TYPE_*
//effect EffectDamageIncrease(int nBonus, int nDamageType=DAMAGE_TYPE_UNIVERSAL);

// 121: Convert nRounds into a number of seconds
// A round is always 6.0 seconds
//float RoundsToSeconds(int nRounds);

// 122: Convert nHours into a number of seconds
// The result will depend on how many minutes there are per hour (game-time)
//float HoursToSeconds(int nHours);

// 123: Convert nTurns into a number of seconds
// A turn is always 60.0 seconds
//float TurnsToSeconds(int nTurns);

// 124. SoundObjectSetFixedVariance
// Sets the constant variance at which to play the sound object
// This variance is a multiplier of the original sound
//void SoundObjectSetFixedVariance( object oSound, float fFixedVariance );

// 125: Get an integer between 0 and 100 (inclusive) to represent oCreature's
// Good/Evil alignment
// (100=good, 0=evil)
// * Return value if oCreature is not a valid creature: -1
//int GetGoodEvilValue(object oCreature);

// 126: GetPartyMemberCount
// Returns a count of how many members are in the party including the player character
//int GetPartyMemberCount();

// 127: Return an ALIGNMENT_* constant to represent oCreature's good/evil alignment
// * Return value if oCreature is not a valid creature: -1
//int GetAlignmentGoodEvil(object oCreature);

// 128: Get the first object in nShape
// - nShape: SHAPE_*
// - fSize:
//   -> If nShape == SHAPE_SPHERE, this is the radius of the sphere
//   -> If nShape == SHAPE_SPELLCYLINDER, this is the radius of the cylinder
//   -> If nShape == SHAPE_CONE, this is the widest radius of the cone
//   -> If nShape == SHAPE_CUBE, this is half the length of one of the sides of
//      the cube
// - lTarget: This is the centre of the effect, usually GetSpellTargetPosition(),
//   or the end of a cylinder or cone.
// - bLineOfSight: This controls whether to do a line-of-sight check on the
//   object returned.
//   (This can be used to ensure that spell effects do not go through walls.)
// - nObjectFilter: This allows you to filter out undesired object types, using
//   bitwise "or".
//   For example, to return only creatures and doors, the value for this
//   parameter would be OBJECT_TYPE_CREATURE | OBJECT_TYPE_DOOR
// - vOrigin: This is only used for cylinders and cones, and specifies the
//   origin of the effect(normally the spell-caster's position).
// Return value on error: OBJECT_INVALID
//object GetFirstObjectInShape(int nShape, float fSize, location lTarget, int bLineOfSight=FALSE, int nObjectFilter=OBJECT_TYPE_CREATURE, vector vOrigin=[0.0,0.0,0.0]);

// 129: Get the next object in nShape
// - nShape: SHAPE_*
// - fSize:
//   -> If nShape == SHAPE_SPHERE, this is the radius of the sphere
//   -> If nShape == SHAPE_SPELLCYLINDER, this is the radius of the cylinder
//   -> If nShape == SHAPE_CONE, this is the widest radius of the cone
//   -> If nShape == SHAPE_CUBE, this is half the length of one of the sides of
//      the cube
// - lTarget: This is the centre of the effect, usually GetSpellTargetPosition(),
//   or the end of a cylinder or cone.
// - bLineOfSight: This controls whether to do a line-of-sight check on the
//   object returned. (This can be used to ensure that spell effects do not go
//   through walls.)
// - nObjectFilter: This allows you to filter out undesired object types, using
//   bitwise "or". For example, to return only creatures and doors, the value for
//   this parameter would be OBJECT_TYPE_CREATURE | OBJECT_TYPE_DOOR
// - vOrigin: This is only used for cylinders and cones, and specifies the origin
//   of the effect (normally the spell-caster's position).
// Return value on error: OBJECT_INVALID
//object GetNextObjectInShape(int nShape, float fSize, location lTarget, int bLineOfSight=FALSE, int nObjectFilter=OBJECT_TYPE_CREATURE, vector vOrigin=[0.0,0.0,0.0]);

// 130: Create an Entangle effect
// When applied, this effect will restrict the creature's movement and apply a
// (-2) to all attacks and a -4 to AC.
//effect EffectEntangle();

// 131: Cause oObject to run evToRun
//void SignalEvent(object oObject, event evToRun);

// 132: Create an event of the type nUserDefinedEventNumber
//event EventUserDefined(int nUserDefinedEventNumber);

// 133: Create a Death effect
// - nSpectacularDeath: if this is TRUE, the creature to which this effect is
//   applied will die in an extraordinary fashion
// - nDisplayFeedback
// - nNoFadeAway: Passing TRUE for this parameter will keep the bodies from fading after the creature
//                dies. Note that NO XP will be awarded if the creature is killed with this parameter.
//effect EffectDeath(int nSpectacularDeath=FALSE, int nDisplayFeedback=TRUE, int nNoFadeAway=FALSE);

// 134: Create a Knockdown effect
// This effect knocks creatures off their feet, they will sit until the effect
// is removed. This should be applied as a temporary effect with a 3 second
// duration minimum (1 second to fall, 1 second sitting, 1 second to get up).
//effect EffectKnockdown();

// 135: Give oItem to oGiveTo
// If oItem is not a valid item, or oGiveTo is not a valid object, nothing will
// happen.
//void ActionGiveItem(object oItem, object oGiveTo);

// 136: Take oItem from oTakeFrom
// If oItem is not a valid item, or oTakeFrom is not a valid object, nothing
// will happen.
//void ActionTakeItem(object oItem, object oTakeFrom);

// 137: Normalize vVector
//vector VectorNormalize(vector vVector);

// 138:
// Gets the stack size of an item.
//int GetItemStackSize( object oItem );

// 139: Get the ability score of type nAbility for a creature (otherwise 0)
// - oCreature: the creature whose ability score we wish to find out
// - nAbilityType: ABILITY_*
// Return value on error: 0
//int GetAbilityScore(object oCreature, int nAbilityType);

// 140: * Returns TRUE if oCreature is a dead NPC, dead PC or a dying PC.
//int GetIsDead(object oCreature);

// 141: Output vVector to the logfile.
// - vVector
// - bPrepend: if this is TRUE, the message will be prefixed with "PRINTVECTOR:"
//void PrintVector(vector vVector, int bPrepend);

// 142: Create a vector with the specified values for x, y and z
//vector Vector(float x=0.0f, float y=0.0f, float z=0.0f);

// 143: Cause the caller to face vTarget
//void SetFacingPoint(vector vTarget);

// 144: Convert fAngle to a vector
//vector AngleToVector(float fAngle);

// 145: Convert vVector to an angle
//float VectorToAngle(vector vVector);

// 146: The caller will perform a Melee Touch Attack on oTarget
// This is not an action, and it assumes the caller is already within range of
// oTarget
// * Returns 0 on a miss, 1 on a hit and 2 on a critical hit
//int TouchAttackMelee(object oTarget, int bDisplayFeedback=TRUE);

// 147: The caller will perform a Ranged Touch Attack on oTarget
// * Returns 0 on a miss, 1 on a hit and 2 on a critical hit
//int TouchAttackRanged(object oTarget, int bDisplayFeedback=TRUE);

// 148: Create a Paralyze effect
//effect EffectParalyze();

// 149: Create a Spell Immunity effect.
// There is a known bug with this function. There *must* be a parameter specified
// when this is called (even if the desired parameter is SPELL_ALL_SPELLS),
// otherwise an effect of type EFFECT_TYPE_INVALIDEFFECT will be returned.
// - nImmunityToSpell: SPELL_*
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nImmunityToSpell is
//   invalid.
//effect EffectSpellImmunity(int nImmunityToSpell=FORCE_POWER_ALL_FORCE_POWERS);

// 150:
// Set the stack size of an item.
// NOTE: The stack size will be clamped to between 1 and the max stack size (as
//       specified in the base item).
//void SetItemStackSize( object oItem, int nStackSize );

// 151: Get the distance in metres between oObjectA and oObjectB.
// * Return value if either object is invalid: 0.0f
//float GetDistanceBetween(object oObjectA, object oObjectB);

// 152: SetReturnStrref
// This function will turn on/off the display of the 'return to ebon hawk' option
// on the map screen and allow the string to be changed to an arbitrary string ref
// srReturnQueryStrRef is the string ref that will be displayed in the query pop
// up confirming that you wish to return to the specified location.
//void SetReturnStrref(int bShow, int srStringRef = 0, int srReturnQueryStrRef = 0);

// 153: EffectForceJump
// The effect required for force jumping
//effect EffectForceJump(object oTarget, int nAdvanced = 0);

// 154: Create a Sleep effect
//effect EffectSleep();

// 155: Get the object which is in oCreature's specified inventory slot
// - nInventorySlot: INVENTORY_SLOT_*
// - oCreature
// * Returns OBJECT_INVALID if oCreature is not a valid creature or there is no
//   item in nInventorySlot.
//object GetItemInSlot(int nInventorySlot, object oCreature=OBJECT_SELF);

// 156: This was previously EffectCharmed();
//effect EffectTemporaryForcePoints(int nTempForce);

// 157: Create a Confuse effect
//effect EffectConfused();

// 158: Create a Frighten effect
//effect EffectFrightened();

// 159: Choke the bugger...
//effect EffectChoke( );

// 160: Sets a global string with the specified identifier.  This is an EXTREMELY
//      restricted function - do not use without expilicit permission.
//      This means if you are not Preston.  Then go see him if you're even thinking
//      about using this.
//void SetGlobalString( string sIdentifier, string sValue );

// 161: Create a Stun effect
//effect EffectStunned();

// 162: Set whether oTarget's action stack can be modified
//void SetCommandable(int bCommandable, object oTarget=OBJECT_SELF);

// 163: Determine whether oTarget's action stack can be modified.
//int GetCommandable(object oTarget=OBJECT_SELF);

// 164: Create a Regenerate effect.
// - nAmount: amount of damage to be regenerated per time interval
// - fIntervalSeconds: length of interval in seconds
//effect EffectRegenerate(int nAmount, float fIntervalSeconds);

// 165: Create a Movement Speed Increase effect.
// - nNewSpeedPercent: This works in a dodgy way so please read this notes carefully.
//   If you supply an integer under 100, 100 gets added to it to produce the final speed.
//   e.g. if you supply 50, then the resulting speed is 150% of the original speed.
//   If you supply 100 or above, then this is used directly as the resulting speed.
//   e.g. if you specify 100, then the resulting speed is 100% of the original speed that is,
//        it is unchanged.
//        However if you specify 200, then the resulting speed is double the original speed.
//effect EffectMovementSpeedIncrease(int nNewSpeedPercent);

// 166: Get the number of hitdice for oCreature.
// * Return value if oCreature is not a valid creature: 0
//int GetHitDice(object oCreature);

// 167: The action subject will follow oFollow until a ClearAllActions() is called.
// - oFollow: this is the object to be followed
// - fFollowDistance: follow distance in metres
// * No return value
//void ActionForceFollowObject(object oFollow, float fFollowDistance=0.0f);

// 168: Get the Tag of oObject
// * Return value if oObject is not a valid object: ""
//string GetTag(object oObject);

// 169: Do a Force Resistance check between oSource and oTarget, returning TRUE if
// the force was resisted.
// * Return value if oSource or oTarget is an invalid object: FALSE
//int ResistForce(object oSource, object oTarget);

// 170: Get the effect type (EFFECT_TYPE_*) of eEffect.
// * Return value if eEffect is invalid: EFFECT_INVALIDEFFECT
//int GetEffectType(effect eEffect);

// 171: Create an Area Of Effect effect in the area of the creature it is applied to.
// If the scripts are not specified, default ones will be used.
//effect EffectAreaOfEffect(int nAreaEffectId, string sOnEnterScript="", string sHeartbeatScript="", string sOnExitScript="");

// 172: * Returns TRUE if the Faction Ids of the two objects are the same
//int GetFactionEqual(object oFirstObject, object oSecondObject=OBJECT_SELF);

// 173: Make oObjectToChangeFaction join the faction of oMemberOfFactionToJoin.
// NB. ** This will only work for two NPCs **
//void ChangeFaction(object oObjectToChangeFaction, object oMemberOfFactionToJoin);

// 174: * Returns TRUE if oObject is listening for something
//int GetIsListening(object oObject);

// 175: Set whether oObject is listening.
//void SetListening(object oObject, int bValue);
void ScriptFunctions::setListening(Aurora::NWScript::FunctionContext &ctx) {
	warning("TODO: SetListening");
}

// 176: Set the string for oObject to listen for.
// Note: this does not set oObject to be listening.
//void SetListenPattern(object oObject, string sPattern, int nNumber=0);
void ScriptFunctions::setListenPattern(Aurora::NWScript::FunctionContext &ctx) {
	warning("TODO: SetListenPattern");
}

// 177: * Returns TRUE if sStringToTest matches sPattern.
//int TestStringAgainstPattern(string sPattern, string sStringToTest);

// 178: Get the appropriate matched string (this should only be used in
// OnConversation scripts).
// * Returns the appropriate matched string, otherwise returns ""
//string GetMatchedSubstring(int nString);

// 179: Get the number of string parameters available.
// * Returns -1 if no string matched (this could be because of a dialogue event)
//int GetMatchedSubstringsCount();

// 180: * Create a Visual Effect that can be applied to an object.
// - nVisualEffectId
// - nMissEffect: if this is TRUE, a random vector near or past the target will
//   be generated, on which to play the effect
//effect EffectVisualEffect(int nVisualEffectId, int nMissEffect=FALSE);

// 181: Get the weakest member of oFactionMember's faction.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionWeakestMember(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 182: Get the strongest member of oFactionMember's faction.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionStrongestMember(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 183: Get the member of oFactionMember's faction that has taken the most hit points
// of damage.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionMostDamagedMember(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 184: Get the member of oFactionMember's faction that has taken the fewest hit
// points of damage.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionLeastDamagedMember(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 185: Get the amount of gold held by oFactionMember's faction.
// * Returns -1 if oFactionMember's faction is invalid.
//int GetFactionGold(object oFactionMember);

// 186: Get an integer between 0 and 100 (inclusive) that represents how
// oSourceFactionMember's faction feels about oTarget.
// * Return value on error: -1
//int GetFactionAverageReputation(object oSourceFactionMember, object oTarget);

// 187: Get an integer between 0 and 100 (inclusive) that represents the average
// good/evil alignment of oFactionMember's faction.
// * Return value on error: -1
//int GetFactionAverageGoodEvilAlignment(object oFactionMember);

// 188. SoundObjectGetFixedVariance
// Gets the constant variance at which to play the sound object
//float SoundObjectGetFixedVariance(object oSound);

// 189: Get the average level of the members of the faction.
// * Return value on error: -1
//int GetFactionAverageLevel(object oFactionMember);

// 190: Get the average XP of the members of the faction.
// * Return value on error: -1
//int GetFactionAverageXP(object oFactionMember);

// 191: Get the most frequent class in the faction - this can be compared with the
// constants CLASS_TYPE_*.
// * Return value on error: -1
//int GetFactionMostFrequentClass(object oFactionMember);

// 192: Get the object faction member with the lowest armour class.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionWorstAC(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 193: Get the object faction member with the highest armour class.
// * Returns OBJECT_INVALID if oFactionMember's faction is invalid.
//object GetFactionBestAC(object oFactionMember=OBJECT_SELF, int bMustBeVisible=TRUE);

// 194: Get a global string with the specified identifier
//      This is an EXTREMELY restricted function.  Use only with explicit permission.
//      This means if you are not Preston.  Then go see him if you're even thinking
//      about using this.
//string GetGlobalString( string sIdentifier );

// 195: In an onConversation script this gets the number of the string pattern
// matched (the one that triggered the script).
// * Returns -1 if no string matched
//int GetListenPatternNumber();

// 196: Jump to an object ID, or as near to it as possible.
//void ActionJumpToObject(object oToJumpTo, int bWalkStraightLineToPoint=TRUE);

// 197: Get the first waypoint with the specified tag.
// * Returns OBJECT_INVALID if the waypoint cannot be found.
//object GetWaypointByTag(string sWaypointTag);

// 198: Get the destination (a waypoint or a door) for a trigger or a door.
// * Returns OBJECT_INVALID if oTransition is not a valid trigger or door.
//object GetTransitionTarget(object oTransition);

// 199: Link the two supplied effects, returning eChildEffect as a child of
// eParentEffect.
// Note: When applying linked effects if the target is immune to all valid
// effects all other effects will be removed as well. This means that if you
// apply a visual effect and a silence effect (in a link) and the target is
// immune to the silence effect that the visual effect will get removed as well.
// Visual Effects are not considered "valid" effects for the purposes of
// determining if an effect will be removed or not and as such should never be
// packaged *only* with other visual effects in a link.
//effect EffectLinkEffects(effect eChildEffect, effect eParentEffect );

} // End of namespace KotOR

} // End of namespace Engines
