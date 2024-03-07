/*----------------------------------------------------------------------------
	Program : CopyMeal.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Copy just one meal from a previous day to selected date.
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

void CopyMeal ( int Verbose )
{
	char	*Description;
	int		rv;
	double	Min, Max, Avg;
	long	SourceHID, DestHID;
	time_t	TimeStamp;

	TimeStamp = time ( NULL );

	// sprintf ( WhereClause, "inserted = %ld", TimeStamp );

	/*----------------------------------------------------------
		find "source" meal
	----------------------------------------------------------*/
	sprintf ( WhereClause, "Hdate = '%s' and Hmember = %ld", CopyMealDate, CookieMember.xmid );
	switch ( CopyMealDescr )
	{
		case 'B': strcat ( WhereClause, " and Hdescr = 'Breakfast'" ); Description = "Breakfast"; break;
		case 'L': strcat ( WhereClause, " and Hdescr = 'Lunch'"     ); Description = "Lunch"; break;
		case 'D': strcat ( WhereClause, " and Hdescr = 'Dinner'"    ); Description = "Dinner"; break;
		case 'S': strcat ( WhereClause, " and Hdescr = 'Snack'"     ); Description = "Snack"; break;
	}

#ifdef DEBUG
#define DEBUG
	printf ( "%s<br>\n", WhereClause );
#endif

	if (( rv = LoadHistory ( WhereClause, &xhistory, 1 )) != 1 )
	{
		if ( Verbose )
		{
			printf ( "%s not found for date %s, rv %d<br>\n", Description, CopyMealDate, rv );
		}
		return;
	}
	SourceHID = xhistory.xhid;

	/*----------------------------------------------------------
		find "destination" meal
	----------------------------------------------------------*/
	sprintf ( WhereClause, "Hdate = '%s' and Hmember = %ld", HistoryDate, CookieMember.xmid );
	switch ( CopyMealDescr )
	{
		case 'B': strcat ( WhereClause, " and Hdescr = 'Breakfast'" ); break;
		case 'L': strcat ( WhereClause, " and Hdescr = 'Lunch'"     ); break;
		case 'D': strcat ( WhereClause, " and Hdescr = 'Dinner'"    ); break;
		case 'S': strcat ( WhereClause, " and Hdescr = 'Snack'"     ); break;
	}

#ifdef DEBUG
	printf ( "%s<br>\n", WhereClause );
#endif

	if (( rv = LoadHistory ( WhereClause, &xhistory, 1 )) != 1 )
	{
#ifdef DEBUG
		printf ( "%s not found for date %s, rv %d<br>\n", Description, HistoryDate, rv );
#endif

		/*----------------------------------------------------------
			destination not found, add it.
		----------------------------------------------------------*/
		sprintf ( Statement, "insert into history (Hmember,Hdescr,Hdate,inserted) values ( %ld, '%s', '%s', %ld )",
					MemberID, Description, HistoryDate, TimeStamp );

#ifdef DEBUG
		printf ( "%s<br>\n", Statement );
#endif

		if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Could not insert history record<br>\n" );
			return;
		}
		else 
		{
			rv = dbySelectMinMaxAvg ( &MySql, "history", "Hid", NULL, LogFileName, &Min, &Max, &Avg );

			if ( rv != 0 )
			{
				printf ( "Could not find newly added history<br>\n" );
				return;
			}
			else
			{
				xhistory.xhid = Max + 0.00001;
#ifdef DEBUG
				printf ( "added history id %ld<br>\n", xhistory.xhid );
#endif
			}
		}
	}

	DestHID = xhistory.xhid;

	sprintf ( Statement, 
		"insert into histfood ( HFhist, HFfood, HFserving ) select '%ld', HFfood, HFserving from histfood where HFhist = %ld",
			DestHID, SourceHID );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) < 1 )
	{
		if ( Verbose )
		{
		/*----------------------------------------------------------
			This was printing because a previous delete left 
			behind the history record after all histfood were
			deleted.  The Delete() has been fixed.
		----------------------------------------------------------*/
			printf ( "No records added, rv %d<br>\n", rv );
		}
	}
}
