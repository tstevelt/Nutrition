/*----------------------------------------------------------------------------
	Program : PaintPassword.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint change password prompts.
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

void PaintPassword ()
{
	printf ( "<input type='hidden' name='forgot' value='%s'>\n", ForgotString );

	printf ( "<div class='story'>\n" );
	printf ( "<table class='table'>\n" );
	printf ( "<tr>\n" );
	printf ( "<td colspan='2'><h3>Set New Password</h3></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>Password 6 to 30 characters, contain three of upper, lower, numbers and punctuation.</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Password</td>\n" );
	printf ( "<td><input type='password' name='SignupPassword' size='30' maxlength='24'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Confirm Password</td>\n" );
	printf ( "<td><input type='password' name='ConfirmPassword' size='30' maxlength='24'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>&nbsp;</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='submit' name='SubmitSavePassword' value='Save Password'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "</table>\n" );
	printf ( "</div>\n" );

}
