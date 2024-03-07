/*----------------------------------------------------------------------------
	Program : ChkInput.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Validate user input
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

void ChkInput ()
{
	switch ( RunMode )
	{
		case MODE_LOOKUP_RECIPE:
			if ( RecipeID == 0 && nsStrlen ( xrecipe.xrdescr ) == 0 )
			{
				printf ( "Search by either ID or partial description.<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			break;

		case MODE_INSERT_RECIPE:
			if ( nsStrlen ( xrecipe.xrdescr ) < 4 )
			{
				printf ( "Please enter a good description<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			if ( xrecipe.xrserving < 1 )
			{
				printf ( "Please enter number of servings this recipe makes.<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			break;

		case MODE_ADD_RECFOOD:
			if ( MealDescr == '?' )
			{
				printf ( "Missing meal description<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			if ( FoodID == 0 )
			{
				printf ( "Missing food ID. Use lookup if needed.<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			else
			{
				sprintf ( WhereClause, "Fid = %ld", FoodID );
				if ( LoadFood ( WhereClause, &xfood, 0 ) != 1 )
				{
					printf ( "Invalid food ID. Use lookup if needed.<br>\n" );
					RunMode = MODE_LOOKUP_RECIPE;
				}
			}
			if ( FoodServings <= 0 )
			{
				printf ( "Missing food amount<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}

			break;

		case MODE_DELETE_RECIPE:
			break;

		case MODE_DELETE_RECFOOD:
			if ( DeleteCount == 0 )
			{
				printf ( "Nothing selected for deletion!<br>\n" );
				RunMode = MODE_LOOKUP_RECIPE;
			}
			break;

	}
}
