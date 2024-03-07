/*----------------------------------------------------------------------------
	Program : SessionFuncs.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Session functions.
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

#include	"nutrilib.h"
#include	"nutriprivate.h"

static	char	SessionFileName[256];
char		SessionUnique[20];
XMEMBER		CookieMember;


static	FILE	*fpSession;
#define		MAXSTRINGSPACE		1024
//static	char	StringSpace[MAXSTRINGSPACE];
//static	int		StringIndex;

static void MakeStringSpace ()
{
//	memset ( StringSpace, '\0', sizeof(StringSpace) );
//	StringIndex = 0;
//
//	CookieMember.xmname = &StringSpace[StringIndex];
//
//	StringIndex = sprintf ( &StringSpace[StringIndex], "Not logged in" );
//	StringIndex++;

	snprintf ( CookieMember.xmname, sizeof(CookieMember.xmname), "Not logged in" );
}

static void MakeSessionFileName ()
{
	sprintf ( SessionFileName, "%s/%s.session", RW_DIRECTORY, SessionUnique );
}

void WriteSession ()
{
	MakeSessionFileName ();

	if (( fpSession = fopen ( SessionFileName, "w" )) == (FILE *)0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Cannot create session file %s", SessionFileName );
		return;
	}

	sprintf ( WhereClause, "member.Mid = %ld", CookieMember.xmid );
	if ( LoadMember ( WhereClause, &CookieMember, 0 ) < 1 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "WriteSession: Cannot LoadMember %ld", CookieMember.xmid );
		nsFclose ( fpSession );
		return;
	}

	fwrite ( &CookieMember, sizeof(XMEMBER), 1, fpSession );

	nsFclose ( fpSession );
}

void ReadSession ()
{
	MakeStringSpace ();

	MakeSessionFileName ();

	if (( fpSession = fopen ( SessionFileName, "r" )) == (FILE *)0 )
	{
		// printf ( "Cannot open %s<br>\n", SessionFileName );
		CookieMember.xmid = 0;
		return;
	}

	fread ( &CookieMember, sizeof(XMEMBER), 1, fpSession );

#ifdef INTERNAL_SERVER_ERROR_PROBLY_DB_NOT_OPEN
	/*---------------------------------------------------------------------------
		menu client programs may not realize that profile was changed.
	---------------------------------------------------------------------------*/
	sprintf ( WhereClause, "member.Mid = %ld", CookieMember.xmid );
	if ( LoadMember ( WhereClause, &CookieMember, 0 ) < 1 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "ReadSession: Cannot LoadMember %ld", CookieMember.xmid );
		nsFclose ( fpSession );
		return;
	}
#endif

	// printf ( "%ld  %s  %c<br>\n", CookieMember.xmid, CookieMember.xmname, CookieMember.xmrole[0] );

	nsFclose ( fpSession  );
}

void RemoveSession ()
{
	MakeStringSpace ();

	MakeSessionFileName ();

	unlink ( SessionFileName );

}
