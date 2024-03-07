/*----------------------------------------------------------------------------
	Program : FindRecipe.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Find recipe by ID or partial description
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

void FindRecipe ()
{
	int		rv;

	if ( RecipeID > 0 )
	{
		sprintf ( WhereClause, "Rid = %ld", RecipeID);
	}
	else if ( nsStrlen ( xrecipe.xrdescr ) > 0 )
	{
		sprintf ( WhereClause, "Rdescr like '%%%s%%'", xrecipe.xrdescr);
	}
	else 
	{
		printf ( "Search by either Recipe ID or partial description<br>\n" );
		RunMode = MODE_START;
		return;
	}

#ifdef DEBUG
#define DEBUG
	printf ( "FindRecipe: %s<br>\n", WhereClause );
#endif

	if (( rv = LoadRecipe ( WhereClause, &xrecipe, 1 )) < 1 )
	{
		printf ( "Could not find recipe, rv %d<br>\n", rv );
		RecipeID = 0;
		RunMode = MODE_START;
	}
	else
	{
		if ( rv > 1 )
		{
			printf ( "Found %d recipes, here is the first one.<br>\n", rv );
		}
		RecipeID = xrecipe.xrid;
		RunMode = MODE_FOUND;
	}
}
