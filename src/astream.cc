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

#include "wave.hh"
#include "astream.hh"

#include <limits>

using namespace std;
using namespace libaudiostream;

oastream::oastream(ao_sample_format format) throw(AudioException):
    m_format(format)
{
    ao_initialize();

    if( (m_default_driver = ao_default_driver_id()) < 0)
	throw AudioException("There is no default driver.");
    
    m_audio = ao_open_live(m_default_driver, &m_format, NULL /* no options */);
    
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
