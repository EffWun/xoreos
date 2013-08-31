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

/** @file engines/kotor/trigger.h
 *  A trigger.
 */

#ifndef ENGINES_KOTOR_TRIGGER_H
#define ENGINES_KOTOR_TRIGGER_H

#include <list>
#include <memory>

#include "common/types.h"
#include "common/ustring.h"

#include "aurora/types.h"

#include "graphics/aurora/types.h"

#include "engines/kotor/object.h"

namespace Graphics {
	class Renderable;
}

namespace Engines {

namespace KotOR {

/** A KotOR trigger. */
class Trigger : public Object {
public:

	void load(const Aurora::GFFStruct &trigger);

	void show() override;
	void hide() override;

	void getPosition(float &x, float &y, float &z) const override;
	void getOrientation(float &x, float &y, float &z) const override;

	void setPosition(float x, float y, float z) override;
	void setOrientation(float x, float y, float z) override;

	void enter() override;
	void leave() override;

	void highlight(bool enabled) override;

private:

	std::unique_ptr<Graphics::Renderable> _debugRenderable;

	void load(const Aurora::GFFStruct &instance, const Aurora::GFFStruct *blueprint);

	//void loadProperties(const Aurora::GFFStruct &gff);
	//void loadPortrait(const Aurora::GFFStruct &gff);
	//void loadAppearance();

	//void getPartModels(PartModels &parts, uint32 state = 'b');
	//void loadBody(PartModels &parts);
	//void loadHead(PartModels &parts);
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_TRIGGER_H
