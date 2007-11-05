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

#include "textfile.hh"

#include <cctype>
#include <fstream>

using namespace std;
using namespace libexercises;

TextFile::TextFile(const TextFile& cpy)
{
    m_strings = cpy.m_strings;
}

TextFile::TextFile(std::string filename):
    m_filename(filename)
{
    m_strings.clear();

    ifstream file(m_filename.c_str());
    
    char ch;
    string tmp_string;

    while(file.get(ch))
    {
	if(isspace(ch))
	{
	    m_strings += tmp_string;
	    m_strings += "|";
	    tmp_string.clear();
	}

	if(isalnum(ch))
	    tmp_string += ch;
    }
    
    if(!tmp_string.empty())
    {
	m_strings += tmp_string;
	m_strings += "|";
    }
} 

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const TextFile& exc)
{
    string tmp;
    tmp.clear();

    string exc_string = exc.get_string();
    typedef string::const_iterator sit;
    for(sit it = exc_string.begin(); it!=exc_string.end(); it++)
    {
	if(*it == '|')
	{
	    out << tmp;
	    tmp.clear();
	}
	else
	    tmp += *it;
    }
    
    return out;
}
