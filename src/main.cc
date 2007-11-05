// -*- C++ -*-
/***************************************************************************
                           Aldo
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
#include "datafile.hh"
#include "resources.hh"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace libmenu;

void OnBlocks();   // defined in blocks_exc.cpp
void OnKoch();      // defined in koch_exc.cpp
void OnTextFile();  // defined in textfile_exc.cpp
void OnQrz();       // defined in qrz_exc.cpp
void OnSetup();     // defined in setup.cpp
void OnExit(Menu&); // defined in this file
void OnResetDefault();
void CheckConfigFile();

int main()
{
    const id_type quickstart_id = 1;
    const id_type koch_id = 2;
    const id_type textfile_id = 3;
    const id_type qrz_id = 4;
    const id_type setup_id = 5;
    const id_type exit_id = 6;

    CheckConfigFile();    

    Menu aldo_menu;
    aldo_menu.set_title(main_menu_title);
    aldo_menu.set_prompt(main_menu_prompt);

    aldo_menu.add_item(quickstart_id, main_menu_item1, OnBlocks);
    aldo_menu.add_item(koch_id, main_menu_item2, OnKoch);
    aldo_menu.add_item(textfile_id, main_menu_item3, OnTextFile);
    aldo_menu.add_item(qrz_id, main_menu_item4, OnQrz);
    aldo_menu.add_item(setup_id, main_menu_item5, OnSetup);
    aldo_menu.add_item(exit_id, main_menu_item6, OnExit);

    while( aldo_menu.running() )
	try
	{
	    aldo_menu.show();
	}
	catch(libdatafile::Not_datafile_format e)
	{
	    std::cerr<<errmsg_noformat<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
	catch(libdatafile::Over_write_file e)
	{
	    std::cerr<<errmsg_overwrite<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
	catch(libdatafile::Option_not_found e)
	{
	    std::cerr<<errmsg_nooption<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
	catch(libdatafile::Section_not_found e)
	{
	    std::cerr<<errmsg_nosection<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
	catch(libdatafile::File_not_opened e)
	{
	    std::cerr<<errmsg_noopenfile<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
	catch(libdatafile::File_not_exist e)
	{
	    std::cerr<<errmsg_nofile<<std::endl;
	    std::cerr<<errmsg_conf<<std::endl;
	}
}

void OnExit(Menu& parent_menu)
{
    parent_menu.close();
}

void CheckConfigFile()
{
    std::string fileconf_name(getenv("HOME"));
    fileconf_name += "/.aldorc";

    std::ifstream stream(fileconf_name.c_str());

    if(stream.fail())
	OnResetDefault();
}
