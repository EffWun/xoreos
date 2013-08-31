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

/** @file aurora/wokfile.h
 *  Handling BioWare's WOKs (Layout files).
 */

#ifndef AURORA_WOKFILE_H
#define AURORA_WOKFILE_H

#include <vector>
#include <memory>
#include <array>

#include "common/types.h"
#include "common/ustring.h"

#include "aurora/types.h"

namespace Common {
	class SeekableReadStream;
}

typedef std::array<int, 3> Triangle;

namespace Aurora {

class WalkMesh;

/** An WOK, BioWare's Walk Mesh Format. */
class WOKFile {
public:

	/** Load a WOK file.
	 *
	 *  @param lyt A stream of an WOK file.
	 */
	void load(Common::SeekableReadStream &lyt);
   std::unique_ptr<WalkMesh> get();

   float _position[3];
   std::vector<Vector3> _vertices;
   std::vector<Vector3> _normals;
   std::vector<Triangle> _triangles;
};

} // End of namespace Aurora

#endif // AURORA_WOKFILE_H
