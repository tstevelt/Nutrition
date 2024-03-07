/*----------------------------------------------------------------------------
	Program : ChkInput.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Validate user input
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

void ChkInput ()
{
	int		rv;
	time_t	tvec;
	char	*DecodedString;
#define		MAXTOKS		10
	char	*tokens[MAXTOKS];
	int		tokcnt;
	char	*String_Address;
	long	StringTime;

	tvec = time ( NULL );

// sprintf ( ErrorArray[ErrorCount++].Message, "XXX not finished." );
// RunMode = MODE_UNKNOWN;
	switch ( RunMode )
	{
		case MODE_SEND_EMAIL:
			if ( EmailMembersCount == 0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "No members selected." );
				RunMode = MODE_UNKNOWN;
			}
			if ( EmailPrivacy == '?' )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Must choose Privacy Mode." );
				RunMode = MODE_UNKNOWN;
			}
			if ( nsStrlen ( EmailSubject ) < 4 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Please use a longer subject." );
				RunMode = MODE_UNKNOWN;
			}
			if ( nsStrlen ( EmailMessage ) < 10 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Please enter a longer message." );
				RunMode = MODE_UNKNOWN;
			}
			break;

		case MODE_CHANGE_EMAIL:
			if (( nsStrlen ( SignupEmail ) < 5 ) || 
				( nsStrchr ( SignupEmail, '@' ) == (char *)0 ) || 
				( nsStrchr ( SignupEmail, '.' ) == (char *)0 ))
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Please enter valid email address." );
				RunMode = MODE_UNKNOWN;
			}
			break;

		case MODE_SAVE_PROFILE:
		case MODE_SAVE_SIGNUP:
			if ( nsStrncasecmp ( SignupName, "demo", 4 ) == 0 )
			{
				break;
			}

			if (( nsStrlen ( SignupName ) < 3 ) || 
				( nsStrchr ( SignupName, ' ' ) == (char *)0 ))
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Please enter both first and last name." );
				RunMode = MODE_UNKNOWN;
			}

			if ( RunMode == MODE_SAVE_SIGNUP )
			{
				if (( nsStrlen ( SignupEmail ) < 5 ) || 
					( nsStrchr ( SignupEmail, '@' ) == (char *)0 ) || 
					( nsStrchr ( SignupEmail, '.' ) == (char *)0 ))
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "Please enter valid email address." );
					RunMode = MODE_UNKNOWN;
				}

				if ( nsStrcmp ( SignupPassword, ConfirmPassword ) != 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "Passwords do not match." );
					RunMode = MODE_UNKNOWN;
				}

				if (( rv = pw_policy ( SignupPassword, 3 )) != 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "%s", pw_policy_string ( rv ) );
					RunMode = MODE_UNKNOWN;
				}

				sprintf ( WhereClause, "Mname = '%s'", SignupName );
				if ( LoadMember ( WhereClause, &xmember, 0 ) > 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "Name is already on file." );
					RunMode = MODE_UNKNOWN;
				}

				sprintf ( WhereClause, "Memail = '%s'", SignupEmail );
				if ( LoadMember ( WhereClause, &xmember, 0 ) > 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "Email address is already on file." );
					sprintf ( ErrorArray[ErrorCount++].Message, "Please use 'Forgot My Password' on the login page." );
					RunMode = MODE_UNKNOWN;
				}
			}
			else if ( RunMode == MODE_SAVE_PROFILE )
			{
				DATEVAL 	TestDateVal;
				if ( StrToDatevalFmt ( SignupBirthdate, DATEFMT_YYYY_MM_DD, &TestDateVal ) != 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message,  "Please enter a date using yyyy-mm-dd format" );
					RunMode = MODE_UNKNOWN;
				}
				if ( ChkMacroArithmetic ( SignupCalorie, SignupCarb, SignupProtein, SignupFat, 1.0 ) != 0 )
				{
					RunMode = MODE_UNKNOWN;
				}
			}

			break;

		case MODE_CHANGE_PASSWORD:
			if ( nsStrcmp ( SignupPassword, ConfirmPassword ) != 0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Passwords do not match." );
				RunMode = MODE_UNKNOWN;
			}

			if (( rv = pw_policy ( SignupPassword, 3 )) != 0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "%s", pw_policy_string ( rv ) );
				RunMode = MODE_UNKNOWN;
			}
			break;

		case MODE_VERIFY:
			// VerifyID
			// VerifyIPaddr
			if ( tvec - VerifyTime > 60 * 60 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Verification link is expired." );
				RunMode = MODE_UNKNOWN;
			}
			break;

		case MODE_LOGIN:
			break; 

		case MODE_FORGOT:
			if (( nsStrlen ( ForgotEmail ) < 5 ) || 
				( nsStrchr ( ForgotEmail, '@' ) == (char *)0 ) || 
				( nsStrchr ( ForgotEmail, '.' ) == (char *)0 ))
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Please enter valid email address." );
				RunMode = MODE_UNKNOWN;
			}
			break; 

		case MODE_LOGOUT:
//			if ( LogoutSelect != 'Y' )
//			{
//				sprintf ( ErrorArray[ErrorCount++].Message, "Pick Yes if you want to log out" );
//				RunMode = MODE_UNKNOWN;
//			}
			break; 

		case MODE_PAINT_PASSWORD:
		case MODE_SAVE_PASSWORD:
			DecodedString = tmsDecode ( ForgotString );
			if ( nsStrcmp ( DecodedString, "hacker" ) == 0 )
			{
				printf ( "<h2>Hacking is a crime!</h2>\n" );
				exit ( 0 );
			}
			if (( tokcnt = GetTokensD ( DecodedString, ":", tokens, MAXTOKS )) < 3 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Can not get tokens from %s", ForgotString );
				RunMode = MODE_UNKNOWN;
				return;
			}
			// xmember.xmid, Remote_Address, tvec

			xmember.xmid    = nsAtol ( tokens[0] );
			String_Address =        tokens[1];
			StringTime     = nsAtol ( tokens[2] );
#ifdef DEBUG
#define DEBUG
			sprintf ( ErrorArray[ErrorCount++].Message, "member %ld, ip addr %s time %ld", xmember.xmid, String_Address, StringTime );
#endif
			if ( nsStrcmp ( String_Address, Remote_Address ) != 0 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Invalid IP address" );
				RunMode = MODE_UNKNOWN;
				return;
			}
			
			if ( tvec - StringTime > 60 * 60 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "New password link is expired." );
				RunMode = MODE_UNKNOWN;
				return;
			}

			sprintf ( WhereClause, "member.Mid = %ld", xmember.xmid );
			if ( LoadMember ( WhereClause, &xmember, 0 ) < 1 )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Unknown member." );
				RunMode = MODE_UNKNOWN;
				return;
			}

			break;

	}
}
