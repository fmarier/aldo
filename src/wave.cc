/***************************************************************************
                           libaudiostream
                          --------------------
  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007 Giuseppe "denever" Martino
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

using namespace std;
using namespace libaudiostream;

Wave::Wave(size_type d): m_size(d)
{
}

Wave::Wave(size_type d, samples_buffer_pointer p): 
    m_size(d), m_data(p)
{
}

Wave::Wave(const Wave& cpy)
{
    if(m_data != 0)
	delete [] m_data;

    m_size = cpy.m_size;
    m_data = new sample_type[m_size];

    for(size_type i = 0; i < m_size; i++)
	m_data[i] = cpy.m_data[i];
}

Wave::~Wave()
{
    if(m_data != 0)
	delete [] m_data;
}

void Wave::reverse()
{}

void Wave::bias(sample_type val)
{}

void Wave::amplify(sample_type val)
{}

Wave& Wave::operator+(const Wave& cpy)
{
    Wave temp(m_size + cpy.m_size);

    for(size_type i = 0; i < m_size; i++)
	temp.set(i, m_data[i]);

    for(size_type i = m_size; i < cpy.m_size; i++)
	temp.set(i, m_data[i]);
    
    return *this;
}

Wave& Wave::operator=(const Wave& cpy)
{
    if(m_data != 0)
	delete [] m_data;

    m_size = cpy.m_size;
    m_data = new sample_type[m_size];

    for(size_type i=0; i < m_size; i++)
	m_data[i] = cpy.m_data[i];
    
    return *this;
}

void Wave::set(size_type pos, int s)
{}
