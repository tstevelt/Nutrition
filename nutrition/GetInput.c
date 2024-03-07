/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Get user input from screen or QUERY_STRING
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

void GetInput ()
{
	int		xa;

	if (( Remote_Address = getenv ( "REMOTE_ADDR" )) == (char *)0 )
	{
		printf ( "Cannot determine your IP address." );
		return;
	}

	if ( webGetInput () != 0 )
	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}

	MenuIndex = MENU_INDEX_HOME;
	RunMode = MODE_UNKNOWN;

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

// not showing up in either apache log???
// fprintf ( stderr, "name=value %s = %s<br>\n", webNames[xa] , webValues[xa] );
// fflush ( stderr );

		if ( nsStrcmp (webNames[xa], "MenuIndex" ) == 0 )
		{
			MenuIndex =  nsAtoi ( webValues[xa] );
		}
		/*----------------------------------------------------------
			login page
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "LoginEmail" ) == 0 )
		{
			LoginEmail = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "LoginPassword" ) == 0 )
		{
			LoginPassword = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitLogin" ) == 0 )
		{
			RunMode = MODE_LOGIN;
		}

		/*----------------------------------------------------------
			forgot page
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "ForgotEmail" ) == 0 )
		{
			ForgotEmail = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitForgot" ) == 0 )
		{
			RunMode = MODE_FORGOT;
		}

		/*----------------------------------------------------------
			responing to forgot email
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "forgot" ) == 0 )
		{
			ForgotString = webValues[xa];
			RunMode = MODE_PAINT_PASSWORD;
		}

		else if ( nsStrcmp ( webNames[xa], "SubmitSavePassword" ) == 0 )
		{
			RunMode = MODE_SAVE_PASSWORD;
		}

		/*----------------------------------------------------------
			logout page
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "LogoutSelect" ) == 0 )
		{
			LogoutSelect = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitLogout" ) == 0 )
		{
			RunMode = MODE_LOGOUT;
		}

		/*----------------------------------------------------------
			signup page
			profile page
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "SignupName" ) == 0 )
		{
			SignupName = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupEmail" ) == 0 )
		{
			SignupEmail = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupPassword" ) == 0 )
		{
			SignupPassword = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "ConfirmPassword" ) == 0 )
		{
			ConfirmPassword = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupWeight" ) == 0 )
		{
			SignupWeight  = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupHeight" ) == 0 )
		{
			SignupHeight  = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "ActivityLevel" ) == 0 )
		{
			SignupActivityLevel = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupDiet" ) == 0 )
		{
			SignupDiet = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupBirthdate" ) == 0 )
		{
			SignupBirthdate = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupGender" ) == 0 )
		{
			SignupGender = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "SignupCalorie" ) == 0 )
		{
			SignupCalorie = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupCarb" ) == 0 )
		{
			SignupCarb    = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupProtein" ) == 0 )
		{
			SignupProtein = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupFat" ) == 0 )
		{
			SignupFat     = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupSodium" ) == 0 )
		{
			SignupSodium = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupFiber" ) == 0 )
		{
			SignupFiber = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SignupAllowCookie" ) == 0 )
		{
			SignupAllowCookie = webValues[xa][0];
		}

		else if ( nsStrcmp ( webNames[xa], "SubmitSignup" ) == 0 )
		{
			RunMode = MODE_SAVE_SIGNUP;
		}
		else if ( nsStrcmp ( webNames[xa], "what" ) == 0 &&  nsStrcmp ( webValues[xa], "SubmitSignup" ) == 0 )
		{
			RunMode = MODE_SAVE_SIGNUP;
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitProfile" ) == 0 )
		{
			RunMode = MODE_SAVE_PROFILE;
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitChangePassword" ) == 0 )
		{
			RunMode = MODE_CHANGE_PASSWORD;
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitChangeEmail" ) == 0 )
		{
			RunMode = MODE_CHANGE_EMAIL;
		}

		/*----------------------------------------------------------
			verify link from verifaction email
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "verify" ) == 0 )
		{
			VerifyID = nsAtol ( webValues[xa] );
			RunMode = MODE_VERIFY;
		}
		else if ( nsStrcmp ( webNames[xa], "ipaddr" ) == 0 )
		{
			VerifyIPaddr = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "time" ) == 0 )
		{
			VerifyTime = nsAtol ( webValues[xa] );
		}

		/*----------------------------------------------------------
			contact page
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "ContactSubject" ) == 0 )
		{
			ContactSubject = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "ContactMessage" ) == 0 )
		{
			ContactMessage = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "ContactCaptcha" ) == 0 )
		{
			ContactCaptcha = nsStrToUpcase ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitContact" ) == 0 )
		{
			RunMode = MODE_CONTACT;
		}

		/*----------------------------------------------------------
			email members page
		----------------------------------------------------------*/
		else if (( nsStrncmp ( webNames[xa], "cV_member_", 10 ) == 0 ) ||
				 ( nsStrncmp ( webNames[xa], "cX_member_", 10 ) == 0 ))
		{
			if ( EmailMembersCount == MAX_EMAIL )
			{
				sprintf ( ErrorArray[ErrorCount++].Message, "Email limited to %d members", MAX_EMAIL );
			}
			else
			{
				EmailMembersArray[EmailMembersCount++] = nsAtol ( &webNames[xa][10] );
			}
		}
		else if ( nsStrcmp ( webNames[xa], "EmailSubject" ) == 0 )
		{
			EmailSubject = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "EmailMessage" ) == 0 )
		{
			EmailMessage = webValues[xa];
		}
		else if ( nsStrcmp ( webNames[xa], "EmailPrivacy" ) == 0 )
		{
			EmailPrivacy = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "SubmitEmail" ) == 0 )
		{
			RunMode = MODE_SEND_EMAIL;
		}

		/*----------------------------------------------------------
			sf=5&from=%ld&to=%ld
		----------------------------------------------------------*/
		else if ( nsStrcmp ( webNames[xa], "sf" ) == 0 )
		{
			RunMode = MODE_SEND_MESSAGE_TO_MEMBER;
		}
		else if ( nsStrcmp ( webNames[xa], "from" ) == 0 )
		{
			CookieMember.xmid = FromMemberID = nsAtol ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "to" ) == 0 )
		{
			ToMemberID = nsAtol ( webValues[xa] );
		}

		else
		{
			sprintf ( ErrorArray[ErrorCount++].Message, "Unknown name=value %s = %s", webNames[xa] , webValues[xa] );
		}
	}

}
