/*----------------------------------------------------------------------------
	Program : FixFood.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : May 2023
	Synopsis: Standardize food description, serving etc
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------

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

#define		MAIN
#include	"FixFood.h"

int main ( int argc, char *argv[] )
{
	int		rv;

	getargs ( argc, argv );
	
	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	if ( RunMode == MODE_ALL )
	{
		sprintf ( WhereClause, "Fid > 0" );
	}
	else
	{
		sprintf ( WhereClause, "Fid = %ld", xfood.xfid );
	}
	if (( rv = LoadFoodCB ( WhereClause, NULL, &xfood, EachFood, 0 )) < 1 )
	{
		printf ( "No foods found\n" );
	}	

	dbyClose ( &MySql );
	
	printf ( "Checked %d, Updated %d, Errors %d\n", VisitCount, UpdateCount, ErrorCount );

	return ( 0 );
}
