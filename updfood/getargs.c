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

#include	"updfood.h"

static void Usage ()
{
	printf ( "\nUpdate food macros for foods which were created from recipes\n\n" );
	printf ( "USAGE: updfood -all\n" );
	printf ( "USAGE: updfood -food ID\n\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	int		xa;

	RunMode = 0;

	for ( xa = 1; xa < argc; xa++ )
	{
		if ( nsStrcmp ( argv[xa], "-all" ) == 0 )
		{
			RunMode = MODE_ALL;
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-food" ) == 0 )
		{
			RunMode = MODE_ONE;
			xa++;
			xfood.xfid = nsAtol ( argv[xa] );
			sprintf ( WhereClause, "Fid = %ld", xfood.xfid );
			if ( LoadFood ( WhereClause, &xfood, 0 ) != 1 )
			{
				printf ( "Unknown food ID\n" );
				exit ( 1 );
			}
			if ( xfood.xfrecipe == 0 )
			{
				printf ( "Food was not created from a recipe\n" );
				exit ( 1 );
			}
			sprintf ( WhereClause, "Rid = %ld", xfood.xfrecipe );
			if ( LoadRecipe ( WhereClause, &xrecipe, 0 ) != 1 )
			{
				printf ( "Recipe %ld not found for food %ld\n", xfood.xfrecipe, xfood.xfid );
				exit ( 1 );
			}
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
