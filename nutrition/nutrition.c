/*----------------------------------------------------------------------------
	Program : nutrition.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: The main nutrition website

	Who		Date		Modification
	---------------------------------------------------------------------

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
#include	"nutrition.h"

int main ( int argc, char *argv[] )
{
	COOKIE_RECORD	MyCookie;
	int		xi, xt;
	long	xl;

	ErrorClass = "error";
	/*----------------------------------------------------------
		cookie stuff has to be written before html starts.
	----------------------------------------------------------*/
	/*----------------------------------------------------------
		get cookie
	----------------------------------------------------------*/
	if ( webParseCookie ( MEMBER_COOKIE_NAME, &MyCookie ) != 0 )
	{
		MyCookie.LoggedIn = 1;
		MyCookie.Counter  = 1;

		shs_seed_random ();

		for ( xt = 1; xt <= 100; xt++ )
		{
			for ( xi = 0; xi < 15; xi++ )
			{
				xl = random_range ( 65, 90 );
				SessionUnique[xi] = (char) xl;
			}

			snprintf ( SessionFileName, sizeof ( SessionFileName ), "%s/%15.15s.session", RW_DIRECTORY, SessionUnique );

			if ( access ( SessionFileName, F_OK ) == 0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Session %s already on file.", SessionFileName );
			}
			else
			{
				break;
			}
		}

		sprintf ( MyCookie.UserName, "%-15.15s", SessionUnique );

		/*----------------------------------------------------------
			write cookie
		----------------------------------------------------------*/
		nsStrcpy  ( MyCookie.CookieName, MEMBER_COOKIE_NAME );
		MyCookie.LifeSeconds = MEMBER_COOKIE_LIFE_TIME;
		webPrintCookieRecord ( &MyCookie );
	}
	else
	{
		sprintf ( SessionUnique, "%s", MyCookie.UserName );
	}

	CurrentDateval ( &dvToday );

	PaintTop ();

	// StartMySQL ( &MySql, "nutrition" );
	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	GetInput ();

	ReadSession ();

	if ( CookieMember.xmid > 0 )
	{
		sprintf ( WhereClause, "id = %ld", CookieMember.xmid );
		LoadMember ( WhereClause, &CookieMember, 0 );
	}

	ChkInput ();

	TakeAction ();

	printf ( "<input type='hidden' id='MenuIndex' name='MenuIndex' value='%d'>\n", MenuIndex );

	GetContents ( MenuIndex );

//	if ( CookieMember.xmid > 0L )
//	{
//		sprintf ( WhereClause, "member.Mid = %ld", CookieMember.xmid );
//		LoadMember ( WhereClause, &xmember, 1 );
//	}

	PaintScreen ();

	PaintBottom ();
	
	/*----------------------------------------------------------
		close database
	----------------------------------------------------------*/
	dbyClose ( &MySql );

	return ( 0 );
}
