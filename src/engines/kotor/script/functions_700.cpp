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

/** @file engines/kotor/script/functions_700.cpp
 *  kotor script functions, 700-799.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/talkman.h"
#include "aurora/2dafile.h"
#include "aurora/2dareg.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/area.h"
#include "engines/kotor/object.h"

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

void ScriptFunctions::registerFunctions700(const Defaults &d) {
}

// 700. ActionBarkString
// this will cause a creature to bark the strRef from the talk table.
//void ActionBarkString(int strRef);

// 701. GetIsConversationActive
// Checks to see if any conversations are currently taking place
//int GetIsConversationActive();

// 702. EffectLightsaberThrow
// This function throws a lightsaber at a target
// If multiple targets are specified, then the lightsaber travels to them
// sequentially, returning to the first object specified
// This effect is applied to an object, so an effector is not needed
//effect EffectLightsaberThrow(object oTarget1, object oTarget2 = OBJECT_INVALID, object oTarget3 = OBJECT_INVALID, int nAdvancedDamage = 0);

// 703.
// creates the effect of a whirl wind.
//effect EffectWhirlWind();

// 704.
// Returns the party ai style
//int GetPartyAIStyle();

// 705.
// Returns the party members ai style
//int GetNPCAIStyle(object oCreature);

// 706.
// Sets the party ai style
//void SetPartyAIStyle(int nStyle);

// 707.
// Sets the party members ai style
//void SetNPCAIStyle(object oCreature, int nStyle);

// 708: SetNPCSelectability
//void SetNPCSelectability(int nNPC, int nSelectability);

// 709: GetNPCSelectability
// nNPC - NPC_
// returns 1 if in current party, 0 if selectable as a party member
// -1 if not in party at all
//int GetNPCSelectability(int nNPC);

// 710: Clear all the effects of the caller.
// * No return value, but if an error occurs, the log file will contain
//   "ClearAllEffects failed.".
//void ClearAllEffects();

// 711: GetLastConversation
// Gets the last conversation string.
//string GetLastConversation();


// 712: ShowPartySelectionGUI
// Brings up the party selection GUI for the player to
// select the members of the party from
// if exit script is specified, will be executed when
// the GUI is exited
// RWT-OEI 08/23/04 - New parameter = nAllowCancel. Passing in TRUE
//  to this parameter makes it possible for the player to cancel out
//  of the party selection GUI, so be careful that you are okay with
//  them cancelling out of it before you pass TRUE.
//  Also, in the sExitScript that gets called after the Party Select
//  GUI exits, you can use GetRunScriptVar to find out if they
//  cancelled. If it returns TRUE, they didn't cancel. If it returns
//  FALSE, they cancelled.  See me if there's questions.
//void ShowPartySelectionGUI(string sExitScript = "", int nForceNPC1 = -1, int nForceNPC2 = -1, int nAllowCancel = FALSE);

// 713: GetStandardFaction
// Find out which standard faction oObject belongs to.
// * Returns INVALID_STANDARD_FACTION if oObject does not belong to
//   a Standard Faction, or an error has occurred.
//int GetStandardFaction(object oObject);

// 714: GivePlotXP
// Give nPercentage% of the experience associated with plot sPlotName
// to the party
// - sPlotName
// - nPercentage
//void GivePlotXP(string sPlotName, int nPercentage);

// 715. GetMinOneHP
// Checks to see if oObject has the MinOneHP Flag set on them.
//int GetMinOneHP(object oObject);

// 716. SetMinOneHP
// Sets/Removes the MinOneHP Flag on oObject.
//void SetMinOneHP(object oObject,int nMinOneHP);

// 717. SWMG_GetPlayerTunnelInfinite
// Gets whether each of the dimensions is infinite
//vector SWMG_GetPlayerTunnelInfinite();

// 718. SWMG_SetPlayerTunnelInfinite
// Sets whether each of the dimensions is infinite
//void SWMG_SetPlayerTunnelInfinite(vector vInfinite);

// 719. SetGlobalFadeIn
// Sets a Fade In that starts after fWait seconds and fades for fLength Seconds.
// The Fade will be from a color specified by the RGB values fR, fG, and fB.
// Note that fR, fG, and fB are normalized values.
// The default values are an immediate cut in from black.
//void SetGlobalFadeIn(float fWait = 0.0f, float fLength = 0.0f, float fR=0.0f, float fG=0.0f, float fB=0.0f);

// 720. SetGlobalFadeOut
// Sets a Fade Out that starts after fWait seconds and fades for fLength Seconds.
// The Fade will be to a color specified by the RGB values fR, fG, and fB.
// Note that fR, fG, and fB are normalized values.
// The default values are an immediate cut to from black.
//void SetGlobalFadeOut(float fWait = 0.0f, float fLength = 0.0f, float fR=0.0f, float fG=0.0f, float fB=0.0f);


// 721. GetLastAttackTarget
// Returns the last attack target for a given object
//object GetLastHostileTarget(object oAttacker = OBJECT_SELF);

// 722. GetLastAttackAction
// Returns the last attack action for a given object
//int GetLastAttackAction(object oAttacker = OBJECT_SELF);

// 723. GetLastForcePowerUsed
// Returns the last force power used (as a spell number that indexes the Spells.2da) by the given object
//int GetLastForcePowerUsed(object oAttacker = OBJECT_SELF);

// 724. GetLastCombatFeatUsed
// Returns the last feat used (as a feat number that indexes the Feats.2da) by the given object
//int GetLastCombatFeatUsed(object oAttacker = OBJECT_SELF);

// 725. GetLastAttackResult
// Returns the result of the last attack
//int GetLastAttackResult(object oAttacker = OBJECT_SELF);

// 726. GetWasForcePowerSuccessful
// Returns whether the last force power used was successful or not
//int GetWasForcePowerSuccessful(object oAttacker = OBJECT_SELF);

// 727. GetFirstAttacker
// Returns the first object in the area that is attacking oCreature
//object GetFirstAttacker(object oCreature = OBJECT_SELF);

// 728. GetNextAttacker
// Returns the next object in the area that is attacking oCreature
//object GetNextAttacker(object oCreature = OBJECT_SELF);

// 729. SetFormation
// Put oCreature into the nFormationPattern about oAnchor at position nPosition
// - oAnchor: The formation is set relative to this object
// - oCreature: This is the creature that you wish to join the formation
// - nFormationPattern: FORMATION_*
// - nPosition: Integer from 1 to 10 to specify which position in the formation
//   oCreature is supposed to take.
//void SetFormation(object oAnchor, object oCreature, int nFormationPattern, int nPosition);

// 730. ActionFollowLeader
// this action has a party member follow the leader.
// DO NOT USE ON A CREATURE THAT IS NOT IN THE PARTY!!
//void ActionFollowLeader();

// 731. SetForcePowerUnsuccessful
// Sets the reason (through a constant) for why a force power failed
//void SetForcePowerUnsuccessful(int nResult, object oCreature = OBJECT_SELF);

// 732. GetIsDebilitated
// Returns whether the given object is debilitated or not
//int GetIsDebilitated(object oCreature = OBJECT_SELF);

// 733. PlayMovie
// Playes a Movie.
//void PlayMovie( string sMovie, int nStreamingMusic = FALSE );

// 734. SaveNPCState
// Tells the party table to save the state of a party member NPC
//void SaveNPCState( int nNPC );

// 735: Get the Category of tTalent.
//int GetCategoryFromTalent(talent tTalent);

// 736: This affects all creatures in the area that are in faction nFactionFrom...
// - Makes them join nFactionTo
// - Clears all actions
// - Disables combat mode
//void SurrenderByFaction(int nFactionFrom, int nFactionTo);

// 737: This affects all creatures in the area that are in faction nFactionFrom.
// making them change to nFactionTo
//void ChangeFactionByFaction(int nFactionFrom, int nFactionTo);

// 738: PlayRoomAnimation
// Plays a looping animation on a room
//void PlayRoomAnimation(string sRoom, int nAnimation);

// 739: ShowGalaxyMap
// Brings up the Galaxy Map Gui, with 'nPlanet' selected.  'nPlanet' can only be a planet
// that has already been set available and selectable.
//void ShowGalaxyMap(int nPlanet);

// 740: SetPlanetSelectable
// Sets 'nPlanet' selectable on the Galaxy Map Gui.
//void SetPlanetSelectable(int nPlanet, int bSelectable);

// 741: GetPlanetSelectable
// Returns wheter or not 'nPlanet' is selectable.
//int GetPlanetSelectable(int nPlanet);

// 742: SetPlanetAvailable
// Sets 'nPlanet' available on the Galaxy Map Gui.
//void SetPlanetAvailable(int nPlanet, int bAvailable);

// 743: GetPlanetAvailable
// Returns wheter or not 'nPlanet' is available.
//int GetPlanetAvailable(int nPlanet);

// 744: GetSelectedPlanet
// Returns the ID of the currently selected planet.  Check Planetary.2da
// for which planet the return value corresponds to. If the return is -1
// no planet is selected.
//int GetSelectedPlanet();

// 745: SoundObjectFadeAndStop
// Fades a sound object for 'fSeconds' and then stops it.
//void SoundObjectFadeAndStop(object oSound,float fSeconds);

// 746: SetAreaFogColor
// Set the fog color for the area oArea.
//void SetAreaFogColor( object oArea, float fRed, float fGreen, float fBlue );

// 747: ChangeItemCost
// Change the cost of an item
//void ChangeItemCost( string sItem, float fCostMultiplier );

// 748: GetIsLiveContentAvailable
// Determines whether a given live content package is available
// nPkg = LIVE_CONTENT_PKG1, LIVE_CONTENT_PKG2, ..., LIVE_CONTENT_PKG6
//int GetIsLiveContentAvailable(int nPkg);

// 749: ResetDialogState
// Resets the GlobalDialogState for the engine.
// NOTE: NEVER USE THIS UNLESS YOU KNOW WHAT ITS FOR!
//       only to be used for a failing OnDialog script
//void ResetDialogState();

// 750: SetAlignmentGoodEvil
// Set oCreature's alignment value
//void SetGoodEvilValue( object oCreature, int nAlignment );

// 751: GetIsPoisoned
// Returns TRUE if the object specified is poisoned.
//int GetIsPoisoned( object oObject );

// 752: GetSpellTarget
// Returns the object id of the spell target
//object GetSpellTarget(object oCreature=OBJECT_SELF);

// 753: SetSoloMode
// Activates/Deactivates solo mode for the player's party.
//void SetSoloMode( int bActivate );

// 754: EffectCutSceneHorrified
// Get a horrified effect for cutscene purposes (ie. this effect will ignore immunities).
//effect EffectCutSceneHorrified();

// 755: EffectCutSceneParalyze
// Get a paralyze effect for cutscene purposes (ie. this effect will ignore immunities).
//effect EffectCutSceneParalyze();

// 756: EffectCutSceneStunned
// Get a stun effect for cutscene purposes (ie. this effect will ignore immunities).
//effect EffectCutSceneStunned();

// 757: CancelPostDialogCharacterSwitch()
// If a dialog has been started by an NPC on a Non PartyMemeberCanInteract object
// calling this function will cancel the Post Dialog switching back to the NPC
// that did the initiating.
//void CancelPostDialogCharacterSwitch();

// 758: SetMaxHitPoints
// Set the maximum hitpoints of oObject
// The objects maximum AND current hitpoints will be nMaxHP after the function is called
//void SetMaxHitPoints(object oObject, int nMaxHP);

// 759: NoClicksFor()
// This command will not allow clicking on anything for 'fDuration' seconds
//void NoClicksFor(float fDuration);

// 760: HoldWorldFadeInForDialog()
// This will hold the fade in at the begining of a module until a dialog starts
//void HoldWorldFadeInForDialog();

// 761: ShipBuild()
// This will return if this is a shipping build. this should be used to disable all debug output.
//int ShipBuild();

// 762: SurrenderRetainBuffs()
// This will do the same as SurrenderToEnemies, except that affected creatures will not
// lose effects which they have put on themselves
//void SurrenderRetainBuffs();

// 763. SuppressStatusSummaryEntry
// This will prevent the next n entries that should have shown up in the status summary
// from being added
// This will not add on to any existing summary suppressions, but rather replace it.  So
// to clear the supression system pass 0 as the entry value
//void SuppressStatusSummaryEntry(int nNumEntries = 1);

// 764. GetCheatCode
// Returns true if cheat code has been enabled
//int GetCheatCode(int nCode);

// 765. SetMusicVolume
// NEVER USE THIS!
//void SetMusicVolume(float fVolume = 1.0f);

// 766. CreateItemOnFloor
// Should only be used for items that have been created on the ground, and will
// be destroyed without ever being picked up or equipped.  Returns true if successful
//object CreateItemOnFloor(string sTemplate, location lLocation, int bUseAppearAnimation=FALSE);

// 767. SetAvailableNPCId
// This will set the object id that should be used for a specific available NPC
//void SetAvailableNPCId(INT nNPC, OBJECT_ID oidNPC);

// DJS-OEI
// 768. GetScriptParameter
// This function will take the index of a script parameter
// and return the value associated with it. The index
// of the first parameter is 1.
//int GetScriptParameter( int nIndex );

//RWT-OEI 12/10/03
// 769. SetFadeUntilScript
// This script function will make it so that the fade cannot be lifted under any circumstances
// other than a call to the SetGlobalFadeIn() script.
// This function should be called AFTER the fade has already been called. For example, you would
// do a SetGlobalFadeOut() first, THEN do SetFadeUntilScript()
// The exception to this if it's used in an OnModuleLoad() script, where instead of starting a new
// fade you are just extending the LevelLoad fade indefinitely. You can just call SetFadeUntilScript
// in such cases and the game will stay faded until a GlobalSetFadeIn() is called.
//void SetFadeUntilScript();

// DJS-OEI 12/15/2003
// 770: Create a Force Body effect
// - nLevel: The level of the Force Body effect.
//    0 = Force Body
//    1 = Improved Force Body
//    2 = Master Force Body
//effect EffectForceBody(int nLevel);

// FAK-OEI 12/15/2003
// 771: Get the number of components for an item
//int GetItemComponent( );

// FAK-OEI 12/15/2003
// 771: Get the number of components for an item in pieces
//int GetItemComponentPieceValue( );

// FAK-OEI 12/15/2003
// 773: Start the GUI for Chemical Workshop
//void ShowChemicalUpgradeScreen(object oCharacter );

// FAK-OEI 12/15/2003
// 774: Get the number of chemicals for an item
//int GetChemicals( );

// FAK-OEI 12/15/2003
// 775: Get the number of chemicals for an item in pieces
//int GetChemicalPieceValue( );

// DJS-OEI 12/30/2003
// 776: Get the number of Force Points that were required to
// cast this spell. This includes modifiers such as Room Force
// Ratings and the Force Body power.
// * Return value on error: 0
//int GetSpellForcePointCost( );

// DJS-OEI 1/2/2004
// 777: Create a Fury effect.
//effect EffectFury();

// DJS-OEI 1/3/2004
// 778: Create a Blind effect.
//effect EffectBlind();

// DJS-OEI 1/4/2004
// 779: Create an FP regeneration modifier effect.
//effect EffectFPRegenModifier( int nPercent );

// DJS-OEI 1/4/2004
// 780: Create a VP regeneration modifier effect.
//effect EffectVPRegenModifier( int nPercent );

// DJS-OEI 1/9/2004
// 781: Create a Force Crush effect.
//effect EffectCrush();

// FAK - OEI 1/12/04
// 782: Minigame grabs a swoop bike upgrade
//int SWMG_GetSwoopUpgrade( int nSlot );

// DJS-OEI 1/12/2004
// 783: Returns whether or not the target has access to a feat,
// even if they can't use it right now due to daily limits or
// other restrictions.
//int GetFeatAcquired( int nFeat, object oCreature=OBJECT_SELF );

// DJS-OEI 1/12/2004
// 784: Returns whether or not the target has access to a spell,
// even if they can't use it right now due to lack of Force Points.
//int GetSpellAcquired( int nSpell, object oCreature=OBJECT_SELF );

// FAK-OEI 1/12/2004
// 785: Displays the Swoop Bike upgrade screen.
//void ShowSwoopUpgradeScreen( );

// DJS-OEI 1/13/2004
// 786: Grants the target a feat without regard for prerequisites.
//void GrantFeat( int nFeat, object oCreature );

// DJS-OEI 1/13/2004
// 787: Grants the target a spell without regard for prerequisites.
//void GrantSpell( int nSpell, object oCreature );

// DJS-OEI 1/13/2004
// 788: Places an active mine on the map.
// nMineType - Mine Type from Traps.2DA
// lPoint - The location in the world to place the mine.
// nDetectDCBase - This value, plus the "DetectDCMod" column in Traps.2DA
// results in the final DC for creatures to detect this mine.
// nDisarmDCBase - This value, plus the "DisarmDCMod" column in Traps.2DA
// results in the final DC for creatures to disarm this mine.
// oCreator - The object that should be considered the owner of the mine.
// If oCreator is set to OBJECT_INVALID, the faction of the mine will be
// considered Hostile1, meaning the party will be vulnerable to it.
//void SpawnMine( int nMineType, location lPoint, int nDetectDCBase, int nDisarmDCBase, object oCreator );

// FAK - OEI 1/15/04
// 789: Yet another minigame function. Returns the object's track's position.
//vector SWMG_GetTrackPosition(object oFollower);

// FAK - OEI 1/15/04
// 790: minigame function that lets you psuedo-set the position of a follower object
//vector SWMG_SetFollowerPosition(vector vPos);

//RWT-OEI 01/16/04
// 791: A function to put the character into a true combat state but the reason set to
//      not real combat. This should help us control animations in cutscenes with a bit
//      more precision. -- Not totally sure this is doing anything just yet. Seems
//      the combat condition gets cleared shortly after anyway.
//      If nEnable is 1, it enables fake combat mode. If 0, it disables it.
//      WARNING: Whenever using this function to enable fake combat mode, you should
//               have a matching call to it to disable it. (pass 0 for nEnable).
//void SetFakeCombatState( object oObject, int nEnable );

// FAK - OEI 1/23/04
// 792: minigame function that deletes a minigame object
//void SWMG_DestroyMiniGameObject(object oObject);

// DJS-OEI 1/26/2004
// 793: Returns the Demolitions skill of the creature that
// placed this mine. This will often be 0. This function accepts
// the object that the mine is attached to (Door, Placeable, or Trigger)
// and will determine which one it actually is at runtime.
//int GetOwnerDemolitionsSkill( object oObject );

// RWT-OEI 01/29/04
// 794: Disables or Enables the Orient On Click behavior in creatures. If
//      disabled, they will not orient to face the player when clicked on
//      for dialogue. The default behavior is TRUE.
//void SetOrientOnClick( object oCreature = OBJECT_SELF, int nState = TRUE );

// DJS-OEI 1/29/2004
// 795: Gets the PC's influence on the alignment of a CNPC.
// Parameters:
// nNPC - NPC_* constant identifying the CNPC we're interested in.
// If this character is not an available party member, the return
// value with be 0. If the character is in the party, but has an
// attitude of Ambivalent, this will be -1.
//int GetInfluence( int nNPC );

// DJS-OEI 1/29/2004
// 796: Sets the PC's influence on the alignment of a CNPC.
// Parameters:
// nNPC - NPC_* constant identifying the CNPC we're interested in.
// If this character is not an available party member, nothing
// will happen.
// nInfluence - The new value for the influence on this CNPC.
//void SetInfluence( int nNPC, int nInfluence );

// DJS-OEI 1/29/2004
// 797: Modifies the PC's influence on the alignment of a CNPC.
// Parameters:
// nNPC - NPC_* constant identifying the CNPC we're interested in.
// If this character is not an available party member, nothing
// will happen.
// nModifier - The modifier to the current influence on this CNPC.
// This may be a negative value to reduce the influence.
//void ModifyInfluence( int nNPC, int nModifier );

// FAK - OEI 2/3/04
// 798: returns the racial sub-type of the oTarget object
//int GetRacialSubType(object oTarget);

// DJS-OEI 2/3/2004
// 799: Increases the value of the given global number by the given amount.
// This function only works with Number type globals, not booleans. It
// will fail with a warning if the final amount is greater than the max
// of 127.
//void IncrementGlobalNumber( string sIdentifier, int nAmount );

} // End of namespace KotOR

} // End of namespace Engines
