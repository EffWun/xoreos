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

/** @file aurora/walkmesh.cpp
 *  Handling BioWare's walk meshes.
 */

#include "aurora/walkmesh.h"
#include "graphics/renderable.h"
#include "graphics/camera.h"

#include "common/matrix.h"
#include "common/util.h"

#include <utility>

namespace Aurora {

void vertex(const Vector3& v) {
	glVertex3f(v.x, v.y, v.z);
}

void normal(const Vector3& n) {
	glNormal3f(n.x, n.y, n.z);
}

class DebugRenderable : public Graphics::Renderable {
public:
	DebugRenderable() : Renderable(Graphics::kRenderableTypeObject) {}

	float _position[3];
	float _roomPosition[3];
	std::vector<Vector3> _vertices;
	std::vector<Vector3> _normals;
	std::vector<Triangle> _triangles;

	void calculateDistance() override {
		const float cameraX =  CameraMan.getPosition()[0];
		const float cameraY =  CameraMan.getPosition()[1];
		const float cameraZ = -CameraMan.getPosition()[2];

		const float x = ABS(_position[0] - cameraX);
		const float y = ABS(_position[1] - cameraY);
		const float z = ABS(_position[2] - cameraZ);


		_distance = x + y + z;
	}

	void render(Graphics::RenderPass pass) override {
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glTranslatef(_roomPosition[0], _roomPosition[1], _roomPosition[2]);
		// glTranslatef(_position[0], _position[1], _position[2]);

		glColor3f(0.6f, 0.0f, 0.0f);

		glBegin(GL_TRIANGLES);

		for (auto i = _triangles.begin(); i != _triangles.end(); ++i) {
			vertex(_vertices[i->at(0)]);
			normal(_normals[i->at(0)]);
			vertex(_vertices[i->at(1)]);
			normal(_normals[i->at(1)]);
			vertex(_vertices[i->at(2)]);
			normal(_normals[i->at(2)]);
		}

		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);

		//glBegin(GL_LINES);

		//for (auto i = _triangles.begin(); i != _triangles.end(); ++i) {
		//    glVertex3f(0.0f, 0.0f, 0.0f);
		//    vertex(_vertices[i->at(0)]);
		//    glVertex3f(0.0f, 0.0f, 0.0f);
		//    vertex(_vertices[i->at(1)]);
		//    glVertex3f(0.0f, 0.0f, 0.0f);
		//    vertex(_vertices[i->at(2)]);
		//}

		//glEnd();
	}
};

std::unique_ptr<Graphics::Renderable> WalkMesh::getMesh() const {
	std::unique_ptr<DebugRenderable> ret(new DebugRenderable());
	ret->_roomPosition[0] = _roomPosition[0];
	ret->_roomPosition[1] = _roomPosition[1];
	ret->_roomPosition[2] = _roomPosition[2];
	ret->_position[0] = _position[0];
	ret->_position[1] = _position[1];
	ret->_position[2] = _position[2];
	ret->_vertices = _vertices;
	ret->_normals = _normals;
	ret->_triangles = _triangles;
	return std::move(ret);
}

}