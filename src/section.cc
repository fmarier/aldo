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

#include "section.hh"

using namespace std;
using namespace libdatafile;

Section::Section(const string& title): m_name(title)
{
    m_options.clear();
}

Section::Section (const Section& cpy): m_name(cpy.m_name), m_options(cpy.m_options)
{}

void Section::add_option(const string& name)
{
    Option tmp(name);
    m_options.push_back(tmp);
}

void Section::remove(const string& name)
{
    for(opt_it i=begin(); i!=end(); i++)
	if(i->name() == name)
	    m_options.erase(i);
	
    throw libdatafile::Option_not_found(name.c_str());
}

opt_it Section::option(const string& name)
{
    for(opt_it i=begin(); i!=end(); i++)
	if(i->name() == name)
	    return i;
	
    throw libdatafile::Option_not_found(name.c_str());
}

string Section::name() const
{
    return m_name;
}

opt_it Section::begin()
{
    return m_options.begin();
}

opt_it Section::end()
{
    return m_options.end();
}
