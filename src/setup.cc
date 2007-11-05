/***************************************************************************
                                Aldo
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

#include "resources.hh"

#include "menu.hh"
#include "dialog.hh"
#include "datafile.hh"
#include "skill.hh"

#include <string>
#include <cstdlib>

#define CONFIG_FILE ".aldorc"

using namespace std;
using namespace libmenu;
using namespace libdatafile;

/*
 * This function returns the data structure containing
 * the current configuration.
 */
Datafile get_configuration()
{
    string fileconf_name(getenv("HOME"));
    fileconf_name += "/";
    fileconf_name += CONFIG_FILE;
    Datafile fileconf(fileconf_name, Update);
    return fileconf;
}

/*
 * This function offers the user te possibility to change a
 * configuration option interactively.
 * The option's old value is displayed in the prompt.
 * Pressing Enter keeps the option's old value.
 * This function automatically distinguishes between integer and string
 * input values and sets the proper one.
 */
void update_option(opt_it option, const string& label)
{
    string tmpstr;
    unsigned int tmpint = option->get();

    if(tmpint == 9999)
    {
	tmpstr = option->getstr();

	do
	{
	    cout << endl;
	    cout << label << " [";
	    cout << tmpstr;
	    cout << "]: ";

	    cin.clear();
	}
	while( ! getline(cin, tmpstr) );

	// if input is empty, keep current value unchanged
	if(tmpstr[0] == '\0')
	    return;

	option->set(tmpstr);
    }
    else
    {
	do
	{
	    cout << endl;
	    cout << label << " [";
	    cout << tmpint;
	    cout << "]: ";
	    
	    cin.clear();
	}
	while( ! getline(cin, tmpstr) );

	// if input is empty, keep current value unchanged
	if(tmpstr[0] == '\0')
	    return;

	tmpint = (unsigned int)atoi(tmpstr.c_str());

	option->set(tmpint);
    }
}

void OnKeyerConf()
{
    Datafile cfg = get_configuration();
    sec_it this_sec = cfg.section("Keyer");
    
    cin.ignore();

    update_option(this_sec->option("BeginPause"), insert_beginpause);
    update_option(this_sec->option("CharPause"), insert_charpause);
    update_option(this_sec->option("StringPause"), insert_strpause);
    update_option(this_sec->option("Speed"), insert_wpm);
    update_option(this_sec->option("DotLength"), insert_dotlen);
    update_option(this_sec->option("LineLength"), insert_linelen);
    update_option(this_sec->option("Tone"), insert_tone);
}

void OnBlocksConf()
{
    Datafile cfg = get_configuration();
    sec_it this_sec = cfg.section("Blocks");

    cin.ignore();

    update_option(this_sec->option("StringsNumber"), insert_strnum);

    update_option(this_sec->option("StringLength"), insert_strlen);

    Dialog<unsigned int> ask_skill(dlg_skill_title, main_menu_prompt);
    ask_skill.add_default_choice(dlg_skill_choice1,libexercises::skill1);
    ask_skill.add_choice(dlg_skill_choice2,libexercises::skill2);
    ask_skill.add_choice(dlg_skill_choice3,libexercises::skill3);
    ask_skill.add_choice(dlg_skill_choice4,libexercises::skill4);
    ask_skill.add_choice(dlg_skill_choice5,libexercises::skill5);
    ask_skill.add_choice(dlg_skill_choice6,libexercises::skill6);
    ask_skill.add_choice(dlg_skill_choice7,0);

    unsigned int skill = ask_skill.show();

    if(skill == 0)
	while(true)
	{
	    Dialog<unsigned int> ask_skill2(dlg_skill2_title, main_menu_prompt);

	    ask_skill2.add_default_choice(dlg_skill2_choice1,libexercises::chars1);
	    ask_skill2.add_choice(dlg_skill2_choice2,libexercises::chars2);
	    ask_skill2.add_choice(dlg_skill2_choice3,libexercises::chars3);
	    ask_skill2.add_choice(dlg_skill2_choice4,libexercises::chars4);
	    ask_skill2.add_choice(dlg_skill2_choice5,libexercises::chars5);
	    ask_skill2.add_choice(dlg_skill2_choice6,libexercises::numbrs);
	    ask_skill2.add_choice(dlg_skill2_choice7,0x1000);
	    ask_skill2.add_choice(dlg_skill2_choice8,libexercises::submixed);
	    ask_skill2.add_choice(dlg_skill2_choice9,libexercises::mixed);
	    ask_skill2.add_choice(dlg_skill2_choice10,0);

	    unsigned int skill2 = ask_skill2.show();

	    if(skill2 != 0 && skill2 != 0x1000)
		skill |= skill2;

	    if(skill2 == 0)
		break;
	}

    this_sec->option("Skill")->set(skill);
}

