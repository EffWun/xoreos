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

/** @file engines/kotor/trigger.cpp
 *  A trigger.
 */

#include "engines/kotor/trigger.h"

#include "common/util.h"
#include "common/maths.h"
#include "common/error.h"
#include "common/ustring.h"

#include "aurora/2dafile.h"
#include "aurora/2dareg.h"
#include "aurora/gfffile.h"
#include "aurora/locstring.h"

#include "graphics/aurora/modelnode.h"
#include "graphics/aurora/model.h"
#include "graphics/renderable.h"

#include "engines/aurora/util.h"
#include "engines/aurora/model.h"

namespace Engines {

namespace KotOR {

void vertex(const Aurora::Vector3& v) {
	glVertex3f(v.x, v.y, v.z);
}

class DebugRenderable : public Graphics::Renderable {
public:
	DebugRenderable() : Renderable(Graphics::kRenderableTypeObject) {
		_position[0] = _position[1] = _position[2] = 0.0f;
	}

	float _position[3];
	//float _roomPosition[3];
	std::vector<Aurora::Vector3> _vertices;

	void calculateDistance() override {
		// const float cameraX =  CameraMan.getPosition()[0];
		// const float cameraY =  CameraMan.getPosition()[1];
		// const float cameraZ = -CameraMan.getPosition()[2];

		// const float x = ABS(_position[0] - cameraX);
		// const float y = ABS(_position[1] - cameraY);
		// const float z = ABS(_position[2] - cameraZ);


		// _distance = x + y + z;
	}

