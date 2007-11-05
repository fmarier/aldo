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

#ifndef WAVE_H
#define WAVE_H

namespace libaudiostream
{
    typedef char* samples_buffer_pointer;
    typedef char sample_type;
    typedef unsigned int size_type;
    
    class Wave
    {
    public:
	explicit Wave(size_type);
	explicit Wave(size_type, samples_buffer_pointer);
	Wave(const Wave&);
	~Wave();

	inline samples_buffer_pointer get_buffer() const
	{
	    return m_data;
	}

	inline size_type size() const
	{
	    return m_size;
	}

	void set(size_type, int);
     	void reverse();
	void bias(sample_type);
	void amplify(sample_type);

	Wave& operator+(const Wave&);
	Wave& operator=(const Wave&);

    protected:
	size_type m_size;
	samples_buffer_pointer m_data;
    };
}
#endif //WAVE_H
