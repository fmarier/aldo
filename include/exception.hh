// -*- C++ -*-
/***************************************************************************
                             libdatafile
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


#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace libdatafile
{

struct Not_datafile_format
{
    const char* m_file_name;
public:
    Not_datafile_format(const char* f): m_file_name(f)
    {}
};

struct  Over_write_file
{
    const char* m_file_name;
public:
    Over_write_file(const char* f): m_file_name(f)
    {}
};


struct  Option_not_found
{
    const char* m_option_name;
public:
    Option_not_found(const char* o): m_option_name(o)
        {}
};


struct  Section_not_found
{
    const char* m_section_name;
public:
    Section_not_found(const char* s): m_section_name(s)
        {}
};


struct  File_not_opened
{
    const char* m_file_name;
public:
    File_not_opened(const char* f): m_file_name(f)
        {}
};

struct  File_not_exist
{
    const char* m_file_name;
public:
    File_not_exist(const char* f): m_file_name(f)
        {}
};

} // Namespace Datafile_exception
 
#endif // EXCEPTION_H








