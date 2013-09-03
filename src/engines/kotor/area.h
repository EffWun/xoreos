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

/** @file engines/kotor/area.h
 *  An area.
 */

#ifndef ENGINES_KOTOR_AREA_H
#define ENGINES_KOTOR_AREA_H

#include <vector>
#include <list>
#include <map>
#include <memory>

#include "common/ustring.h"
#include "common/mutex.h"

#include "aurora/types.h"
#include "aurora/lytfile.h"
#include "aurora/visfile.h"

#include "sound/types.h"

#include "events/types.h"
#include "events/notifyable.h"

#include "graphics/aurora/types.h"
#include "graphics/aurora/model.h"

namespace Aurora {
	class WalkMesh;
}

namespace Engines {

namespace KotOR {

	class Module;
class Object;
class Room;

/** A KotOR area. */
class Area : public Events::Notifyable {
public:
	explicit Area(Module& module);
	virtual ~Area();

	void load(const Common::UString &resRef);

	/** Return the area's localized name. */
	const Common::UString &getName();

	void show();
	void hide();

	void addEvent(const Events::Event &event);
	void processEventQueue();

	void removeFocus();


protected:
	void notifyCameraMoved();


// private:
public:
	typedef std::list<Object *> ObjectList;

	typedef std::map<uint32, Object *> ObjectMap;


	bool _loaded;
	Module* _module;

	Common::UString _resRef;
	Common::UString _name;

	Common::UString _ambientDay;
	Common::UString _ambientNight;

	Common::UString _musicDay;
	Common::UString _musicNight;
	Common::UString _musicBattle;

	std::vector<Common::UString> _musicBattleStinger;

	float _ambientDayVol;
	float _ambientNightVol;

	bool _visible;

	Sound::ChannelHandle _ambientSound;
	Sound::ChannelHandle _ambientMusic;

	Aurora::LYTFile _lyt;
	Aurora::VISFile _vis;

	std::vector<std::unique_ptr<Room>> _rooms;

	ObjectList _objects;

	ObjectMap _objectMap;

	Object *_activeObject;

	bool _highlightAll;

	std::list<Events::Event> _eventQueue;

	Common::Mutex _mutex;


	void loadLYT();
	void loadVIS();

	void loadARE(const Aurora::GFFStruct &are);
	void loadGIT(const Aurora::GFFStruct &git);

	void loadModels();
	void loadVisibles();

	void loadProperties(const Aurora::GFFStruct &props);

	void loadPlaceables(const Aurora::GFFList &list);
	void loadDoors     (const Aurora::GFFList &list);
	void loadCreatures (const Aurora::GFFList &list);
	void loadTriggers  (const Aurora::GFFList &list);

	void loadObject(Object &object);

	void stopSound();
	void stopAmbientMusic();
	void stopAmbientSound();

	void playAmbientMusic(Common::UString music = "");
	void playAmbientSound(Common::UString sound = "");

	void checkActive();
	void setActive(Object *object);
	Object *getObjectAt(int x, int y);

	void highlightAll(bool enabled);

	friend class Console;
};

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_AREA_H
