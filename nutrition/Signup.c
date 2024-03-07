/*----------------------------------------------------------------------------
	Program : Signup.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Save signup information and send email for address verification
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

int Signup ()
{
	int			Affected;
	int			rv = 0;
	char		fn[128];
	FILE		*fp;
	char		Link[256];
	time_t		tvec;
	time_t		TimeStamp;

	TimeStamp = time ( NULL );

	// sprintf ( WhereClause, "inserted = %ld", TimeStamp );
	/*----------------------------------------------------------
		insert member
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"insert into member ( Mname, Memail, Mpassword, Mipaddr, inserted ) values ( '%s', '%s', '%s', '%s', %ld )",
			SignupName, SignupEmail, pw_sha_make_pw ( (unsigned char *) SignupPassword ), Remote_Address, TimeStamp );

	Affected = dbyInsert ( "Signup", &MySql, Statement, 0, LogFileName );
	if ( Affected == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "1. Signup failed to insert new member record." );
		rv = -2;
	}
	else if (( xmember.xmid = mysql_insert_id ( &MySql )) == 0L )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "2. Signup failed to insert new member record." );
		rv = -3;
	}
	 
	if ( rv == 0 )
	{
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

			snprintf ( Link, sizeof(Link), "http://nutrition.silverhammersoftware.com?verify=%ld&ipaddr=%s&time=%ld", xmember.xmid, Remote_Address, tvec );

			fprintf ( fp, "<html>\n" );

			fprintf ( fp, "<head>\n" );
			fprintf ( fp, "<title>message</title>\n" );
			fprintf ( fp, "</head>\n" );

			fprintf ( fp, "<body color='#FAEBD7'>\n" );

			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "Hello %s,\n", SignupName );
			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "This email address was used to sign up on %s.<br>\n", URL_NAME );
			fprintf ( fp, "If you did not sign up, then please ignore this messeage.\n" );
			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "Otherwise, we are asking that you verify your email address<br>\n" );
			fprintf ( fp, "by clicking the link below (expires within one hour):\n" );
			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "<a href='%s'>Verify %s</a>\n", Link, SignupEmail );
			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "Thank you, Nutrition\n" );
			fprintf ( fp, "<p>\n" );

			fprintf ( fp, "After verifying, use the 'Edit Profile' to enter your gender, weight<br>\n" );
			fprintf ( fp, "and target macro nutrients.<br>\n" );
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
			
			sprintf ( ErrorArray[ErrorCount++].Message, 
				"Verification email sent to %s. Please respond within one hour from the same device (IP address).", SignupEmail );
		}
	}

	return ( rv );
}
