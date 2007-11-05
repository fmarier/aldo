// -*- C++ -*-
/***************************************************************************
                             libdatafile
                          --------------------
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


#ifndef DATAFILE_H
#define DATAFILE_H

#include "section.hh"

namespace libdatafile
{
    typedef std::list <Section>::iterator sec_it;
    enum access {Read = 2, Write = 4, Create = 8, Update = 16};
    
    class Datafile
    {
    private:
	bool m_opened;
	std::list <Section> m_sections;
	std::string m_filename;
	access m_access;
	
	std::string read_value_in(const std::string&);
	std::string read_option_name_in(const std::string&);
	
	sec_it begin();
	sec_it end();
	
    public:
	Datafile(const std::string&, const access&);
	Datafile(const Datafile&);
	~Datafile();
	
	void open();
	void save();
    	
	sec_it section(const std::string&);
	
	void add_section(const std::string&);
	void remove_section(const std::string&);
    };
}
#endif //Datafile_H



