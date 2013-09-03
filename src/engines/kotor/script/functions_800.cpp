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

/** @file engines/kotor/script/functions_800.cpp
 *  kotor script functions, 800-847.
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

void ScriptFunctions::registerFunctions800(const Defaults &d) {
	FunctionMan.registerFunction("GetPartyLeader", 845,
			boost::bind(&ScriptFunctions::getPartyLeader, this, _1),
			createSignature(1, kTypeObject));
}

void ScriptFunctions::getPartyLeader(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = _module->getPC();
}

// DJS-OEI 2/3/2004
// 800: Decreases the value of the given global number by the given amount.
// This function only works with Number type globals, not booleans. It
// will fail with a warning if the final amount is less than the minimum
// of -128.
//void DecrementGlobalNumber( string sIdentifier, int nAmount );

// RWT-OEI 02/06/04
// 801: SetBonusForcePoints - This sets the number of bonus force points
//      that will always be added to that character's total calculated
//      force points.
//void SetBonusForcePoints( object oCreature, int nBonusFP );

// RWT-OEI 02/06/04
// 802: AddBonusForcePoints - This adds nBonusFP to the current total
//      bonus that the player has. The Bonus Force Points are a pool
//      of force points that will always be added after the player's
//      total force points are calculated (based on level, force dice,
//      etc.)
//void AddBonusForcePoints( object oCreature, int nBonusFP );

// RWT-OEI 02/06/04
// 803: GetBonusForcePoints - This returns the total number of bonus
//      force points a player has. Bonus Force Points are a pool of
//      points that are always added to a player's Max Force Points.
//void GetBonusForcePoints( object oCreature );

// FAK - OEI 2/11/04
// 804: SWMG_SetJumpSpeed -- the sets the 'jump speed' for the swoop
//      bike races. Gravity will act upon this velocity.
//void SWMG_SetJumpSpeed(float fSpeed);

// PC CODE MERGER
// 805. IsMoviePlaying--dummy func so we can compile
//int IsMoviePlaying();

// 806 QueueMovie
//void QueueMovie(string sMovie, int nSkippable = TRUE);

// 807
//void PlayMovieQueue(int nAllowSkips = TRUE);

// 808
//void YavinHackDoorClose(object oCreature);

// 809
// new function for droid confusion so inherint mind immunity can be
// avoided.
//effect EffectDroidConfused();
// END PC CODE MERGER

// 810
// DJS-OEI 3/8/2004
// Determines if the given creature is in Stealth mode or not.
// 0 = Creature is not stealthed.
// 1 = Creature is stealthed.
// This function will return 0 for any non-creature.
//int IsStealthed( object oCreature );

// 811
// DJS-OEI 3/12/2004
// Determines if the given creature is using any Meditation Tree
// Force Power.
// 0 = Creature is not meditating.
// 1 = Creature is meditating.
// This function will return 0 for any non-creature.
//int IsMeditating( object oCreature );

// 812
// DJS-OEI 3/16/2004
// Determines if the given creature is using the Total Defense
// Stance.
// 0 = Creature is not in Total Defense.
// 1 = Creature is in Total Defense.
// This function will return 0 for any non-creature.
//int IsInTotalDefense( object oCreature );

// 813
// RWT-OEI 03/19/04
// Stores a Heal Target for the Healer AI script. Should probably
// not be used outside of the Healer AI script.
//void SetHealTarget( object oidHealer, object oidTarget );

// 814
// RWT-OEI 03/19/04
// Retrieves the Heal Target for the Healer AI script. Should probably
// not be used outside of the Healer AI script.
//object GetHealTarget( object oidHealer );

// 815
// RWT-OEI 03/23/04
// Returns a vector containing a random destination that the
// given creature can walk to that's within the range of the
// passed parameter.
//vector GetRandomDestination( object oCreature, int rangeLimit );

// 816
// DJS-OEI 3/25/2004
// Returns whether the given creature is currently in the
// requested Lightsaber/Consular Form and can make use of
// its benefits. This function will perform trumping checks
// and lightsaber-wielding checks for those Forms that require
// them.
//int IsFormActive( object oCreature, int nFormID );

// 817
// DJS-OEI 3/28/2004
// Returns the Form Mask of the requested spell. This is used
// to determine if a spell is affected by various Forms, usually
// Consular forms that modify duration/range.
//int GetSpellFormMask( int nSpellID );

// 818
// DJS-OEI 3/29/2004
// Return the base number of Force Points required to cast
// the given spell. This does not take into account modifiers
// of any kind.
//int GetSpellBaseForcePointCost( int nSpellID );

// 819
// RWT-OEI 04/05/04
// Setting this to TRUE makes it so that the Stealth status is
// left on characters even when entering cutscenes. By default,
// stealth is removed from anyone taking part in a cutscene.
// ALWAYS set this back to FALSE on every End Dialog node in
// the cutscene you wanted to stay stealthed in. This isn't a
// flag that should be left on indefinitely. In fact, it isn't
// saved, so needs to be set/unset on a case by case basis.
//void SetKeepStealthInDialog( int nStealthState );

// 820
// RWT-OEI 04/06/04
// This returns TRUE or FALSE if there is a clear line of sight from
// the source vector to the target vector. This is used in the AI to
// help the creatures using ranged weapons find better places to shoot
// when the player moves out of sight.
//int HasLineOfSight( vector vSource, vector vTarget, object oSource = OBJECT_INVALID, object oTarget = OBJECT_INVALID );

// 821
// FAK - OEI 5/3/04
// ShowDemoScreen, displays a texture, timeout, string and xy for string
//int ShowDemoScreen(string sTexture, int nTimeout, int nDisplayString, int nDisplayX, int nDisplayY );

// 822
// DJS-OEI 5/4/2004
// Forces a Heartbeat on the given creature. THIS ONLY WORKS FOR CREATURES
// AT THE MOMENT. This heartbeat should force perception updates to occur.
//void ForceHeartbeat( object oCreature );

// 823
// DJS-OEI 5/5/2004
// Creates a Force Sight effect.
//effect EffectForceSight();

// 824
// FAK - OEI 5/7/04
// gets the walk state of the creature: 0 walk or standing, 1 is running
//int IsRunning( object oCreature );

// 825
// FAK - OEI 5/24/04
// applies a velocity to the player object
//void SWMG_PlayerApplyForce(vector vForce);

// 826
// DJS-OEI 6/12/2004
// This function allows a script to set the conditions which constitute
// a combat forfeit by a member of the player's party. This is typically
// used to handle Battle Circle behavior or other challenge-based combats.
// nForfeitFlags: This is an OR'ed together series of FORFEIT_* defines.
//void SetForfeitConditions( int nForfeitFlags );

// 827
// DJS-OEI 6/12/2004
// This function returns the last FORFEIT_* condition that the player
// has violated.
//int GetLastForfeitViolation();

// 828
// AWD-OEI 6/21/2004
// This function does not return a value.
// This function modifies the BASE value of the REFLEX saving throw for aObject
//void ModifyReflexSavingThrowBase(object aObject, int aModValue);

// 829
// AWD-OEI 6/21/2004
// This function does not return a value.
// This function modifies the BASE value of the FORTITUDE saving throw for aObject
//void ModifyFortitudeSavingThrowBase(object aObject, int aModValue);

// 830
// AWD-OEI 6/21/2004
// This function does not return a value.
// This function modifies the BASE value of the WILL saving throw for aObject
//void ModifyWillSavingThrowBase(object aObject, int aModValue);

// DJS-OEI 6/21/2004
// 831
// This function will return the one CExoString parameter
// allowed for the currently running script.
//string GetScriptStringParameter();

// 832
// AWD-OEI 6/29/2004
// This function returns the personal space value of an object
//float GetObjectPersonalSpace(object aObject);

// 833
// AWD-OEI 7/06/2004
// This function adjusts a creatures stats.
// oObject is the creature that will have it's attribute adjusted
// The following constants are acceptable for the nAttribute parameter:
// ABILITY_STRENGTH
// ABILITY_DEXTERITY
// ABILITY_CONSTITUTION
// ABILITY_INTELLIGENCE
// ABILITY_WISDOM
// ABILITY_CHARISMA
// nAmount is the integer vlaue to adjust the stat by (negative values will work).
//void AdjustCreatureAttributes(object oObject, int nAttribute, int nAmount);

// 834
// AWD-OEI 7/08/2004
// This function raises a creature's priority level.
//void SetCreatureAILevel(object oObject, int nPriority);

// 835
// AWD-OEI 7/08/2004
// This function raises a creature's priority level.
//void ResetCreatureAILevel(object oObject);

// 836
// RWT-OEI 07/17/04
// This function adds a Puppet to the Puppet Table by
// template.
// Returns 1 if successful, 0 if there was an error
// This does not spawn the puppet or anything. It just
// adds it to the party table and makes it available for
// use down the line. Exactly like AddAvailableNPCByTemplate
//int AddAvailablePUPByTemplate( int nPUP, string sTemplate );

// 837
// RWT-OEI 07/17/04
// This function adds a Puppet to the Puppet Table by
// creature ID
// Returns 1 if successful, 0 if there was an error
// This does not spawn the puppet or anything. It just
// adds it to the party table and makes it available for
// use down the line. Exactly like AddAvailableNPCByTemplate
//int AddAvailablePUPByObject( int nPUP, object oPuppet );

// 838
// RWT-OEI 07/17/04
// This function assigns a PUPPET constant to a
// Party NPC.  The party NPC -MUST- be in the game
// before calling this.
// Both the PUP and the NPC have
// to be available in their respective tables
// Returns 1 if successful, 0 if there was an error
//int AssignPUP( int nPUP, int nNPC );

// 839
// RWT-OEI 07/17/04
// This function spawns a Party PUPPET.
// This must be used whenever you want a copy
// of the puppet around to manipulate in the game
// since the puppet is stored in the party table
// just like NPCs are.  Once a puppet is assigned
// to a party NPC (see AssignPUP), it will spawn
// or disappear whenever its owner joins or leaves
// the party.
// This does not add it to the party automatically,
// just like SpawnNPC doesn't. You must call AddPuppet()
// to actually add it to the party
//object SpawnAvailablePUP( int nPUP, location lLocation );

// 840
// RWT-OEI 07/18/04
// This adds an existing puppet object to the party. The
// puppet object must already exist via SpawnAvailablePUP
// and must already be available via AddAvailablePUP*
// functions.
//int AddPartyPuppet(int nPUP, object oidCreature);

// 841
// RWT-OEI 07/19/04
// This returns the object ID of the puppet's owner.
// The Puppet's owner must exist and must be in the party
// in order to be found.
// Returns invalid object Id if the owner cannot be found.
//object GetPUPOwner(object oPUP = OBJECT_SELF);

// 842
// RWT-OEI 07/19/04
// Returns 1 if the creature is a Puppet in the party.
// Otherwise returns 0. It is possible for a 'party puppet'
// to exist without actually being in the party table.
// such as when SpawnAvailablePUP is used without subsequently
// using AddPartyPuppet to add the newly spawned puppet to
// the party table. A puppet in that in-between state would
// return 0 from this function
//int GetIsPuppet(object oPUP = OBJECT_SELF );

// 843
// RWT-OEI 07/20/04
// Similiar to ActionFollowLeader() except the creature
// follows its owner
//nRange is how close it should follow. Note that once this
//action is queued, it will be the only thing this creature
//does until a ClearAllActions() is used.
//void ActionFollowOwner(float fRange = 2.5);

// 844
// RWT-OEI 07/21/04
// Returns TRUE if the object ID passed is the character
// that the player is actively controlling at that point.
// Note that this function is *NOT* able to return correct
// information during Area Loading since the player is not
// actively controlling anyone at that point.
//int GetIsPartyLeader(object oCharacter = OBJECT_SELF);

// 845
// RWT-OEI 07/21/04
// Returns the object ID of the character that the player
// is actively controlling. This is the 'Party Leader'.
// Returns object Invalid on error
// Note that this function is *NOT* able to return correct
// information during Area Loading since the player is not
// actively controlling anyone at that point.
//object GetPartyLeader();

// 846
// JAB-OEI 07/22/04
// Will remove the CNPC from the 3 person party, and remove
// him/her from the area, effectively sending the CNPC back
// to the base. The CNPC data is still stored in the
// party table, and calling this function will not destroy
// the CNPC in any way.
// Returns TRUE for success.
//int RemoveNPCFromPartyToBase(int nNPC);

// 847
// AWD-OEI 7/22/2004
// This causes a creature to flourish with it's currently equipped weapon.
//void CreatureFlourishWeapon(object oObject);

// 848
// Create a Mind Trick effect
//effect EffectMindTrick();

// 849
// Create a Faction Modifier effect.
//effect EffectFactionModifier( int nNewFaction );

// 850
// ChangeObjectAppearance
// oObjectToChange = Object to change appearance of
// nAppearance = appearance to change to (from appearance.2da)
//void ChangeObjectAppearance( object oObjectToChange, int nAppearance );

// 851
// GetIsXBox
// Returns TRUE if this script is being executed on the X-Box. Returns FALSE
// if this is the PC build.
//int GetIsXBox();

// 852
// Create a Droid Scramble effect
//effect EffectDroidScramble();

// 853
// ActionSwitchWeapons
// Forces the creature to switch between Config 1 and Config 2
// of their equipment. Does not work in dialogs. Works with
// AssignCommand()
//void ActionSwitchWeapons();

// 854
// DJS-OEI 8/29/2004
// PlayOverlayAnimation
// This function will play an overlay animation on a character
// even if the character is moving. This does not cause an action
// to be placed on the queue. The animation passed in must be
// designated as an overlay in Animations.2DA.
//void PlayOverlayAnimation( object oTarget, int nAnimation );

// 855
// RWT-OEI 08/30/04
// UnlockAllSongs
// Calling this will set all songs as having been unlocked.
// It is INTENDED to be used in the end-game scripts to unlock
// any end-game songs as well as the KotOR1 sound track.
//void UnlockAllSongs();

// 856
// RWT-OEI 08/31/04
// Passing TRUE into this function turns off the player's maps.
// Passing FALSE into this function re-enables them. This change
// is permanent once called, so it is important that there *is*
// a matching call to DisableMap(FALSE) somewhere or else the
// player is stuck without a map indefinitely.
//void DisableMap(int nFlag = FALSE);

// 857
// RWT-OEI 08/31/04
// This function schedules a mine to play its DETONATION
// animation once it is destroyed. Note that this detonates
// the mine immediately but has nothing to do with causing
// the mine to do any damage to anything around it. To
// get the mine to damage things around it when it detonates
// do:
// AssignCommand(<mine>,ExecuteScript( "k_trp_generic",<mine>));
// right before you call DetonateMine(). By my experience so far
// you don't need any kind of delay between the two.
//void DetonateMine(object oMine);

// 858
// RWT-OEI 09/06/04
// This function turns off the innate health regeneration that all party
// members have. The health regen will *stay* off until it is turned back
// on by passing FALSE to this function.
//void DisableHealthRegen(int nFlag = FALSE);

// 859
// DJS-OEI 9/7/2004
// This function sets the current Jedi Form on the given creature. This
// call will do nothing if the target does not know the Form itself.
//void SetCurrentForm( object oCreature, int nFormID );

// 860
// RWT-OEI 09/09/04
// This will disable or enable area transit
//void SetDisableTransit(int nFlag = FALSE);

// 861
//RWT-OEI 09/09/04
// This will set the specific input class.
// The valid options are:
// 0 - Normal PC control
// 1 - Mini game control
// 2 - GUI control
// 3 - Dialog Control
// 4 - Freelook control
//void SetInputClass(int nClass);

// 862
//RWT-OEI 09/15/04
// This script allows an object to recieve updates even if it is outside
//the normal range limit of 250.0f meters away from the player. This should
//ONLY be used for cutscenes that involve objects that are more than 250
//meters away from the player. It needs to be used on a object by object
//basis.
//This flag should *always* be set to false once the cutscene it is needed
//for is over, or else the game will spend CPU time updating the object
//when it doesn't need to.
//For questions on use of this function, or what its purpose is, check
//with me.
//void SetForceAlwaysUpdate(object oObject, int nFlag);

//863
//RWT-OEI 09/15/04
//This function enables or disables rain
//void EnableRain( int nFlag );

//864
//RWT-OEI 09/27/04
//This function displays the generic Message Box with the strref
//message in it
//sIcon is the resref for an icon you would like to display.
//void DisplayMessageBox(int nStrRef, string sIcon = "");

//865
//RWT-OEI 09/28/04
//This function displays a datapad popup. Just pass it the
//object ID of a datapad.
//void DisplayDatapad(object oDatapad);

// 866
// CTJ-OEI 09-29-04
// Removes the heartbeat script on the placeable.  Useful for
// placeables whose contents get populated in the heartbeat
// script and then the heartbeat no longer needs to be called.
//void RemoveHeartbeat(object oPlaceable);


//867
// JF-OEI 10-07-2004
// Remove an effect by ID
//void RemoveEffectByID( object oCreature, int nEffectID );

//868
// RWT-OEI 10/07/04
// This script removes an effect by an identical match
// based on:
// Must have matching EffectID types.
// Must have the same value in Integer(0)
// Must have the same value in Integer(1)
// I'm specifically using this function for Mandalore's implant swapping
// script and it will probably not be useful for anyone else. If you're
// not sure what this script function does, see me before using it.
//void RemoveEffectByExactMatch( object oCreature, effect eEffect);

// 869
// DJS-OEI 10/9/2004
// This function adjusts a creature's skills.
// oObject is the creature that will have its skill adjusted
// The following constants are acceptable for the nSkill parameter:
// SKILL_COMPUTER_USE
// SKILL_DEMOLITIONS
// SKILL_STEALTH
// SKILL_AWARENESS
// SKILL_PERSUADE
// SKILL_REPAIR
// SKILL_SECURITY
// SKILL_TREAT_INJURY
// nAmount is the integer value to adjust the stat by (negative values will work).
//void AdjustCreatureSkills(object oObject, int nSkill, int nAmount);

// 870
// DJS-OEI 10/10/2004
// This function returns the base Skill Rank for the requested
// skill. It does not include modifiers from effects/items.
// The following constants are acceptable for the nSkill parameter:
// SKILL_COMPUTER_USE
// SKILL_DEMOLITIONS
// SKILL_STEALTH
// SKILL_AWARENESS
// SKILL_PERSUADE
// SKILL_REPAIR
// SKILL_SECURITY
// SKILL_TREAT_INJURY
// oObject is the creature that will have its skill base returned.
//int GetSkillRankBase(int nSkill, object oObject=OBJECT_SELF);

// 871
// DJS-OEI 10/15/2004
// This function will allow the caller to modify the rendering behavior
// of the target object.
// oObject - The object to change rendering state on.
// bEnable - If 0, the object will stop rendering. Else, the object will render.
//void EnableRendering( object oObject, int bEnable );

// 872
// RWT-OEI 10/19/04
// This function returns TRUE if the creature has actions in its
// Combat Action queue.
//int GetCombatActionsPending(object oCreature);

// 873
// RWT-OEI 10/26/04
// This function saves the party member at that index with the object
// that is passed in.
//void SaveNPCByObject( int nNPC, object oidCharacter);

// 874
// RWT-OEI 10/26/04
// This function saves the party puppet at that index with the object
// that is passed in. For the Remote, just use '0' for nPUP
//void SavePUPByObject( int nPUP, object oidPuppet );

// 875
// RWT-OEI 10/29/04
// Returns TRUE if the object passed in is the character that the player
// made at the start of the game
//int GetIsPlayerMadeCharacter(object oidCharacter);

// 876
// RWT-OEI 11/12/04
// This repopulates the NPCObject table in CSWPartyTable. Do not use this
// unless you understand exactly what it is doing.
//void RebuildPartyTable();

} // End of namespace KotOR

} // End of namespace Engines
