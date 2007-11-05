// -*- C++ -*-
/***************************************************************************
                             libdatafile
                          --------------------
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

#ifndef OPTION_H
#define OPTION_H

#include "exception.hh"
#include <string>

namespace libdatafile
{
    class Option
    {
    private:
	std::string m_name;

	std::string m_valuestr;
	unsigned int m_value;
	
    public:
	Option(const std::string&);
	Option(const Option&);
	void set(unsigned int);
	void set(const std::string&);
	unsigned int get() const;
	std::string getstr() const;
	std::string name() const;
    };
}
#endif // OPTION_H
