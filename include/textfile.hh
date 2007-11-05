// -*- C++ -*-
/***************************************************************************
                          libexercises part of Aldo
                          ---------------------
Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 Giuseppe "denever" Martino
    begin                : Sun May 6 2001
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

#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "keyer.hh"

#include <string>

namespace libexercises
{
    class TextFile
    {
	friend libkeyer::Keyer& operator<<(libkeyer::Keyer&, const TextFile&);

    private:
	std::string m_strings;
	std::string m_filename;
	
    public:
	TextFile()
	{
	    m_strings.clear();
	    m_filename.clear();
	}
	
	TextFile(std::string);
	TextFile(const TextFile&);
	
	inline std::string get_string() const
	{
	    return m_strings;
	}
    };

    libkeyer::Keyer& operator<<(libkeyer::Keyer&, const TextFile&);
}
#endif //TEXTFILE_H
