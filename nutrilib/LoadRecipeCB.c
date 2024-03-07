/*----------------------------------------------------------------------------
	Program : LoadRecipeCB.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load <table> record into buffer, with CallBack function
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

static  char    Statement[MAXSTATEMENT];

int LoadRecipeCB ( char * WhereClause, char * OrderByClause, XRECIPE *ptrRecipe, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryRecipe;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from recipe", FIELDS_RECIPE );

	if ( WhereClause != NULL && nsStrlen ( WhereClause ) > 1 && nsStrcmp ( WhereClause, "all" ) != 0 )
	{
		strcat ( Statement, " where " );
		strcat ( Statement, WhereClause );
	}

	if ( OrderByClause != NULL && nsStrlen ( OrderByClause ) > 1 )
	{
		strcat ( Statement, " order by " );
		strcat ( Statement, OrderByClause );
	}

	qryRecipe = dbySelect ( "LoadRecipe", &MySql, Statement, LogFileName );
	if ( qryRecipe == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadRecipe select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryRecipe->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadRecipe select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryRecipe->EachRow = mysql_fetch_row ( qryRecipe->Result )) != NULL )
		{
// FIELDS_RECIPE  "Rid,Rdescr,Rserving,Rfood"

			ptrRecipe->xrid       =  nsAtol( qryRecipe->EachRow[0] );
			snprintf ( ptrRecipe->xrdescr, sizeof(ptrRecipe->xrdescr), "%s", qryRecipe->EachRow[1] );
			ptrRecipe->xrserving  =  nsAtol( qryRecipe->EachRow[2] );
			ptrRecipe->xrfood     =  nsAtol( qryRecipe->EachRow[3] );
			ptrRecipe->xinserted  =  nsAtol( qryRecipe->EachRow[4] );
			ptrRecipe->xrmember   =  nsAtol( qryRecipe->EachRow[5] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrRecipe ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryRecipe->NumRows );
}
