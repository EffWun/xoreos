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

/** @file engines/kotor/script/functions_600.cpp
 *  kotor script functions, 600-699.
 */

#include <boost/bind.hpp>

#include "common/util.h"
#include "common/error.h"

#include "aurora/talkman.h"

#include "aurora/nwscript/types.h"
#include "aurora/nwscript/util.h"
#include "aurora/nwscript/functioncontext.h"
#include "aurora/nwscript/functionman.h"

#include "engines/kotor/types.h"
#include "engines/kotor/object.h"
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

void ScriptFunctions::registerFunctions600(const Defaults &d) {
	FunctionMan.registerFunction("GetLocalBoolean", 679,
			boost::bind(&ScriptFunctions::getLocalBoolean, this, _1),
			createSignature(3, kTypeInt, kTypeObject, kTypeString));
	FunctionMan.registerFunction("SetLocalBoolean", 680,
			boost::bind(&ScriptFunctions::setLocalBoolean, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeInt));
	FunctionMan.registerFunction("GetLocalNumber", 681,
			boost::bind(&ScriptFunctions::getLocalNumber, this, _1),
			createSignature(3, kTypeInt, kTypeObject, kTypeString));
	FunctionMan.registerFunction("SetLocalNumber", 682,
			boost::bind(&ScriptFunctions::setLocalNumber, this, _1),
			createSignature(4, kTypeVoid, kTypeObject, kTypeString, kTypeInt));
}

// 679. GetLocalBoolean
// This gets a boolean flag on an object
// currently the index is a range between 20 and 63
void ScriptFunctions::getLocalBoolean(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Aurora::NWScript::Object *object = params[0].getObject();
	if (object) {
		bool val = object->getVariable(params[1].getInt(), kTypeInt).getInt() != 0;
		ctx.getReturn() = static_cast<int>(val);
    }
}

// 680. SetLocalBoolean
// This sets a boolean flag on an object
// currently the index is a range between 20 and 63
void ScriptFunctions::setLocalBoolean(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Aurora::NWScript::Object *object = params[0].getObject();
	if (object) {
		bool val = params[2].getInt() != 0;
		object->setVariable(params[1].getInt(), static_cast<int>(val));
    }
}

// 681. GetLocalNumber
// This gets a number on an object
// currently the index is a range between 12 and 28
// int GetLocalNumber( object oObject, int nIndex );
void ScriptFunctions::getLocalNumber(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Aurora::NWScript::Object *object = params[0].getObject();
	if (object) {
		ctx.getReturn() = object->getVariable(params[1].getInt(), kTypeInt).getInt();
    }
}

// 682. SetLocalNumber
// This sets a number on an object
// currently the index is a range between 12 and 28
// the value range is 0 to 255
// void SetLocalNumber( object oObject, int nIndex, int nValue );
void ScriptFunctions::setLocalNumber(Aurora::NWScript::FunctionContext &ctx) {
	const Aurora::NWScript::Parameters &params = ctx.getParams();

	Aurora::NWScript::Object *object = params[0].getObject();
	if (object) {
		object->setVariable(params[1].getInt(), params[2].getInt());
    }
}
// 600: SWMG_IsPlayer
//int SWMG_IsPlayer(object oid=OBJECT_SELF);

// 601: SWMG_IsEnemy
//int SWMG_IsEnemy(object oid=OBJECT_SELF);

// 602: SWMG_IsTrigger
//int SWMG_IsTrigger(object oid=OBJECT_SELF);

// 603: SWMG_IsObstacle
//int SWMG_IsObstacle(object oid=OBJECT_SELF);

// 604: SWMG_SetFollowerHitPoints
//void SWMG_SetFollowerHitPoints(object oFollower, int nHP);

// 605: SWMG_OnDamage
//void SWMG_OnDamage();

// 606: SWMG_GetLastHPChange
//int SWMG_GetLastHPChange();

// 607: SWMG_RemoveAnimation
//void SWMG_RemoveAnimation(object oObject, string sAnimName);

// 608: SWMG_GetCameraNearClip
//float SWMG_GetCameraNearClip();

// 609: SWMG_GetCameraFarClip
//float SWMG_GetCameraFarClip();

// 610: SWMG_SetCameraClip
//void SWMG_SetCameraClip(float fNear, float fFar);

