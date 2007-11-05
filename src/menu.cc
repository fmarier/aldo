/***************************************************************************
                             libmenu
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

#include "menu.hh"

#include <iostream>
#include <cctype>

using namespace std;
using namespace libmenu;

typedef std::vector<Item>::const_iterator CI;
typedef std::vector<Item>::iterator IT;

Item::Item(const Item& cpy)
{
    m_id = cpy.m_id;
    m_type = cpy.m_type;
    m_caption = cpy.m_caption;
    m_cmd1 = cpy.m_cmd1;
    m_cmd2 = cpy.m_cmd2;
}

void Item::exe(Menu& menu) const
{
    switch(m_type)
    {
    case type1:
	if(m_cmd1)
	    (*m_cmd1)();
	break;

    case type2:
	if(m_cmd2)
	    (*m_cmd2)(menu);
	break;

    case none:
	return;
    }
}

Item& Item::operator=(const Item& i)
{
    m_caption = i.m_caption;
    m_cmd1 = i.m_cmd1;
    m_cmd2 = i.m_cmd2;
    return(*this);
}

string Item::caption() const
{
    return m_caption;
}
		
Menu::Menu(): m_title("Menu"), m_prompt("Prompt:"), m_running(true)
{
    m_its.clear(); 
}

Menu::Menu(const string& t, const string& p):
m_title(t), m_prompt(p), m_running(true)
{
    m_its.clear();
}

Menu::Menu(const Menu& cpy)
{
    m_title = cpy.m_title;
    m_prompt = cpy.m_prompt;
    m_its = cpy.m_its;
    m_running = cpy.m_running;
}

void Menu::operator--()
{
    m_its.pop_back();
}

void Menu::add_item(id_type id, std::string c, Function1 f)
{
    m_its.push_back( Item(id,c,f) );
}

void Menu::add_item(id_type id, std::string c, Function2 f)
{
    m_its.push_back( Item(id, c, f) );
}

void Menu::add_item_at(unsigned int pos, id_type id, std::string c, Function1 f)
{
    IT it(&m_its[pos]);
    m_its.insert(it, Item(id,c,f) );
}

void Menu::add_item_at(unsigned int pos, id_type id, std::string c, Function2 f)
{
    IT it(&m_its[pos]);
    m_its.insert(it, Item(id,c,f) );
}

void Menu::delete_item_at(unsigned int pos)
{
    IT it(&m_its[pos]);
    m_its.erase(it);
}

void Menu::delete_item(id_type id)
{
    for(IT it = m_its.begin(); it != m_its.end(); it++)
	if(it->id() == id)
	    m_its.erase(it);
}

void Menu::show()
{
    cout<<m_title<<endl;

    unsigned char i = 49;
    for(CI it=m_its.begin(); it!=m_its.end(); it++, i++)
    {
	cout<<"\t"<<i<<": "<<it->caption()<<endl;

	if(i == 57)
	    i=96;
    }
    
    unsigned choice = m_its.size();
    do
    {
	string trash;
	cout << m_prompt << ": ";

	if (! getline(cin,trash) ) // If there is an input error
	{
	    cout << endl;
	    std::cin.clear();
	    continue;
	}

	if(!trash.empty())
	    if (int(trash[0]) > 47)
	    {
		if(int(trash[0]) < 58)
		    choice = int(trash[0]) - 49;

		if( (int(trash[0]) > 96) && (int(trash[0]) < 123) ) 
		    choice = int(trash[0]) - 88;
	    }
    }
    while( choice > m_its.size()-1 );
    cout << endl;
    
    m_last = m_its.at(choice).id();
 
    m_its.at(choice).exe(*this);
}

bool Menu::find(id_type id)
{
    for(CI it = m_its.begin(); it!=m_its.end(); it++)
	if(it->id() == id)
	    return true;
    return false;
}
