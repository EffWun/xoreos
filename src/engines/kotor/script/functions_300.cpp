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
// 300: Play nAnimation immediately.
// - nAnimation: ANIMATION_*
// - fSpeed
// - fSeconds: Duration of the animation (this is not used for Fire and
//   Forget animations) If a time of -1.0f is specified for a looping animation
//   it will loop until the next animation is applied.
//void PlayAnimation(int nAnimation, float fSpeed=1.0, float fSeconds=0.0);

// 301: Create a Spell Talent.
// - nSpell: SPELL_*
//talent TalentSpell(int nSpell);

// 302: Create a Feat Talent.
// - nFeat: FEAT_*
//talent TalentFeat(int nFeat);

// 303: Create a Skill Talent.
// - nSkill: SKILL_*
//talent TalentSkill(int nSkill);

// 304: Determine if oObject has effects originating from nSpell.
// - nSpell: SPELL_*
// - oObject
//int GetHasSpellEffect(int nSpell, object oObject=OBJECT_SELF);

// 305: Get the spell (SPELL_*) that applied eSpellEffect.
// * Returns -1 if eSpellEffect was applied outside a spell script.
//int GetEffectSpellId(effect eSpellEffect);

// 306: Determine whether oCreature has tTalent.
//int GetCreatureHasTalent(talent tTalent, object oCreature=OBJECT_SELF);

// 307: Get a random talent of oCreature, within nCategory.
// - nCategory: TALENT_CATEGORY_*
// - oCreature
// - nInclusion: types of talent to include
//talent GetCreatureTalentRandom(int nCategory, object oCreature=OBJECT_SELF, int nInclusion=0);

// 308: Get the best talent (i.e. closest to nCRMax without going over) of oCreature,
// within nCategory.
// - nCategory: TALENT_CATEGORY_*
// - nCRMax: Challenge Rating of the talent
// - oCreature
// - nInclusion: types of talent to include
// - nExcludeType: TALENT_TYPE_FEAT or TALENT_TYPE_FORCE, type of talent that we wish to ignore
// - nExcludeId: Talent ID of the talent we wish to ignore.
//   A value of TALENT_EXCLUDE_ALL_OF_TYPE for this parameter will mean that all talents of
//   type nExcludeType are ignored.
//talent GetCreatureTalentBest(int nCategory, int nCRMax, object oCreature=OBJECT_SELF, int nInclusion=0, int nExcludeType = -1, int nExcludeId = -1);

// 309: Use tChosenTalent on oTarget.
//void ActionUseTalentOnObject(talent tChosenTalent, object oTarget);

// 310: Use tChosenTalent at lTargetLocation.
//void ActionUseTalentAtLocation(talent tChosenTalent, location lTargetLocation);

// 311: Get the gold piece value of oItem.
// * Returns 0 if oItem is not a valid item.
//int GetGoldPieceValue(object oItem);

// 312: * Returns TRUE if oCreature is of a playable racial type.
//int GetIsPlayableRacialType(object oCreature);

// 313: Jump to lDestination.  The action is added to the TOP of the action queue.
//void JumpToLocation(location lDestination);

// 314: Create a Temporary Hitpoints effect.
// - nHitPoints: a positive integer
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nHitPoints < 0.
//effect EffectTemporaryHitpoints(int nHitPoints);

// 315: Get the number of ranks that oTarget has in nSkill.
// - nSkill: SKILL_*
// - oTarget
// * Returns -1 if oTarget doesn't have nSkill.
// * Returns 0 if nSkill is untrained.
//int GetSkillRank(int nSkill, object oTarget=OBJECT_SELF);

// 316: Get the attack target of oCreature.
// This only works when oCreature is in combat.
//object GetAttackTarget(object oCreature=OBJECT_SELF);

// 317: Get the attack type (SPECIAL_ATTACK_*) of oCreature's last attack.
// This only works when oCreature is in combat.
//int GetLastAttackType(object oCreature=OBJECT_SELF);

// 318: Get the attack mode (COMBAT_MODE_*) of oCreature's last attack.
// This only works when oCreature is in combat.
//int GetLastAttackMode(object oCreature=OBJECT_SELF);

