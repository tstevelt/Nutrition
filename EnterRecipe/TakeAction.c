/*----------------------------------------------------------------------------
	Program : TakeAction.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Run selected sub-routine.
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

void TakeAction ()
{
	switch ( RunMode )
	{
		case MODE_START:
		case MODE_FOUND:
			break;
		case MODE_LOOKUP_RECIPE:
			FindRecipe ();
			break;
		case MODE_INSERT_RECIPE:
			AddRecipe ();
			break;
		case MODE_UPDATE_RECIPE:
			UpdateRecipe ();
			break;
		case MODE_DELETE_RECIPE:
			DeleteRecipe ();
			break;
		case MODE_ADD_RECFOOD:
			AddRecfood ();
			FindRecipe ();
			break;
		case MODE_DELETE_RECFOOD:
			DeleteRecfood ();
			FindRecipe ();
			break;
		case MODE_CREATE_FOOD:
			CreateFood ();
			FindRecipe ();
			break;
		case MODE_QUIT:
			memset ( &xrecipe, '\0', sizeof(XRECIPE) );
			RecipeID = 0;
			break;
		default:
			printf ( "TakeAction: unknown run mode %d<br>\n", RunMode );
			break;
	}
}
