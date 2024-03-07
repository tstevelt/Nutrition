/*----------------------------------------------------------------------------
	Program : SavePassword.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Save valid password.
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

void SavePassword ()
{
	long	Affected;
	int		WasLoggedIn = 0;

	if ( CookieMember.xmid > 0 )
	{
		xmember.xmid = CookieMember.xmid;
		WasLoggedIn = 1;
	}

	/*----------------------------------------------------------
		set new password
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"update member set Mpassword = '%s' where member.Mid = %ld", 
			pw_sha_make_pw ( (unsigned char *) SignupPassword), xmember.xmid );

#ifdef DEBUG
#define DEBUG
	sprintf ( ErrorArray[ErrorCount++].Message, Statement );
#endif

	Affected = dbyUpdate ( "SavePassword", &MySql, Statement, 0, LogFileName );
	if ( Affected == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Change password failed." );
		return;
	}
	else if ( WasLoggedIn == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Password saved for %s.", xmember.xmname );
	}
	else
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Password changed." );
	}


	if ( CookieMember.xmid == 0 )
	{
		MenuIndex = MENU_INDEX_LOGIN;
	}
	else
	{
		MenuIndex = MENU_INDEX_HOME;
	}

	return;
}