// 319: Get the distance in metres between oObjectA and oObjectB in 2D.
// * Return value if either object is invalid: 0.0f
//float GetDistanceBetween2D(object oObjectA, object oObjectB);

// 320: * Returns TRUE if oCreature is in combat.
//RWT-OEI 09/30/04 - If you pass TRUE in as the second parameter then
//this function will only return true if the character is in REAL combat.
//If you don't know what that means, don't pass in TRUE.
//int GetIsInCombat(object oCreature=OBJECT_SELF, int bOnlyCountReal = FALSE);

// 321: Get the last command (ASSOCIATE_COMMAND_*) issued to oAssociate.
//int GetLastAssociateCommand(object oAssociate=OBJECT_SELF);

// 322: Give nGP gold to oCreature.
//void GiveGoldToCreature(object oCreature, int nGP);

// 323: Set the destroyable status of the caller.
// - bDestroyable: If this is FALSE, the caller does not fade out on death, but
//   sticks around as a corpse.
// - bRaiseable: If this is TRUE, the caller can be raised via resurrection.
// - bSelectableWhenDead: If this is TRUE, the caller is selectable after death.
//void SetIsDestroyable(int bDestroyable, int bRaiseable=TRUE, int bSelectableWhenDead=FALSE);

// 324: Set the locked state of oTarget, which can be a door or a placeable object.
//void SetLocked(object oTarget, int bLocked);

// 325: Get the locked state of oTarget, which can be a door or a placeable object.
//int GetLocked(object oTarget);

// 326: Use this in a trigger's OnClick event script to get the object that last
// clicked on it.
// This is identical to GetEnteringObject.
//object GetClickingObject();

// 327: Initialise oTarget to listen for the standard Associates commands.
//void SetAssociateListenPatterns(object oTarget=OBJECT_SELF);

// 328: Get the last weapon that oCreature used in an attack.
// * Returns OBJECT_INVALID if oCreature did not attack, or has no weapon equipped.
//object GetLastWeaponUsed(object oCreature);

// 329: Use oPlaceable.
//void ActionInteractObject(object oPlaceable);

// 330: Get the last object that used the placeable object that is calling this function.
// * Returns OBJECT_INVALID if it is called by something other than a placeable or
//   a door.
//object GetLastUsedBy();

// 331: Returns the ability modifier for the specified ability
// Get oCreature's ability modifier for nAbility.
// - nAbility: ABILITY_*
// - oCreature
//int GetAbilityModifier(int nAbility, object oCreature=OBJECT_SELF);

// 332: Determined whether oItem has been identified.
//int GetIdentified(object oItem);

// 333: Set whether oItem has been identified.
//void SetIdentified(object oItem, int bIdentified);

// 334: Get the distance between lLocationA and lLocationB. in 2D
//float GetDistanceBetweenLocations2D(location lLocationA, location lLocationB);

// 335: Get the distance from the caller to oObject in metres.
// * Return value on error: -1.0f
//float GetDistanceToObject2D(object oObject);

// 336: Get the last blocking door encountered by the caller of this function.
// * Returns OBJECT_INVALID if the caller is not a valid creature.
//object GetBlockingDoor();

// 337: - oTargetDoor
// - nDoorAction: DOOR_ACTION_*
// * Returns TRUE if nDoorAction can be performed on oTargetDoor.
//int GetIsDoorActionPossible(object oTargetDoor, int nDoorAction);

// 338: Perform nDoorAction on oTargetDoor.
//void DoDoorAction(object oTargetDoor, int nDoorAction);

// 339: Get the first item in oTarget's inventory (start to cycle through oTarget's
// inventory).
// * Returns OBJECT_INVALID if the caller is not a creature, item, placeable or store,
//   or if no item is found.
//object GetFirstItemInInventory(object oTarget=OBJECT_SELF);

// 340: Get the next item in oTarget's inventory (continue to cycle through oTarget's
// inventory).
// * Returns OBJECT_INVALID if the caller is not a creature, item, placeable or store,
//   or if no item is found.
//object GetNextItemInInventory(object oTarget=OBJECT_SELF);

