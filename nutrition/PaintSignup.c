/*----------------------------------------------------------------------------
	Program : PaintSignup.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint signup screen for input.
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

void PaintSignup ()
{
	printf ( "<table class='table'>\n" );
	printf ( "<tr>\n" );
	printf ( "<td colspan='2'><h3>Sign up</h3></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Your name</td>\n" );
	printf ( "<td><input type='search' name='SignupName' size='35' maxlength='30'" );
	if ( nsStrlen ( SignupName ) > 0 )
	{
		printf ( " value='%s'", SignupName );
	}
	printf ( "></td>\n" );
	printf ( "</tr>\n" );


	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>\n" );
	printf ( "Your email address has to be verified before you can log in.\n" );
	printf ( "<ul>\n" );
	printf ( "<li>A verification email will be sent.</li>\n" );
	printf ( "<li>The email will expire in one hour.</li>\n" );
	printf ( "<li>You must verify from the same device.</li>\n" );
	printf ( "</ul>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Email address</td>\n" );
	printf ( "<td><input type='search' name='SignupEmail' size='85' maxlength='80'" );
	if ( nsStrlen ( SignupEmail ) > 0 )
	{
		printf ( " value='%s'", SignupEmail );
	}
	printf ( "></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>Password 6 to 30 characters, contain three of upper, lower, numbers and punctuation.</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Password</td>\n" );
	printf ( "<td><input type='password' name='SignupPassword' size='30' maxlength='24'></td>\n" );
	printf ( "</tr>\n" );
	
	printf ( "<tr>\n" );
	printf ( "<td>Confirm Password</td>\n" );
	printf ( "<td><input type='password' name='ConfirmPassword' size='30' maxlength='24'></td>\n" );
	printf ( "</tr>\n" );

//	printf ( "<tr>\n" );
//	printf ( "<td colspan='2'><hr></td>\n" );
//	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td align='right'>\n" );
	printf ( "<input type='checkbox' id='SignupAllowCookie'>\n" );
	printf ( "</td>\n" );
	printf ( "<td>\n" );
	printf ( "I will allow cookies in order to stay logged in.\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<input type='hidden' id='what' name='what' value='noop'>\n" );
	printf ( "<td colspan='2' align='center'><input type='button' name='SubmitSignup' value='Sign up' onclick='javascript:CheckCookie();'></td>\n" );
	printf ( "</tr>\n" );
	printf ( "</table>\n" );

}