// 611: SWMG_GetPlayer
//object SWMG_GetPlayer();

// 612: SWMG_GetEnemyCount
//int SWMG_GetEnemyCount();

// 613: SWMG_GetEnemy
//object SWMG_GetEnemy(int nEntry);

// 614: SWMG_GetObstacleCount
//int SWMG_GetObstacleCount();

// 615: SWMG_GetObstacle
//object SWMG_GetObstacle(int nEntry);

// 616: SWMG_GetHitPoints
//int SWMG_GetHitPoints(object oFollower);

// 617: SWMG_GetMaxHitPoints
//int SWMG_GetMaxHitPoints(object oFollower);

// 618: SWMG_SetMaxHitPoints
//void SWMG_SetMaxHitPoints(object oFollower, int nMaxHP);

// 619: SWMG_GetSphereRadius
//float SWMG_GetSphereRadius(object oFollower);

// 620: SWMG_SetSphereRadius
//void SWMG_SetSphereRadius(object oFollower, float fRadius);

// 621: SWMG_GetNumLoops
//int SWMG_GetNumLoops(object oFollower);

// 622: SWMG_SetNumLoops
//void SWMG_SetNumLoops(object oFollower, int nNumLoops);

// 623: SWMG_GetPosition
//vector SWMG_GetPosition(object oFollower);

// 624: SWMG_GetGunBankCount
//int SWMG_GetGunBankCount(object oFollower);

// 625: SWMG_GetGunBankBulletModel
//string SWMG_GetGunBankBulletModel(object oFollower, int nGunBank);

// 626: SWMG_GetGunBankGunModel
//string SWMG_GetGunBankGunModel(object oFollower, int nGunBank);

// 627: SWMG_GetGunBankDamage
//int SWMG_GetGunBankDamage(object oFollower, int nGunBank);

// 628: SWMG_GetGunBankTimeBetweenShots
//float SWMG_GetGunBankTimeBetweenShots(object oFollower, int nGunBank);

// 629: SWMG_GetGunBankLifespan
//float SWMG_GetGunBankLifespan(object oFollower, int nGunBank);

// 630: SWMG_GetGunBankSpeed
//float SWMG_GetGunBankSpeed(object oFollower, int nGunBank);

// 631: SWMG_GetGunBankTarget
//int SWMG_GetGunBankTarget(object oFollower, int nGunBank);

// 632: SWMG_SetGunBankBulletModel
//void SWMG_SetGunBankBulletModel(object oFollower, int nGunBank, string sBulletModel);

// 633: SWMG_SetGunBankGunModel
//void SWMG_SetGunBankGunModel(object oFollower, int nGunBank, string sGunModel);

// 634: SWMG_SetGunBankDamage
//void SWMG_SetGunBankDamage(object oFollower, int nGunBank, int nDamage);

// 635: SWMG_SetGunBankTimeBetweenShots
//void SWMG_SetGunBankTimeBetweenShots(object oFollower, int nGunBank, float fTBS);

// 636: SWMG_SetGunBankLifespan
//void SWMG_SetGunBankLifespan(object oFollower, int nGunBank, float fLifespan);

// 637: SWMG_SetGunBankSpeed
//void SWMG_SetGunBankSpeed(object oFollower, int nGunBank, float fSpeed);

// 638: SWMG_SetGunBankTarget
//void SWMG_SetGunBankTarget(object oFollower, int nGunBank, int nTarget);

// 639: SWMG_GetLastBulletHitPart
//string SWMG_GetLastBulletHitPart();

// 640: SWMG_IsGunBankTargetting
//int SWMG_IsGunBankTargetting(object oFollower, int nGunBank);

// 641: SWMG_GetPlayerOffset
// returns a vector with the player rotation for rotation minigames
// returns a vector with the player translation for translation minigames
//vector SWMG_GetPlayerOffset();

// 642: SWMG_GetPlayerInvincibility
//float SWMG_GetPlayerInvincibility();

// 643: SWMG_GetPlayerSpeed
//float SWMG_GetPlayerSpeed();

// 644: SWMG_GetPlayerMinSpeed
//float SWMG_GetPlayerMinSpeed ();

// 645: SWMG_GetPlayerAccelerationPerSecond
//float SWMG_GetPlayerAccelerationPerSecond();

