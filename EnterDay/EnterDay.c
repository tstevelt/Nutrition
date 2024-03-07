/*----------------------------------------------------------------------------
	Program : EnterDay.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : Apr 2023
	Synopsis: Enter foods eaten during a day.
	Return  : 

	Who		Date		Modification
	---------------------------------------------------------------------
	tms		04/27/2023	If B-status food is used, then change Fstatus to A

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
#include	"EnterDay.h"

int main ( int argc, char *argv[] )
{
	COOKIE_RECORD	MyCookie;
#define		MEMBER_COOKIE_NAME		"member"

	PaintTop ( 1 );

	/*----------------------------------------------------------
		cookie stuff has to be written before html starts.
	----------------------------------------------------------*/
	/*----------------------------------------------------------
		get cookie
	----------------------------------------------------------*/
	if ( webParseCookie ( MEMBER_COOKIE_NAME, &MyCookie ) != 0 )
	{
		printf ( "Cannot find cookie.  Please LOGIN<br>\n" );
		exit ( 0 );
	}
	else
	{
		sprintf ( SessionUnique, "%s", MyCookie.UserName );
	}


	ReadSession ();

//	StartMySQL ( &MySql, "nutrition" );
	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	if ( CookieMember.xmid == 0 )
	{
		printf ( "Please LOGIN<br>\n" );
		exit ( 0 );
	}

	sprintf ( WhereClause, "Mid = %ld", CookieMember.xmid );
	if ( LoadMember ( WhereClause, &xmember, 0 ) != 1 )
	{
		printf ( "Cannot find member<br>\n" );
		printf ( "No member record found for ID %ld<br>", CookieMember.xmid );
		printf ( "Please register<br>\n" );
		exit ( 0 );
	}

	PaintTop ( 2 );

	GetInput ();

	ChkInput ();

	TakeAction ();

	if ( nsStrlen ( HistoryDate ) > 0 )
	{
		CalcTotals ();
	}
	PaintScreen ();

	return ( 0 );
}
