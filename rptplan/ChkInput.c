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

#include	"rptplan.h"

int ChkInput ()
{
	DATEVAL		dvTest;

	if ( RunMode != MODE_RUN )
	{
		return ( 0 );
	}

	if ( MinFoods < MINFOODS ||  MaxFoods > MAXFOODS )
	{
		webContentHtml ();
		printf ( "Daily food plan should include %d to %d foods. <br>\n", MINFOODS, MAXFOODS );
		RunMode = MODE_START;
		return ( -1 );
	}

	if ( FTD )
	{
		if ( StrToDatevalFmt ( FTD_Date, DATEFMT_YYYY_MM_DD, &dvTest ) != 0 )
		{
			webContentHtml ();
			printf ( "Finish the day format yyyy-mm-dd<br>\n" );
			RunMode = MODE_START;
			return ( -1 );
		}
	}

	return ( 0 );
}
