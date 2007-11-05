// -*- C++ -*-
/***************************************************************************
                             libmenu
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

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

namespace libmenu
{
    class Menu;

    enum item_type { none = 0, type1 = 1, type2 = 2};

    typedef unsigned int id_type;

    typedef void (*Function1)();
    typedef void (*Function2)(Menu&);

    class Item
    {
    private:
	unsigned int m_id;
	std::string m_caption;
	
	item_type m_type;

	Function1 m_cmd1;
	Function2 m_cmd2;
	
    public:
	Item()
	    :m_id(0), m_type(none), m_cmd1(0), m_cmd2(0)
	{}

	Item(id_type id, std::string c, Function1 f1)
	    : m_id(id), m_caption(c), m_type(type1), m_cmd1(f1), m_cmd2(0)
	{}
	
	Item(id_type id, std::string c, Function2 f2)
	    : m_id(id), m_caption(c), m_type(type2), m_cmd1(0), m_cmd2(f2)
	{}

	Item(const Item& cpy);

	std::string caption() const;
	
	void exe(Menu&) const;
	
	item_type get_type()
	{
	    return m_type;
	}

	Item& operator=(const Item&);
	
	inline id_type id() const
	{
	    return m_id;
	}
    };

    class Menu
    {
    private:
	std::string m_title;
	std::string m_prompt;
	std::vector<Item> m_its;
	bool m_running;
	unsigned int m_last;
		
    public:
	Menu();
	Menu(const std::string&, const std::string&);
	Menu(const Menu& cpy);
	
	void show();
	void add_item(id_type, std::string, Function1);
	void add_item(id_type, std::string, Function2);
	void operator--();
	void add_item_at(unsigned int, id_type, std::string, Function1);
	void add_item_at(unsigned int, id_type, std::string, Function2);
	void delete_item_at(unsigned int);
	void delete_item(id_type);
	bool find(id_type);

	inline void set_title(std::string title)
	{
	    m_title = title;
	}

	inline void set_prompt(std::string prompt)
	{
	    m_prompt = prompt;
	}

	inline bool running() const
	{
	    return m_running;
	}
	
	inline void close()
	{
	    m_running = false;
	}
	
	inline unsigned last_selected()
	{
	    return m_last;
	}
    };
}
#endif // MENU_H
