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

#ifndef SECTION_H
#define SECTION_H

#include "option.hh"
#include <list>

namespace libdatafile
{
    typedef std::list <Option>::iterator opt_it;
    
    class Section
    {
    private:
	std::string m_name;
	std::list <Option> m_options;    
    
    public:
	std::string name() const;
	
	Section(const std::string& title);
	Section(const Section&);
	
	void add_option(const std::string& name);
	void remove(const std::string& name);
	
	opt_it option(const std::string& name);
	
	opt_it begin();
	opt_it end();
    };
}
#endif //SECTION_H
