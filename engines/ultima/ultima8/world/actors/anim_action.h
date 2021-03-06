/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
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
 */

#ifndef WORLD_ACTORS_ANIMACTION_H
#define WORLD_ACTORS_ANIMACTION_H

#include "ultima/shared/std/containers.h"
#include "ultima/ultima8/misc/direction.h"

namespace Ultima {
namespace Ultima8 {

class Actor;

struct AnimFrame {
	int _frame;
	int _deltaZ;
	int _deltaDir;
	int _sfx;
	uint32 _flags;

	enum AnimFrameFlags {
		AFF_UNK1     = 0x00000001,
		AFF_ONGROUND = 0x00000002,
		AFF_FLIPPED  = 0x00000020,
		AFF_CRUFLIP  = 0x00000080,
		AFF_SPECIAL  = 0x00000800, // U8 only
		AFF_HURTY    = 0x00001000, // Crusader only - TODO: find a better name for this.
		AFF_USECODE  = 0x00004000,
		AFF_NOSTOP   = 0x00008000  // Crusader only - Probably - applied to most death animations
		//AFF_UNKNOWN  = 0xF0E0B01C,
		//AFF_FIRE     = 0x0F1F00C0
	};

	inline bool is_flipped() const {
		return (_flags & AFF_FLIPPED) != 0;
	}
	inline int attack_range() const {
		return ((_flags >> 2) & 0x07);
	}

	inline bool is_callusecode() const {
		return (_flags & AFF_USECODE) != 0;
	}
};

class AnimAction {
	friend class AnimDat;

public:
	//! return the range of the animation to play
	//! \param actor The actor to play the animation for
	//! \param dir The direction
	//! \param startframe The first frame to play
	//! \param endframe The frame after the last frame to play
	void getAnimRange(const Actor *actor, Direction dir,
	                  unsigned int &startframe, unsigned int &endframe) const;

	//! return the range of the animation to play
	//! \param lastanim The lastanim of the Actor
	//! \param lastdir The direction of the Actor
	//! \param firststep The firststep flag of the Actor
	//! \param dir The direction
	//! \param startframe The first frame to play
	//! \param endframe The frame after the last frame to play
	void getAnimRange(unsigned int lastanim, Direction lastdir,
	                  bool firststep, Direction dir,
	                  unsigned int &startframe, unsigned int &endframe) const;

	unsigned int getDirCount() const {
		return _dirCount;
	}

	unsigned int getSize() const {
		return _size;
	}
	
	int getFrameRepeat() const {
		return _frameRepeat;
	}
	
	uint32 getShapeNum() const {
		return _shapeNum;
	}
	
	uint32 getAction() const {
		return _action;
	}
	
	bool hasFlags(uint32 mask) const {
		return (_flags & mask) != 0;
	}
	
	const AnimFrame &getFrame(Direction dir, unsigned int frameno) const;

	enum AnimActionFlags {
		AAF_TWOSTEP      = 0x0001,
		AAF_ATTACK       = 0x0002,
		AAF_LOOPING      = 0x0004,
		AAF_UNSTOPPABLE  = 0x0008,
		AAF_LOOPING2     = 0x0010, // CHECKME: guessing at this flag
		AAF_LOOPING3     = 0x0040, // CHECKME: Crusader triggers a new anim in the terminate if this flag is set and the start point was null
		AAF_HANGING      = 0x0080,
		AAF_CRUS_ROTATED = 0x1000,
		AAF_CRUS_16DIRS  = 0x4000, // Crusader
		AAF_DESTROYACTOR = 0x8000, // destroy actor after animation finishes
		AAF_UNKFLAGS     = 0x3F20
	};

private:
	uint32 _shapeNum;
	uint32 _action;

	Std::vector<AnimFrame> _frames[16]; // 8 or 16 directions
	unsigned int _size;
	int _frameRepeat;
	uint32 _flags;

	unsigned int _dirCount;
};

} // End of namespace Ultima8
} // End of namespace Ultima

#endif
