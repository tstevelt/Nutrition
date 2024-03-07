/*----------------------------------------------------------------------------
	Program : PaintProfile.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint user profile for input.
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

#define DEBUG
#undef DEBUG

void PaintProfile ()
{
	/*----------------------------------------------------------
		load member
	----------------------------------------------------------*/
	sprintf ( WhereClause, "member.Mid = %ld", CookieMember.xmid );
#ifdef DEBUG
	printf ( "%s<br>\n", WhereClause );
#endif 
	if ( LoadMember ( WhereClause, &xmember, 0 ) < 1 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Cannot load member information" );
		return;
	}

	/*----------------------------------------------------------
		change email address
	----------------------------------------------------------*/
	printf ( "<table class='table table-borderless'>\n" );
	printf ( "<tr>\n" );
	printf ( "<td colspan='2'><h3>Change your email address</h3></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>\n" );
	printf ( "If you change your email address, you will be logged out and have to verify you new address before you can log in again.\n" );
	printf ( "<ul>\n" );
	printf ( "<li>A verification email will be sent.</li>\n" );
	printf ( "<li>The email will expire in one hour.</li>\n" );
	printf ( "<li>You must verify from the same device.</li>\n" );
	printf ( "</ul>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td width='25%%'>New Email Address</td>\n" );
	printf ( "<td width='75%%'><input type='search' name='SignupEmail' size='35' maxlength='30'\n" );
	printf ( " value='%s'>\n", xmember.xmemail );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>\n" );
	printf ( "<input type='reset' name='reset' value='Reset'>\n" );
	printf ( "<input type='submit' name='SubmitChangeEmail' value='Save New Email'%s>\n", CookieMember.xmid ==DEMO_MEMBER ? " disabled" : "" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "</table>\n" );

	printf ( "</div>\n" );

	/*----------------------------------------------------------
		change name and subscription info
	----------------------------------------------------------*/
#ifdef DEBUG
	printf ( "<div class='story'>\n" );
	printf ( "status %c role %c gender %c<br>\n", xmember.xmstatus[0], xmember.xmrole[0], xmember.xmgender[0] );
	printf ( "</div>\n" );
