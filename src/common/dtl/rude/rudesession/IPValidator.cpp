// IPValidator.cpp
//
// Copyright (C) 2005 Matthew Flood
// See file AUTHORS for contact information
//
// This file is part of RudeSession.
//
// RudeSession is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
// 
// RudeSession is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with RudeSession; (see COPYING) if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//------------------------------------------------------------------------

#include "IPValidator.h"


#include <stdio.h>


namespace rude{
namespace session{


void IPValidator::dec2bin(int dec, char *bin, int pos)
{
   if (dec <= 0)
   {
		if(pos == 0)
		{
      	return;
		}
		*bin = '0';
		*(bin + 1) = 0;
		dec2bin(dec, bin + 1, pos -1);
   } 


   if (dec % 2)
      *bin = '1';
   else
      *bin = '0';
   
   *(bin+1) = 0;


   dec2bin(dec/2,bin+1, pos -1);
}

bool IPValidator::validate(const char *goodip, const char *testip, int mask)
{
	// A zero mask always returns true
	//
	if(mask <= 0)
	{
		return true;
	}

	if(mask > 32)
	{
		mask=32;
	}

	// null IP's always return false;
	//
	if(testip == (char*) 0 || goodip == (char*) 0)
	{
		return false;
	}

	// turn IP's into bitstring
	int one;
	int two;
	int three;
	int four;
	
	char bin1[40];
	char bin2[40];
	char first[9];
	char second[9];
	char third[9];
	char fourth[9];
	
	sscanf(testip, "%d.%d.%d.%d", &one, &two, &three, &four);

	dec2bin(one, first, 8);
	dec2bin(two, second, 8);
	dec2bin(three, third, 8);
	dec2bin(four, fourth, 8);
	
	sprintf(bin1, "%s%s%s%s", fourth, third, second, first );


	sscanf(goodip, "%d.%d.%d.%d", &one, &two, &three, &four);

	dec2bin(one, first, 8);
	dec2bin(two, second, 8);
	dec2bin(three, third, 8);
	dec2bin(four, fourth, 8);
	
	sprintf(bin2, "%s%s%s%s", fourth, third, second, first );
	
	// the ip addresses are backwards....
	// need to check from the end to the beginning....
	//
	for(int x=0; x < mask; x++)
	{
		int index=32 - x - 1;
		if( bin1[index] != bin2[index])
		{
			// ip mismatch
			return false;
		}
	} 
	return true;
}

}} // end namespaces

