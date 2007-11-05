// -*- C++ -*-
/***************************************************************************
                          libexercises part of Aldo
                          ---------------------
    begin                : Sun May 6 2001
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

#ifndef QRZ_H
#define QRZ_H

#include "keyer.hh"

#include <string>

namespace libexercises
{
    class Qrz
    {
	friend libkeyer::Keyer& operator<<(libkeyer::Keyer&, const Qrz&);

    private:
	std::string m_strings;
	unsigned int m_num_chars;
	unsigned int m_num_strings;    
		
    public:
	Qrz(): m_num_chars(0), m_num_strings(0)
	{
	    m_strings.clear();
	}

	Qrz(const std::string &, unsigned int);
	Qrz(const Qrz&);

	unsigned int verify(const std::string&) const;

	inline unsigned int string_len() const 
	{
	    return m_num_chars;
	}

	inline unsigned int len() const
	{
	    return m_num_strings;
	}

	inline std::string get_string() const
	{
	    return m_strings;
	}
    };

    libkeyer::Keyer& operator<<(libkeyer::Keyer&, const Qrz&);
}
#endif //QRZ_H
