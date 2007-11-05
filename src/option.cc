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

#include "option.hh"

using namespace std;
using namespace libdatafile;

Option::Option(const string& name): m_name(name), m_value(9999)
{}

Option::Option(const Option& cpy): m_name(cpy.m_name),  m_value(cpy.m_value)
{}

void Option::set(unsigned int vl)
{
    if(m_valuestr.empty())
	m_value = vl;
}

void Option::set(const std::string& vl)
{
    m_value = 9999;
    m_valuestr = vl;
}

unsigned int Option::get() const
{
    return m_value;
}

string Option::getstr() const
{
    return m_valuestr;
}
 
string Option::name() const
{
    return m_name;
}
