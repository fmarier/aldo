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

#include "koch.hh"
#include "keyer.hh"
#include "datafile.hh"
#include "dialog.hh"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

unsigned int check(const libexercises::Koch &);
string skillname(unsigned int);

void OnKoch()
{
    string fileconf_name(getenv("HOME"));
    fileconf_name += "/.aldorc";

    //read config from datafile ~/.aldorc
    libdatafile::Datafile fileconf(fileconf_name, libdatafile::Update);

    libdatafile::sec_it keyer_sec = fileconf.section("Keyer");
    unsigned int beginpause = keyer_sec->option("BeginPause")->get();
    unsigned int charpause = keyer_sec->option("CharPause")->get();
    unsigned int strpause = keyer_sec->option("StringPause")->get();
    unsigned int dotlen = keyer_sec->option("DotLength")->get();
    unsigned int linelen = keyer_sec->option("LineLength")->get();
    unsigned int tone = keyer_sec->option("Tone")->get();
    string       device = keyer_sec->option("Device")->getstr();

    libdatafile::sec_it koch_sec = fileconf.section("Koch");
    std::string chars = koch_sec->option("Chars")->getstr();
    unsigned int strnum = koch_sec->option("StringsNumber")->get();
    unsigned int strlen = koch_sec->option("StringLength")->get();
    unsigned int startspeed = koch_sec->option("StartSpeed")->get();
    unsigned int skill = koch_sec->option("Skill")->get();

    unsigned int next_difficulty = koch_sec->option("Difficulty")->get();
    
    Dialog<bool> ask_exit_koch(dlg_koch_title, main_menu_prompt);
    ask_exit_koch.add_choice(dlg_koch_exit, false);
    ask_exit_koch.add_default_choice(dlg_koch_continue, true);

    libexercises::Koch koch_exc(chars, strnum, strlen, skill, next_difficulty);

    do
    {
	cout<<msg_speed<<startspeed<<" wpm"<<endl;
	cout<<msg_start<<endl;

	cout<<"Letters in lesson: ";
	typedef std::list< std::string >::const_iterator c_str;
	for(c_str cit = chars.begin(); cit != chars.end(); cit++)
	    cout<<*cit<<" ";
	cout<<endl;

	libaudiostream::AudioWorkSpace aws(device);

	libkeyer::Keyer current_keyer(aws, startspeed, charpause, strpause, dotlen, linelen);

	current_keyer.set_tone(tone);

	sleep(beginpause);

	current_keyer << koch_exc;
	
	sleep(beginpause);

	if( check(koch_exc) >= 90)
	    koch_exc.next();
	else
	    koch_exc.shuffle();
    }
    while(ask_exit_koch.show());

    //save exercise status
    koch_sec->option("Chars")->set(koch_exc.get_chars());
    koch_sec->option("StringsNumber")->set(koch_exc.strnum());
    koch_sec->option("StringLength")->set(koch_exc.strlen());
    koch_sec->option("Skill")->set(koch_exc.skill());
    koch_sec->option("Difficulty")->set(koch_exc.difficulty());    
}