// 341: A creature can have up to three classes.  This function determines the
// creature's class (CLASS_TYPE_*) based on nClassPosition.
// - nClassPosition: 1, 2 or 3
// - oCreature
// * Returns CLASS_TYPE_INVALID if the oCreature does not have a class in
//   nClassPosition (i.e. a single-class creature will only have a value in
//   nClassLocation=1) or if oCreature is not a valid creature.
//int GetClassByPosition(int nClassPosition, object oCreature=OBJECT_SELF);

// 342: A creature can have up to three classes.  This function determines the
// creature's class level based on nClass Position.
// - nClassPosition: 1, 2 or 3
// - oCreature
// * Returns 0 if oCreature does not have a class in nClassPosition
//   (i.e. a single-class creature will only have a value in nClassLocation=1)
//   or if oCreature is not a valid creature.
//int GetLevelByPosition(int nClassPosition, object oCreature=OBJECT_SELF);

// 343: Determine the levels that oCreature holds in nClassType.
// - nClassType: CLASS_TYPE_*
// - oCreature
//int GetLevelByClass(int nClassType, object oCreature=OBJECT_SELF);

// 344: Get the amount of damage of type nDamageType that has been dealt to the caller.
// - nDamageType: DAMAGE_TYPE_*
//int GetDamageDealtByType(int nDamageType);

// 345: Get the total amount of damage that has been dealt to the caller.
//int GetTotalDamageDealt();

// 346: Get the last object that damaged the caller.
// * Returns OBJECT_INVALID if the caller is not a valid object.
//object GetLastDamager();

// 347: Get the last object that disarmed the trap on the caller.
// * Returns OBJECT_INVALID if the caller is not a valid placeable, trigger or
//   door.
//object GetLastDisarmed();

// 348: Get the last object that disturbed the inventory of the caller.
// * Returns OBJECT_INVALID if the caller is not a valid creature or placeable.
//object GetLastDisturbed();

// 349: Get the last object that locked the caller.
// * Returns OBJECT_INVALID if the caller is not a valid door or placeable.
//object GetLastLocked();

// 350: Get the last object that unlocked the caller.
// * Returns OBJECT_INVALID if the caller is not a valid door or placeable.
//object GetLastUnlocked();

// 351: Create a Skill Increase effect.
// - nSkill: SKILL_*
// - nValue
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if nSkill is invalid.
//effect EffectSkillIncrease(int nSkill, int nValue);

// 352: Get the type of disturbance (INVENTORY_DISTURB_*) that caused the caller's
// OnInventoryDisturbed script to fire.  This will only work for creatures and
// placeables.
//int GetInventoryDisturbType();

// 353: get the item that caused the caller's OnInventoryDisturbed script to fire.
// * Returns OBJECT_INVALID if the caller is not a valid object.
//object GetInventoryDisturbItem();

// 354: Displays the upgrade screen where the player can modify weapons and armor
// If oItem is NOT invalid, then the player will be forced to upgrade oItem and only oItem.
// If oCharacter is NOT invalid, then that character's various skills will be used... *NOT IMPLEMENTED*
// If nDisableItemCreation = TRUE, then the player will not be able to access the item creation screen
// If nDisableUpgrade = TRUE, then the player will be forced straight to item creation and not be able
//      to access Item Upgrading.
//void ShowUpgradeScreen(object oItem = OBJECT_INVALID, object oCharacter = OBJECT_INVALID, int nDisableItemCreation = FALSE, int nDisableUpgrade = FALSE, string sOverride2DA = "");

// 355: Set eEffect to be versus a specific alignment.
// - eEffect
// - nLawChaos: ALIGNMENT_LAWFUL/ALIGNMENT_CHAOTIC/ALIGNMENT_ALL
// - nGoodEvil: ALIGNMENT_GOOD/ALIGNMENT_EVIL/ALIGNMENT_ALL
//effect VersusAlignmentEffect(effect eEffect, int nLawChaos=ALIGNMENT_ALL, int nGoodEvil=ALIGNMENT_ALL);

// 356: Set eEffect to be versus nRacialType.
// - eEffect
// - nRacialType: RACIAL_TYPE_*
//effect VersusRacialTypeEffect(effect eEffect, int nRacialType);