// 646: SWMG_GetPlayerTunnelPos
//vector SWMG_GetPlayerTunnelPos();

// 647: SWMG_SetPlayerOffset
//void SWMG_SetPlayerOffset(vector vOffset);

// 648: SWMG_SetPlayerInvincibility
//void SWMG_SetPlayerInvincibility(float fInvincibility);

// 649: SWMG_SetPlayerSpeed
//void SWMG_SetPlayerSpeed(float fSpeed);

// 650: SWMG_SetPlayerMinSpeed
//void SWMG_SetPlayerMinSpeed(float fMinSpeed);

// 651: SWMG_SetPlayerAccelerationPerSecond
//void SWMG_SetPlayerAccelerationPerSecond(float fAPS);

// 652: SWMG_SetPlayerTunnelPos
//void SWMG_SetPlayerTunnelPos(vector vTunnel);

// 653: SWMG_GetPlayerTunnelNeg
//vector SWMG_GetPlayerTunnelNeg();

// 654: SWMG_SetPlayerTunnelNeg
//void SWMG_SetPlayerTunnelNeg(vector vTunnel);

// 655: SWMG_GetPlayerOrigin
//vector SWMG_GetPlayerOrigin();

// 656: SWMG_SetPlayerOrigin
//void SWMG_SetPlayerOrigin(vector vOrigin);

// 657: SWMG_GetGunBankHorizontalSpread
//float SWMG_GetGunBankHorizontalSpread(object oEnemy, int nGunBank);

// 658: SWMG_GetGunBankVerticalSpread
//float SWMG_GetGunBankVerticalSpread(object oEnemy, int nGunBank);

// 659: SWMG_GetGunBankSensingRadius
//float SWMG_GetGunBankSensingRadius(object oEnemy, int nGunBank);

// 660: SWMG_GetGunBankInaccuracy
//float SWMG_GetGunBankInaccuracy(object oEnemy, int nGunBank);

// 661: SWMG_SetGunBankHorizontalSpread
//void SWMG_SetGunBankHorizontalSpread(object oEnemy, int nGunBank, float fHorizontalSpread);

// 662: SWMG_SetGunBankVerticalSpread
//void SWMG_SetGunBankVerticalSpread(object oEnemy, int nGunBank, float fVerticalSpread);

// 663: SWMG_SetGunBankSensingRadius
//void SWMG_SetGunBankSensingRadius(object oEnemy, int nGunBank, float fSensingRadius);

// 664: SWMG_SetGunBankInaccuracy
//void SWMG_SetGunBankInaccuracy(object oEnemy, int nGunBank, float fInaccuracy);

// 665: GetIsInvulnerable
// This returns whether the follower object is currently invulnerable to damage
//int SWMG_GetIsInvulnerable( object oFollower );

// 666: StartInvulnerability
// This will begin a period of invulnerability (as defined by Invincibility)
//void SWMG_StartInvulnerability( object oFollower );

// 667: GetPlayerMaxSpeed
// This returns the player character's max speed
//float SWMG_GetPlayerMaxSpeed();

// 668: SetPlayerMaxSpeed
// This sets the player character's max speed
//void SWMG_SetPlayerMaxSpeed( float fMaxSpeed );

// 669: AddJournalWorldEntry
// Adds a user entered entry to the world notices
//void AddJournalWorldEntry( int nIndex, string szEntry, string szTitle = "World Entry" );

// 670: AddJournalWorldEntryStrref
// Adds an entry to the world notices using stringrefs
//void AddJournalWorldEntryStrref ( int strref, int strrefTitle );

// 671: BarkString
// this will cause a creature to bark the strRef from the talk table
// If creature is specefied as OBJECT_INVALID a general bark is made.
//void BarkString(object oCreature,int strRef, int nBarkX = -1, int nBarkY = -1);

// 672: DeleteJournalWorldAllEntries
// Nuke's 'em all, user entered or otherwise.
//void DeleteJournalWorldAllEntries();

// 673: DeleteJournalWorldEntry
// Deletes a user entered world notice
//void DeleteJournalWorldEntry( int nIndex );

// 674: DeleteJournalWorldEntryStrref
// Deletes the world notice pertaining to the string ref
//void DeleteJournalWorldEntryStrref( int strref );

// 675: EffectForceDrain
// This command will reduce the force points of a creature.
//effect EffectForceDrain( int nDamage );

