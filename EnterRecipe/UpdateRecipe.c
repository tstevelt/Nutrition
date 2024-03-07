/*----------------------------------------------------------------------------
	Program : UpdateRecipe.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Update recipe description and serving
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

void UpdateRecipe ()
{
	int		Affected;

	if ( RecipeID > 0 )
	{
		sprintf ( Statement, "update recipe set Rdescr = '%s', Rserving = %d where Rid = %ld",
					xrecipe.xrdescr , xrecipe.xrserving , RecipeID );
	}

	Affected = dbyUpdate ( "recipe", &MySql, Statement, 0, LogFileName );
	
	if ( Affected < 0 )
	{
		SaveError ( "dbyUpdate failed" );
		RunMode = MODE_FOUND;
		return;
	}
	else if ( Affected == 0 )
	{
		SaveError ( "No changes" );
		RunMode = MODE_FOUND;
		return;
	}

	sprintf ( WhereClause, "Rid = %ld", RecipeID );
	LoadRecipe ( WhereClause, &xrecipe, 0 );

	RunMode = MODE_FOUND;
}
