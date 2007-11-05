// -*- C++ -*-
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

#ifdef HAVE_CONFIG_H
 #include "config.h"
#endif

#define chkmsg_1  "Please input the signs you copied."
#define chkmsg_2  "If you didn't copy a sign, put '@'."

#define fbkmsg_title "EVALUATION"

#define ovrmsg_title "Overall success rate"

#define smbmsg_title     "Success rate per symbol"
#define smbmsg_symbol    "symbol"
#define smbmsg_copied    "copied"
#define smbmsg_keyed     "keyed"
#define smbmsg_correct   "correct"
#define smbmsg_incorrect "incorrect"
#define smbmsg_missed    "missed"
#define smbmsg_percent   "percentages"

#define cmpmsg_title     "Comparison between keyed and copied sign groups"
#define cmpmsg_group     "Group index"
#define cmpmsg_correct   "correct"
#define cmpmsg_incorrect "incorrect"
#define cmpmsg_missed    "missed"
#define cmpmsg_keyed     "Keyed signs = what was transmitted"
#define cmpmsg_copied    "Copied signs = what you have input"

#define errmsg_noformat   "Configuration file is incorrectly formatted"
#define errmsg_overwrite  "You have tried to overwrite the configuration file"
#define errmsg_nooption   "Can't find an option in the configuration file"
#define errmsg_nosection  "Can't find section in the configuration file"
#define errmsg_noopenfile "Can't open the configuration file"
#define errmsg_nofile     "The configuration file doesn't exist"
#define errmsg_conf       "Select Default Settings in the Setup Menu"
#define errmsg_devicefile "Can't write on device file "
#define errmsg_rate       "Wrong rate"
#define errmsg_format     "Format error"
#define errmsg_fragment   "Fragment error"
#define errmsg_stereo     "Stereo error"

#define main_menu_title  "Aldo " VERSION " Main Menu"
#define main_menu_prompt "Your choice"
#define main_menu_item1  "Blocks method"
#define main_menu_item2  "Koch method"
#define main_menu_item3  "Read from file"
#define main_menu_item4  "Callsigns"
#define main_menu_item5  "Setup"
#define main_menu_item6  "Exit"

#define msg_start      "About to start keying. Get ready..."
#define msg_changes    "Change these settings from the Setup Menu."
#define msg_speed      "Keying speed: "
#define msg_strlen     "String length: "
#define msg_skill      "Training character set: "
#define msg_strnum     "Number of strings: "
#define msg_callformat "Template callsign: "

#define dlg_skill_title   "Select training character set"
#define dlg_skill_choice1 "e,i,s,h,t,m,o"
#define dlg_skill_choice2 "e,i,s,h,t,m,o,a,j,w,v,u"
#define dlg_skill_choice3 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g"
#define dlg_skill_choice4 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g,r,p,l,f"
#define dlg_skill_choice5 "e,i,s,h,t,m,o,a,w,j,u,v,n,d,b,g,r,p,l,f,k,c,y,q,z,x"
#define dlg_skill_choice6 "All chars and numbers"
#define dlg_skill_choice7 "Custom character set"

#define dlg_skill2_title    "Add a group or option to your exercise:"
#define dlg_skill2_choice1  "e,i,s,h,t,m,o"
#define dlg_skill2_choice2  "a,w,j,v,u"
#define dlg_skill2_choice3  "n,d,b,g"
#define dlg_skill2_choice4  "r,p,l,f"
#define dlg_skill2_choice5  "k,c,y,q,z,x"
#define dlg_skill2_choice6  "0123456789"
#define dlg_skill2_choice7  "Chars ordered "
#define dlg_skill2_choice8  "Chars submixed with group order "
#define dlg_skill2_choice9  "Chars mixed without group order "
#define dlg_skill2_choice10 "End"

#define dlg_koch_title    "Do you want to continue with the Koch method?"
#define dlg_koch_continue "Yes"
#define dlg_koch_exit     "No"

#define insert_device     "Soundcard device file"
#define insert_samplerate "Sample rate"
#define insert_samplesize "Sample size"

#define insert_beginpause "Pause before keying (seconds)"
#define insert_charpause  "Length of space between two characters in a word (number of dots)"
#define insert_strpause   "Length of space between two words (number of dots)"
#define insert_dotlen     "Dit length"
#define insert_linelen    "Dah length"
#define insert_tone       "Frequency of buzzer (Hz)"

#define insert_chars      "Training character set"
#define insert_pos        "Starting position"    
#define insert_wpm        "Keying speed (words per minute)"
#define insert_strlen     "Length of strings"
#define insert_filename   "Name of file to read"
#define insert_strnum     "Number of strings to send"
#define insert_callformat "Enter callsign template"

#define conf_menu_title "Setup Menu"
#define conf_menu_item1 "Keyer Setup"
#define conf_menu_item2 "Blocks method Setup"
#define conf_menu_item3 "Koch method Setup"
#define conf_menu_item4 "Qrz exercise Setup"
#define conf_menu_item5 "Default Settings"
#define conf_menu_item6 "Return to Main Menu"
