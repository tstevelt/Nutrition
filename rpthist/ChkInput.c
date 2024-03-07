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

#include	"rpthist.h"

int ChkInput ()
{
	DATEVAL     TestDateVal, StartDateVal;

	if ( StrToDatevalFmt ( EndDate, DATEFMT_YYYY_MM_DD, &TestDateVal ) != 0 )
	{
		printf ( "Please enter a date using yyyy-mm-dd format<br>\n" );
		RunMode = MODE_START;
		return ( -1 );
	}

// DateDiff ( Duration == '1' )
// int DateAdd ( DATEVAL *a , int NumberOfDays , DATEVAL *b );
	if ( Duration > 0 )
	{
		DateAdd ( &TestDateVal, (0 - Duration + 1), &StartDateVal );
		sprintf ( StartDate, "%04d-%02d-%02d", StartDateVal.year4, StartDateVal.month, StartDateVal.day );
	}
	else
	{
		sprintf ( StartDate, "%s",  EndDate );
	}


	return ( 0 );
}
