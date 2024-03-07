/*----------------------------------------------------------------------------
	Program : AddRecipe.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Insert recipe header record.
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

void AddRecipe ()
{
	int		rv;
	time_t	TimeStamp;

	TimeStamp = time ( NULL );

	if ( RecipeID > 0 )
	{
		sprintf ( Statement, "insert into recipe (Rid,Rdescr,Rserving,inserted,Rmember) values ( %ld, '%s', %d, %ld, %ld )",
					RecipeID, xrecipe.xrdescr, xrecipe.xrserving, TimeStamp, CookieMember.xmid );
	}
	else
	{
		sprintf ( Statement, "insert into recipe (Rdescr,Rserving,inserted,Rmember) values ( '%s', %d, %ld, %ld )",
					xrecipe.xrdescr, xrecipe.xrserving, TimeStamp, CookieMember.xmid );
	}

#ifdef DEBUG
#define DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "Could not insert recipe record<br>\n" );
		RunMode = MODE_START;
		return;
	}

	sprintf ( WhereClause, "inserted = %ld", TimeStamp );
#ifdef DEBUG
	printf ( "%s<br>\n", WhereClause );
#endif
	if (( rv = LoadRecipe ( WhereClause, &xrecipe, 0 )) != 1 )
	{
		printf ( "Could not load new  recipe<br>\n" );
		RunMode = MODE_START;
		return;
	}
	RecipeID = xrecipe.xrid;
#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif
	RunMode = MODE_FOUND;
}
