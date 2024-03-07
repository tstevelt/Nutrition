/*----------------------------------------------------------------------------
	Program : updfood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Update recipe when its component foods change.

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
#include	"updfood.h"

int main ( int argc, char *argv[] )
{
	int		rv;

	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	getargs ( argc, argv );

	switch ( RunMode )
	{
		case MODE_ALL:
			sprintf ( WhereClause, "Frecipe > 0" );
			if (( rv = LoadFoodCB ( WhereClause, NULL, &xfood, EachFood, 0 )) < 1 )
			{
				printf ( "No foods found which were created from recipes\n" );
				break;
			}
			break;

		case MODE_ONE:
			EachFood ( &xfood );
			break;
	}

	dbyClose ( &MySql );

	return ( 0 );
}
