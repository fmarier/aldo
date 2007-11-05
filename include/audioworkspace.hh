// -*- C++ -*-
/***************************************************************************
                           libaudiostream
                          --------------------
    begin                : Sat 9 Mar 2002
    copyright            : Giuseppe "denever" Martino
    email                : denever@users.sourceforge.net
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, write to the Free Software            *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,             *
 *  MA 02110-1301 USA                                                      *
 *                                                                         *
 ***************************************************************************/

#ifndef AUDIOWORKSPACE_H
#define AUDIOWORKSPACE_H

#include "wave.hh"

namespace libaudiostream
{
    class oastream;

    class AudioWorkSpace
    {
    public:
	AudioWorkSpace();
	AudioWorkSpace(size_type, size_type, size_type, size_type);
	AudioWorkSpace(const Wave&);
	virtual ~AudioWorkSpace();
	
	oastream create_output_stream();

	Wave gen_pause(size_type);
	Wave gen_sine_wave(size_type, double, double);
    private:
	size_type m_bits;
	size_type m_sample_rate;
	size_type m_channels;
	size_type m_byte_format;
    };
}
#endif //AUDIOWORKSPACE_H



