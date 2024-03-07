/*----------------------------------------------------------------------------
	Program : SaveProfile.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Save member information
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

#define	DEBUG
#undef	DEBUG

static  char    Statement[MAXSTATEMENT];

void SaveProfile ()
{
	/*----------------------------------------------------------
		save name and numbers
		printf ( "<td width='60%%'><input type='search' name='SignupName' size='35' maxlength='30'\n" );
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement), "update member \
set Mname = '%s', Mgender = '%c', Mbirthdate = '%s', Mweight = %d, Mheight = %d, Mcalorie = %d, Mcarb = %d, Mprotein = %d, Mfat = %d, Msodium = %d, Mfiber = %d, Mactive = '%c', Mdiet = '%c' \
where member.Mid = %ld", 
			SignupName, SignupGender, SignupBirthdate, SignupWeight, SignupHeight, SignupCalorie, SignupCarb, SignupProtein, SignupFat, SignupSodium, SignupFiber, SignupActivityLevel, SignupDiet,
			CookieMember.xmid );

#ifdef DEBUG
	sprintf ( ErrorArray[ErrorCount++].Message, Statement );
#endif

	dbyUpdate ( "SaveProfile", &MySql, Statement, 0, LogFileName );

	sprintf ( WhereClause, "Mid = %ld", CookieMember.xmid );
	LoadMember ( WhereClause, &CookieMember, 0 );
	WriteSession ();

}
