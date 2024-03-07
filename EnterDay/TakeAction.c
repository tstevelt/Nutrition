/*----------------------------------------------------------------------------
	Program : TakeAction.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Run the selected sub-routine
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

void TakeAction ()
{
	DATEVAL 	TestDateVal, NewDateVal;

	switch ( RunMode )
	{
		case MODE_GET_DATE:
			break;
		case MODE_DO_DATE:
			break;
		case MODE_ADD_FOOD:
			AddFood ();
			break;
		case MODE_DELETE:
			DeleteFood ();
			break;
		case MODE_COPY_MEAL:
			CopyMeal ( 1 );
			break;
		case MODE_COPY_DAY:
			CopyDay ();
			break;
		case MODE_PREV_DAY:
			StrToDatevalFmt ( HistoryDate, DATEFMT_YYYY_MM_DD, &TestDateVal );
			DateAdd ( &TestDateVal, -1, &NewDateVal );
			sprintf ( HistoryDate, "%04d-%02d-%02d", NewDateVal.year4, NewDateVal.month, NewDateVal.day );
			break;
		case MODE_NEXT_DAY:
			StrToDatevalFmt ( HistoryDate, DATEFMT_YYYY_MM_DD, &TestDateVal );
			DateAdd ( &TestDateVal, 1, &NewDateVal );
			sprintf ( HistoryDate, "%04d-%02d-%02d", NewDateVal.year4, NewDateVal.month, NewDateVal.day );
			break;
		default:
			printf ( "TakeAction: unknown run mode %d<br>\n", RunMode );
			break;
	}
}