// 357: Set eEffect to be versus traps.
//effect VersusTrapEffect(effect eEffect);

// 358: Get the gender of oCreature.
//int GetGender(object oCreature);

// 359: * Returns TRUE if tTalent is valid.
//int GetIsTalentValid(talent tTalent);

// 360: Causes the action subject to move away from lMoveAwayFrom.
//void ActionMoveAwayFromLocation(location lMoveAwayFrom, int bRun=FALSE, float fMoveAwayRange=40.0f);

// 361: Get the target that the caller attempted to attack - this should be used in
// conjunction with GetAttackTarget(). This value is set every time an attack is
// made, and is reset at the end of combat.
// * Returns OBJECT_INVALID if the caller is not a valid creature.
//object GetAttemptedAttackTarget();

// 362: Get the type (TALENT_TYPE_*) of tTalent.
//int GetTypeFromTalent(talent tTalent);

// 363: Get the ID of tTalent.  This could be a SPELL_*, FEAT_* or SKILL_*.
//int GetIdFromTalent(talent tTalent);

// 364: Starts a game of pazaak.
// - nOpponentPazaakDeck: Index into PazaakDecks.2da; specifies which deck the opponent will use.
// - sEndScript: Script to be run when game finishes.
// - nMaxWager: Max player wager.  If <= 0, the player's credits won't be modified by the result of the game and the wager screen will not show up.
// - bShowTutorial: Plays in tutorial mode (nMaxWager should be 0).
//void PlayPazaak(int nOpponentPazaakDeck, string sEndScript, int nMaxWager, int bShowTutorial=FALSE, object oOpponent=OBJECT_INVALID);

// 365: Returns result of last Pazaak game.  Should be used only in an EndScript sent to PlayPazaak.
// * Returns 0 if player loses, 1 if player wins.
//int GetLastPazaakResult();

// 366:  displays a feed back string for the object spicified and the constant
// repersents the string to be displayed see:FeedBackText.2da
//void DisplayFeedBackText(object oCreature, int nTextConstant);

// 367: Add a journal quest entry to the player.
// - szPlotID: the plot identifier used in the toolset's Journal Editor
// - nState: the state of the plot as seen in the toolset's Journal Editor
// - bAllowOverrideHigher: If this is TRUE, you can set the state to a lower
//   number than the one it is currently on
//void AddJournalQuestEntry(string szPlotID, int nState, int bAllowOverrideHigher=FALSE);

// 368: Remove a journal quest entry from the player.
// - szPlotID: the plot identifier used in the toolset's Journal Editor
//void RemoveJournalQuestEntry(string szPlotID);

// 369: Gets the State value of a journal quest.  Returns 0 if no quest entry has been added for this szPlotID.
// - szPlotID: the plot identifier used in the toolset's Journal Editor
//int GetJournalEntry(string szPlotID);

// 370: PlayRumblePattern
// Starts a defined rumble pattern playing
//int PlayRumblePattern(int nPattern);

// 371: StopRumblePattern
// Stops a defined rumble pattern
//int StopRumblePattern(int nPattern);

// 372: Damages the creatures force points
//effect EffectDamageForcePoints(int nDamage);

// 373: Heals the creatures force points
//effect EffectHealForcePoints(int nHeal);


// 374: Send a server message (szMessage) to the oPlayer.
//void SendMessageToPC(object oPlayer, string szMessage);

// 375: Get the target at which the caller attempted to cast a spell.
// This value is set every time a spell is cast and is reset at the end of
// combat.
// * Returns OBJECT_INVALID if the caller is not a valid creature.
//object GetAttemptedSpellTarget();

// 376: Get the last creature that opened the caller.
// * Returns OBJECT_INVALID if the caller is not a valid door or placeable.
//object GetLastOpenedBy();

// 377: Determine whether oCreature has nSpell memorised.
// PLEASE NOTE!!! - This function will return FALSE if the target
// is not currently able to use the spell due to lack of sufficient
// Force Points. Use GetSpellAcquired() if you just want to
// know if they've got it or not.
// - nSpell: SPELL_*
// - oCreature
//int GetHasSpell(int nSpell, object oCreature=OBJECT_SELF);

