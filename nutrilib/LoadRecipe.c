/*----------------------------------------------------------------------------
	Program : LoadRecipe.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load <table> record into buffer
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

#include	"nutriprivate.h"
#include	"nutrilib.h"

static int Breakout ()
{
	return ( -1 );
}

int LoadRecipe ( char * WhereClause, XRECIPE *ptrRecipe, int PrintErrors )
{
	int		NumberOfRows = 0;

	NumberOfRows = LoadRecipeCB ( WhereClause, NULL, ptrRecipe, Breakout, PrintErrors );

	return ( NumberOfRows );
}
