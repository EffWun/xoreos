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

/** @file engines/kotor/script/functions_200.cpp
 *  kotor script functions, 200-299.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/talkman.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"
#include "aurora/nwscript/ncsfile.h"

#include "engines/aurora/tokenman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/module.h"
#include "engines/kotor/area.h"
#include "engines/kotor/object.h"
#include "engines/kotor/creature.h"
#include "engines/kotor/location.h"

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

void ScriptFunctions::registerFunctions200(const Defaults &d) {
	FunctionMan.registerFunction("GetObjectByTag", 200,
			boost::bind(&ScriptFunctions::getObjectByTag, this, _1),
			createSignature(3, kTypeObject, kTypeString, kTypeInt),
			createDefaults(1, d.int0));
	FunctionMan.registerFunction("ApplyEffectToObject", 220,
			boost::bind(&ScriptFunctions::applyEffectToObject, this, _1),
			createSignature(5, kTypeVoid, kTypeInt, kTypeEngineType, kTypeObject, kTypeFloat),
			createDefaults(1, d.float0_0));
}

void ScriptFunctions::getObjectByTag(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = (Aurora::NWScript::Object *) 0;
	if (!_module) {
		throw Common::Exception("No module");
    }

	const Common::UString &tag = ctx.getParams()[0].getString();
	if (tag.empty())
		return;

	int nth = ctx.getParams()[1].getInt();

	if (!_module->findObjectInit(_objSearchContext, tag))
		return;

	do {
		_module->findNextObject(_objSearchContext);
    } while (nth-- > 0);

	ctx.getReturn() = _objSearchContext.getObject();
}

// 220: Apply eEffect to oTarget.
//void ApplyEffectToObject(int nDurationType, effect eEffect, object oTarget, float fDuration = 0.0f);
void ScriptFunctions::applyEffectToObject(Aurora::NWScript::FunctionContext &ctx) {
	warning("TODO: ApplyEffectToObject");
}
// 200: Get the nNth object with the specified tag.
// - sTag
// - nNth: the nth object with this tag may be requested
// * Returns OBJECT_INVALID if the object cannot be found.
//object GetObjectByTag(string sTag, int nNth=0);

// 201: Adjust the alignment of oSubject.
// - oSubject
// - nAlignment:
//   -> ALIGNMENT_LIGHT_SIDE/ALIGNMENT_DARK_SIDE: oSubject's
//      alignment will be shifted in the direction specified
//   -> ALIGNMENT_NEUTRAL: nShift is applied to oSubject's dark side/light side
//      alignment value in the direction which is towards neutrality.
//     e.g. If oSubject has an alignment value of 80 (i.e. light side)
//          then if nShift is 15, the alignment value will become (80-15)=65
//     Furthermore, the shift will at most take the alignment value to 50 and
//     not beyond.
//     e.g. If oSubject has an alignment value of 40 then if nShift is 15,
//          the aligment value will become 50
// - nShift: this is the desired shift in alignment
// * No return value
// - bDontModifyNPCs - Defaults to 'FALSE', if you pass in 'TRUE' then you can adjust
//   the playercharacter's alignment without impacting the rest of the NPCs
//void AdjustAlignment(object oSubject, int nAlignment, int nShift, int bDontModifyNPCs = FALSE);

// 202: Do nothing for fSeconds seconds.
//void ActionWait(float fSeconds);

// 203: Set the transition bitmap of a player; this should only be called in area
// transition scripts. This action should be run by the person "clicking" the
// area transition via AssignCommand.
// - nPredefinedAreaTransition:
//   -> To use a predefined area transition bitmap, use one of AREA_TRANSITION_*
//   -> To use a custom, user-defined area transition bitmap, use
//      AREA_TRANSITION_USER_DEFINED and specify the filename in the second
//      parameter
// - sCustomAreaTransitionBMP: this is the filename of a custom, user-defined
//   area transition bitmap
//void SetAreaTransitionBMP(int nPredefinedAreaTransition, string sCustomAreaTransitionBMP="");

// AMF: APRIL 28, 2003 - I HAVE CHANGED THIS FUNCTION AS PER DAN'S REQUEST
// 204: Starts a conversation with oObjectToConverseWith - this will cause their
// OnDialog event to fire.
// - oObjectToConverseWith
// - sDialogResRef: If this is blank, the creature's own dialogue file will be used
// - bPrivateConversation: If this is blank, the default is FALSE.
// - nConversationType - If this is blank the default will be Cinematic, ie. a normal conversation type
//                                  other choices inclue: CONVERSATION_TYPE_COMPUTER
//   UPDATE:  nConversationType actually has no meaning anymore.  This has been replaced by a flag in the dialog editor.  However
//                for backwards compatability it has been left here.  So when using this command place CONVERSATION_TYPE_CINEMATIC in here. - DJF
// - bIgnoreStartRange - If this is blank the default will be FALSE, ie. Start conversation ranges are in effect
//                                                                      Setting this to TRUE will cause creatures to start a conversation without requiring to close
//                                                                      the distance between the two object in dialog.
// - sNameObjectToIgnore1-6 - Normally objects in the animation list of the dialog editor have to be available for animations on that node to work
//                                        these 6 strings are to indicate 6 objects that dont need to be available for things to proceed.  The string should be EXACTLY
//                                        the same as the string that it represents in the dialog editor.
// - nBarkX and nBarkY - These override the left, top corner position for the bark string if the conversation starting is a bark string.
//                       They only happen on a conversation by conversation basis and don't stay in effect in subsequent conversations.
//void ActionStartConversation(object oObjectToConverse, string sDialogResRef = "", int bPrivateConversation = FALSE, int nConversationType = CONVERSATION_TYPE_CINEMATIC, int bIgnoreStartRange = FALSE, string sNameObjectToIgnore1 = "", string sNameObjectToIgnore2 = "", string sNameObjectToIgnore3 = "", string sNameObjectToIgnore4 = "", string sNameObjectToIgnore5 = "", string sNameObjectToIgnore6 = "", int bUseLeader = FALSE, int nBarkX = -1, int nBarkY = -1, int bDontClearAllActions = 0);

// 205: Pause the current conversation.
//void ActionPauseConversation();

// 206: Resume a conversation after it has been paused.
//void ActionResumeConversation();

// 207: Create a Beam effect.
// - nBeamVisualEffect: VFX_BEAM_*
// - oEffector: the beam is emitted from this creature
// - nBodyPart: BODY_NODE_*
// - bMissEffect: If this is TRUE, the beam will fire to a random vector near or
//   past the target
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nBeamVisualEffect is
//   not valid.
//effect EffectBeam(int nBeamVisualEffect, object oEffector, int nBodyPart, int bMissEffect=FALSE);

// 208: Get an integer between 0 and 100 (inclusive) that represents how oSource
// feels about oTarget.
// -> 0-10 means oSource is hostile to oTarget
// -> 11-89 means oSource is neutral to oTarget
// -> 90-100 means oSource is friendly to oTarget
// * Returns -1 if oSource or oTarget does not identify a valid object
//int GetReputation(object oSource, object oTarget);

// 209: Adjust how oSourceFactionMember's faction feels about oTarget by the
// specified amount.
// Note: This adjusts Faction Reputation, how the entire faction that
// oSourceFactionMember is in, feels about oTarget.
// * No return value
//void AdjustReputation(object oTarget, object oSourceFactionMember, int nAdjustment);

// 210: Gets the actual file name of the current module
//string GetModuleFileName();

// 211: Get the creature that is going to attack oTarget.
// Note: This value is cleared out at the end of every combat round and should
// not be used in any case except when getting a "going to be attacked" shout
// from the master creature (and this creature is a henchman)
// * Returns OBJECT_INVALID if oTarget is not a valid creature.
//object GetGoingToBeAttackedBy(object oTarget);

// 212: Create a Force Resistance Increase effect.
// - nValue: size of Force Resistance increase
//effect EffectForceResistanceIncrease(int nValue);

// 213: Get the location of oObject.
//location GetLocation(object oObject);

// 214: The subject will jump to lLocation instantly (even between areas).
// If lLocation is invalid, nothing will happen.
//void ActionJumpToLocation(location lLocation);

// 215: Create a location.
//location Location(vector vPosition, float fOrientation);

// 216: Apply eEffect at lLocation.
//void ApplyEffectAtLocation(int nDurationType, effect eEffect, location lLocation, float fDuration=0.0f);

// 217: * Returns TRUE if oCreature is a Player Controlled character.
//int GetIsPC(object oCreature);

// 218: Convert fFeet into a number of meters.
//float FeetToMeters(float fFeet);

// 219: Convert fYards into a number of meters.
//float YardsToMeters(float fYards);

// 220: Apply eEffect to oTarget.
//void ApplyEffectToObject(int nDurationType, effect eEffect, object oTarget, float fDuration=0.0f);

// 221: The caller will immediately speak sStringToSpeak (this is different from
// ActionSpeakString)
// - sStringToSpeak
// - nTalkVolume: TALKVOLUME_*
//void SpeakString(string sStringToSpeak, int nTalkVolume=TALKVOLUME_TALK);

// 222: Get the location of the caller's last spell target.
//location GetSpellTargetLocation();

// 223: Get the position vector from lLocation.
//vector GetPositionFromLocation(location lLocation);

// 224: the effect of body fule.. convers HP -> FP i think
//effect EffectBodyFuel( );

// 225: Get the orientation value from lLocation.
//float GetFacingFromLocation(location lLocation);

// 226: Get the creature nearest to lLocation, subject to all the criteria specified.
// - nFirstCriteriaType: CREATURE_TYPE_*
// - nFirstCriteriaValue:
//   -> CLASS_TYPE_* if nFirstCriteriaType was CREATURE_TYPE_CLASS
//   -> SPELL_* if nFirstCriteriaType was CREATURE_TYPE_DOES_NOT_HAVE_SPELL_EFFECT
//      or CREATURE_TYPE_HAS_SPELL_EFFECT
//   -> TRUE or FALSE if nFirstCriteriaType was CREATURE_TYPE_IS_ALIVE
//   -> PERCEPTION_* if nFirstCriteriaType was CREATURE_TYPE_PERCEPTION
//   -> PLAYER_CHAR_IS_PC or PLAYER_CHAR_NOT_PC if nFirstCriteriaType was
//      CREATURE_TYPE_PLAYER_CHAR
//   -> RACIAL_TYPE_* if nFirstCriteriaType was CREATURE_TYPE_RACIAL_TYPE
//   -> REPUTATION_TYPE_* if nFirstCriteriaType was CREATURE_TYPE_REPUTATION
//   For example, to get the nearest PC, use
//   (CREATURE_TYPE_PLAYER_CHAR, PLAYER_CHAR_IS_PC)
// - lLocation: We're trying to find the creature of the specified type that is
//   nearest to lLocation
// - nNth: We don't have to find the first nearest: we can find the Nth nearest....
// - nSecondCriteriaType: This is used in the same way as nFirstCriteriaType to
//   further specify the type of creature that we are looking for.
// - nSecondCriteriaValue: This is used in the same way as nFirstCriteriaValue
//   to further specify the type of creature that we are looking for.
// - nThirdCriteriaType: This is used in the same way as nFirstCriteriaType to
//   further specify the type of creature that we are looking for.
// - nThirdCriteriaValue: This is used in the same way as nFirstCriteriaValue to
//   further specify the type of creature that we are looking for.
// * Return value on error: OBJECT_INVALID
//object GetNearestCreatureToLocation(int nFirstCriteriaType, int nFirstCriteriaValue,  location lLocation, int nNth=1, int nSecondCriteriaType=-1, int nSecondCriteriaValue=-1, int nThirdCriteriaType=-1,  int nThirdCriteriaValue=-1 );

// 227: Get the Nth object nearest to oTarget that is of the specified type.
// - nObjectType: OBJECT_TYPE_*
// - oTarget
// - nNth
// * Return value on error: OBJECT_INVALID
//object GetNearestObject(int nObjectType=OBJECT_TYPE_ALL, object oTarget=OBJECT_SELF, int nNth=1);

// 228: Get the nNth object nearest to lLocation that is of the specified type.
// - nObjectType: OBJECT_TYPE_*
// - lLocation
// - nNth
// * Return value on error: OBJECT_INVALID
//object GetNearestObjectToLocation(int nObjectType, location lLocation, int nNth=1);

// 229: Get the nth Object nearest to oTarget that has sTag as its tag.
// * Return value on error: OBJECT_INVALID
//object GetNearestObjectByTag(string sTag, object oTarget=OBJECT_SELF, int nNth=1);

// 230: Convert nInteger into a floating point number.
//float IntToFloat(int nInteger);

// 231: Convert fFloat into the nearest integer.
//int FloatToInt(float fFloat);

// 232: Convert sNumber into an integer.
//int StringToInt(string sNumber);

// 233: Convert sNumber into a floating point number.
//float StringToFloat(string sNumber);

// 234: Cast spell nSpell at lTargetLocation.
// - nSpell: SPELL_*
// - lTargetLocation
// - nMetaMagic: METAMAGIC_*
// - bCheat: If this is TRUE, then the executor of the action doesn't have to be
//   able to cast the spell.
// - nProjectilePathType: PROJECTILE_PATH_TYPE_*
// - bInstantSpell: If this is TRUE, the spell is cast immediately; this allows
//   the end-user to simulate
//   a high-level magic user having lots of advance warning of impending trouble.
//void   ActionCastSpellAtLocation(int nSpell, location lTargetLocation, int nMetaMagic=0, int bCheat=FALSE, int nProjectilePathType=PROJECTILE_PATH_TYPE_DEFAULT, int bInstantSpell=FALSE);

// 235: * Returns TRUE if oSource considers oTarget as an enemy.
//int GetIsEnemy(object oTarget, object oSource=OBJECT_SELF);

// 236: * Returns TRUE if oSource considers oTarget as a friend.
//int GetIsFriend(object oTarget, object oSource=OBJECT_SELF);

// 237: * Returns TRUE if oSource considers oTarget as neutral.
//int GetIsNeutral(object oTarget, object oSource=OBJECT_SELF);

// 238: Get the PC that is involved in the conversation.
// * Returns OBJECT_INVALID on error.
//object GetPCSpeaker();

// 239: Get a string from the talk table using nStrRef.
//string GetStringByStrRef(int nStrRef);

// 240: Causes the creature to speak a translated string.
// - nStrRef: Reference of the string in the talk table
// - nTalkVolume: TALKVOLUME_*
//void ActionSpeakStringByStrRef(int nStrRef, int nTalkVolume=TALKVOLUME_TALK);

// 241: Destroy oObject (irrevocably).
// This will not work on modules and areas.
// The bNoFade and fDelayUntilFade are for creatures and placeables only
//void DestroyObject(object oDestroy, float fDelay=0.0f, int bNoFade = FALSE, float fDelayUntilFade = 0.0f, int nHideFeedback = 0);

// 242: Get the module.
// * Return value on error: OBJECT_INVALID
//object GetModule();

// 243: Create an object of the specified type at lLocation.
// - nObjectType: OBJECT_TYPE_ITEM, OBJECT_TYPE_CREATURE, OBJECT_TYPE_PLACEABLE,
//   OBJECT_TYPE_STORE
// - sTemplate
// - lLocation
// - bUseAppearAnimation
// Waypoints can now also be created using the CreateObject function.
// nObjectType is: OBJECT_TYPE_WAYPOINT
// sTemplate will be the tag of the waypoint
// lLocation is where the waypoint will be placed
// bUseAppearAnimation is ignored
//object CreateObject(int nObjectType, string sTemplate, location lLocation, int bUseAppearAnimation=FALSE);

// 244: Create an event which triggers the "SpellCastAt" script
//event EventSpellCastAt(object oCaster, int nSpell, int bHarmful=TRUE);

// 245: This is for use in a "Spell Cast" script, it gets who cast the spell.
// The spell could have been cast by a creature, placeable or door.
// * Returns OBJECT_INVALID if the caller is not a creature, placeable or door.
//object GetLastSpellCaster();

// 246: This is for use in a "Spell Cast" script, it gets the ID of the spell that
// was cast.
//int GetLastSpell();

// 247: This is for use in a user-defined script, it gets the event number.
//int GetUserDefinedEventNumber();

// 248: This is for use in a Spell script, it gets the ID of the spell that is being
// cast (SPELL_*).
//int GetSpellId();

// 249: Generate a random name.
//string RandomName();

// 250: Create a Poison effect.
// - nPoisonType: POISON_*
//effect EffectPoison(int nPoisonType);

// 251: Returns whether this script is being run
//      while a load game is in progress
//int GetLoadFromSaveGame();

// 252: Assured Deflection
// This effect ensures that all projectiles shot at a jedi will be deflected
// without doing an opposed roll.  It takes an optional parameter to say whether
// the deflected projectile will return to the attacker and cause damage
//effect EffectAssuredDeflection(int nReturn = 0);

// 253: Get the name of oObject.
//string GetName(object oObject);

// 254: Use this in a conversation script to get the person with whom you are conversing.
// * Returns OBJECT_INVALID if the caller is not a valid creature.
//object GetLastSpeaker();

// 255: Use this in an OnDialog script to start up the dialog tree.
// - sResRef: if this is not specified, the default dialog file will be used
// - oObjectToDialog: if this is not specified the person that triggered the
//   event will be used
//int BeginConversation(string sResRef="", object oObjectToDialog=OBJECT_INVALID);

// 256: Use this in an OnPerception script to get the object that was perceived.
// * Returns OBJECT_INVALID if the caller is not a valid creature.
//object GetLastPerceived();

// 257: Use this in an OnPerception script to determine whether the object that was
// perceived was heard.
//int GetLastPerceptionHeard();

// 258: Use this in an OnPerception script to determine whether the object that was
// perceived has become inaudible.
//int GetLastPerceptionInaudible();

// 259: Use this in an OnPerception script to determine whether the object that was
// perceived was seen.
//int GetLastPerceptionSeen();

// 260: Use this in an OnClosed script to get the object that closed the door or placeable.
// * Returns OBJECT_INVALID if the caller is not a valid door or placeable.
//object GetLastClosedBy();

// 261: Use this in an OnPerception script to determine whether the object that was
// perceived has vanished.
//int GetLastPerceptionVanished();

// 262: Get the first object within oPersistentObject.
// - oPersistentObject
// - nResidentObjectType: OBJECT_TYPE_*
// - nPersistentZone: PERSISTENT_ZONE_ACTIVE. [This could also take the value
//   PERSISTENT_ZONE_FOLLOW, but this is no longer used.]
// * Returns OBJECT_INVALID if no object is found.
//object GetFirstInPersistentObject(object oPersistentObject=OBJECT_SELF, int nResidentObjectType=OBJECT_TYPE_CREATURE, int nPersistentZone=PERSISTENT_ZONE_ACTIVE);

// 263: Get the next object within oPersistentObject.
// - oPersistentObject
// - nResidentObjectType: OBJECT_TYPE_*
// - nPersistentZone: PERSISTENT_ZONE_ACTIVE. [This could also take the value
//   PERSISTENT_ZONE_FOLLOW, but this is no longer used.]
// * Returns OBJECT_INVALID if no object is found.
//object GetNextInPersistentObject(object oPersistentObject=OBJECT_SELF, int nResidentObjectType=OBJECT_TYPE_CREATURE, int nPersistentZone=PERSISTENT_ZONE_ACTIVE);

// 264: This returns the creator of oAreaOfEffectObject.
// * Returns OBJECT_INVALID if oAreaOfEffectObject is not a valid Area of Effect object.
//object GetAreaOfEffectCreator(object oAreaOfEffectObject=OBJECT_SELF);

// 265: Brings up the level up GUI for the player.  The GUI will only show up
//      if the player has gained enough experience points to level up.
// * Returns TRUE if the GUI was successfully brought up; FALSE if not.
//int ShowLevelUpGUI();

// 266: Flag the specified item as being non-equippable or not.  Set bNonEquippable
//      to TRUE to prevent this item from being equipped, and FALSE to allow
//      the normal equipping checks to determine if the item can be equipped.
// NOTE: This will do nothing if the object passed in is not an item.  Items that
//       are already equipped when this is called will not automatically be
//       unequipped.  These items will just be prevented from being re-equipped
//       should they be unequipped.
//void SetItemNonEquippable( object oItem, int bNonEquippable );

// 267: GetButtonMashCheck
// This function returns whether the button mash check, used for the combat tutorial, is on
//int GetButtonMashCheck();

// 268: SetButtonMashCheck
// This function sets the button mash check variable, and is used for turning the check on and off
//void SetButtonMashCheck(int nCheck);

// 269: EffectForcePushTargeted
// This effect is exactly the same as force push, except it takes a location parameter that specifies
// where the location of the force push is to be done from.  All orientations are also based on this location.
// AMF:  The new ignore test direct line variable should be used with extreme caution
// It overrides geometry checks for force pushes, so that the object that the effect is applied to
// is guaranteed to move that far, ignoring collisions.  It is best used for cutscenes.
//effect EffectForcePushTargeted(location lCentre, int nIgnoreTestDirectLine = 0);

// 270: Create a Haste effect.
//effect EffectHaste();

// 271: Give oItem to oGiveTo (instant; for similar Action use ActionGiveItem)
// If oItem is not a valid item, or oGiveTo is not a valid object, nothing will
// happen.
//void GiveItem(object oItem, object oGiveTo);

// 272: Convert oObject into a hexadecimal string.
//string ObjectToString(object oObject);

// 273: Create an Immunity effect.
// - nImmunityType: IMMUNITY_TYPE_*
//effect EffectImmunity(int nImmunityType);

// 274: - oCreature
// - nImmunityType: IMMUNITY_TYPE_*
// - oVersus: if this is specified, then we also check for the race and
//   alignment of oVersus
// * Returns TRUE if oCreature has immunity of type nImmunity versus oVersus.
//int GetIsImmune(object oCreature, int nImmunityType, object oVersus=OBJECT_INVALID);

// 275: Creates a Damage Immunity Increase effect.
// - nDamageType: DAMAGE_TYPE_*
// - nPercentImmunity
//effect EffectDamageImmunityIncrease(int nDamageType, int nPercentImmunity);

// 276: Determine whether oEncounter is active.
//int  GetEncounterActive(object oEncounter=OBJECT_SELF);

// 277: Set oEncounter's active state to nNewValue.
// - nNewValue: TRUE/FALSE
// - oEncounter
//void SetEncounterActive(int nNewValue, object oEncounter=OBJECT_SELF);

// 278: Get the maximum number of times that oEncounter will spawn.
//int GetEncounterSpawnsMax(object oEncounter=OBJECT_SELF);

// 279: Set the maximum number of times that oEncounter can spawn
//void SetEncounterSpawnsMax(int nNewValue, object oEncounter=OBJECT_SELF);

// 280: Get the number of times that oEncounter has spawned so far
//int  GetEncounterSpawnsCurrent(object oEncounter=OBJECT_SELF);

// 281: Set the number of times that oEncounter has spawned so far
//void SetEncounterSpawnsCurrent(int nNewValue, object oEncounter=OBJECT_SELF);

// 282: Use this in an OnItemAcquired script to get the item that was acquired.
// * Returns OBJECT_INVALID if the module is not valid.
//object GetModuleItemAcquired();

// 283: Use this in an OnItemAcquired script to get the creatre that previously
// possessed the item.
// * Returns OBJECT_INVALID if the item was picked up from the ground.
//object GetModuleItemAcquiredFrom();

// 284: Set the value for a custom token.
//void SetCustomToken(int nCustomTokenNumber, string sTokenValue);

// 285: Determine whether oCreature has nFeat, and nFeat is useable.
// PLEASE NOTE!!! - This function will return FALSE if the target
// is not currently able to use the feat due to daily limits or
// other restrictions. Use GetFeatAcquired() if you just want to
// know if they've got it or not.
// - nFeat: FEAT_*
// - oCreature
//int GetHasFeat(int nFeat, object oCreature=OBJECT_SELF);

// 286: Determine whether oCreature has nSkill, and nSkill is useable.
// - nSkill: SKILL_*
// - oCreature
//int GetHasSkill(int nSkill, object oCreature=OBJECT_SELF);

// 287: Use nFeat on oTarget.
// - nFeat: FEAT_*
// - oTarget
//void ActionUseFeat(int nFeat, object oTarget);

// 288: Runs the action "UseSkill" on the current creature
// Use nSkill on oTarget.
// - nSkill: SKILL_*
// - oTarget
// - nSubSkill: SUBSKILL_*
// - oItemUsed: Item to use in conjunction with the skill
//void ActionUseSkill(int nSkill, object oTarget, int nSubSkill=0, object oItemUsed=OBJECT_INVALID );

// 289: Determine whether oSource sees oTarget.
//int GetObjectSeen(object oTarget, object oSource=OBJECT_SELF);

// 290: Determine whether oSource hears oTarget.
//int GetObjectHeard(object oTarget, object oSource=OBJECT_SELF);

// 291: Use this in an OnPlayerDeath module script to get the last player that died.
//object GetLastPlayerDied();

// 292: Use this in an OnItemLost script to get the item that was lost/dropped.
// * Returns OBJECT_INVALID if the module is not valid.
//object GetModuleItemLost();

// 293: Use this in an OnItemLost script to get the creature that lost the item.
// * Returns OBJECT_INVALID if the module is not valid.
//object GetModuleItemLostBy();

// 294: Do aActionToDo.
//void ActionDoCommand(action aActionToDo);

// 295: Conversation event.
//event EventConversation();

// 296: Set the difficulty level of oEncounter.
// - nEncounterDifficulty: ENCOUNTER_DIFFICULTY_*
// - oEncounter
//void SetEncounterDifficulty(int nEncounterDifficulty, object oEncounter=OBJECT_SELF);

// 297: Get the difficulty level of oEncounter.
//int GetEncounterDifficulty(object oEncounter=OBJECT_SELF);

// 298: Get the distance between lLocationA and lLocationB.
//float GetDistanceBetweenLocations(location lLocationA, location lLocationB);

// 299: Use this in spell scripts to get nDamage adjusted by oTarget's reflex and
// evasion saves.
// - nDamage
// - oTarget
// - nDC: Difficulty check
// - nSaveType: SAVING_THROW_TYPE_*
// - oSaveVersus
//int GetReflexAdjustedDamage(int nDamage, object oTarget, int nDC, int nSaveType=SAVING_THROW_TYPE_NONE, object oSaveVersus=OBJECT_SELF);

} // End of namespace KotOR

} // End of namespace Engines
