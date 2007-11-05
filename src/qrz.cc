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

#include "qrz.hh"
#include "random.hh"

using namespace std;
using namespace libexercises;

Qrz::Qrz(const Qrz& cpy)
{
    m_strings = cpy.m_strings;
}

Qrz::Qrz(const string& qrz_format, unsigned int qrz_num): m_num_strings(qrz_num)
{
    m_num_chars = qrz_format.size();

    string group_chars("eishtmoawjuvrlpfndbgkcyqzx");
    string group_numbrs("0123456789");

    librandom::Random RND;

    string buffer;
    buffer.clear();

    typedef std::string::const_iterator cit;

    for(unsigned int i=0; i<m_num_strings; i++)
	for(cit it = qrz_format.begin(); it!= qrz_format.end(); it++)
	    switch(*it)
	    {
	    case '@':
		m_strings += group_chars[ RND.integer(0, group_chars.size()-1)];
		break;

	    case '#':
		m_strings += group_numbrs[ RND.integer(0, group_numbrs.size()-1)];
		break;

	    case '?':
		if(RND.integer(0,1))
		    m_strings += group_chars[RND.integer(0, group_chars.size()-1)];
		break;

	    case '$':
		if(RND.integer(0,1))
		    m_strings += group_numbrs[RND.integer(0, group_numbrs.size()-1)];
		break;

	    default:
		m_strings += *it;
	    }
}

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const Qrz& exc)
{
    unsigned int strlen = exc.string_len();

    for(unsigned int i=0; i< exc.len(); i++)
	out << exc.get_string().substr(i* strlen, strlen);
    
    return out;
}

unsigned int Qrz::verify(const std::string& catched) const
{
    double wrong_letters=0.0;

    if(catched.size() == m_strings.size())
    {
    	if(catched != m_strings)
	    for(unsigned int i=0; i<m_num_chars*m_num_strings; i++)
	    {
		if(catched[i] != m_strings[i])
		    wrong_letters++;
	    }
    }
    else
	return 0;
    
    double total = m_num_chars * m_num_strings;
    double catched_tax = wrong_letters/total;
    
    return int(100 - 100 * catched_tax); // return percentual of cathed letters
}
