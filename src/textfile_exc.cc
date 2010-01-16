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

#include "textfile.hh"
#include "keyer.hh"
#include "datafile.hh"

#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

void OnTextFile()
{
    string fileconf_name(getenv("HOME"));
    fileconf_name += "/.aldorc";
    
    libdatafile::Datafile fileconf(fileconf_name, libdatafile::Read);  //read config from datafile ~/.aldorc
    
    libdatafile::sec_it keyer_sec = fileconf.section("Keyer");
    unsigned int beginpause = keyer_sec->option("BeginPause")->get();
    unsigned int speed = keyer_sec->option("Speed")->get();
    unsigned int charpause = keyer_sec->option("CharPause")->get();
    unsigned int strpause = keyer_sec->option("StringPause")->get();
    unsigned int dotlen = keyer_sec->option("DotLength")->get();
    unsigned int linelen = keyer_sec->option("LineLength")->get();
    unsigned int tone = keyer_sec->option("Tone")->get();
    string       device = keyer_sec->option("Device")->getstr();
        
    string filename;
    do
    {
	cout << endl;
	cout<<insert_filename<<": ";
	cin.clear();
    }
    while(! getline(cin, filename) );

    libaudiostream::AudioWorkSpace aws(device);

    libkeyer::Keyer current_keyer(aws, speed, charpause, strpause, dotlen, linelen);

    current_keyer.set_tone(tone);

    libexercises::TextFile textfile_exc(filename);
    
    cout<<msg_speed<<speed<<" wpm"<<endl;
    cout<<msg_start<<endl;    

    sleep(beginpause);

    current_keyer<<textfile_exc;
}
