/*----------------------------------------------------------------------------
	Program : CopyDay.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Copy a previous day's foods to selected date.
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

static	char	MealsArray[5];
static	int		MealsCount;

static int EachHistory ( XHISTORY *ptr )
{
#ifdef DEBUG
#define DEBUG
	printf ( "%s %s<br>\n", ptr->xhdate, ptr->xhdescr );
#endif

	if ( MealsCount >= 4 )
	{
		printf ( "Too many meals found for %s<br>\n", CopyDayDate );
		return ( -1 );
	}
	MealsArray[MealsCount] = ptr->xhdescr[0];
	MealsCount++;
	
	return ( 0 );
}

void CopyDay ()
{
	long	rv;
	int		xm;

	MealsCount = 0;

	sprintf ( WhereClause, "Hdate = '%s' and Hmember = %ld", CopyDayDate, CookieMember.xmid );
	rv = LoadHistoryCB ( WhereClause, NULL, &xhistory, EachHistory, 0 );

	if ( rv == 0 )
	{
		printf ( "No meals found for that day<br>\n" );
		return;
	}

	nsStrcpy ( CopyMealDate, CopyDayDate );
	for ( xm = 0; xm < MealsCount; xm++ )
	{
		CopyMealDescr = MealsArray[xm];
		CopyMeal ( 0 );
	}
}
