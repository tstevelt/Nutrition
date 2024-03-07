/*----------------------------------------------------------------------------
	Program : Login.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Try to login the user.
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

#include	"nutrition.h"

static  char    Statement[MAXSTATEMENT];

static	int		DebugLogin = 0;

int Login ()
{
	DBY_QUERY     *qryMember;
	int			rv = 0;

	CookieMember.xmid = 0L;

	snprintf ( Statement, sizeof(Statement),
		"select Mid, Mname, Mstatus, Mrole from member where (Memail = '%s' or Mname = '%s') and Mpassword = '%s'", 
					LoginEmail, LoginEmail, pw_sha_make_pw ( (unsigned char *) LoginPassword ) );

if ( DebugLogin )
{
	fprintf ( stderr, "%s\n", Statement );
}

	qryMember = dbySelect ( "Login", &MySql, Statement, LogFileName );
	if ( qryMember == (DBY_QUERY *) 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Login select returned NULL." );
		rv = -1;
	}
	else if ( qryMember->NumRows == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Unknown member or password." );
		rv = -2;
	}
	else 
	{
		/*---------------------------------------------------------
			check status
		----------------------------------------------------------*/
		qryMember->EachRow = mysql_fetch_row ( qryMember->Result );
		switch ( qryMember->EachRow[2][0] )
		{
			case 'P':
				sprintf ( ErrorArray[ErrorCount++].Message, "%s, please verify your email before logging in!", qryMember->EachRow[1] );
				break;

			case 'V':
				CookieMember.xmid = nsAtol ( qryMember->EachRow[0] );
				CookieMember.xmrole[0] =     qryMember->EachRow[3][0];
				// sprintf ( ErrorArray[ErrorCount++].Message, "Okay %s.", qryMember->EachRow[1] );
				WriteSession ();
				break;

			default:	
				sprintf ( ErrorArray[ErrorCount++].Message, "Unknown member status" );
				rv = -4;
				break;
		}
	}

	if ( rv == 0 )
	{
		MenuIndex = MENU_INDEX_HOME;
	}

	return ( rv );
}