#endif
	if ( xmember.xmstatus[0] == 'V' )
	{
		printf ( "<div class='story'>\n" );
		printf ( "<table class='table table-borderless'>\n" );
		printf ( "<tr>\n" );
		printf ( "<td colspan='2'><h3>Edit Profile</h3></td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td width='25%%'>Name</td>\n" );
		printf ( "<td width='75%%'><input type='search' name='SignupName' size='35' maxlength='30'\n" );
		printf ( " value='%s'>\n", xmember.xmname );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Gender</td>\n" );
		printf ( "<td>\n" );
		printf ( "<select name='SignupGender' id='SignupGender'>\n" );
		printf ( "<option value='M' %s>Male</option>\n",    xmember.xmgender[0] != 'F' ? "selected" : "" );
		printf ( "<option value='F' %s>Female</option>\n",  xmember.xmgender[0] == 'F' ? "selected" : "" );
		printf ( "</select>\n" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Birth Date (yyyy-mm-dd)</td>\n" );
		printf ( "<td><input type='search' name='SignupBirthdate' id='SignupBirthdate' size='10'\n" );
		printf ( " value='%s'>\n", xmember.xmbirthdate );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Weight (pounds)</td>\n" );
		printf ( "<td><input type='search' name='SignupWeight' id='SignupWeight' size='6'\n" );
		printf ( " value='%d'>\n", xmember.xmweight );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Height (inches)</td>\n" );
		printf ( "<td><input type='search' name='SignupHeight' id='SignupHeight' size='4'\n" );
		printf ( " value='%d'>\n", xmember.xmheight );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		/*----------------------------------------------------------
			calc suggested macro values, if requested
		----------------------------------------------------------*/
		printf ( "<tr>\n" );
		printf ( "<td>Activity Level</td>\n" );
		printf ( "<td>\n" );
		printf ( "<select name='ActivityLevel' id='ActivityLevel'>\n" );
		printf ( "<option value='?'>-- activity level --</option>\n" );
		printf ( "<option value='%c'%s>Sedentary</option>\n", ACTIVE_SEDENTARY, xmember.xmactive[0] == ACTIVE_SEDENTARY ? " selected" : "" );
		printf ( "<option value='%c'%s>Low Active</option>\n", ACTIVE_LOW, xmember.xmactive[0] == ACTIVE_LOW ? " selected" : "" );
		printf ( "<option value='%c'%s>Active</option>\n", ACTIVE_ACTIVE, xmember.xmactive[0] == ACTIVE_ACTIVE ? " selected" : "" );
		printf ( "<option value='%c'%s>Very Active</option>\n", ACTIVE_HIGH, xmember.xmactive[0] == ACTIVE_HIGH ? " selected" : "" );
		printf ( "</select>\n" );
		printf ( "<input type='button' value='?' onclick='javascript:PopupWindow(600,300,\"ExplainActivity.html\");'>\n" );
		printf ( "&emsp;<select name='SignupDiet' id='SignupDiet'>\n" );
		printf ( "<option value='?'>-- diet --</option>\n" );
		printf ( "<option value='%c'%s>Standard</option>\n", DIET_STANDARD, xmember.xmdiet[0] == DIET_STANDARD ? " selected" : "" );
		printf ( "<option value='%c'%s>Low Carb</option>\n", DIET_LOW_CARB, xmember.xmdiet[0] == DIET_LOW_CARB ? " selected" : "" );
		printf ( "<option value='%c'%s>Moderate</option>\n", DIET_MODERATE, xmember.xmdiet[0] == DIET_MODERATE ? " selected" : "" );
		printf ( "<option value='%c'%s>Low Fat</option>\n",  DIET_LOW_FAT, xmember.xmdiet[0] == DIET_LOW_FAT ? " selected" : "" );
		printf ( "<option value='%c'%s>Paleo</option>\n", DIET_PALEO, xmember.xmdiet[0] == DIET_PALEO ? " selected" : "" );
		printf ( "<option value='%c'%s>Conley</option>\n", DIET_CONLEY, xmember.xmdiet[0] == DIET_CONLEY ? " selected" : "" );
		printf ( "</select>\n" );
		printf ( "<input type='button' value='?' onclick='javascript:PopupWindow(800,400,\"ExplainDietTable.html\");'>\n" );
		printf ( "&emsp;<input type='button' id='buttonCalcSuggMacro' value='Calculate Suggested' onclick='javascript:CalcSuggMacro();'>\n" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Calorie Target</td>\n" );
		printf ( "<td><input type='search' name='SignupCalorie' id='SignupCalorie' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmcalorie );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Carbohydrates (grams)</td>\n" );
		printf ( "<td><input type='search' name='SignupCarb' id='SignupCarb' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmcarb );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Protein (grams)</td>\n" );
		printf ( "<td><input type='search' name='SignupProtein' id='SignupProtein' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmprotein );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Fat (grams)</td>\n" );
		printf ( "<td><input type='search' name='SignupFat' id='SignupFat' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmfat );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Sodium (mg))</td>\n" );
		printf ( "<td><input type='search' name='SignupSodium' id='SignupSodium' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmsodium );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td>Daily Fiber (grams)</td>\n" );
		printf ( "<td><input type='search' name='SignupFiber' id='SignupFiber' size='10'\n" );
		printf ( " value='%d'>\n", xmember.xmfiber );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td colspan='2'>\n" );
		printf ( "<input type='reset' name='reset' value='Reset'>\n" );
		printf ( "<input type='submit' name='SubmitProfile' value='Save Changes'%s>\n", CookieMember.xmid ==DEMO_MEMBER ? " disabled" : "" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "</table>\n" );

		printf ( "</div>\n" );

	}

	/*----------------------------------------------------------
		change password
	----------------------------------------------------------*/
	printf ( "<div class='story'>\n" );
	
	printf ( "<table class='table table-borderless'>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'><h3>Change Password</h3></td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>Password 6 to 30 characters, contain three of upper, lower, numbers and punctuation.</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td width='25%%'>Password</td>\n" );
	printf ( "<td width='75%%'><input type='password' name='SignupPassword' size='30' maxlength='24'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Confirm Password</td>\n" );
	printf ( "<td><input type='password' name='ConfirmPassword' size='30' maxlength='24'>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>\n" );
	printf ( "<input type='submit' name='SubmitChangePassword' value='Change Password'%s>\n", CookieMember.xmid ==DEMO_MEMBER ? " disabled" : "" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "</table>\n" );

}
