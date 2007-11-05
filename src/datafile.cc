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

#include "datafile.hh"

#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;
using namespace libdatafile;

Datafile::Datafile(const string& name, const access& a = Read): m_opened(false), m_filename(name), m_access(a)
{
    m_sections.clear();
    if( (m_access == Read) || (m_access == Update) )
    	open();
}

Datafile::Datafile(const Datafile& cpy): m_opened(cpy.m_opened), m_filename(cpy.m_filename), m_access(cpy.m_access)
{
    m_sections = cpy.m_sections;
}

Datafile::~Datafile()
{
    if((m_access == Write) || (m_access == Update) || (m_access == Create))
	save();
}

void Datafile::open()
{
    ifstream stream(m_filename.c_str());

    string alfa;
    string section_name;
    char ch;

    alfa.clear();
    section_name.clear();

    bool comment = false;

    if(stream.fail())
	throw libdatafile::File_not_exist(m_filename.c_str());

    while(stream.get(ch))
	switch(ch)
	{
	case '[': // New Section
	    if(!comment)
	    {
		section_name.clear();
		break;
	    }

	case ']': // Create Section
	    if(!comment)
	    {
		section_name = alfa;
		alfa.clear();
		add_section(section_name);
		break;
	    }

	case '#':
	    comment = true;
	    break;

	case '=':
	    if(!comment) // Create an option
	    {
		section(section_name)->add_option(alfa);
		string tmpstr;
		stream >> tmpstr;

		if(isdigit(tmpstr[0]))
		{
		    istringstream tmps (tmpstr);

		    int tmp;
		    tmps>>tmp;

		    section(section_name)->option(alfa)->set(tmp);
		}
		else
		    section(section_name)->option(alfa)->set(tmpstr);

		alfa.clear();
	    }

	case '\n':
		comment = false;
		alfa.clear();
		break;

	default:
		if(!comment)
		    if(!isspace(ch))
			alfa += ch;
	}
}

void Datafile::save()
{
    ofstream out(m_filename.c_str());

    out.clear();

    for(sec_it i=begin(); i!=end(); i++)
    {
	out<<endl<<"["<<i->name()<<"]"<<endl;
	for(opt_it j=i->begin(); j!=i->end(); j++)
	{
	    out<<j->name()<<" = ";

	    if(j->get() != 9999)
		out<<j->get()<<endl;
	    else
		out<<j->getstr()<<endl;
	}
    }

    out.close();
}

sec_it Datafile::section(const string& name)
{
    if(m_sections.empty())
	throw libdatafile::File_not_opened(m_filename.c_str());

    for(sec_it i=m_sections.begin(); i!=m_sections.end(); i++)
	if(i->name() == name)
	    return i;

    throw libdatafile::Section_not_found(name.c_str());
}

void Datafile::add_section(const string& name)
{
    Section tmp(name);
    m_sections.push_back(tmp);
}

void Datafile::remove_section(const string& name)
{
    if(m_sections.empty())
	throw libdatafile::File_not_opened(m_filename.c_str());

    for(sec_it i=begin(); i!=end(); i++)
	if(i->name() == name)
	    m_sections.erase(i);

    throw libdatafile::Section_not_found(name.c_str());
}

sec_it Datafile::begin()
{
    return m_sections.begin();
}

sec_it Datafile::end()
{
    return m_sections.end();
}