void OnKochConf()
{
    Datafile cfg = get_configuration();
    sec_it this_sec = cfg.section("Koch");

    cin.ignore();

    update_option(this_sec->option("Chars"), insert_chars);

    update_option(this_sec->option("StringsNumber"), insert_strnum);

    update_option(this_sec->option("StringLength"), insert_strlen);

    update_option(this_sec->option("StartSpeed"), insert_wpm);

    update_option(this_sec->option("Skill"), insert_pos);
    
    update_option(this_sec->option("Difficulty"), insert_pos);    
}

void OnQrzConf()
{
    Datafile cfg = get_configuration();
    sec_it this_sec = cfg.section("Qrz");
	
    cin.ignore();

    update_option(this_sec->option("CallFormat"), insert_callformat);
    update_option(this_sec->option("StringsNumber"), insert_strnum);
}

void OnResetDefault()
{
    string fileconf_name(getenv("HOME"));
    fileconf_name += "/";
    fileconf_name += CONFIG_FILE;

    Datafile fileconf(fileconf_name, Create);

    fileconf.add_section("Keyer");
    sec_it keyer_sec = fileconf.section("Keyer");

    keyer_sec->add_option("BeginPause");
    keyer_sec->option("BeginPause")->set(2);

    keyer_sec->add_option("Speed");
    keyer_sec->option("Speed")->set(10);

    keyer_sec->add_option("CharPause");
    keyer_sec->option("CharPause") ->set(3);

    keyer_sec->add_option("StringPause");
    keyer_sec->option("StringPause")->set(7);

    keyer_sec->add_option("DotLength");
    keyer_sec->option("DotLength")->set(1);

    keyer_sec->add_option("LineLength");
    keyer_sec->option("LineLength")->set(3);

    keyer_sec->add_option("Tone");
    keyer_sec->option("Tone")->set(900);

    fileconf.add_section("Blocks");
    sec_it blocks_sec = fileconf.section("Blocks");

    blocks_sec->add_option("StringsNumber");
    blocks_sec->option("StringsNumber")->set(3);

    blocks_sec->add_option("StringLength");
    blocks_sec->option("StringLength")->set(5);

    blocks_sec->add_option("Skill");
    blocks_sec->option("Skill")->set(libexercises::skill1);

    fileconf.add_section("Koch");
    sec_it koch_sec = fileconf.section("Koch");

    koch_sec->add_option("Chars");
    koch_sec->option("Chars")->set("eishtmoawjuvndbgrplfkcyqzx0123456789");

    koch_sec->add_option("StringsNumber");
    koch_sec->option("StringsNumber")->set(15);

    koch_sec->add_option("StringLength");
    koch_sec->option("StringLength")->set(2);

    koch_sec->add_option("StartSpeed");
    koch_sec->option("StartSpeed")->set(20);

    koch_sec->add_option("Skill");
    koch_sec->option("Skill")->set(2);

    koch_sec->add_option("Difficulty");
    koch_sec->option("Difficulty")->set(0);
    
    fileconf.add_section("Qrz");
    sec_it qrz_sec = fileconf.section("Qrz");

    qrz_sec->add_option("CallFormat");
    qrz_sec->option("CallFormat")->set("@@@@@");

    qrz_sec->add_option("StringsNumber");
    qrz_sec->option("StringsNumber")->set(3);
}

void OnExitSetup(Menu& main)
{
    main.close();
}

void OnSetup()
{
    Menu setup_menu(conf_menu_title, main_menu_prompt);

    const id_type keyconf_id  = 1;
    const id_type clasconf_id = 2;
    const id_type kochconf_id = 3;
    const id_type qrzconf_id = 4;
    const id_type rstdfl_id = 5;
    const id_type exit_id = 6;

    setup_menu.add_item(keyconf_id,   conf_menu_item1, OnKeyerConf);
    setup_menu.add_item(clasconf_id,  conf_menu_item2, OnBlocksConf);
    setup_menu.add_item(kochconf_id,  conf_menu_item3, OnKochConf);
    setup_menu.add_item(qrzconf_id,   conf_menu_item4, OnQrzConf);
    setup_menu.add_item(rstdfl_id,    conf_menu_item5, OnResetDefault);
    setup_menu.add_item(exit_id,      conf_menu_item6, OnExitSetup);

    while( setup_menu.running() )
    {
	try
	{
	    setup_menu.show();
	}
	catch(Not_datafile_format e)
	{
	    cerr<<errmsg_noformat<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
	catch(Over_write_file e)
	{
	    cerr<<errmsg_overwrite<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
	catch(Option_not_found e)
	{
	    cerr<<errmsg_nooption<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
	catch(Section_not_found e)
	{
	    cerr<<errmsg_nosection<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
	catch(File_not_opened e)
	{
	    cerr<<errmsg_noopenfile<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
	catch(File_not_exist e)
	{
	    cerr<<errmsg_nofile<<endl;
	    cerr<<errmsg_conf<<endl;
	    return;
	}
    }
}
