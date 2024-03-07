/*----------------------------------------------------------------------------
	Program : LoadHistoryCB.c
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

int LoadHistoryCB ( char * WhereClause, char * OrderByClause, XHISTORY *ptrHistory, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryHistory;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from history", FIELDS_HISTORY );

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

	qryHistory = dbySelect ( "LoadHistory", &MySql, Statement, LogFileName );
	if ( qryHistory == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadHistory select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryHistory->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadHistory select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryHistory->EachRow = mysql_fetch_row ( qryHistory->Result )) != NULL )
		{
			ptrHistory->xhid     =  nsAtol( qryHistory->EachRow[0] );
			ptrHistory->xhmember =  nsAtol( qryHistory->EachRow[1] );
			snprintf ( ptrHistory->xhdescr, sizeof(ptrHistory->xhdescr), "%s", qryHistory->EachRow[2] );
			snprintf ( ptrHistory->xhdate, sizeof(ptrHistory->xhdate), "%s", qryHistory->EachRow[3] );
			ptrHistory->xinserted =  nsAtol( qryHistory->EachRow[4] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrHistory ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryHistory->NumRows );
}
