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
#include "blocks.hh"
#include "koch.hh"

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>

// width of screen in characters
#define TERMINAL_WIDTH 80

// markers for the correspondence between keyed symbol and copied symbol
#define CORRECT_MARKER   '.'
#define INCORRECT_MARKER '!'
#define MISSED_MARKER    '@'

using namespace std;

typedef map<char, unsigned int>::const_iterator c_map;
typedef list< string >::const_iterator c_lststr;
typedef string::const_iterator c_str;

/*
 * Returns a string truncated or padded to a given length. The padding is to
 * the right and the padding character is 'MISSED_MARKER'.
 */
string padding(unsigned int len, const string& b)
{
    int s = len - b.size();	
    if(s > 0)
	return b + string(s,MISSED_MARKER);

    if(s < 0)
	return string(b, 0, len);

    return b;
}

/*
 * This function computes the width in characters for representing an integer
 * in base 10. It is useful in determining the maximum with needed for
 * displaying a loop counter, such that vertical alignment can be achieved.
 */
size_t width_base_10(const size_t n)
{
    size_t n_width = 0;
    for (size_t n_max = n; n_max > 0; n_max /= 10) {
	++n_width;
    }
    return n_width;
}

/*
 * This function displays the copy success rate.
 */
void display_overall_rate(const unsigned int percentage)
{
    cout<<endl<<ovrmsg_title<<": ";
    cout.width(3);
    cout<<percentage<<'%'<<endl;
}

/*
 * This function displays the copy success rate per keyed symbol.
 */
void display_symbol_rate(const list<string>& lks, const list<string>& lcs)
{
    map<char, unsigned int> keyed_all;
    map<char, unsigned int> keyed_bad;
    map<char, unsigned int> keyed_missed;
    map<char, unsigned int> copied_all;
    map<char, unsigned int> copied_good;
    map<char, unsigned int> copied_bad;

    // compute results

    // iterate over the lists of strings
    c_lststr lks_it;
    c_lststr lcs_it;
    for(lks_it = lks.begin(), lcs_it = lcs.begin();
        lks_it != lks.end() && lcs_it != lcs.end();
        ++lks_it, ++lcs_it
       )
    {
	// ensure that the copied string is as long as the keyed string,
	// padding it with 'MISSED_MARKER' if necessary
	string copied = padding((*lks_it).size(), *lcs_it);

	// iterate over the characters in each group
	c_str kit;
	c_str cit;
	for(kit = (*lks_it).begin(), cit = copied.begin();
	    kit != (*lks_it).end();
	    ++kit, ++cit
	   )
	{
	    char kc = *kit;  // keyed symbol
	    char cc = *cit;  // copied sybmol

	    keyed_all[kc]++;   // mark keyed symbol
	    copied_all[cc]++;  // mark copied symbol

	    if(kc == cc)
	    {
		// keyed symbol was copied correctly
		copied_good[cc]++;
	    }
	    else if(cc != MISSED_MARKER)
	    {
		// keyed symbol was copied incorrectly
		keyed_bad[kc]++;
		copied_bad[cc]++;
	    }
	    else
	    {
		// keyed symbol was missed
		keyed_missed[kc]++;
	    }
	}
    }

    // display results

    cout<<endl<<smbmsg_title<<':'<<endl; // display feedback category "title"
    cout << '"' << smbmsg_symbol << ':'
	<< smbmsg_keyed << " = " << smbmsg_correct << " + " << smbmsg_incorrect << " + " << smbmsg_missed
	<< " (" << smbmsg_percent << "); "
	<< smbmsg_copied << " = " << smbmsg_correct << " + " << smbmsg_incorrect
	<< " (" << smbmsg_percent << ")\"" << endl
	<< endl;

    // loop over maps
    char c;
    size_t count_width = width_base_10(lks.size() * lks.front().size());
    for(c_map mtc = keyed_all.begin(); mtc != keyed_all.end(); ++mtc)
    {
	c = (*mtc).first;

	// symbol
	cout << c << ":";

	// sum of counts for keyed symbols
	cout.width(count_width);
	cout << keyed_all[c] << " = ";
	cout.width(count_width);
	cout << copied_good[c] << " + ";
	cout.width(count_width);
	cout << keyed_bad[c] << " + ";
	cout.width(count_width);
	cout << keyed_missed[c];

	// sum of percentages for keyed symbols
	cout << " (";
	if (keyed_all[c] != 0)
	{
	    cout.width(3);
	    cout << 100*copied_good[c]/keyed_all[c] << "% + ";
	    cout.width(3);
	    cout << 100*keyed_bad[c]/keyed_all[c] << "% + ";
	    cout.width(3);
	    cout << 100*keyed_missed[c]/keyed_all[c] << '%';
	}
	else
	{
	    cout << "?% + ?% + ?%";
	}
	cout << "); ";

	// sum of counts for copied symbols
	cout.width(count_width);
	cout << copied_all[c] << " = ";
	cout.width(count_width);
	cout << copied_good[c] << " + ";
	cout.width(count_width);
	cout << copied_bad[c];
	
	// sum of percentages for copied symbols
	cout << " (";
	if (copied_all[c] != 0)
	{
	    cout.width(3);
	    cout << 100*copied_good[c]/copied_all[c] << "% + ";
	    cout.width(3);
	    cout << 100*copied_bad[c]/copied_all[c] << '%';
	}
	else
	{
	    cout << "?% + ?%";
	}
	cout << ')' << endl;
    }
}

