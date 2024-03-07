/*----------------------------------------------------------------------------
	Program : SaveEmail.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Save new email address
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

int SaveEmail ()
{
	int			Affected;
	int			rv = 0;
	char		fn[128];
	FILE		*fp;
	char		Link[256];
	time_t		tvec;

	/*----------------------------------------------------------
		check if email already on file
	----------------------------------------------------------*/
	sprintf ( WhereClause, "Memail = '%s'", SignupEmail );
	if ( LoadMember ( WhereClause, &xmember, 0 ) >= 1 )
	{
		if ( CookieMember.xmid == xmember.xmid )
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "Same email address -- nothing to do." );
		}
		else
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "Email address is already on file." );
		}
		rv = -1;
		return ( rv );
	}

// sprintf ( ErrorArray[ErrorCount++].Message, "Not finished." );
// return  ( 0 );

	/*----------------------------------------------------------
		set new password
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"update member set Memail = '%s', Mstatus = 'P' where member.Mid = %ld", 
			SignupEmail, CookieMember.xmid );

#ifdef DEBUG
#define DEBUG
	sprintf ( ErrorArray[ErrorCount++].Message, Statement );
#endif

	Affected = dbyUpdate ( "SaveEmail", &MySql, Statement, 0, LogFileName );
	if ( Affected == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Change email failed." );
		rv = -2;
		return ( rv );
	}
	else
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Email changed." );
	}


	/*----------------------------------------------------------
		send verification email
	----------------------------------------------------------*/
	sprintf ( fn, "/var/local/tmp/member_%d.txt", getpid() );
	if (( fp = fopen ( fn, "w" )) == (FILE *)0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Cannot create file to send email." );
	}
	else
	{
		tvec = time ( NULL );

		snprintf ( Link, sizeof(Link), "http://nutrition.silverhammersoftware.com?verify=%ld&ipaddr=%s&time=%ld", CookieMember.xmid, Remote_Address, tvec );

		fprintf ( fp, "<html>\n" );

		fprintf ( fp, "<head>\n" );
		fprintf ( fp, "<title>message</title>\n" );
		fprintf ( fp, "</head>\n" );

		fprintf ( fp, "<body color='#FAEBD7'>\n" );

		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "Hello %s,\n", SignupName );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "This email address was changed on %s.<br>\n", URL_NAME );
		fprintf ( fp, "If you did not change your email address, then please ignore this messeage.\n" );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "Otherwise, we are asking that you verify your email address<br>\n" );
		fprintf ( fp, "by clicking the link below (expires within one hour):\n" );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "<a href='%s'>Verify %s</a>\n", Link, SignupEmail );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "Thank you, Nutrition\n" );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "Sign up from IP ADDRESS %s\n", Remote_Address );
		fprintf ( fp, "<p>\n" );

		fprintf ( fp, "</body>\n" );
		fprintf ( fp, "</html>\n" );

		nsFclose ( fp );

		SendAttached ( "tstevelt@silverhammersoftware.com",
						SignupEmail,
						"",
						"",
						"Email Verification from Nutrition",
						1, fn,
						0, NULL );
		
		sprintf ( ErrorArray[ErrorCount++].Message, "Verification email sent to %s. Please respond within one hour from the same device (IP address).", SignupEmail );
	}

	Logout ();

	return ( rv );
}