	void render(Graphics::RenderPass pass) override {
		glRotatef(90.0, -1.0, 0.0, 0.0);
		// glTranslatef(_roomPosition[0], _roomPosition[1], _roomPosition[2]);
		glTranslatef(_position[0], _position[1], _position[2]);

		glColor3f(0.0f, 0.6f, 0.0f);

		glBegin(GL_LINE_LOOP);

		for (auto i = _vertices.begin(); i != _vertices.end(); ++i) {
			vertex(*i);
		}

		glEnd();

		glColor3f(1.0f, 1.0f, 1.0f);
	}
};

void Trigger::show() {
	if (_debugRenderable)
		_debugRenderable->show();
}

void Trigger::hide() {
	if (_debugRenderable)
		_debugRenderable->hide();
}

void Trigger::setPosition(float x, float y, float z) {
	static_cast<DebugRenderable*>(_debugRenderable.get())->_position[0] = x;
	static_cast<DebugRenderable*>(_debugRenderable.get())->_position[1] = y;
	static_cast<DebugRenderable*>(_debugRenderable.get())->_position[2] = z;
}

void Trigger::getPosition(float& x, float& y, float& z) const {
	x = static_cast<DebugRenderable*>(_debugRenderable.get())->_position[0];
	y = static_cast<DebugRenderable*>(_debugRenderable.get())->_position[1];
	z = static_cast<DebugRenderable*>(_debugRenderable.get())->_position[2];
}

void Trigger::setOrientation(float x, float y, float z) {
	// _model->setRotation(x, z, -y);
}

void Trigger::getOrientation(float& x, float& y, float& z) const {
	// _model->setRotation(x, z, -y);
}

void Trigger::load(const Aurora::GFFStruct &trigger) {
	auto debugRenderable = new DebugRenderable;
	_debugRenderable.reset(debugRenderable);
	debugRenderable->_position[0] = trigger.getDouble("XPosition");
	debugRenderable->_position[1] = trigger.getDouble("YPosition");
	debugRenderable->_position[2] = trigger.getDouble("ZPosition");

	const Aurora::GFFList& geometry = trigger.getList("Geometry");
	for (auto i = geometry.begin(); i != geometry.end(); ++i) {
		Aurora::Vector3 vertex;
		vertex.x = (*i)->getDouble("PointX");
		vertex.y = (*i)->getDouble("PointY");
		vertex.z = (*i)->getDouble("PointZ");
		debugRenderable->_vertices.push_back(vertex);
	}
}

//void Trigger::load(const Aurora::GFFStruct &trigger) {
//    Common::UString temp = trigger.getString("TemplateResRef");
//
//    Aurora::GFFFile *utc = 0;
//    if (!temp.empty()) {
//     try {
//       utc = new Aurora::GFFFile(temp, Aurora::kFileTypeUTC, MKTAG('U', 'T', 'C', ' '));
//     } catch (...) {
//       delete utc;
//     }
//    }
//    load(trigger, utc ? &utc->getTopLevel() : 0);
//
//    if (!utc)
//     warning("Trigger \"%s\" has no blueprint", _tag.c_str());
//
//    delete utc;
//}
//
//void Trigger::load(const Aurora::GFFStruct &instance, const Aurora::GFFStruct *blueprint) {
//    assert(!_loaded);
//
//    // General properties
//
//    if (blueprint)
//        loadProperties(*blueprint); // Blueprint
//    loadProperties(instance);    // Instance
//
//
//    // Appearance
//
//    if (_appearance == Aurora::kFieldIDInvalid)
//        throw Common::Exception("Trigger without an appearance");
//
//    loadAppearance();
//
//    // Position
//
//    setPosition(instance.getDouble("XPosition"),
//                instance.getDouble("YPosition"),
//                instance.getDouble("ZPosition"));
//
//    // Orientation
//
//    float bearingX = instance.getDouble("XOrientation");
//    float bearingY = instance.getDouble("YOrientation");
//
//    float o[3];
//    Common::vector2orientation(bearingX, bearingY, o[0], o[1], o[2]);
//
//    setOrientation(o[0], o[1], o[2]);
//
//    _loaded = true;
//}
//
//void Trigger::loadProperties(const Aurora::GFFStruct &gff) {
//    // Tag
//    _tag = gff.getString("Tag", _tag);
//
//    // Name
//    if (gff.hasField("LocName")) {
//        Aurora::LocString name;
//        gff.getLocString("LocName", name);
//
//        _name = name.getString();
//    }
//
//    // Description
//    if (gff.hasField("Description")) {
//        Aurora::LocString description;
//        gff.getLocString("Description", description);
//
//        _description = description.getString();
//    }
//
//    // Portrait
//    loadPortrait(gff);
//
//    // Appearance
//    _appearance = gff.getUint("Appearance_Type", _appearance);
//
//    // Static
//    _static = gff.getBool("Static", _static);
//
//    // Usable
//    _usable = gff.getBool("Useable", _usable);
//}
//
//void Trigger::loadPortrait(const Aurora::GFFStruct &gff) {
//    uint32 portraitID = gff.getUint("PortraitId");
//    if (portraitID != 0) {
//        const Aurora::TwoDAFile &twoda = TwoDAReg.get("portraits");
//
//        Common::UString portrait = twoda.getRow(portraitID).getString("BaseResRef");
//        if (!portrait.empty())
//            _portrait = "po_" + portrait;
//    }
//
//    _portrait = gff.getString("Portrait", _portrait);
//}
//
//void Trigger::loadAppearance() {
//    PartModels parts;
//
//    getPartModels(parts);
//
//    if ((parts.type == "P") || parts.body.empty()) {
//        warning("TODO: Model \"%s\": ModelType \"%s\" (\"%s\")",
//                _tag.c_str(), parts.type.c_str(), parts.body.c_str());
//        return;
//    }
//
//    loadBody(parts);
//    loadHead(parts);
//}
//
//void Trigger::getPartModels(PartModels &parts, uint32 state) {
//    const Aurora::TwoDARow &appearance = TwoDAReg.get("appearance").getRow(_appearance);
//
//    parts.type = appearance.getString("modeltype");
//
//    parts.body = appearance.getString(Common::UString("model") + state);
//    if (parts.body.empty())
//        parts.body = appearance.getString("race");
//
//    parts.bodyTexture = appearance.getString(Common::UString("tex") + state);
//    if (!parts.bodyTexture.empty())
//        parts.bodyTexture += "01";
//
//    if (parts.bodyTexture.empty())
//        parts.bodyTexture = appearance.getString("racetex");
//
//    if ((parts.type == "B") || (parts.type == "P")) {
//        const int headNormalID = appearance.getInt("normalhead");
//        const int headBackupID = appearance.getInt("backuphead");
//
//        const Aurora::TwoDAFile &heads = TwoDAReg.get("heads");
//
//        if      (headNormalID >= 0)
//            parts.head = heads.getRow(headNormalID).getString("head");
//        else if (headBackupID >= 0)
//            parts.head = heads.getRow(headBackupID).getString("head");
//    }
//}
//
//void Trigger::loadBody(PartModels &parts) {
//    _model = loadModelObject(parts.body, parts.bodyTexture);
//    if (!_model)
//        return;
//
//    _ids.push_back(_model->getID());
//
//    _model->setTag(_tag);
//    _model->setClickable(isClickable());
//}
//
//void Trigger::loadHead(PartModels &parts) {
//    if (!_model || parts.head.empty())
//        return;
//
//    Graphics::Aurora::ModelNode *headHook = _model->getNode("headhook");
//    if (!headHook)
//        return;
//
//    headHook->addChild(loadModelObject(parts.head));
//}

void Trigger::enter() {
	highlight(true);
}

void Trigger::leave() {
	highlight(false);
}

void Trigger::highlight(bool enabled) {
	// _model->drawBound(enabled);
}

} // End of namespace KotOR

} // End of namespace Engines
