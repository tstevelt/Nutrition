/*----------------------------------------------------------------------------
	Program : EachDay.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Generate meals for a day and save to database.
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

#include	"MakeDemoMeals.h"

typedef struct
{
	long	FoodID;
} RECORD;

#define		MAXFOOD		10000
static	RECORD	Array[MAXFOOD];
static	int		Count = 0;

static void MakeMeal ( DATEVAL *Date, char *MealDescr, int StartNdx, int EndNdx )
{
	time_t	TimeStamp;
	int		rv;
	int		Index;

	TimeStamp = time ( NULL );

	/*----------------------------------------------------------
		add history record
	----------------------------------------------------------*/
	sprintf ( Statement, 
		"insert into history (Hmember, Hdescr, Hdate, inserted )  values ( %ld, '%s', '%04d-%02d-%02d', %ld )",
			(long)DEMO_MEMBER, MealDescr, Date->year4, Date->month, Date->day, TimeStamp );

#ifdef DEBUG
	printf ( "%s\n", Statement );
#endif
	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "History insert failed, rv %d\n", rv );
		exit ( 1 );
	}

	/*----------------------------------------------------------
		find history record based on inserted time
		too damn fast, all TimeStamp are the same.
		use max(Hid) instead
	----------------------------------------------------------*/
	sprintf ( WhereClause, "Hid = (select max(Hid) from history where Hmember = %ld)", (long)DEMO_MEMBER );
#ifdef DEBUG
	printf ( "%s\n", WhereClause );
#endif
	if ( LoadHistory ( WhereClause, &xhistory, 0 ) < 1 )
	{
		printf ( "Cannot find newly added history\n" );
		exit ( 1 );
	}

#ifdef DEBUG
	printf ( "New Hid %ld for member %ld\n", xhistory.xhid, xhistory.xhmember );
#endif

	HistoryCount++;

	/*----------------------------------------------------------
		add histfood record for index range
	----------------------------------------------------------*/
	for ( Index = StartNdx; Index <= EndNdx; Index++ )
	{
		sprintf ( Statement, "insert into histfood (HFhist, HFfood, HFserving) values ( %ld, %ld, 1.0 )",
				xhistory.xhid, Array[Index].FoodID );

#ifdef DEBUG
		printf ( "%s\n", Statement );
#endif
		if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
		{
			printf ( "Histfood insert failed, rv %d\n", rv );
			exit ( 1 );
		}

		HistfoodCount++;
	}
}

int EachDay ( DATEVAL *Date )
{
	char	fn[128];
	FILE	*fp;
	char	xbuffer[1024];
	int		SawID;

	sprintf ( fn, "%s/MakeDemoMeals.%d", TEMPDIR, getpid() );

	sprintf ( xbuffer, "/usr/local/bin/GenMealPlan -member %d -db all -generations 10 -minfoods 11 -maxfoods 11 -s > %s", DEMO_MEMBER, fn );

	system ( xbuffer );

	if (( fp = fopen ( fn, "r" )) == NULL )
	{
		printf ( "Cannot open %s for reading\n", fn );
		exit ( 1 );
	}

	SawID = Count = 0;
	while ( Count < 11 && fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
	{
		if ( nsStrncmp ( xbuffer, "ID", 2 ) == 0 )
		{
			SawID = 1;
			continue;
		}
		if ( SawID == 1 && Count < 11 )
		{
			Array[Count].FoodID = nsAtol ( xbuffer );
			Count++;
		}
	}

	fclose ( fp );

	if ( Count < 11 )
	{
		printf ( "Did not get 11 foods, got %d\n", Count );
		exit ( 1 );
	}

#ifdef DEBUG
	for ( ndx = 0; ndx < Count; ndx++ )
	{
		printf ( "%8ld\n", Array[ndx].FoodID );
	}
#endif

	MakeMeal ( Date, "Breakfast", 0,  2 );
	MakeMeal ( Date, "Lunch",     3,  5 );
	MakeMeal ( Date, "Dinner",    6,  8 );
	MakeMeal ( Date, "Snack",     9, 10 );

	DayCount++;

	return ( 0 );
}
