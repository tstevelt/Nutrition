/*----------------------------------------------------------------------------
	Program : DeleteRecfood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Remove component food from recipe.
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

#include	"EnterRecipe.h"

#define DEBUG
#undef DEBUG

void DeleteRecfood ()
{
	int		xd;
	long	rv;

	for ( xd = 0; xd < DeleteCount; xd++ )
	{
		sprintf ( Statement, "delete from recfood where RFrecipe = %ld and RFfood = %ld",
			DeleteArray[xd].HistID, DeleteArray[xd].FoodID );

#ifdef DEBUG
		printf ( "%s<br>\n", Statement );
#endif

		if (( rv = dbyDelete ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Could not delete food from recipe, rv %ld<br>\n", rv );
		}
	}
}
