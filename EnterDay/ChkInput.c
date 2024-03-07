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

#include	"EnterDay.h"

void ChkInput ()
{
	DATEVAL 	TestDateVal;

	switch ( RunMode )
	{
		case MODE_GET_DATE:
			break;
		case MODE_DO_DATE:
			if ( StrToDatevalFmt ( HistoryDate, DATEFMT_YYYY_MM_DD, &TestDateVal ) != 0 )
			{
				printf ( "Please enter a date using yyyy-mm-dd format<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			break;

		case MODE_ADD_FOOD:
			if ( MealDescr == '?' )
			{
				printf ( "Missing meal description<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			if ( FoodID == 0 )
			{
				printf ( "Missing food ID. Use lookup if needed.<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			else
			{
				sprintf ( WhereClause, "Fid = %ld", FoodID );
				if ( LoadFood ( WhereClause, &xfood, 0 ) != 1 )
				{
					printf ( "Invalid food ID. Use lookup if needed.<br>\n" );
					RunMode = MODE_GET_DATE;
				}
			}
			if ( FoodServings <= 0 )
			{
				printf ( "Missing number of servings<br>\n" );
				RunMode = MODE_GET_DATE;
			}

			break;

		case MODE_COPY_MEAL:
			if ( StrToDatevalFmt ( CopyMealDate, DATEFMT_YYYY_MM_DD, &TestDateVal ) != 0 )
			{
				printf ( "Please enter a date using yyyy-mm-dd format<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			if ( CopyMealDescr == '?' )
			{
				printf ( "Missing meal description<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			break;

		case MODE_COPY_DAY:
			if ( StrToDatevalFmt ( CopyDayDate, DATEFMT_YYYY_MM_DD, &TestDateVal ) != 0 )
			{
				printf ( "Please enter a date using yyyy-mm-dd format<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			break;

		case MODE_DELETE:
			if ( DeleteCount == 0 )
			{
				printf ( "Nothing selected for deletion!<br>\n" );
				RunMode = MODE_GET_DATE;
			}
			break;

	}
}
