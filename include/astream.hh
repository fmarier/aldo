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

#ifndef AUDIOSTREAM_H
#define AUDIOSTREAM_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_AO_AO_H
#include <ao/ao.h>
#endif

#include "wave.hh"
#include "audioworkspace.hh"
#include "audioexcep.hh"

namespace libaudiostream
{
    class oastream
    {
    public:
	oastream(ao_sample_format) throw(AudioException);

	oastream(const oastream&);
	
	~oastream();
	
	oastream& operator<<(const Wave&) throw(AudioException);

	oastream& operator=(const oastream&);
    private:
	ao_device* m_audio;
	ao_sample_format m_format;
	unsigned int m_default_driver;
    };
}

#endif //AUDIOSTREAM_H