// 676: EffectTemporaryForcePoints

//effect EffectPsychicStatic();

// 677: PlayVisualAreaEffect
//void PlayVisualAreaEffect(int nEffectID, location lTarget);

// 678: SetJournalQuestEntryPicture
// Sets the picture for the quest entry on this object (creature)
//void SetJournalQuestEntryPicture(string szPlotID, object oObject, int nPictureIndex, int bAllPartyMemebers=TRUE, int bAllPlayers=FALSE);

// 679. GetLocalBoolean
// This gets a boolean flag on an object
// currently the index is a range between 20 and 63
//int GetLocalBoolean( object oObject, int nIndex );

// 680. SetLocalBoolean
// This sets a boolean flag on an object
// currently the index is a range between 20 and 63
//void SetLocalBoolean( object oObject, int nIndex, int nValue );

// 681. GetLocalNumber
// This gets a number on an object
// currently the index is a range between 12 and 28
//int GetLocalNumber( object oObject, int nIndex );

// 682. SetLocalNumber
// This sets a number on an object
// currently the index is a range between 12 and 28
// the value range is 0 to 255
//void SetLocalNumber( object oObject, int nIndex, int nValue );

// 683. SWMG_GetSoundFrequency
// Gets the frequency of a trackfollower sound
//int SWMG_GetSoundFrequency( object oFollower, int nSound );

// 684. SWMG_SetSoundFrequency
// Sets the frequency of a trackfollower sound
//void SWMG_SetSoundFrequency( object oFollower, int nSound, int nFrequency );

// 685. SWMG_GetSoundFrequencyIsRandom
// Gets whether the frequency of a trackfollower sound is using the random model
//int SWMG_GetSoundFrequencyIsRandom( object oFollower, int nSound );

// 686. SWMG_SetSoundFrequencyIsRandom
// Sets whether the frequency of a trackfollower sound is using the random model
//void SWMG_SetSoundFrequencyIsRandom( object oFollower, int nSound, int bIsRandom );

// 687. SWMG_GetSoundVolume
// Gets the volume of a trackfollower sound
//int SWMG_GetSoundVolume( object oFollower, int nSound );

// 688. SWMG_SetSoundVolume
// Sets the volume of a trackfollower sound
//void SWMG_SetSoundVolume( object oFollower, int nSound, int nVolume );

// 689. SoundObjectGetPitchVariance
// Gets the pitch variance of a placeable sound object
//float SoundObjectGetPitchVariance( object oSound );

// 690. SoundObjectSetPitchVariance
// Sets the pitch variance of a placeable sound object
//void SoundObjectSetPitchVariance( object oSound, float fVariance );

// 691. SoundObjectGetVolume
// Gets the volume of a placeable sound object
//int SoundObjectGetVolume( object oSound );

// 692: GetGlobalLocation
// This function returns the a global location scripting variable.
//location GetGlobalLocation( string sIdentifier );

// 693: SetGlobalLocation
// This function sets the a global location scripting variable.
//void SetGlobalLocation( string sIdentifier, location lValue );

// 694. AddAvailableNPCByObject
// This adds a NPC to the list of available party members using
// a game object as the template
// Returns if true if successful, false if the NPC had already
// been added or the object specified is invalid
//int AddAvailableNPCByObject( int nNPC, object oCreature );

// 695. RemoveAvailableNPC
// This removes a NPC from the list of available party members
// Returns whether it was successful or not
//int RemoveAvailableNPC( int nNPC );

// 696. IsAvailableNPC
// This returns whether a NPC is in the list of available party members
//int IsAvailableCreature( int nNPC );

// 697. AddAvailableNPCByTemplate
// This adds a NPC to the list of available party members using
// a template
// Returns if true if successful, false if the NPC had already
// been added or the template specified is invalid
//int AddAvailableNPCByTemplate( int nNPC, string sTemplate );

// 698. SpawnAvailableNPC
// This spawns a NPC from the list of available creatures
// Returns a pointer to the creature object
//object SpawnAvailableNPC( int nNPC, location lPosition );

// 699. IsNPCPartyMember
// Returns if a given NPC constant is in the party currently
//int IsNPCPartyMember( int nNPC );

} // End of namespace KotOR

} // End of namespace Engines
