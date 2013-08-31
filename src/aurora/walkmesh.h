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

/** @file aurora/walkmeshfile.h
 *  Handling BioWare's walk meshes.
 */

#ifndef AURORA_WALKMESH_H
#define AURORA_WALKMESH_H

#include "aurora/types.h"

#include <memory>
#include <vector>
#include <array>

namespace Graphics {
	class Renderable;
}

typedef std::array<int, 3> Triangle;

namespace Aurora {

/** A WalkMesh */
class WalkMesh {
public:

	std::unique_ptr<Graphics::Renderable> getMesh() const;

	float _position[3];
	float _roomPosition[3];

	std::vector<Vector3> _vertices;
	std::vector<Vector3> _normals;
	std::vector<Triangle> _triangles;
};

} // End of namespace Aurora

#endif // AURORA_WALKMESH_H
