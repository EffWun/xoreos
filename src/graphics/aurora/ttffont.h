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

/** @file graphics/aurora/ttffont.h
 *  A TrueType font.
 */

#ifndef GRAPHICS_AURORA_TTFFONT_H
#define GRAPHICS_AURORA_TTFFONT_H

#include <vector>
#include <map>

#include "common/types.h"

#include "graphics/font.h"

#include "graphics/aurora/textureman.h"

namespace Common {
	class UString;
}

namespace Graphics {

class Surface;
class TTFRenderer;

namespace Aurora {

class Texture;

class TTFFont : public Graphics::Font {
public:
	TTFFont(Common::SeekableReadStream *ttf, int height);
	TTFFont(const Common::UString &name, int height);
	~TTFFont();

	float getWidth (uint32 c) const;
	float getHeight()         const;

	void draw(uint32 c) const;

	void buildChars(const Common::UString &str);

private:
	/** A texture page filled with characters. */
	struct Page {
		Surface *surface;
		TextureHandle texture;

		bool needRebuild;

		uint32 curX;
		uint32 curY;

		uint32 heightLeft;
		uint32 widthLeft;

		Page();

		void rebuild();
	};

	/** A font character. */
	struct Char {
		float width;

		float tX[4], tY[4];
		float vX[4], vY[4];

		uint page;
	};


	TTFRenderer *_ttf;

	std::vector<Page *> _pages;
	std::map<uint32, Char> _chars;

	std::map<uint32, Char>::const_iterator _missingChar;
	float _missingWidth;

	uint32 _height;

	void load(Common::SeekableReadStream *ttf, int height);

	void rebuildPages();
	void addChar(uint32 c);
	void drawMissing() const;
};

} // End of namespace Aurora

} // End of namespace Graphics

#endif // GRAPHICS_AURORA_TTFFONT_H
