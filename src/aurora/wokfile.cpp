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

/** @file aurora/wokfile.cpp
 *  Handling BioWare's WOKs (Layout files).
 */

#include "common/stream.h"
#include "common/streamtokenizer.h"
#include "common/util.h"

#include "aurora/wokfile.h"
#include "aurora/walkmesh.h"
#include "aurora/error.h"

#define BOOST_RESULT_OF_USE_DECLTYPE

#include <boost/fusion/include/define_struct.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/fold.hpp>
namespace fu = boost::fusion;

#include <iterator>
#include <array>
#include <memory>

typedef __int32 Int32;
typedef unsigned __int32 Uint32;

typedef std::array<char, 4> FourChar;
typedef std::array<byte, 48> FourtyEightByte;

BOOST_FUSION_DEFINE_STRUCT(
   (wok), Header,
   (FourChar, fileType)
   (FourChar, version)
   (Uint32, walkmeshType)
   (FourtyEightByte, reserved)
   (float, positionX)
   (float, positionY)
   (float, positionZ)
   (Uint32, verticesCount)
   (Uint32, offsetToVertices)
   (Uint32, facesCount)
   (Uint32, offsetToFaces)
   (Uint32, offsetToWalkTypes)
   (Uint32, offsetToNormalizedInvertedNormals)
   (Uint32, offsetToFacePlanesCoefficient)
   (Uint32, countAABB)
   (Uint32, offsetToAABBs)
   (Uint32, unknownEntry)
   (Uint32, walkableFacesEdgesAdjacencyMatrixCount)
   (Uint32, offsetToWalkableFacesEdgesAdjacencyMatrix)
   (Uint32, perimetricEdgesCount)
   (Uint32, offsetToPerimetricEdges)
   (Uint32, perimetersCount)
   (Uint32, offsetToPerimeters)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), Vertex,
   (float, X)
   (float, Y)
   (float, Z)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), Face,
   (int, V1_Index)
   (int, V2_Index)
   (int, V3_Index)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), WalkType,
   (Int32, walkType)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), AABB_Node,
   (wok::Vertex, BoxMin)
   (wok::Vertex, BoxMax)
   (Int32, LeafFaceIndex)
   (Int32, MostSignificantPlane)
   (Int32, UnknownFixedAt4)
   (Int32, LeftNodeArrayIndex)
   (Int32, RightNodeArrayIndex)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), EdgesAdjacency,
   (Int32, Face1_Adjacency)
   (Int32, Face2_Adjacency)
   (Int32, Face3_Adjacency)
)

BOOST_FUSION_DEFINE_STRUCT(
   (wok), PerimetricEdges,
   (Int32, Edge_Index)
   (Int32, RoomAdjacency)
)

namespace Aurora {

struct load_impl {
	Common::ReadStream* _s;
	explicit load_impl(Common::ReadStream& s) : _s(&s) {}

	void operator()(Uint32& i) const {
		i = _s->readUint32LE();
	}

	void operator()(Int32& i) const {
		i = _s->readSint32LE();
	}

	void operator()(float& f) const {
		f = _s->readIEEEFloatLE();
	}

	template <class T, int N>
	void operator()(std::array<T, N>& t) const {
		_s->read(t.data(), N * sizeof(T));
	}
};

template <class T>
T doLoad(Common::ReadStream& s) {
	T ret;
	fu::for_each(ret, load_impl(s));
	return ret;
}

struct dump {
	template <class T>
	std::ostream* operator()(std::ostream* os, const T& t) const {
		(*os) << t << std::endl;
		return os;
	}

	template <class T, int N>
	std::ostream* operator()(std::ostream* os, const std::array<T, N>& t) const {
		boost::copy(t, std::ostream_iterator<T>(*os, ","));
		(*os) << std::endl;
		return os;
	}
};

void WOKFile::load(Common::SeekableReadStream &s) {
	auto header = doLoad<wok::Header>(s);
	//fu::fold(header, xxofs, dump());

	// *xxofs << "--Vertices--" << std::endl;

	for (auto i = 0; i < header.verticesCount; ++i) {
		s.seekTo(header.offsetToVertices + i * sizeof(wok::Vertex));
		auto vertex = doLoad<wok::Vertex>(s);
		//*xxofs << vertex.X << "," << vertex.Y << "," << vertex.Z << std::endl;

		Vector3 pt;
		pt.x = vertex.X;
		pt.y = vertex.Y;
		pt.z = vertex.Z;

		_vertices.push_back(pt);
	}

	//*xxofs << "--Normals--" << std::endl;

	for (auto i = 0; i < header.verticesCount; ++i) {
		s.seekTo(header.offsetToNormalizedInvertedNormals + i * sizeof(wok::Vertex));
		auto vertex = doLoad<wok::Vertex>(s);
		//*xxofs << vertex.X << "," << vertex.Y << "," << vertex.Z << std::endl;

		Vector3 pt;
		pt.x = vertex.X;
		pt.y = vertex.Y;
		pt.z = vertex.Z;

		_normals.push_back(pt);
	}

	//*xxofs << "--Triangles--" << std::endl;

	for (auto i = 0; i < header.facesCount; ++i) {
		s.seekTo(header.offsetToFaces + i * sizeof(wok::Face));
		auto face = doLoad<wok::Face>(s);
		//*xxofs << face.V1_Index << "," << face.V2_Index << "," << face.V3_Index << std::endl;
		Triangle t;
		t[0] = face.V1_Index;
		t[1] = face.V2_Index;
		t[2] = face.V3_Index;
		_triangles.push_back(t);
	}

	_position[0] = header.positionX;
	_position[1] = header.positionY;
	_position[2] = header.positionZ;

}

std::unique_ptr<WalkMesh> WOKFile::get() {
	std::unique_ptr<WalkMesh> ret(new WalkMesh);
	ret->_position[0] = _position[0];
	ret->_position[1] = _position[1];
	ret->_position[2] = _position[2];
	ret->_vertices = _vertices;
	ret->_normals = _normals;
	ret->_triangles = _triangles;
	return std::move(ret);
}

} // End of namespace Aurora
