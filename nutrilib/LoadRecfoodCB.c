/*----------------------------------------------------------------------------
	Program : LoadRecfoodCB.c
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

int LoadRecfoodCB ( char * WhereClause, char * OrderByClause, XRECFOOD *ptrRecfood, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryRecfood;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from recfood", FIELDS_RECFOOD );

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

	qryRecfood = dbySelect ( "LoadRecfood", &MySql, Statement, LogFileName );
	if ( qryRecfood == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadRecfood select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryRecfood->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadRecfood select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryRecfood->EachRow = mysql_fetch_row ( qryRecfood->Result )) != NULL )
		{
// FIELDS_RECFOOD  "RFrecipe,RFfood,RFamount"

			ptrRecfood->xrfrecipe =  nsAtol( qryRecfood->EachRow[0] );
			ptrRecfood->xrffood   =  nsAtol( qryRecfood->EachRow[1] );
			ptrRecfood->xrfamount =  nsAtof( qryRecfood->EachRow[2] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrRecfood ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryRecfood->NumRows );
}
