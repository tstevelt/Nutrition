/*----------------------------------------------------------------------------
	Program : AddFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Add selected food to meal for the day.
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

#define DEBUG
#undef DEBUG

void AddFood ()
{
	int		rv;
	char	*Description;
	time_t	TimeStamp;

	TimeStamp = time ( NULL );

	/*----------------------------------------------------------
		find history record for date and meal
	----------------------------------------------------------*/
	sprintf ( WhereClause, "Hmember = %ld and Hdate = '%s'", MemberID, HistoryDate );
	switch ( MealDescr )
	{
		case 'B': strcat ( WhereClause, " and Hdescr = 'Breakfast'" ); Description = "Breakfast"; break;
		case 'L': strcat ( WhereClause, " and Hdescr = 'Lunch'"     ); Description = "Lunch"; break;
		case 'D': strcat ( WhereClause, " and Hdescr = 'Dinner'"    ); Description = "Dinner"; break;
		case 'S': strcat ( WhereClause, " and Hdescr = 'Snack'"     ); Description = "Snack"; break;
	}

#ifdef DEBUG
	printf ( "%s<br>\n", WhereClause );
#endif
	if (( rv = LoadHistory ( WhereClause, &xhistory, 1 )) != 1 )
	{
#ifdef DEBUG
		printf ( "history not found, rv %d<br>\n", rv );
#endif

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
			sprintf ( WhereClause, "inserted = %ld", TimeStamp );
			if (( rv = LoadHistory ( WhereClause, &xhistory, 0 )) != 1 )
			{
				printf ( "Could not find newly added history<br>\n" );
				return;
			}
			else
			{
#ifdef DEBUG
				printf ( "added history id %ld<br>\n", xhistory.xhid );
#endif
			}
		}

	}
#ifdef DEBUG
	else
	{
		printf ( "found history id %ld<br>\n", xhistory.xhid );
	}
#endif

	sprintf ( Statement, "insert into histfood (HFhist, HFfood, HFserving) values ( %ld, %ld, %.2f )",
		xhistory.xhid, FoodID, FoodServings );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "Could not insert food record<br>\n" );
		return;
	}

	/*----------------------------------------------------------
		if chosen food is a B-status, then change to A
	----------------------------------------------------------*/
	if ( xfood.xfstatus[0] != 'A' )
	{
		sprintf ( Statement, "update food set Fstatus = 'A' where Fid = %ld", FoodID );
		if (( rv = dbyUpdate ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Could not update food status<br>\n" );
			return;
		}
	}
}
