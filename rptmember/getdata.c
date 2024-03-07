/*----------------------------------------------------------------------------
	Program : getdata.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Get selected date, output to pipe-delimited file
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

#include	"rptmember.h"

static	int		lineno = 0;

char *ltos ( long number )
{
	static	char	buffer[20];

	sprintf ( buffer, "%ld", number );
	return ( buffer );
}

int EachMember ( XMEMBER *ptr )
{
	char		HistoryWhereClause[128];
	long		Count;
	char		LatestDate[12];
	char		JoinedDate[12];
	DBY_QUERY	*qry;
	struct tm	*t;

	t  = localtime ( &ptr->xinserted );
	if ( t == NULL )
	{
		fprintf ( stderr, "localtime: this is weird\n" );
		exit ( 1 );
	}

	while ( t->tm_year > 99 )
		t->tm_year -= 100;
	
	t->tm_year += 2000;

	sprintf ( JoinedDate, "%04d-%02d-%02d", t->tm_year, t->tm_mon + 1, t->tm_mday );

#ifdef DEBUG
#define DEBUG
	printf ( "Joined %s<br>\n", JoinedDate );
#endif

	/*----------------------------------------------------------
		find number of meals in the previous seven FULL days.
	----------------------------------------------------------*/
	sprintf ( HistoryWhereClause, "Hmember = %ld and Hdate >= '%04d-%02d-%02d' and Hdate <= '%04d-%02d-%02d'",
					ptr->xmid,
					SevenDays.year4, SevenDays.month, SevenDays.day,
					Yesterday.year4, Yesterday.month, Yesterday.day );

#ifdef DEBUG
	printf ( "%s<br>\n", HistoryWhereClause );
#endif

	Count = dbySelectCount ( &MySql, "history", HistoryWhereClause, LogFileName );
	
	/*----------------------------------------------------------
		find the date of the latest meal, even if Count is zero.
	----------------------------------------------------------*/
	sprintf ( Statement, "select max(Hdate) from history where Hmember = %ld", ptr->xmid );	

	 sprintf ( LatestDate, "          " );
	if (( qry = dbySelect ( "nutrition", &MySql, Statement, LogFileName )) == NULL )
	{
#ifdef DEBUG
		printf ( "Did not find any existing meals for DEMO account<br>\n" );
#endif
	}
	else if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
	{
#ifdef DEBUG
		printf ( "max(Hdate) DEMO account fetch failed<br>\n" );
#endif
	}
	else if ( qry->EachRow[0] != NULL )
	{
		sprintf ( LatestDate, "%s", qry->EachRow[0] );
	}


	fprintf ( fpData, "%ld|%s|%s|%s|%ld|%s\n",
		ptr->xmid,
		ptr->xmname,
		JoinedDate,
		ptr->xmemail,
		Count,
		LatestDate );

	lineno++;

	return ( 0 );
}

int getdata ()
{
	CurrentDateval ( &Today );

	if ( IncludeToday == 'N' )
	{
		DateAdd ( &Today, -1, &Yesterday );
		DateAdd ( &Yesterday, -6, &SevenDays );
	}
	else
	{
		memcpy ( &Yesterday, &Today, sizeof(DATEVAL) );
		DateAdd ( &Yesterday, -7, &SevenDays );
	}

	sprintf ( fnData, "%s/rptmember_%d.data", TEMPDIR, getpid () );
	if (( fpData = fopen ( fnData, "w" )) == (FILE *) 0 )
	{
		SaveError ( "can not create report file" );
		return ( -1 );
	}

	sprintf ( WhereClause, "Mid > 0" );
	sprintf ( OrderByClause, "Mname" );
	LoadMemberCB ( WhereClause, OrderByClause, &xmember, EachMember, 0 );

	nsFclose ( fpData );

	return ( lineno );
}

