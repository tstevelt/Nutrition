/*----------------------------------------------------------------------------
	Program : MakeDemoMeals.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Mar 29, 2023
	Synopsis: Create fake random meals for demo user.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		04/08/2023	And delete old meals
	tms		05/03/2023	Use GenMealPlan to match all 6 targets

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

#define		MAIN
#include	"MakeDemoMeals.h"

int main ( int argc, char *argv[] )
{
	DBY_QUERY	*qry;
	char	LatestDate[12];
	DATEVAL	HistoryDate;;
	DATEVAL	NextDate;;
	DATEVAL	Today;
	DATEVAL	DeleteDate;
	long	DeleteHistory, DeleteHistfood;

	CurrentDateval ( &Today );

	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	getargs ( argc, argv );

	sprintf ( WhereClause, "Mid = %ld", (long)DEMO_MEMBER );
	if ( LoadMember ( WhereClause, &xmember, 0 ) != 1 )
	{
		printf ( "DEMO member not found\n" );
		exit ( 1 );
	}

#ifdef DEBUG
	printf ( "DEMO Calorie %d  Carb %d  Protein %d  Fat %d  Sodium %d  Fiber %d\n",
		xmember.xmcalorie,
		xmember.xmcarb,
		xmember.xmprotein,
		xmember.xmfat,
		xmember.xmsodium,
		xmember.xmfiber );
#endif

	switch ( RunMode )
	{
		case MODE_ALL:
			sprintf ( Statement, "select max(Hdate) from history where Hmember = %ld", (long)DEMO_MEMBER );
#ifdef DEBUG
			printf ( "%s\n", Statement );
#endif
			LatestDate[0] = '\0';

			if (( qry = dbySelect ( "nutrition", &MySql, Statement, LogFileName )) == NULL )
			{
				printf ( "Did not find any existing meals for DEMO account\n" );
				// break;
			}
			else
			{
				if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
				{
					printf ( "max(Hdate) DEMO account fetch failed\n" );
					// break;
				}
				else
				{
					if (  qry->EachRow[0] == NULL )
					{
						printf ( "max(Hdate) is NULL\n" );
						// break;
					}
					else
					{
						sprintf ( LatestDate, "%s", qry->EachRow[0] );
					}
				}
			}

			if ( LatestDate[0] == '\0' )
			{
				DateAdd ( &Today, -14, &DeleteDate );
				sprintf ( LatestDate, "%04d-%02d-%02d", DeleteDate.year4, DeleteDate.month, DeleteDate.day );
			}

			/*----------------------------
				0123456789
				yyyy-mm-dd
			----------------------------*/
			HistoryDate.year4  = nsAtoi(&LatestDate[0]);
			HistoryDate.month = nsAtoi(&LatestDate[5]);
			HistoryDate.day   = nsAtoi(&LatestDate[8]);

			if ( memcmp ( &HistoryDate, &Today, sizeof(DATEVAL) ) == 0 )
			{
				printf ( "DEMO member meals are up-to-date\n" );
				// exit ( 0 );
			}
			else
			{
#ifdef DEBUG
				printf ( "%s = %04d-%02d-%02d\n", 
					LatestDate, HistoryDate.year4, HistoryDate.month, HistoryDate.day );
#endif
				while ( memcmp ( &HistoryDate, &Today, sizeof(DATEVAL) ) < 0 )
				{
					DateAdd ( &HistoryDate, 1, &NextDate );

					printf ( "%04d-%02d-%02d\n", NextDate.year4, NextDate.month, NextDate.day );

					EachDay ( &NextDate );

					memcpy ( &HistoryDate, &NextDate,  sizeof(DATEVAL) );
				}
			}

			/*----------------------------------------------------------
				delete old (more than 30 days) meals 
			----------------------------------------------------------*/
			DateAdd ( &Today, -30, &DeleteDate );

			sprintf ( Statement, 
"delete from histfood where HFhist in (select Hid from history where Hmember = %ld and Hdate < '%04d-%02d-%02d')",
					(long)DEMO_MEMBER, DeleteDate.year4,  DeleteDate.month, DeleteDate.day );

#ifdef DEBUG
			printf ( "%s\n", Statement );
#endif

			if (( DeleteHistfood = dbyDelete ( "nutrition", &MySql, Statement, 0, LogFileName )) < 1 )
			{
#ifdef DEBUG
				printf ( "No old meals for demo member\n" );
#endif
			}
			else
			{
				sprintf ( Statement, 
					"delete from history where Hmember = %ld and Hdate < '%04d-%02d-%02d'",
						(long)DEMO_MEMBER, DeleteDate.year4,  DeleteDate.month, DeleteDate.day );

#ifdef DEBUG
				printf ( "%s\n", Statement );
#endif
					
				if (( DeleteHistory = dbyDelete ( "nutrition", &MySql, Statement, 0, LogFileName )) < 1 )
				{
					printf ( "Could not delete meal, rv %ld\n", DeleteHistory );
				}
			}
				

			break;

		case MODE_ONE:
			break;
	}

	dbyClose ( &MySql );
	
	printf ( "Added   %3d days, %3d meals and %3d foods\n", DayCount, HistoryCount, HistfoodCount );
	printf ( "Deleted           %3d meals and %3d foods\n", (int)DeleteHistory, (int)DeleteHistfood );

	return ( 0 );
}
