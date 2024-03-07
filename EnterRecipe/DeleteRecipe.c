/*----------------------------------------------------------------------------
	Program : DeleteRecipe.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Delete recipe record
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

int DeleteRecipe ()
{
	int		Affected;

	if ( RecipeID > 0 )
	{
		sprintf ( Statement, "delete from recipe where Rid = %ld", RecipeID );
	}
	else
	{
		return ( -1 );
	}

	Affected = dbyDelete ( "recipe", &MySql, Statement, 0, LogFileName );
	
	if ( Affected < 0 )
	{
		SaveError ( "dbyDelete failed" );
		RunMode = MODE_FOUND;
		return ( -2 );
	}
	else if ( Affected == 0 )
	{
		SaveError ( "Recipe not deleted" );
		RunMode = MODE_FOUND;
		return ( -3 );
	}
	else
	{
		RunMode = MODE_START;
		memset ( &xrecipe, '\0', sizeof(XRECIPE) );
		RecipeID = 0;
	}

	return ( 0 );
}
