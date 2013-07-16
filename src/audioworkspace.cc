/***************************************************************************
                     This is part of libaudiostream
                          --------------------
Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 Giuseppe "denever" Martino
    begin                : Sat 6 Aug 2005
    email                : denever [at] users.sf.net
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

#include "audioworkspace.hh"
#include "astream.hh"

#include <ao/ao.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <string.h>
    
using namespace std;
using namespace libaudiostream;

int offset = numeric_limits<short>::max()/2 - 1;

AudioWorkSpace::AudioWorkSpace(std::string device):
    m_bits(16), m_sample_rate(44100), m_channels(2), m_byte_format(AO_FMT_LITTLE), m_device(device)
{
}

AudioWorkSpace::AudioWorkSpace(size_type b, size_type sr, size_type ch, size_type bf, string device):
    m_bits(b), m_sample_rate(sr), m_channels(ch), m_byte_format(bf), m_device(device)
{
}

AudioWorkSpace::AudioWorkSpace(const Wave&)
{}

AudioWorkSpace::~AudioWorkSpace()
{}
	
Wave AudioWorkSpace::gen_pause(size_type millisecond)
{
    size_type sample_number = millisecond * m_sample_rate/1000;

    size_type len = m_bits/8 * m_channels * sample_number;

    char* buffer = new char[len];
    
    for(unsigned int i = 0; i<sample_number; i++)
    {
	buffer[4*i] = buffer[4*i+2] = 0;
	buffer[4*i+1] = buffer[4*i+3] = 0;
    }

    Wave w(len, buffer);

    return w;
}

Wave AudioWorkSpace::gen_sine_wave(size_type millisecond, double frequency, double phase)
{
    size_type sample_number = millisecond * m_sample_rate/1000;

    size_type len =  m_bits/8 * m_channels * sample_number;

    char* buffer = new char[len];
    
    for(unsigned int i = 0; i < sample_number; i++)
    {
	int sample = (int)(0.75 * 32768.0 * sin(2 * M_PI * frequency * ((float) i/m_sample_rate)));
    
    unsigned int rt = 30;     //rise-time   (inspired by qrq)
    unsigned int ft = 30;     //fall-time   (inspired by qrq)
    
    if ( i < rt ) { sample *= sin(M_PI*i/(2.0*rt)); }
    
    if ( i > (sample_number - ft) ) { sample *= sin(2*M_PI*(i- (sample_number - ft) +ft)/(4.0*ft)) ; }

	buffer[4*i] = buffer[4*i+2] = sample & 0xff;
	buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
    }
    
    Wave w(len, buffer);
    
    return w;
}

oastream AudioWorkSpace::create_output_stream()
{
    ao_sample_format format;
    
    memset(&format, 0, sizeof(format));
    format.bits = m_bits;
    format.channels = m_channels;
    format.rate = m_sample_rate;
    format.byte_format = AO_FMT_LITTLE;
    format.matrix = NULL;

    return oastream(format, m_device);
}

/*
double SineWave::get_phase()
{
    return m_duration*m_frequency*2*M_PI/m_samplerate;
}

    {
	phase += frequency * 2 * M_PI/m_sample_rate;

	int sample = int(32768 + 0.75 * 32768.0 * std::sin(phase));

	w.set(i, sample);
    }

*/

