/*----------------------------------------------------------------------------
	Program : getargs.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Get command line arguments
	Return  : 
----------------------------------------------------------------------------*/
//     Nutrition Tracking Website
// 
//     Copyright (C)  2023-2024 Tom Stevelt
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Affero General Public License as
//     published by the Free Software Foundation, either version 3 of the
//     License, or (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU Affero General Public License for more details.
// 
//     You should have received a copy of the GNU Affero General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include	"FixFood.h"

static void Usage ()
{
	printf ( "USAGE: FixFood -all     [-d]\n" );
	printf ( "       FixFood -one Fid [-d]\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	if ( argc < 2 )
	{
		Usage();
	}

	for ( int xa = 1; xa < argc; xa++ )
	{
		if ( nsStrcmp ( argv[xa], "-all" ) == 0 )
		{
			RunMode = MODE_ALL;
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-one" ) == 0 )
		{
			RunMode = MODE_ONE;
			xa++;
			xfood.xfid = nsAtol ( argv[xa] );
		}
		else if ( nsStrcmp ( argv[xa], "-d" ) == 0 )
		{
			Debug = 1;
		}
		else
		{
			Usage ();
		}
	}
}
