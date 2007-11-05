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

#include "dialog.hh"
#include "blocks.hh"
#include "keyer.hh"
#include "datafile.hh"

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>

using namespace std;

unsigned int check(const libexercises::Blocks&);
std::string skillname(unsigned int);

void OnBlocks()
{
    string fileconf_name(getenv("HOME"));
    fileconf_name += "/.aldorc";

    libdatafile::Datafile fileconf(fileconf_name, libdatafile::Read);  // read config from ~/.aldorc
    
    libdatafile::sec_it keyer_sec = fileconf.section("Keyer");
    unsigned int beginpause = keyer_sec->option("BeginPause")->get();
    unsigned int speed = keyer_sec->option("Speed")->get();
    unsigned int charpause = keyer_sec->option("CharPause")->get();
    unsigned int strpause = keyer_sec->option("StringPause")->get();
    unsigned int dotlen = keyer_sec->option("DotLength")->get();
    unsigned int linelen = keyer_sec->option("LineLength")->get();
    unsigned int tone = keyer_sec->option("Tone")->get();
    
    libdatafile::sec_it quick_sec = fileconf.section("Blocks");
    unsigned int strlen = quick_sec->option("StringLength")->get();
    unsigned int strnum = quick_sec->option("StringsNumber")->get();
    unsigned int skill = quick_sec->option("Skill")->get();

    libaudiostream::AudioWorkSpace aws;

    libkeyer::Keyer current_keyer(aws, speed, charpause, strpause, dotlen, linelen);

    current_keyer.set_tone(tone);
    
    cout<<msg_speed<<speed<<" wpm"<<endl;
    cout<<msg_strlen<<strlen<<endl;
    cout<<msg_strnum<<strnum<<endl;
    cout<<msg_skill<<skillname(skill)<<endl;

    cout<<msg_start<<endl;

    libexercises::Blocks blocks_exc(strnum, skill, strlen);

    sleep(beginpause);

    current_keyer<<blocks_exc;

    sleep(beginpause);

    check(blocks_exc);
}

std::string skillname(unsigned int v)
{
    bool comma = false;
    string output;
    output.clear();
       
    if(v & libexercises::chars1)
    {
	output += std::string(dlg_skill_choice1);
	comma = true; 
    }

    if(v & libexercises::chars2)
    {
	if(comma)
	    output += ",";

	output += std::string(dlg_skill2_choice2);
    }

    if(v & libexercises::chars3)
    {
	if(comma)
	    output += ",";
	
	output += std::string(dlg_skill2_choice3);
    }
	
    if(v & libexercises::chars4)
    {
	if(comma)
	    output += ",";

	output += std::string(dlg_skill2_choice4);
    }
	
    if(v & libexercises::chars5)
    {
	if(comma)
	    output += ",";

	output += std::string(dlg_skill2_choice5);
    }
    
    if(v & libexercises::numbrs)
    {
	if(comma)
	    output += ",";

	output += std::string(dlg_skill2_choice6);
    }
	
    output += "\n";
    
    if(v & libexercises::submixed)
    {
	output += std::string(dlg_skill2_choice8);
    }

    if(v & libexercises::mixed)
    {
	output += std::string(dlg_skill2_choice9);
    }
    
    if((v & 0xC0) == 0)
    {
	output += std::string(dlg_skill2_choice7);
    }
    
    return output;
}