/*
 * This function takes a keyed sign group and a copied sign group and
 * generates a mistakes string of the same length. The mistakes string
 * contains mistake marker characters at the positions where the keyed
 * and the copied strings differ and unobtrusive spacer characters at
 * the other positions.
 */
string mark_mistakes(const string keyed, const string copied)
{
    string mistakes;     // start with empty string

    c_str kit = keyed.begin();
    c_str cit = copied.begin();

    while(kit != keyed.end())
	if(cit != copied.end())
	{
	    if(*kit == *cit)
		mistakes += CORRECT_MARKER;    // unobtrusive spacer
	    else if(*cit == MISSED_MARKER)
		mistakes += MISSED_MARKER;     // missed symbol
	    else
		mistakes += INCORRECT_MARKER;  // incorrect copy
	    ++kit;
	    ++cit;		
	}
	else
	{
	    mistakes += MISSED_MARKER;
	    ++kit;
	}

    return mistakes;
}

list<string> get_marked_strings(const list<string>& lks, const list<string>& lcs)
{
    list< string > lms; //list of marked strings

    c_lststr lks_it = lks.begin();
    c_lststr lcs_it = lcs.begin();

    while(lks_it != lks.end())
	if(lcs_it != lcs.end())
	{
	    lms.push_back(mark_mistakes(*lks_it, *lcs_it));
	    ++lks_it;
	    ++lcs_it;
	}
	else
	{
	    lms.push_back( string((*lks_it).size(), INCORRECT_MARKER) );
	    ++lks_it;
	}

    return lms;
}

/*
 * This function displays the keyed sign groups and the copied sign groups
 * alongside each other, accompanied by markers which indicate the positions
 * of the copying mistakes.
 */
void display_comparison(const list<string>& lks, const list<string>& lcs)
{
    // display evaluation header

    cout<<endl<<cmpmsg_title<<':'<<endl;     // display feedback category "title"

    string legend_indent = string( string(cmpmsg_group).length(), ' ');     // indentation string
    cout << '"' << cmpmsg_group << ':'
	<< '\'' << CORRECT_MARKER   << "'=" << cmpmsg_correct   << ", "
	<< '\'' << MISSED_MARKER    << "'=" << cmpmsg_missed    << ", "
	<< '\'' << INCORRECT_MARKER << "'=" << cmpmsg_incorrect << endl
	<< legend_indent << "k:" << cmpmsg_keyed << endl
	<< legend_indent << "c:" << cmpmsg_copied << '"' << endl
	<< endl;

    // build evaluation cells (on three rows)

    // combine parameter lists into a list of mistake strings
    list<string> lms = get_marked_strings(lks, lcs);

    // temporary variables for preparing output lines
    ostringstream mistaken_row_formatter;
    string mistaken_row;
    string keyed_row;
    string copied_row;

    // how many characters are needed for representing the highest index
    size_t n_width = width_base_10(lks.size());

    // indentation string for keyed and copied strings
    string indent = string(n_width, ' ');

    // format the evaluation strings
    // (loop with iterators over the lists of strings)
    unsigned int n;
    c_lststr lms_it = lms.begin();
    c_lststr lks_it = lks.begin();
    c_lststr lcs_it = lcs.begin();
    for(
        n = 1
        ;
        lms_it != lms.end() &&
        lks_it != lks.end() &&
        lcs_it != lcs.end()
        ;
        ++n,
        ++lms_it,
        ++lks_it,
        ++lcs_it
       )
    {
	mistaken_row_formatter << " ";
	mistaken_row_formatter.width(n_width);
	mistaken_row_formatter << n << ":" << *lms_it;

	keyed_row += indent + "k:" + *lks_it;

	copied_row += indent + "c:" + padding((*lks_it).size(), *lcs_it);
    }
    mistaken_row = mistaken_row_formatter.str();

    // display evaluation cells, breaking the lines at or before TERMINAL_WIDTH

    // (TERMINAL_WIDTH / cell_width) feedback cells fit on a row
    // cell_width is the sum of:
    //       1 character blank to separate the cells
    // n_width characters for the counter
    //       1 character blank between the counter and the sign group
    //  size() characters for the sign group
    unsigned int cell_width = 2 + n_width + lks.front().size();

    // how many characters to use in a screen row,
    // such that lines break at cell border
    unsigned int used_width = (TERMINAL_WIDTH / cell_width) * cell_width;

    // loop over the screen rows
    for(size_t pos = 0; pos < mistaken_row.size(); pos += used_width)
    {
	// display output lines
	cout << mistaken_row.substr(pos, used_width) << endl;	// e.g. 12:!.!.@@!
	cout << keyed_row.substr(pos, used_width) << endl;	//         eishtmo
	cout << copied_row.substr(pos, used_width) << endl;	//         aibh@@d
	cout << endl;
    }
}

