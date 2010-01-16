/***************************************************************************
                           libaudiostream
                          --------------------
Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 Giuseppe "denever" Martino
    begin                : Sat 9 Mar 2002
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

#include "wave.hh"
#include "astream.hh"

#include <limits>

using namespace std;
using namespace libaudiostream;

oastream::oastream(ao_sample_format format, string device = "default")
    throw(AudioException):
    m_format(format)
{
    ao_option *options = NULL;
    const char *devstr = NULL;

    ao_initialize();

    if( (m_default_driver = ao_default_driver_id()) < 0)
	throw AudioException("There is no default driver.");

    if (device == "default")
	devstr = NULL;
    else if ((m_default_driver == ao_driver_id("alsa"))
	|| m_default_driver == ao_driver_id("sun")
	|| m_default_driver == ao_driver_id("aixs"))
	devstr = "dev";
    else if (m_default_driver == ao_driver_id("esd"))
	devstr = "host";
    else if (m_default_driver == ao_driver_id("oss"))
	devstr = "dsp";

    if (devstr) {
	if (ao_append_option(&options, "dev", device.c_str()) != 1)
	    throw AudioException("Error appending 'device' option");
    }
    
    m_audio = ao_open_live(m_default_driver, &m_format, options);
    
    ao_free_options(options);

    if(!m_audio)
	throw AudioException("Error opening device");
}

oastream::oastream(const oastream& cpy)
{
    m_audio = cpy.m_audio;

    m_format = cpy.m_format;

    m_default_driver = cpy.m_default_driver;
}

oastream& oastream::operator=(const oastream& cpy)
{
    m_audio = cpy.m_audio;

    m_format = cpy.m_format;

    m_default_driver = cpy.m_default_driver;
    
    return *this;
}

oastream& oastream::operator<<(const Wave& wave) throw(AudioException)
{
    if(m_audio)
	ao_play(m_audio, wave.get_buffer(), wave.size() );
    else
	throw AudioException("Error opening device");
    return *this;
}
    
oastream::~oastream()
{
    ao_close(m_audio);
    
    ao_shutdown();
}
