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

#include "aurora/types.h"

#include "engines/kotor/situated.h"

#include <memory>

namespace Graphics {
	class Renderable;
}

namespace Aurora {
	namespace NWScript {
		class NCSFile;
    }
}


namespace Engines {

namespace KotOR {

/** A KotOR trigger. */
class Trigger : public Situated {
public:
	Trigger();

	void load(const Aurora::GFFStruct &trigger);

	void hide();

	void enter();
	void leave();

	void highlight(bool enabled);

	std::unique_ptr<Aurora::NWScript::NCSFile> _ncs;

protected:
	void loadObject(const Aurora::GFFStruct &gff);
	void loadAppearance();
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_TRIGGER_H
