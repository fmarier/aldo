/***************************************************************************
                          libkeyer part of Aldo
                          ---------------------
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

#include "keyer.hh"

using namespace libkeyer;
using namespace libaudiostream;
using namespace std;

typedef unsigned int morse_symbol;

// the first two nybles are the dits/dahs 1 for a dit, 0 for a dah, the last nyble is the number of dits & dahs
static const morse_symbol map[] = 
{
// Letters from map[0] to map[25]
    0x8002, 0x7004, 0x5004, 0x6003, 0x8001, 0xD004, 0x2003,
    0xF004, 0xC002, 0x8004, 0x4003, 0xB004, 0x0002, 0x4002,
    0x0003, 0x9004, 0x2004, 0xA003, 0xE003, 0x0001, 0xC003,
    0xE004, 0x8003, 0x6004, 0x4004, 0x3004,
// Numbers from map[26] to map[35]
    0x0005, 0x8005, 0xC005, 0xE005, 0xF005, 0xF805, 0x7805,
    0x3805, 0x1805, 0x0805,
// punctuation from map[36] to map[52]
    0x5006, // !  -.-.--
    0xB406, // "  .-..-.
    0xA805, // &  .-...
    0x8406, // '  .----.
    0x4805, // (  -.--.
    0x4806, // )  -.--.-
    0xA805, // +  .-.-.
    0x3006, // ,  --..--
    0x7806, // -  -....-
    0xA806, // .  .-.-.-
    0x6805, // /  -..-.
    0x1C06, // :  ---...
    0x5406, // ;  -.-.-.
    0x7005, // =  -...-
    0xCF06, // ?  ..--.. (seems to be playing as ..--.-, which is wrong!)
    0x9406, // @  .--.-.
    0xC806, // _  ..--.-
    0,0,0,0,
    0xFF08
};

Keyer::Keyer(AudioWorkSpace& aws, unsigned int speed, unsigned int ch, unsigned int wd, unsigned int d, unsigned int l)
    : m_aws(aws), m_audio(aws.create_output_stream()), m_speed(speed), m_interch(ch), m_interword(wd), m_tone(900.0), m_dot(d), m_line(l)
{
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int(60000/dpm);
}

void Keyer::set_speed(unsigned int speed)
{
    m_speed = speed;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int(60000/dpm);
}

void Keyer::set_charpause_len(unsigned int len)
{   
    m_interch = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int( 60000/dpm );
}

void Keyer::set_stringpause_len(unsigned int len)
{    
    m_interword = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int( 60000/dpm );
}

void Keyer::set_dot_len(unsigned int len)
{
    m_dot = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int( 60000/dpm );
}

void Keyer::set_line_len(unsigned int len)
{
    m_line = len;
    unsigned int dpm = m_speed*((36 + 4 * m_interch + m_interword)*m_dot);
    m_count = int( 60000/dpm );
}

void Keyer::play(unsigned int n)
{
    libaudiostream::Wave tone = m_aws.gen_sine_wave(m_count * n, m_tone, 0.0);
    libaudiostream::Wave pause = m_aws.gen_pause(m_count);

    m_audio << tone << pause;
}   

Keyer& Keyer::operator<<(const morse_symbol& input)
{
    unsigned int data = input & 0xFF00;
    unsigned int size = input & 0x000F;
    
    while(size != 0)
    {
	if( (data & 0x8000) == 0)
	    play(m_line);

	if( (data & 0x8000) == 0x8000)
	    play(m_dot);

	data = data << 1;

	size--;
    }

    return *this;
}

Keyer& Keyer::operator<<(unsigned char ch)
{
    if( (ch > 96) && (ch < 123))
    {
        // lower case characters
        ch -= 97;
    }
    else if( (ch > 64) && (ch < 91))
    {
        // upper case characters
        ch -= 65;
    }
    else if( (ch >47) && (ch < 58))
    {
        // digits
        ch -= 22;               // -48 + 26 = -22
    }
    else
    {
        // punctuation
        switch( ch ) {
            case 33: ch = 36; break; // !
            case 34: ch = 37; break; // "
            case 38: ch = 38; break; // &
            case 39: ch = 39; break; // '
            case 40: ch = 40; break; // (
            case 41: ch = 41; break; // )
            case 43: ch = 42; break; // +
            case 44: ch = 43; break; // ,
            case 45: ch = 44; break; // -
            case 46: ch = 45; break; // .
            case 47: ch = 46; break; // /
            case 58: ch = 47; break; // :
            case 59: ch = 48; break; // ;
            case 61: ch = 49; break; // =
            case 63: ch = 50; break; // ?
            case 64: ch = 51; break; // @
            case 95: ch = 52; break; // _
            default: ch = 255; break; // no morse for this character
        }
    }

    if(ch != 255)
        *this<<morse_symbol(map[ch]);

    return *this;
}

Keyer& Keyer::operator<<(const std::string& input)
{
    typedef std::string::const_iterator cit;

    for(cit it = input.begin(); it!=input.end(); it++)
    {
	unsigned char ch = *it;
	*this<<ch;
	char_pause();
    }
    
    string_pause();

    return *this;		
}
    
void Keyer::char_pause()
{
    libaudiostream::Wave pause = m_aws.gen_pause(m_count*m_interch);
    m_audio<<pause; // ugly kludge
}

void Keyer::string_pause()
{
    libaudiostream::Wave pause = m_aws.gen_pause(m_count*m_interword);
    m_audio<<pause; // ugly kludge
}
