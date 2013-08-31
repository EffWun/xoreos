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

/** @file engines/kotor/room.cpp
 *  A room.
 */

#include "room.h"

#include "graphics/aurora/model.h"
#include "engines/aurora/model.h"

#include "aurora/error.h"
#include "aurora/resman.h"
#include "aurora/wokfile.h"
#include "aurora/walkmesh.h"

#include "common/stream.h"
#include "common/util.h"

#include <fstream>

namespace Aurora {

   std::ofstream* xxofs = 0;

}

namespace Engines {

namespace KotOR {

std::unique_ptr<Aurora::WalkMesh> loadWalkMesh(const Aurora::LYTFile::Room &lytRoom) {
	try {
	  std::unique_ptr<Common::SeekableReadStream> res(ResMan.getResource(lytRoom.model, Aurora::kFileTypeWOK));
		if (!res) throw Common::Exception("No such WOK");

	  Aurora::WOKFile wokFile;
	  Aurora::xxofs = new std::ofstream("c:\\tmp\\wok_" + std::string(lytRoom.model.c_str()) + ".txt");
	  wokFile.load(*res);
	  delete Aurora::xxofs;
	  auto ret = wokFile.get();
	  ret->_position[0] = lytRoom.x;
	  ret->_position[1] = lytRoom.y;
	  ret->_position[2] = lytRoom.z;
	  return std::move(ret);
	} catch (Common::Exception &e) {
		e.add("Failed loading WOK \"%s\"", lytRoom.model.c_str());
		throw;
	}
}

Room::Room(const Aurora::LYTFile::Room &lytRoom) :
	lytRoom(&lytRoom), visible(false) {

	 if (lytRoom.model == "****") {
		 // No model for that room
		 return;
	 }

	 _roomModel.reset(loadModelObject(lytRoom.model));
	 if (!_roomModel) throw Common::Exception("Can't load model for room \"%s\"", lytRoom.model.c_str());
	 _roomModel->setPosition(lytRoom.x, lytRoom.y, lytRoom.z);

	 _walkMesh = loadWalkMesh(lytRoom);
	 _walkMeshModel = _walkMesh->getMesh();
}

void Room::show() {
   _roomModel->show();
   _walkMeshModel->show();
}

void Room::hide() {
   _roomModel->hide();
   _walkMeshModel->hide();
}

} // End of namespace KotOR

} // End of namespace Engines
