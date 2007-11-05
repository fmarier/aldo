/***************************************************************************
                          libexercises part of Aldo
                          ---------------------
    begin                : Sun May 6 2001
    copyright            : Giuseppe "denever" Martino
    improved             : Bob Harrington
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

#include "blocks.hh"
#include "random.hh"

using namespace std;
using namespace libexercises;

// These are group of chars and numbers ordered by skill
#define group_chars1 string("eishtmo")
#define group_chars2 string("awjuv")
#define group_chars3 string("ndbg")
#define group_chars4 string("rplf")
#define group_chars5 string("kcyqzx")
#define group_numbrs string("0123456789")


// give a random string from input
string Blocks::randstring(string input, unsigned int num)
{
    unsigned int size = input.size();

    librandom::Random RND;

    string output;
    output.clear();

    while(num!=0)
    {
	unsigned int pos = RND.integer(0, size-1);
        output +=input[pos];
        num--;
    }

    return output;
}

string Blocks::gen(string input, unsigned int num) // output a string (of size num) chars taken from input
{
    string output;
    output.clear();
    
    unsigned int i = 0;
    while(num)
    {
	output += input[i];
	num--;
	i++;
	if(i==input.size()) i=0;
    }
    return output;
}	

unsigned int Blocks::share()
{
    // Count number of group_chars used in this skill
        
    unsigned int val = m_skill & 0x3F;
    unsigned int counter = 0;

    do
    {
	if(val & 0x01)
	    counter++;
	
	val = val >> 1;
    }
    while(val);
     
    unsigned int total = m_num_strings * m_num_chars;
    unsigned int bound = total/counter;
    
    if(total %  counter)
	bound++;

    return bound;  // bound is number of chars on total that will belong to a group_chars    
}

Blocks::Blocks(unsigned int num, unsigned int s, unsigned int numch): 
    m_num_chars(numch), m_num_strings(num), m_skill(s)
{
    if(m_skill & mixed)
	m_prepare_mixed();

    if(m_skill & submixed)
	m_prepare_submixed();

    if((m_skill & 0xC0) == 0)
	m_prepare_ordered();
}

Blocks::Blocks(const Blocks& cpy)
{
    m_strings = cpy.m_strings;
}

void Blocks::m_prepare_mixed()
{
    if(m_skill & chars1) // if is used in skill group_chars1
	m_strings += group_chars1;
	
    if(m_skill & chars2) // So on..
	m_strings += group_chars2;
	    
    if(m_skill & chars3)
	m_strings += group_chars3;
	
    if(m_skill & chars4)
	m_strings += group_chars4;
	    
    if(m_skill & chars5)
	    m_strings += group_chars5;
	    
    if(m_skill & numbrs)
	m_strings += group_numbrs;
	
    m_strings = randstring(m_strings, m_num_chars * m_num_strings);
}

void Blocks::m_prepare_submixed()
{
    unsigned int bound = share();

    if(m_skill & chars1) // if is used in skill group_chars1
	m_strings += randstring(group_chars1, bound);

    if(m_skill & chars2) // So on..
	m_strings += randstring(group_chars2, bound);
	    
    if(m_skill & chars3)
	m_strings += randstring(group_chars3, bound);
	
    if(m_skill & chars4)
	m_strings += randstring(group_chars4, bound);
	    
    if(m_skill & chars5)
	m_strings += randstring(group_chars5, bound);
    
    if(m_skill & numbrs)
	m_strings += randstring(group_numbrs, bound);

    m_strings = m_strings.substr(0, m_num_chars * m_num_strings);
}

void Blocks::m_prepare_ordered()
{
    unsigned int bound = share();

    if(m_skill & chars1)
	m_strings += gen(group_chars1, bound);

    if(m_skill & chars2)
	m_strings += gen(group_chars2, bound);
    
    if(m_skill & chars3)
	m_strings += gen(group_chars3, bound);

    if(m_skill & chars4)
	m_strings += gen(group_chars4, bound);
    
    if(m_skill & chars5)
	m_strings += gen(group_chars5, bound);
    
    if(m_skill & numbrs)
	m_strings += gen(group_numbrs, bound);

    m_strings = m_strings.substr(0, m_num_chars * m_num_strings);
}

Blocks::~Blocks()
{
    m_strings.clear();
}

libkeyer::Keyer& libexercises::operator<<(libkeyer::Keyer& out, const Blocks& exc)
{
    std::list<std::string> lks = exc.tokenize();
    typedef std::list< std::string >::const_iterator c_str;
    
    for(c_str lks_it = lks.begin(); lks_it != lks.end(); lks_it++)
	out << *lks_it;

    return out;		
}

std::list<std::string> Blocks::tokenize() const
{
    std::list<std::string> tmp_list;
    string tmp_str;
    unsigned int count = 0;

    for(unsigned i=0; i < m_strings.size(); ++i)
    {	
	if(count == m_num_chars)
	{
	    tmp_list.push_back(tmp_str);
	    tmp_str.clear();
	    count = 0;
	}
	tmp_str += m_strings[i];
	count++;
    }

    tmp_list.push_back(tmp_str);

    return tmp_list;
}

/*
unsigned int Blocks::execute()
{
    current_keyer << blocks_exc;

    sleep(beginpause);

    check(blocks_exc);
}
*/
