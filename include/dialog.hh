// -*- C++ -*-
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

#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Choice
{
private:
    std::string m_caption;
    T m_return_value;

public:
    Choice();
    Choice(std::string, T);

    Choice(const Choice<T> & cpy)
    {
	m_caption = cpy.m_caption;
	m_return_value = cpy.m_return_value;
    }

    Choice<T>& operator=(const Choice<T>& cpy)
    {
	m_caption = cpy.m_caption;
	m_return_value = cpy.m_return_value;
	
	return *this;
    }

    ~Choice()
    {}

    std::string caption() const;
    T selected() const;
};

template <typename T>
class Dialog
{
private:
    std::string m_title;
    std::string m_prompt;
    std::vector <Choice <T> > m_choices;
    unsigned int m_default;
    unsigned int m_size;

public:
    Dialog();
    Dialog(std::string, std::string);
    Dialog(const Dialog&);

    void add_choice(std::string, T);
    void add_default_choice(std::string, T);
    T show();
};

template <typename T>
Choice<T>::Choice(): m_caption("Empty"), m_return_value(0)
{}

template <typename T>
Choice<T>::Choice(std::string c, T v): m_caption(c), m_return_value(v)
{}

template <typename T>
std::string Choice<T>::caption() const
{
    return m_caption;
}

template <typename T>
T Choice<T>::selected() const
{
    return m_return_value;
}

template <typename T>
Dialog<T>::Dialog(): m_title("Dialog"), m_prompt("Prompt:"), m_default(0)
{}

template <typename T>
Dialog<T>::Dialog(std::string t, std::string p):m_title(t), m_prompt(p), m_default(0), m_size(0)
{}

template <typename T>
Dialog<T>::Dialog(const Dialog& copy)
{
    m_title = copy.m_title;
    m_prompt = copy.m_prompt;
    m_choices = copy.m_choices;
    m_default = copy.m_default;
}

template <typename T>
void Dialog<T>::add_choice(std::string c, T r)
{
    m_choices.push_back(Choice<T>(c,r));
    m_size++;
}

template <typename T>
void Dialog<T>::add_default_choice(std::string c, T r)
{
    m_size++;
    m_choices.push_back(Choice<T>(c,r));
    m_default = m_size;
}

template <typename T>
T Dialog<T>::show()
{
    std::cin.ignore();

    std::cout<<m_title<<std::endl;

    unsigned char i = 49;

    for(unsigned int it = 0; it < m_choices.size(); it++, i++)
    {
	std::cout<<"\t"<<i<<": "<<m_choices.at(it).caption()<< std::endl;
	
	if(i == 57)
	    i = 96;
    }

    unsigned choice = m_choices.size();
    
    do
    {
	std::string trash;

	if(m_default)
	    std::cout << m_prompt << " [" << m_default << "]: ";
	else
	    std::cout << m_prompt << ": ";

	if ( ! std::getline(std::cin, trash) )  // If there is an input error
	{
	    std::cout << std::endl;
	    std::cin.clear();
	    continue;
	}

	if(!trash.empty())
	{
	    if (int(trash[0]) > 47)
	    {
		if(int(trash[0]) < 58)
		    choice = int(trash[0]) - 49;

		if( (int(trash[0]) > 96) && (int(trash[0]) < 123) ) 
		    choice = int(trash[0]) - 88;
	    }
	}
	else
	    choice = m_default - 1;

    }
    while( choice > m_choices.size()-1 );

    return m_choices.at(choice).selected();
}
#endif //DIALOG_H
