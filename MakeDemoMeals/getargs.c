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

#include	"MakeDemoMeals.h"

static void Usage ()
{
	printf ( "\nCreate random meals for DEMO account.\n\n" );
	printf ( "USAGE: MakeDemoMeals -go\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	int		xa;

	RunMode = 0;

	for ( xa = 1; xa < argc; xa++ )
	{
		if ( nsStrcmp ( argv[xa], "-go" ) == 0 )
		{
			RunMode = MODE_ALL;
		}
		else
		{
			Usage ();
		}
	}
	if ( RunMode == 0 )
	{
		Usage ();
	}
}
