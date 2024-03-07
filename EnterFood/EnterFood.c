/*----------------------------------------------------------------------------
	Program : EnterFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Enter a food into the database

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
#include	"EnterFood.h"

void ErrorSysLoaded ( char *FunctionName )
{
}

int	UseErrorSys = 1;
static	int		DebugMain = 0;

int main ( int argc, char *argv[] )
{
	COOKIE_RECORD	MyCookie;
#define		MEMBER_COOKIE_NAME		"member"
	extern	char	SessionUnique[20];

//xxxxxxxxxxxxx

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
	if ( CookieMember.xmid == 0 )
	{
		printf ( "Please LOGIN<br>\n" );
		exit ( 0 );
	}

//	StartMySQL ( &MySql, "nutrition" );
	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	PaintTop ( 2 );

//xxxxxxxxxxxxx

	GetInput ();

	if ( DebugMain )
	{
		printf ( "RunMode %d, xid %ld<br>\n", RunMode, xfood.xfid );
	}

	/*----------------------------------------------------------
		ChkInput may change RunMode depending on errors or input.
	----------------------------------------------------------*/
	ChkInput ();

	switch ( RunMode )
	{
		case MODE_CLEAR:
			memset ( &xfood, '\0', sizeof(xfood) );
			RunMode = MODE_START;
			/* fall-through */
		case MODE_START:
			PaintScreen ();
			break;

		case MODE_LOAD:
			Load ();
			PaintScreen ();
			break;

		case MODE_LOOKUP:
			if ( Lookup () < 1 )
			{
				RunMode = MODE_START;
				PaintScreen ();
			}
			break;

		case MODE_INSERT:
			//if ( ChkMacroArithmetic ( xfood.xfcalorie, xfood.xfcarb, xfood.xfprotein, xfood.xffat, 1.0 ) == 0 )
			//{
			//}
				Insert ();
			RunMode = MODE_FOUND;
			PaintScreen ();
			break;

		case MODE_UPDATE:
			//if ( ChkMacroArithmetic ( xfood.xfcalorie, xfood.xfcarb, xfood.xfprotein, xfood.xffat, 1.0 ) == 0 )
			//{
			//}
				Update ();
			RunMode = MODE_FOUND;
			PaintScreen ();
			break;

		case MODE_DELETE:
			if ( Delete () == 0 )
			{
				memset ( &xfood, '\0', sizeof(xfood) );
			}
			PaintScreen ();
			break;

		case MODE_FOUND:
			PaintScreen ();
			break;

		default :
			sprintf ( StatementOne, "Unknown RunMode %d.", RunMode );
			SaveError ( StatementOne );
			break;
	}


	printf ( "</form>\n" );

	ErrorSysLoaded ( "Loaded" );

	printf ( "</body>\n" );
	printf ( "</html>\n" );

	dbyClose ( &MySql );

	return ( 0 );
}
