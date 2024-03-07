/*----------------------------------------------------------------------------
	Program : DeleteFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Remove food from meal.
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

#include	"EnterDay.h"

static	long	MealsArray[5];
static	int		MealsCount = 0;

#define DEBUG
#undef DEBUG

static int EachHistory ( XHISTORY *ptr )
{
#ifdef DEBUG
	printf ( "%s %s<br>\n", ptr->xhdate, ptr->xhdescr );
#endif

	if ( MealsCount >= 4 )
	{
		printf ( "Too many meals found for %s<br>\n", HistoryDate );
		return ( -1 );
	}
	MealsArray[MealsCount] = ptr->xhid;
	MealsCount++;
	
	return ( 0 );
}

void DeleteFood ()
{
	int		xd, xm;
	long	rv;

	for ( xd = 0; xd < DeleteCount; xd++ )
	{
		sprintf ( Statement, "delete from histfood where HFhist = %ld and HFfood = %ld",
			DeleteArray[xd].HistID, DeleteArray[xd].FoodID );

#ifdef DEBUG
		printf ( "%s<br>\n", Statement );
#endif

		if (( rv = dbyDelete ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Could not delete food from meal, rv %ld<br>\n", rv );
		}
	}
		
	/*----------------------------------------------------------
		clean up history records with no histfood children.
	----------------------------------------------------------*/
	MealsCount = 0;

	sprintf ( WhereClause, "Hdate = '%s' and Hmember = %ld", HistoryDate, CookieMember.xmid );
	rv = LoadHistoryCB ( WhereClause, NULL, &xhistory, EachHistory, 0 );
#ifdef DEBUG
		printf ( "where %s --> %ld<br>\n", WhereClause, rv );
#endif

	if ( rv == 0 || MealsCount  == 0 )
	{
		printf ( "Impossible!<br>\n" );
		return;
	}

	for ( xm = 0; xm < MealsCount; xm++ )
	{
		sprintf ( WhereClause, "HFhist = %ld", MealsArray[xm] );

		rv = dbySelectCount ( &MySql, "histfood", WhereClause, LogFileName );
#ifdef DEBUG
		printf ( "where %s --> %ld<br>\n", WhereClause, rv );
#endif
		if ( rv > 0 )
		{
			continue;
		}	

		sprintf ( Statement, "delete from history where Hid = %ld", MealsArray[xm] );

#ifdef DEBUG
		printf ( "%s<br>\n", Statement );
#endif

		if (( rv = dbyDelete ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Could not delete food from meal, rv %ld<br>\n", rv );
		}

	}
}
