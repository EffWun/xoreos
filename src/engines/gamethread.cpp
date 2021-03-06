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

/** @file engines/gamethread.cpp
 *  The thread the game logic runs in.
 */

#include "common/version.h"
#include "common/util.h"
#include "common/error.h"
#include "common/configman.h"

#include "engines/gamethread.h"
#include "engines/enginemanager.h"

#include "graphics/graphics.h"

namespace Engines {

GameThread::GameThread() : _game(0) {
}

GameThread::~GameThread() {
	destroyThread();

	delete _game;
}

void GameThread::init(const Common::UString &baseDir) {
	// Detecting the game

	delete _game;
	_game = new GameInstance(baseDir);

	if (!EngineMan.probeGame(*_game))
		throw Common::Exception("Unable to detect the game");

	// Get the game description from the config, or alternatively
	// construct one from the game name and platform.
	Common::UString description;
	if (!ConfigMan.getKey("description", description))
		description = EngineMan.getGameName(*_game, true);

	GfxMan.setWindowTitle(Common::UString(XOREOS_NAMEVERSION) + " -- " + description);

	status("Detected game \"%s\"", EngineMan.getGameName(*_game, false).c_str());

	EngineMan.createEngine(*_game);
}

void GameThread::run() {
	if (!createThread())
		throw Common::Exception("Failed creating game logic thread");
}

void GameThread::threadMethod() {
	if (!_game)
		return;

	try {
		EngineMan.run(*_game);
	} catch (Common::Exception &e) {
		Common::printException(e);
	}

	delete _game;
	_game = 0;
}

} // End of namespace Engines