/*
 * This function lets the user input the copied sign groups
 */
list<string> get_copied_strings(unsigned int num_groups)
{
    list<string> lcs;

    cout << endl << chkmsg_1 << endl;
    cout << chkmsg_2 << endl;

    // how many characters are needed for representing the highest index
    int i_width = width_base_10(num_groups);

    for(unsigned int i=0; i<num_groups; i++)
    {
	string tmp;

	do
	{
	    cout.width(i_width);
	    cout << (i+1) << ": ";
	    cin.clear();
	}
	while(! getline(cin, tmp));

	lcs.push_back(tmp);
    }
    return lcs;
}

/*
 * This function compares two strings and returns lets the user input the copied sign groups
 */
unsigned int count_wrong_letters(string keyed, string copied)
{
    unsigned int wrong_letters = 0;

    c_str kit = keyed.begin();
    c_str cit = copied.begin();

    while(kit != keyed.end())
	if(cit != copied.end())
	{
	    if(*kit != *cit)
		wrong_letters++;

	    ++kit;
	    ++cit;		
	}
	else
	{
	    wrong_letters++;
	    ++kit;
	}

    //wrong_letters = keyed.size(); // if copied key has a different lenght of keyed all letters are wrong

    return wrong_letters;
}

unsigned int get_overall_rate(const list<string>& lks, const list<string>& lcs)
{
    double wrong_letters = 0.0;
    double total = 0.0;

    c_lststr lks_it = lks.begin();
    c_lststr lcs_it = lcs.begin();

    while(lks_it != lks.end())
    {
	total += (*lks_it).size();

	if(lcs_it != lcs.end())
	{

	    wrong_letters += count_wrong_letters(*lks_it, *lcs_it);

	    ++lks_it;
	    ++lcs_it;
	}
	else
	{
	    wrong_letters += (*lks_it).size();
	    ++lks_it;
	}
    }

    double wrong_tax = wrong_letters/total;
    
    return int(100 - 100 * wrong_tax);
}


/*
 * This function lets the user input the copied sign groups and displays 
 * information about how well an exercise was completed. 
 * Its goal is to help the user discover the areas where improvement is possible.
 */
unsigned int check(const libexercises::Blocks& current_exercise)
{
    list<string> lks = current_exercise.tokenize(); // list of keyed strings
    list<string> lcs = get_copied_strings(lks.size()); // list of copied strings

    cout << endl << fbkmsg_title << endl; // introduce the feedback information

    unsigned int overall_rate = get_overall_rate(lks, lcs); // overall success rate

    display_overall_rate(overall_rate);     // display overall success rate
    display_symbol_rate(lks, lcs); // display success rate per keyed symbol
    display_comparison(lks, lcs);  // display comparison between keyed and copied sign groups

    cout<<endl;

    return overall_rate;
}

/*
 * This function lets the user input the copied sign groups and displays
 * feedback about how it went.
*/
unsigned int check(const libexercises::Koch& current_exercise)
{
    list<string> lks = current_exercise.tokenize(); // list of keyed strings
    list<string> lcs = get_copied_strings(lks.size()); // list of copied strings

    cout << endl << fbkmsg_title << endl; // introduce the feedback information

    unsigned int overall_rate = get_overall_rate(lks, lcs); // overall success rate

    display_overall_rate(overall_rate);     // display overall success rate
    display_symbol_rate(lks, lcs); // display success rate per keyed symbol
    display_comparison(lks, lcs);  // display comparison between keyed and copied sign groups

    cout<<endl;

    return overall_rate;
}
