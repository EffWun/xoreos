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

/** @file engines/kotor/room.h
 *  A room.
 */

#ifndef ENGINES_KOTOR_ROOM_H
#define ENGINES_KOTOR_ROOM_H

#include <memory>
#include <vector>

#include "aurora/lytfile.h"

namespace Graphics {
	class Renderable;
	namespace Aurora {
		class Model;
	}
}

namespace Aurora {
	class WalkMesh;
}

namespace Engines {

namespace KotOR {

/** A KotOR room. */
class Room {
public:
	void show();
	void hide();

	const Aurora::LYTFile::Room *lytRoom;
	std::unique_ptr<Aurora::WalkMesh> _walkMesh;

	std::unique_ptr<Graphics::Aurora::Model> _roomModel;
	std::unique_ptr<Graphics::Renderable> _walkMeshModel;

	bool visible;
	std::vector<Room *> visibles;

	explicit Room(const Aurora::LYTFile::Room &lRoom);
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_ROOM_H
