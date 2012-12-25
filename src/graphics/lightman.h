/* eos - A reimplementation of BioWare's Aurora engine
 *
 * eos is the legal property of its developers, whose names can be
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
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file graphics/lightman.h
 *  The light manager.
 */

#ifndef GRAPHICS_LIGHTMAN_H
#define GRAPHICS_LIGHTMAN_H

#include <list>

#include "common/types.h"
#include "common/singleton.h"
#include "common/mutex.h"
#include "common/matrix.h"

#include "graphics/types.h"

namespace Graphics {

class LightHandle;
class LightingHandle;

class Renderable;

/** The light manager. */
class LightManager : public Common::Singleton<LightManager> {
public:
	LightManager();
	~LightManager();

	// Global parameters

	/** Enable/Disable lighting. */
	void enableLighting(bool enable);

	/** Set the maximum of enabled lights per Renderable. Can't be more than 8. */
	void setMaxLights(uint8 max);

	/** Set the ambient RGBA intensity of the entire scene. */
	void setAmbient(float r, float g, float b, float a);

	// Individual lights

	/** Add a light */
	LightHandle addLight();
	/** Switch a light on/off. */
	void switchOnOff(LightHandle &light, bool on);
	/** Set a light's ambient color. */
	void setAmbient (LightHandle &light, float r, float g, float b, float a);
	/** Set a light's diffuse color. */
	void setDiffuse (LightHandle &light, float r, float g, float b, float a);
	/** Set a light's specular color. */
	void setSpecular(LightHandle &light, float r, float g, float b, float a);
	/** Set a light's position. */
	void setPosition(LightHandle &light, float x, float y, float z);

	// Lightings

	/** Create a lighting. */
	LightingHandle createLighting();
	/** Evaluate the lighting for this position. */
	void evaluateLighting(LightingHandle &lighting, float x, float y, float z);
	/** Update all lightings. */
	void updateLighting();

	// To be called from the renderer in the main thread.

	void setCamera(const Common::Matrix &camera);

	void showLights();
	void renderLights();
	void renderLights(const LightingHandle &lighting);

private:
	struct Light {
		uint32 referenceCount;

		bool switchedOn;

		GLfloat ambient [4];
		GLfloat diffuse [4];
		GLfloat specular[4];
		GLfloat position[4];

		Light();
		~Light();
	};

	struct Lighting {
		uint32 referenceCount;

		float position[3];

		std::list<LightHandle> lights;

		Lighting();
		~Lighting();
	};

	typedef std::list<Light *> LightList;
	typedef std::list<Lighting *> LightingList;


	Common::Mutex _mutex;

	bool  _enabledLighting; ///< Is lighting enabled?
	uint8 _maxLights;       ///< Maximum of enabled lights per Renderable.

	GLfloat _ambientIntensity[4]; ///< The ambient RGBA intensity of the entire scene.

	LightList _lights;
	LightingList _lightings;

	Common::Matrix _camera;


	void assign(LightHandle &light, const LightHandle &from);
	void assign(LightingHandle &lighting, const LightingHandle &from);
	void release(LightHandle &light);
	void release(LightingHandle &lighting);

	void evaluateLighting(Lighting &lighting);


	friend class LightHandle;
	friend class LightingHandle;
};

/** A handle to a light. */
class LightHandle {
public:
	LightHandle();
	LightHandle(const LightHandle &right);
	~LightHandle();

	LightHandle &operator=(const LightHandle &right);

	bool empty() const;

	void clear();

private:
	bool _empty;
	LightManager::LightList::iterator _it;

	LightHandle(LightManager::LightList::iterator &i);

	friend class LightManager;
	friend class LightDistanceSort;
};

/** A handle to a light. */
class LightingHandle {
public:
	LightingHandle();
	LightingHandle(const LightingHandle &right);
	~LightingHandle();

	LightingHandle &operator=(const LightingHandle &right);

	bool empty() const;

	void clear();

private:
	bool _empty;
	LightManager::LightingList::iterator _it;

	LightingHandle(LightManager::LightingList::iterator &i);

	friend class LightManager;
};

} // End of namespace Graphics

/** Shortcut for accessing the graphics queue manager. */
#define LightMan Graphics::LightManager::instance()

#endif // GRAPHICS_LIGHTMAN_H
