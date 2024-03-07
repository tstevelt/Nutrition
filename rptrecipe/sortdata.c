/*----------------------------------------------------------------------------
	Program : sortdata.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Sort pipe-delimited file prior to final report creation
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

#include	"rptrecipe.h"

void sortdata ()
{
	char	cmdline[1024];

	return;

	switch ( SortBy )
	{
		case 'N':
			/* nothing to do, data was selected with OrderByClause */
			return;

		case 'C':
			snprintf ( cmdline, sizeof(cmdline), "sort -t '|'  -k 4,4n -o %s %s", fnData, fnData );
			break;

		case 'P':
			snprintf ( cmdline, sizeof(cmdline), "sort -t '|'  -k 6,6nr -o %s %s", fnData, fnData );
			break;

		case 'D':
			snprintf ( cmdline, sizeof(cmdline), "sort -t '|'  -k 8,8nr -k 4,4n -o %s %s", fnData, fnData );
			break;
	}
	system ( cmdline );
}
