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

/** @file engines/kotor/script/functions_400.cpp
 *  kotor script functions, 400-499.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/ssffile.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"

#include "engines/kotor/area.h"
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

void ScriptFunctions::registerFunctions400(const Defaults &d) {
}

// 400: The creature will equip the range weapon in its possession that can do the
// most damage.
// If no valid range weapon can be found, it will equip the most damaging melee
// weapon.
// - oVersus: You can try to get the most damaging weapon against oVersus
//void ActionEquipMostDamagingRanged(object oVersus=OBJECT_INVALID);

// 401: Get the Armour Class of oItem.
// * Return 0 if the oItem is not a valid item, or if oItem has no armour value.
//int GetItemACValue(object oItem);

// 402:
// Effect that will play an animation and display a visual effect to indicate the
// target has resisted a force power.
//effect EffectForceResisted( object oSource );

// 403: Expose the entire map of oArea to oPlayer.
//void ExploreAreaForPlayer(object oArea, object oPlayer);

// 404: The creature will equip the armour in its possession that has the highest
// armour class.
//void ActionEquipMostEffectiveArmor();

// 405: * Returns TRUE if it is currently day.
//int GetIsDay();

// 406: * Returns TRUE if it is currently night.
//int GetIsNight();

// 407: * Returns TRUE if it is currently dawn.
//int GetIsDawn();

// 408: * Returns TRUE if it is currently dusk.
//int GetIsDusk();

// 409: * Returns TRUE if oCreature was spawned from an encounter.
//int GetIsEncounterCreature(object oCreature=OBJECT_SELF);

// 410: Use this in an OnPlayerDying module script to get the last player who is dying.
//object GetLastPlayerDying();

// 411: Get the starting location of the module.
//location GetStartingLocation();

// 412: Make oCreatureToChange join one of the standard factions.
// ** This will only work on an NPC **
// - nStandardFaction: STANDARD_FACTION_*
//void ChangeToStandardFaction(object oCreatureToChange, int nStandardFaction);

// 413: Play oSound.
//void SoundObjectPlay(object oSound);

// 414: Stop playing oSound.
//void SoundObjectStop(object oSound);

// 415: Set the volume of oSound.
// - oSound
// - nVolume: 0-127
//void SoundObjectSetVolume(object oSound, int nVolume);

// 416: Set the position of oSound.
//void SoundObjectSetPosition(object oSound, vector vPosition);

// 417: Immediately speak a conversation one-liner.
// - sDialogResRef
// - oTokenTarget: This must be specified if there are creature-specific tokens
//   in the string.
//void SpeakOneLinerConversation(string sDialogResRef="", object oTokenTarget=OBJECT_TYPE_INVALID);

// 418: Get the amount of gold possessed by oTarget.
//int GetGold(object oTarget=OBJECT_SELF);

// 419: Use this in an OnRespawnButtonPressed module script to get the object id of
// the player who last pressed the respawn button.
//object GetLastRespawnButtonPresser();

// 420:
// Effect that will display a visual effect on the specified object's hand to
// indicate a force power has fizzled out.
//effect EffectForceFizzle();

// 421: SetLightsaberPowered
// Allows a script to set the state of the lightsaber.  This will override any
// game determined lightsaber powerstates.
//void SetLightsaberPowered( object oCreature, int bOverride, int bPowered = TRUE, int bShowTransition = FALSE);

// 422: * Returns TRUE if the weapon equipped is capable of damaging oVersus.
//int GetIsWeaponEffective(object oVersus=OBJECT_INVALID, int bOffHand=FALSE);

// 423: Use this in a SpellCast script to determine whether the spell was considered
// harmful.
// * Returns TRUE if the last spell cast was harmful.
//int GetLastSpellHarmful();

// 424: Activate oItem.
//event EventActivateItem(object oItem, location lTarget, object oTarget=OBJECT_INVALID);

// 425: Play the background music for oArea.
//void MusicBackgroundPlay(object oArea);

// 426: Stop the background music for oArea.
//void MusicBackgroundStop(object oArea);

// 427: Set the delay for the background music for oArea.
// - oArea
// - nDelay: delay in milliseconds
//void MusicBackgroundSetDelay(object oArea, int nDelay);

// 428: Change the background day track for oArea to nTrack.
// - oArea
// - nTrack
//void MusicBackgroundChangeDay(object oArea, int nTrack, int nStreamingMusic = FALSE);

// 429: Change the background night track for oArea to nTrack.
// - oArea
// - nTrack
//void MusicBackgroundChangeNight(object oArea, int nTrack, int nStreamingMusic = FALSE);

// 430: Play the battle music for oArea.
//void MusicBattlePlay(object oArea);

// 431: Stop the battle music for oArea.
//void MusicBattleStop(object oArea);

// 432: Change the battle track for oArea.
// - oArea
// - nTrack
//void MusicBattleChange(object oArea, int nTrack);

// 433: Play the ambient sound for oArea.
//void AmbientSoundPlay(object oArea);

// 434: Stop the ambient sound for oArea.
//void AmbientSoundStop(object oArea);

// 435: Change the ambient day track for oArea to nTrack.
// - oArea
// - nTrack
//void AmbientSoundChangeDay(object oArea, int nTrack);

// 436: Change the ambient night track for oArea to nTrack.
// - oArea
// - nTrack
//void AmbientSoundChangeNight(object oArea, int nTrack);

// 437: Get the object that killed the caller.
//object GetLastKiller();

// 438: Use this in a spell script to get the item used to cast the spell.
//object GetSpellCastItem();

// 439: Use this in an OnItemActivated module script to get the item that was activated.
//object GetItemActivated();

// 440: Use this in an OnItemActivated module script to get the creature that
// activated the item.
//object GetItemActivator();

// 441: Use this in an OnItemActivated module script to get the location of the item's
// target.
//location GetItemActivatedTargetLocation();

// 442: Use this in an OnItemActivated module script to get the item's target.
//object GetItemActivatedTarget();

// 443: * Returns TRUE if oObject (which is a placeable or a door) is currently open.
//int GetIsOpen(object oObject);

// 444: Take nAmount of gold from oCreatureToTakeFrom.
// - nAmount
// - oCreatureToTakeFrom: If this is not a valid creature, nothing will happen.
// - bDestroy: If this is TRUE, the caller will not get the gold.  Instead, the
//   gold will be destroyed and will vanish from the game.
//void TakeGoldFromCreature(int nAmount, object oCreatureToTakeFrom, int bDestroy=FALSE);

// 445: Determine whether oObject is in conversation.
//int GetIsInConversation(object oObject);

// 446: Create an Ability Decrease effect.
// - nAbility: ABILITY_*
// - nModifyBy: This is the amount by which to decrement the ability
//effect EffectAbilityDecrease(int nAbility, int nModifyBy);

// 447: Create an Attack Decrease effect.
// - nPenalty
// - nModifierType: ATTACK_BONUS_*
//effect EffectAttackDecrease(int nPenalty, int nModifierType=ATTACK_BONUS_MISC);

// 448: Create a Damage Decrease effect.
// - nPenalty
// - nDamageType: DAMAGE_TYPE_*
//effect EffectDamageDecrease(int nPenalty, int nDamageType=DAMAGE_TYPE_UNIVERSAL);

// 449: Create a Damage Immunity Decrease effect.
// - nDamageType: DAMAGE_TYPE_*
// - nPercentImmunity
//effect EffectDamageImmunityDecrease(int nDamageType, int nPercentImmunity);

// 450: Create an AC Decrease effect.
// - nValue
// - nModifyType: AC_*
// - nDamageType: DAMAGE_TYPE_*
//   * Default value for nDamageType should only ever be used in this function prototype.
//effect EffectACDecrease(int nValue, int nModifyType=AC_DODGE_BONUS, int nDamageType=AC_VS_DAMAGE_TYPE_ALL);

// 451: Create a Movement Speed Decrease effect.
// - nPercentChange: This is expected to be a positive integer between 1 and 99 inclusive.
//   If a negative integer is supplied then a movement speed increase will result,
//   and if a number >= 100 is supplied then the effect is deleted.
//effect EffectMovementSpeedDecrease(int nPercentChange);

// 452: Create a Saving Throw Decrease effect.
// - nSave
// - nValue
// - nSaveType: SAVING_THROW_TYPE_*
//effect EffectSavingThrowDecrease(int nSave, int nValue, int nSaveType=SAVING_THROW_TYPE_ALL);

// 453: Create a Skill Decrease effect.
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nSkill is invalid.
//effect EffectSkillDecrease(int nSkill, int nValue);

// 454: Create a Force Resistance Decrease effect.
//effect EffectForceResistanceDecrease(int nValue);

// 455: Determine whether oTarget is a plot object.
//int GetPlotFlag(object oTarget=OBJECT_SELF);

// 456: Set oTarget's plot object status.
//void SetPlotFlag(object oTarget, int nPlotFlag);

// 457: Create an Invisibility effect.
// - nInvisibilityType: INVISIBILITY_TYPE_*
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nInvisibilityType
//   is invalid.
//effect EffectInvisibility(int nInvisibilityType);

// 458: Create a Concealment effect.
// - nPercentage: 1-100 inclusive
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nPercentage < 1 or
//   nPercentage > 100.
//effect EffectConcealment(int nPercentage);

// 459: Create a Force Shield that has parameters from the guven index into the forceshields.2da
//effect EffectForceShield(int nShield);

// 460: Create a Dispel Magic All effect.
//effect EffectDispelMagicAll(int nCasterLevel);

// 461: Cut immediately to placeable camera 'nCameraId' during dialog.  nCameraId must be
//      an existing Placeable Camera ID.  Function only works during Dialog.
//void SetDialogPlaceableCamera( int nCameraId );


// 462:
// Returns: TRUE if the player is in 'solo mode' (ie. the party is not supposed to follow the player).
//          FALSE otherwise.
//int GetSoloMode();

// 463: Create a Disguise effect.
// - * nDisguiseAppearance: DISGUISE_TYPE_*s
//effect EffectDisguise(int nDisguiseAppearance);

// 464:
// Returns the maximum amount of stealth xp available in the area.
//int GetMaxStealthXP();

// 465: Create a True Seeing effect.
//effect EffectTrueSeeing();

// 466: Create a See Invisible effect.
//effect EffectSeeInvisible();

// 467: Create a Time Stop effect.
//effect EffectTimeStop();

// 468:
// Set the maximum amount of stealth xp available in the area.
//void SetMaxStealthXP( int nMax );

// 469: Increase the blaster deflection rate, i think...
//effect EffectBlasterDeflectionIncrease(int nChange);

// 470:decrease the blaster deflection rate
//effect EffectBlasterDeflectionDecrease(int nChange);

// 471: Make the creature horified. BOO!
//effect EffectHorrified( );

// 472: Create a Spell Level Absorption effect.
// - nMaxSpellLevelAbsorbed: maximum spell level that will be absorbed by the
//   effect
// - nTotalSpellLevelsAbsorbed: maximum number of spell levels that will be
//   absorbed by the effect
// - nSpellSchool: SPELL_SCHOOL_*
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if:
//   nMaxSpellLevelAbsorbed is not between -1 and 9 inclusive, or nSpellSchool
//   is invalid.
//effect EffectSpellLevelAbsorption(int nMaxSpellLevelAbsorbed, int nTotalSpellLevelsAbsorbed=0, int nSpellSchool=0 );

// 473: Create a Dispel Magic Best effect.
//effect EffectDispelMagicBest(int nCasterLevel);

// 474:
// Returns the current amount of stealth xp available in the area.
//int GetCurrentStealthXP();

// 475: Get the number of stacked items that oItem comprises.
//int GetNumStackedItems(object oItem);

// 476: Use this on an NPC to cause all creatures within a 10-metre radius to stop
// what they are doing and sets the NPC's enemies within this range to be
// neutral towards the NPC. If this command is run on a PC or an object that is
// not a creature, nothing will happen.
//void SurrenderToEnemies();

// 477: Create a Miss Chance effect.
// - nPercentage: 1-100 inclusive
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nPercentage < 1 or
//   nPercentage > 100.
//effect EffectMissChance(int nPercentage);

// 478:
// Set the current amount of stealth xp available in the area.
//void SetCurrentStealthXP( int nCurrent );

// 479: Get the size (CREATURE_SIZE_*) of oCreature.
//int GetCreatureSize(object oCreature);

// 480:
// Award the stealth xp to the given oTarget.  This will only work on creatures.
//void AwardStealthXP( object oTarget );

// 481:
// Returns whether or not the stealth xp bonus is enabled (ie. whether or not
// AwardStealthXP() will actually award any available stealth xp).
//int GetStealthXPEnabled();

// 482:
// Sets whether or not the stealth xp bonus is enabled (ie. whether or not
// AwardStealthXP() will actually award any available stealth xp).
//void SetStealthXPEnabled( int bEnabled );

// 483: The action subject will unlock oTarget, which can be a door or a placeable
// object.
//void ActionUnlockObject(object oTarget);

// 484: The action subject will lock oTarget, which can be a door or a placeable
// object.
//void ActionLockObject(object oTarget);

// 485: Create a Modify Attacks effect to add attacks.
// - nAttacks: maximum is 5, even with the effect stacked
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nAttacks > 5.
//effect EffectModifyAttacks(int nAttacks);

// 486: Get the last trap detected by oTarget.
// * Return value on error: OBJECT_INVALID
//object GetLastTrapDetected(object oTarget=OBJECT_SELF);

// 487: Create a Damage Shield effect which does (nDamageAmount + nRandomAmount)
// damage to any melee attacker on a successful attack of damage type nDamageType.
// - nDamageAmount: an integer value
// - nRandomAmount: DAMAGE_BONUS_*
// - nDamageType: DAMAGE_TYPE_*
//effect EffectDamageShield(int nDamageAmount, int nRandomAmount, int nDamageType);

// 488: Get the trap nearest to oTarget.
// Note : "trap objects" are actually any trigger, placeable or door that is
// trapped in oTarget's area.
// - oTarget
// - nTrapDetected: if this is TRUE, the trap returned has to have been detected
//   by oTarget.
//object GetNearestTrapToObject(object oTarget=OBJECT_SELF, int nTrapDetected=TRUE);

// 489: the will get the last attmpted movment target
//object GetAttemptedMovementTarget();


// 490: this function returns the bloking creature for the k_def_CBTBlk01 script
//object GetBlockingCreature(object oTarget=OBJECT_SELF);

// 491: Get oTarget's base fortitude saving throw value (this will only work for
// creatures, doors, and placeables).
// * Returns 0 if oTarget is invalid.
//int GetFortitudeSavingThrow(object oTarget);

// 492: Get oTarget's base will saving throw value (this will only work for creatures,
// doors, and placeables).
// * Returns 0 if oTarget is invalid.
//int GetWillSavingThrow(object oTarget);

// 493: Get oTarget's base reflex saving throw value (this will only work for
// creatures, doors, and placeables).
// * Returns 0 if oTarget is invalid.
//int GetReflexSavingThrow(object oTarget);

// 494: Get oCreature's challenge rating.
// * Returns 0.0 if oCreature is invalid.
//float GetChallengeRating(object oCreature);

// 495: Returns the found enemy creature on a pathfind.
//object GetFoundEnemyCreature(object oTarget=OBJECT_SELF);

// 496: Get oCreature's movement rate.
// * Returns 0 if oCreature is invalid.
//int GetMovementRate(object oCreature);

// 497: GetSubRace of oCreature
// Returns SUBRACE_*
//int GetSubRace(object oCreature);

// 498:
// Returns the amount the stealth xp bonus gets decreased each time the player is detected.
//int GetStealthXPDecrement();

// 499:
// Sets the amount the stealth xp bonus gets decreased each time the player is detected.
//void SetStealthXPDecrement( int nDecrement );

} // End of namespace KotOR

} // End of namespace Engines
