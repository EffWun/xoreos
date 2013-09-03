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

/** @file engines/kotor/script/functions_500.cpp
 *  kotor script functions, 500-599.
 */

#include <boost/bind.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "common/util.h"
#include "common/error.h"
#include "common/configman.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/kotor.h"
#include "engines/kotor/module.h"
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

// boost-date_time stuff
using boost::posix_time::ptime;
using boost::posix_time::second_clock;

namespace Engines {

namespace KotOR {

void ScriptFunctions::registerFunctions500(const Defaults &d) {
}
// 500:
//void DuplicateHeadAppearance(object oidCreatureToChange, object oidCreatureToMatch);

// 501: The action subject will fake casting a spell at oTarget; the conjure and cast
// animations and visuals will occur, nothing else.
// - nSpell
// - oTarget
// - nProjectilePathType: PROJECTILE_PATH_TYPE_*
//void ActionCastFakeSpellAtObject(int nSpell, object oTarget, int nProjectilePathType=PROJECTILE_PATH_TYPE_DEFAULT);

// 502: The action subject will fake casting a spell at lLocation; the conjure and
// cast animations and visuals will occur, nothing else.
// - nSpell
// - lTarget
// - nProjectilePathType: PROJECTILE_PATH_TYPE_*
//void ActionCastFakeSpellAtLocation(int nSpell, location lTarget, int nProjectilePathType=PROJECTILE_PATH_TYPE_DEFAULT);

// 503: CutsceneAttack
// This function allows the designer to specify exactly what's going to happen in a combat round
// There are no guarentees made that the animation specified here will be correct - only that it will be played,
// so it is up to the designer to ensure that they have selected the right animation
// It relies upon constants specified above for the attack result
//void CutsceneAttack(object oTarget, int nAnimation, int nAttackResult, int nDamage);

// 504: Set the camera mode for oPlayer.
// - oPlayer
// - nCameraMode: CAMERA_MODE_*
// * If oPlayer is not player-controlled or nCameraMode is invalid, nothing
//   happens.
//void SetCameraMode(object oPlayer, int nCameraMode);

// 505: SetLockOrientationInDialog
// Allows the locking and unlocking of orientation changes for an object in dialog
// - oObject - Object
// - nValue - TRUE or FALSE
//void SetLockOrientationInDialog(object oObject, int nValue);

// 506: SetLockHeadFollowInDialog
// Allows the locking and undlocking of head following for an object in dialog
// - oObject - Object
// - nValue - TRUE or FALSE
//void SetLockHeadFollowInDialog(object oObject, int nValue);

// 507: CutsceneMoveToPoint
// Used by the cutscene system to allow designers to script combat
//void CutsceneMove(object oObject, vector vPosition, int nRun);

// 508: EnableVideoEffect
// Enables the video frame buffer effect specified by nEffectType, which is
// an index into VideoEffects.2da. This video effect will apply indefinitely,
// and so it should *always* be cleared by a call to DisableVideoEffect().
//void EnableVideoEffect(int nEffectType);

// 509: Shut down the currently loaded module and start a new one (moving all
// currently-connected players to the starting point.
//void StartNewModule(string sModuleName, string sWayPoint="", string sMovie1="", string sMovie2="", string sMovie3="", string sMovie4="", string sMovie5="", string sMovie6="");

// 510: DisableVideoEffect
// Disables any video frame buffer effect that may be running. See
// EnableVideoEffect() to see how to use them.
//void DisableVideoEffect();

// 511: * Returns TRUE if oItem is a ranged weapon.
//int GetWeaponRanged(object oItem);

// 512: Only if we are in a single player game, AutoSave the game.
//void DoSinglePlayerAutoSave();

// 513: Get the game difficulty (GAME_DIFFICULTY_*).
//int GetGameDifficulty();

// 514:
// This will test the combat action queu to see if the user has placed any actions on the queue.
// will only work during combat.
//int GetUserActionsPending();

// 515: RevealMap
// Reveals the map at the given WORLD point 'vPoint' with a MAP Grid Radius 'nRadius'
// If this function is called with no parameters it will reveal the entire map.
// (NOTE: if this function is called with a valid point but a default radius, ie. 'nRadius' of -1
//        then the entire map will be revealed)
//void RevealMap(vector vPoint=[0.0,0.0,0.0],int nRadius=-1);

// 516: SetTutorialWindowsEnabled
// Sets whether or not the tutorial windows are enabled (ie. whether or not they will
// appear when certain things happen for the first time).
//void SetTutorialWindowsEnabled( int bEnabled );

// 517: ShowTutorialWindow
// nWindow - A row index from Tutorial.2DA specifying the message to display.
// Pops up the specified tutorial window.  If the tutorial window has already popped
// up once before, this will do nothing.
//void ShowTutorialWindow( int nWindow );

// 518: StartCreditSequence
// Starts the credits sequence.  If bTransparentBackground is TRUE, the credits will be displayed
// with a transparent background, allowing whatever is currently onscreen to show through.  If it
// is set to FALSE, the credits will be displayed on a black background.
//void StartCreditSequence( int bTransparentBackground );

// 519: IsCreditSequenceInProgress
// Returns TRUE if the credits sequence is currently in progress, FALSE otherwise.
//int IsCreditSequenceInProgress();

// 520: Sets the minigame lateral acceleration/sec value
//void SWMG_SetLateralAccelerationPerSecond(float fLAPS);

// 521: Returns the minigame lateral acceleration/sec value
//float SWMG_GetLateralAccelerationPerSecond();

// 522: Get the current action (ACTION_*) that oObject is executing.
//int GetCurrentAction(object oObject=OBJECT_SELF);

// 523:
//float GetDifficultyModifier();

// 524: Returns the appearance type of oCreature (0 if creature doesn't exist)
// - oCreature
//int GetAppearanceType(object oCreature);

// 525: Display floaty text above the specified creature.
// The text will also appear in the chat buffer of each player that receives the
// floaty text.
// - nStrRefToDisplay: String ref (therefore text is translated)
// - oCreatureToFloatAbove
// - bBroadcastToFaction: If this is TRUE then only creatures in the same faction
//   as oCreatureToFloatAbove
//   will see the floaty text, and only if they are within range (30 metres).
//void FloatingTextStrRefOnCreature(int nStrRefToDisplay, object oCreatureToFloatAbove, int bBroadcastToFaction=TRUE);

// 526: Display floaty text above the specified creature.
// The text will also appear in the chat buffer of each player that receives the
// floaty text.
// - sStringToDisplay: String
// - oCreatureToFloatAbove
// - bBroadcastToFaction: If this is TRUE then only creatures in the same faction
//   as oCreatureToFloatAbove
//   will see the floaty text, and only if they are within range (30 metres).
//void FloatingTextStringOnCreature(string sStringToDisplay, object oCreatureToFloatAbove, int bBroadcastToFaction=TRUE);

// 527: - oTrapObject: a placeable, door or trigger
// * Returns TRUE if oTrapObject is disarmable.
//int GetTrapDisarmable(object oTrapObject);

// 528: - oTrapObject: a placeable, door or trigger
// * Returns TRUE if oTrapObject is detectable.
//int GetTrapDetectable(object oTrapObject);

// 529: - oTrapObject: a placeable, door or trigger
// - oCreature
// * Returns TRUE if oCreature has detected oTrapObject
//int GetTrapDetectedBy(object oTrapObject, object oCreature);

// 530: - oTrapObject: a placeable, door or trigger
// * Returns TRUE if oTrapObject has been flagged as visible to all creatures.
//int GetTrapFlagged(object oTrapObject);

// 531: Get the trap base type (TRAP_BASE_TYPE_*) of oTrapObject.
// - oTrapObject: a placeable, door or trigger
//int GetTrapBaseType(object oTrapObject);

// 532: - oTrapObject: a placeable, door or trigger
// * Returns TRUE if oTrapObject is one-shot (i.e. it does not reset itself
//   after firing.
//int GetTrapOneShot(object oTrapObject);

// 533: Get the creator of oTrapObject, the creature that set the trap.
// - oTrapObject: a placeable, door or trigger
// * Returns OBJECT_INVALID if oTrapObject was created in the toolset.
//object GetTrapCreator(object oTrapObject);

// 534: Get the tag of the key that will disarm oTrapObject.
// - oTrapObject: a placeable, door or trigger
//string GetTrapKeyTag(object oTrapObject);

// 535: Get the DC for disarming oTrapObject.
// - oTrapObject: a placeable, door or trigger
//int GetTrapDisarmDC(object oTrapObject);

// 536: Get the DC for detecting oTrapObject.
// - oTrapObject: a placeable, door or trigger
//int GetTrapDetectDC(object oTrapObject);

// 537: * Returns TRUE if a specific key is required to open the lock on oObject.
//int GetLockKeyRequired(object oObject);

// 538: Get the tag of the key that will open the lock on oObject.
//int GetLockKeyTag(object oObject);

// 539: * Returns TRUE if the lock on oObject is lockable.
//int GetLockLockable(object oObject);

// 540: Get the DC for unlocking oObject.
//int GetLockUnlockDC(object oObject);

// 541: Get the DC for locking oObject.
//int GetLockLockDC(object oObject);

// 542: Get the last PC that levelled up.
//object GetPCLevellingUp();

// 543: - nFeat: FEAT_*
// - oObject
// * Returns TRUE if oObject has effects on it originating from nFeat.
//int GetHasFeatEffect(int nFeat, object oObject=OBJECT_SELF);

// 544: Set the status of the illumination for oPlaceable.
// - oPlaceable
// - bIlluminate: if this is TRUE, oPlaceable's illumination will be turned on.
//   If this is FALSE, oPlaceable's illumination will be turned off.
// Note: You must call RecomputeStaticLighting() after calling this function in
// order for the changes to occur visually for the players.
// SetPlaceableIllumination() buffers the illumination changes, which are then
// sent out to the players once RecomputeStaticLighting() is called.  As such,
// it is best to call SetPlaceableIllumination() for all the placeables you wish
// to set the illumination on, and then call RecomputeStaticLighting() once after
// all the placeable illumination has been set.
// * If oPlaceable is not a placeable object, or oPlaceable is a placeable that
//   doesn't have a light, nothing will happen.
//void SetPlaceableIllumination(object oPlaceable=OBJECT_SELF, int bIlluminate=TRUE);

// 545: * Returns TRUE if the illumination for oPlaceable is on
//int GetPlaceableIllumination(object oPlaceable=OBJECT_SELF);

// 546: - oPlaceable
// - nPlaceableAction: PLACEABLE_ACTION_*
// * Returns TRUE if nPlacebleAction is valid for oPlaceable.
//int GetIsPlaceableObjectActionPossible(object oPlaceable, int nPlaceableAction);

// 547: The caller performs nPlaceableAction on oPlaceable.
// - oPlaceable
// - nPlaceableAction: PLACEABLE_ACTION_*
//void DoPlaceableObjectAction(object oPlaceable, int nPlaceableAction);

// 548: Get the first PC in the player list.
// This resets the position in the player list for GetNextPC().
//object GetFirstPC();

// 549: Get the next PC in the player list.
// This picks up where the last GetFirstPC() or GetNextPC() left off.
//object GetNextPC();

// 550: Set oDetector to have detected oTrap.
//int SetTrapDetectedBy(object oTrap, object oDetector);

// 551: Note: Only placeables, doors and triggers can be trapped.
// * Returns TRUE if oObject is trapped.
//int GetIsTrapped(object oObject);

// 552: SetEffectIcon
// This will link the specified effect icon to the specified effect.  The
// effect returned will contain the link to the effect icon and applying this
// effect will cause an effect icon to appear on the portrait/charsheet gui.
// eEffect: The effect which should cause the effect icon to appear.
// nIcon: Index into effecticon.2da of the effect icon to use.
//effect SetEffectIcon( effect eEffect, int nIcon );

// 553: FaceObjectAwayFromObject
// This will cause the object oFacer to face away from oObjectToFaceAwayFrom.
// The objects must be in the same area for this to work.
//void FaceObjectAwayFromObject( object oFacer, object oObjectToFaceAwayFrom );

// 554: Spawn in the Death GUI.
// The default (as defined by BioWare) can be spawned in by PopUpGUIPanel, but
// if you want to turn off the "Respawn" or "Wait for Help" buttons, this is the
// function to use.
// - oPC
// - bRespawnButtonEnabled: if this is TRUE, the "Respawn" button will be enabled
//   on the Death GUI.
// - bWaitForHelpButtonEnabled: if this is TRUE, the "Wait For Help" button will
//   be enabled on the Death GUI.
// - nHelpStringReference
// - sHelpString
//void PopUpDeathGUIPanel(object oPC, int bRespawnButtonEnabled=TRUE, int bWaitForHelpButtonEnabled=TRUE, int nHelpStringReference=0, string sHelpString="");

// 555: Disable oTrap.
// - oTrap: a placeable, door or trigger.
//void SetTrapDisabled(object oTrap);

// 556: Get the last object that was sent as a GetLastAttacker(), GetLastDamager(),
// GetLastSpellCaster() (for a hostile spell), or GetLastDisturbed() (when a
// creature is pickpocketed).
// Note: Return values may only ever be:
// 1) A Creature
// 2) Plot Characters will never have this value set
// 3) Area of Effect Objects will return the AOE creator if they are registered
//    as this value, otherwise they will return INVALID_OBJECT_ID
// 4) Traps will not return the creature that set the trap.
// 5) This value will never be overwritten by another non-creature object.
// 6) This value will never be a dead/destroyed creature
//object GetLastHostileActor(object oVictim=OBJECT_SELF);

// 557: Force all the characters of the players who are currently in the game to
// be exported to their respective directories i.e. LocalVault/ServerVault/ etc.
//void ExportAllCharacters();

// 558: Get the Day Track for oArea.
//int MusicBackgroundGetDayTrack(object oArea);

// 559: Get the Night Track for oArea.
//int MusicBackgroundGetNightTrack(object oArea);

// 560: Write sLogEntry as a timestamped entry into the log file
//void WriteTimestampedLogEntry(string sLogEntry);

// 561: Get the module's name in the language of the server that's running it.
// * If there is no entry for the language of the server, it will return an
//   empty string
//string GetModuleName();

// 562: Get the leader of the faction of which oMemberOfFaction is a member.
// * Returns OBJECT_INVALID if oMemberOfFaction is not a valid creature.
//object GetFactionLeader(object oMemberOfFaction);

// 563: Turns on or off the speed blur effect in rendered scenes.
// bEnabled: Set TRUE to turn it on, FALSE to turn it off.
// fRatio: Sets the frame accumulation ratio.
//void SWMG_SetSpeedBlurEffect( int bEnabled, float fRatio=0.75f );

// 564: Immediately ends the currently running game and returns to the start screen.
// nShowEndGameGui: Set TRUE to display the death gui.
//void EndGame( int nShowEndGameGui=TRUE );

// 565: Get a variable passed when calling console debug runscript
//int GetRunScriptVar();

// 566: This function returns a value that matches one of the MOVEMENT_SPEED_... constants
//      if the OID passed in is not found or not a creature then it will return
//  MOVEMENT_SPEED_IMMOBILE.
//int GetCreatureMovmentType(object oidCreature);

// 567: Set the ambient day volume for oArea to nVolume.
// - oArea
// - nVolume: 0 - 100
//void AmbientSoundSetDayVolume(object oArea, int nVolume);

// 568: Set the ambient night volume for oArea to nVolume.
// - oArea
// - nVolume: 0 - 100
//void AmbientSoundSetNightVolume(object oArea, int nVolume);

// 569: Get the Battle Track for oArea.
//int MusicBackgroundGetBattleTrack(object oArea);

// 570: Determine whether oObject has an inventory.
// * Returns TRUE for creatures and stores, and checks to see if an item or placeable object is a container.
// * Returns FALSE for all other object types.
//int GetHasInventory(object oObject);

// 571: Get the duration (in seconds) of the sound attached to nStrRef
// * Returns 0.0f if no duration is stored or if no sound is attached
//float GetStrRefSoundDuration(int nStrRef);

// 572: Add oPC to oPartyLeader's party.  This will only work on two PCs.
// - oPC: player to add to a party
// - oPartyLeader: player already in the party
//void AddToParty(object oPC, object oPartyLeader);

// 573: Remove oPC from their current party. This will only work on a PC.
// - oPC: removes this player from whatever party they're currently in.
//void RemoveFromParty(object oPC);

// 574: Adds a creature to the party
// Returns whether the addition was successful
// AddPartyMember
//int AddPartyMember(int nNPC, object oCreature);

// 575: Removes a creature from the party
// Returns whether the removal was syccessful
// RemovePartyMember
//int RemovePartyMember(int nNPC);

// 576: Returns whether a specified creature is a party member
// IsObjectPartyMember
//int IsObjectPartyMember(object oCreature);

// 577: Returns the party member at a given index in the party.
// The order of members in the party can vary based on
// who the current leader is (member 0 is always the current
// party leader).
// GetPartyMemberByIndex
//object GetPartyMemberByIndex(int nIndex);

// 578: GetGlobalBoolean
// This function returns the value of a global boolean (TRUE or FALSE) scripting variable.
//int GetGlobalBoolean( string sIdentifier );

// 579: SetGlobalBoolean
// This function sets the value of a global boolean (TRUE or FALSE) scripting variable.
//void SetGlobalBoolean( string sIdentifier, int nValue );

// 580: GetGlobalNumber
// This function returns the value of a global number (-128 to +127) scripting variable.
//int GetGlobalNumber( string sIdentifier );

// 581: SetGlobalNumber
// This function sets the value of a global number (-128 to +127) scripting variable.
//void SetGlobalNumber( string sIdentifier, int nValue );

// post a string to the screen at column nX and row nY for fLife seconds
// 582. AurPostString
//void AurPostString(string sString, int nX, int nY, float fLife);

// 583: OnAnimKey
// get the event and the name of the model on which the event happened
// SWMG_GetLastEvent
//string SWMG_GetLastEvent();

// 584: SWMG_GetLastEventModelName
//string SWMG_GetLastEventModelName();

// 585: gets an object by its name (duh!)
// SWMG_GetObjectByName
//object SWMG_GetObjectByName(string sName);

// 586: plays an animation on an object
// SWMG_PlayAnimation
//void SWMG_PlayAnimation(object oObject, string sAnimName, int bLooping=1, int bQueue=0, int bOverlay=0);

// 587: OnHitBullet
// get the damage, the target type (see TARGETflags), and the shooter
// SWMG_GetLastBulletHitDamage
//int SWMG_GetLastBulletHitDamage();

// 588: SWMG_GetLastBulletHitTarget
//int SWMG_GetLastBulletHitTarget();

// 589: SWMG_GetLastBulletHitShooter
//object SWMG_GetLastBulletHitShooter();

// 590: adjusts a followers hit points, can specify the absolute value to set to
// SWMG_AdjustFollowerHitPoints
//int SWMG_AdjustFollowerHitPoints(object oFollower, int nHP, int nAbsolute=0);

// 591: the default implementation of OnBulletHit
// SWMG_OnBulletHit
//void SWMG_OnBulletHit();

// 592: the default implementation of OnObstacleHit
// SWMG_OnObstacleHit
//void SWMG_OnObstacleHit();

// 593: returns the last follower and obstacle hit
// SWMG_GetLastFollowerHit
//object SWMG_GetLastFollowerHit();

// 594: SWMG_GetLastObstacleHit
//object SWMG_GetLastObstacleHit();

// 595: gets information about the last bullet fired
// SWMG_GetLastBulletFiredDamage
//int SWMG_GetLastBulletFiredDamage();

// 596: SWMG_GetLastBulletFiredTarget
//int SWMG_GetLastBulletFiredTarget();

// 597: gets an objects name
// SWMG_GetObjectName
//string SWMG_GetObjectName(object oid=OBJECT_SELF);

// 598: the default implementation of OnDeath
// SWMG_OnDeath
//void SWMG_OnDeath();

// 599: a bunch of Is functions for your pleasure
// SWMG_IsFollower
//int SWMG_IsFollower(object oid=OBJECT_SELF);

} // End of namespace KotOR

} // End of namespace Engines
