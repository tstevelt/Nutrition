/*----------------------------------------------------------------------------
	Program : SendEmail.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Send emails to members.  Message is in global var EmailMessage.
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
static	char	EmailAddress[32000];

void SendEmail ()
{
	char		fn[128];
	FILE		*fp;
	int			ndx, cnt;

/*----------------------------------------------------------
	create email
----------------------------------------------------------*/
	sprintf ( fn, "/var/local/tmp/member_%d.txt", getpid() );
	if (( fp = fopen ( fn, "w" )) == (FILE *)0 )
	{
		fprintf ( stderr, "Cannot create file to send email.\n" );
		return;
	}

	fprintf ( fp, "%s\n", EmailMessage );
	
	nsFclose ( fp );

/*----------------------------------------------------------
	for each member in list
	1) verify they have email address
	2a) either build group address or 
	2b) send individually
----------------------------------------------------------*/
	memset ( EmailAddress, '\0', sizeof(EmailAddress) );

	for ( ndx = 0, cnt = 0; ndx < EmailMembersCount; ndx++ )
	{
		snprintf ( Statement, sizeof(Statement), "id = %ld", EmailMembersArray[ndx] );
		if ( LoadMember ( Statement, &xmember, 1 ) != 1 )
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "Cannot load member %ld.", EmailMembersArray[ndx] );
			continue;
		}

		if ( xmember.xmstatus[0] != 'V' )
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "No verified email %s", xmember.xmname );
			continue;
		}

		if ( EmailPrivacy == 'I' )
		{
			SendAttached ( "tstevelt@silverhammersoftware.com",
						xmember.xmemail,
						"",
						"",
						EmailSubject,
						1, fn,
						0, NULL );
		}
		else
		{
			if ( cnt )
			{
				strcat ( EmailAddress, "," );
			}
			strcat ( EmailAddress, xmember.xmemail );
			cnt++;
		}
	}

	if ( EmailPrivacy == 'G' )
	{
		SendAttached ( "tstevelt@silverhammersoftware.com",
						EmailAddress,
						"",
						"",
						EmailSubject,
						1, fn,
						0, NULL );
		
	}
}
