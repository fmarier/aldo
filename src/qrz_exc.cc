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

#include "resources.hh"

#include "qrz.hh"
#include "keyer.hh"
#include "datafile.hh"

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

// unsigned int check(const libexercises::Classic&);
std::string skillname(unsigned int);

void OnQrz()
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
    
    libdatafile::sec_it qrz_sec = fileconf.section("Qrz");
    string callformat = qrz_sec->option("CallFormat")->getstr();
    unsigned int strnum = qrz_sec->option("StringsNumber")->get();	

    libaudiostream::AudioWorkSpace aws;

    libkeyer::Keyer current_keyer(aws, speed, charpause, strpause, dotlen, linelen);

    current_keyer.set_tone(tone);
    
    cout<<msg_speed<<speed<<" wpm"<<endl;
    cout<<msg_callformat<<callformat<<endl;
    cout<<msg_start<<endl;

    libexercises::Qrz qrz_exc(callformat, strnum);
  
    sleep(beginpause);
    
    current_keyer<<qrz_exc;

    sleep(beginpause);

//    check(qrz_exc);
}
