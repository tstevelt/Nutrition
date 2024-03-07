/*----------------------------------------------------------------------------
	Program : TakeAction.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Run selected sub-routine.
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

void TakeAction ()
{
	char	fn[128];
	FILE	*fp;

	switch ( RunMode )
	{
		case MODE_UNKNOWN:
		case MODE_PAINT_BLOG:
			break;

		case MODE_SAVE_SIGNUP:
			Signup ();
			break;

		case MODE_VERIFY:
			Verify ();
			break;

		case MODE_LOGIN:
			Login ();
			break;

		case MODE_FORGOT:
			Forgot ();
			break;

		case MODE_CHANGE_EMAIL:
			SaveEmail ();
			break;

		case MODE_SAVE_PROFILE:
			SaveProfile ();
			break;
			
		case MODE_SAVE_PASSWORD:
		case MODE_CHANGE_PASSWORD:
			SavePassword ();
			break;

		case MODE_LOGOUT:
			Logout ();
			break;

		case MODE_CONTACT:
			sprintf ( fn, "/tmp/member_%d.txt", getpid() );
			if (( fp = fopen ( fn, "w" )) == (FILE *)0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Cannot create file to send email." );
				return;
			}

			fprintf ( fp, "This is a message from %s:\n", URL_NAME );

			fprintf ( fp, "Sent from IP ADDRESS %s\n", Remote_Address );

			fprintf ( fp, "\n" );

			fprintf ( fp, "%s\n\n", ContactMessage );
			nsFclose ( fp );

			SendAttached ( "tstevelt@silverhammersoftware.com",
							"tstevelt@silverhammersoftware.com",
							"",
							"",
							ContactSubject,
							0, fn,
							0, NULL );
			
			unlink ( fn );

			sprintf ( ErrorArray[ErrorCount++].Message, "Thank you for your message!" );
			MenuIndex = MENU_INDEX_HOME;
			break;

		case MODE_SEND_EMAIL:
			SendEmail ();
			break;

		default:
			sprintf ( ErrorArray[ErrorCount++].Message, "TakeAction: unknown code %d.", RunMode );
			break;
	}
}