// 378: Open oStore for oPC.
//void OpenStore(object oStore, object oPC, int nBonusMarkUp=0, int nBonusMarkDown=0);

// 379:
//void ActionSurrenderToEnemies();

// 380: Get the first member of oMemberOfFaction's faction (start to cycle through
// oMemberOfFaction's faction).
// * Returns OBJECT_INVALID if oMemberOfFaction's faction is invalid.
//object GetFirstFactionMember(object oMemberOfFaction, int bPCOnly=TRUE);

// 381: Get the next member of oMemberOfFaction's faction (continue to cycle through
// oMemberOfFaction's faction).
// * Returns OBJECT_INVALID if oMemberOfFaction's faction is invalid.
//object GetNextFactionMember(object oMemberOfFaction, int bPCOnly=TRUE);

// 382: Force the action subject to move to lDestination.
//void ActionForceMoveToLocation(location lDestination, int bRun=FALSE, float fTimeout=30.0f);

// 383: Force the action subject to move to oMoveTo.
//void ActionForceMoveToObject(object oMoveTo, int bRun=FALSE, float fRange=1.0f, float fTimeout=30.0f);

// 384: Get the experience assigned in the journal editor for szPlotID.
//int GetJournalQuestExperience(string szPlotID);

// 385: Jump to oToJumpTo (the action is added to the top of the action queue).
//void JumpToObject(object oToJumpTo, int nWalkStraightLineToPoint=1);

// 386: Set whether oMapPin is enabled.
// - oMapPin
// - nEnabled: 0=Off, 1=On
//void SetMapPinEnabled(object oMapPin, int nEnabled);

// 387: Create a Hit Point Change When Dying effect.
// - fHitPointChangePerRound: this can be positive or negative, but not zero.
// * Returns an effect of type EFFECT_TYPE_INVALIDEFFECT if fHitPointChangePerRound is 0.
//effect EffectHitPointChangeWhenDying(float fHitPointChangePerRound);

// 388: Spawn a GUI panel for the client that controls oPC.
// - oPC
// - nGUIPanel: GUI_PANEL_*
// * Nothing happens if oPC is not a player character or if an invalid value is
//   used for nGUIPanel.
//void PopUpGUIPanel(object oPC, int nGUIPanel);

// 389: This allows you to add a new class to any creature object
//void AddMultiClass(int nClassType, object oSource);

// 390: Tests a linked effect to see if the target is immune to it.
// If the target is imune to any of the linked effect then he is immune to all of it
//int GetIsLinkImmune(object oTarget, effect eEffect );

// 391: Stunn the droid
//effect EffectDroidStun( );

// 392: Force push the creature...
//effect EffectForcePushed();

// 393: Gives nXpAmount to oCreature.
//void GiveXPToCreature(object oCreature, int nXpAmount);

// 394: Sets oCreature's experience to nXpAmount.
//void SetXP(object oCreature, int nXpAmount);

// 395: Get oCreature's experience.
//int GetXP(object oCreature);

// 396: Convert nInteger to hex, returning the hex value as a string.
// * Return value has the format "0x????????" where each ? will be a hex digit
//   (8 digits in total).
//string IntToHexString(int nInteger);

// 397: Get the base item type (BASE_ITEM_*) of oItem.
// * Returns BASE_ITEM_INVALID if oItem is an invalid item.
//int GetBaseItemType(object oItem);

// 398: Determines whether oItem has nProperty.
// - oItem
// - nProperty: ITEM_PROPERTY_*
// * Returns FALSE if oItem is not a valid item, or if oItem does not have
//   nProperty.
//int GetItemHasItemProperty(object oItem, int nProperty);

// 399: The creature will equip the melee weapon in its possession that can do the
// most damage. If no valid melee weapon is found, it will equip the most
// damaging range weapon. This function should only ever be called in the
// EndOfCombatRound scripts, because otherwise it would have to stop the combat
// round to run simulation.
// - oVersus: You can try to get the most damaging weapon against oVersus
// - bOffHand
//void ActionEquipMostDamagingMelee(object oVersus=OBJECT_INVALID, int bOffHand=FALSE);

} // End of namespace KotOR

} // End of namespace Engines
