/*----------------------------------------------------------------------------
	Program : AddRecfood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Save component food to the recfood table.
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

void AddRecfood ()
{
	int		rv;

	sprintf ( Statement, "insert into recfood (RFrecipe, RFfood, RFamount) values ( %ld, %ld, %.2f )",
		RecipeID, FoodID, FoodServings );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "Could not insert food record<br>\n" );
	}
}
