/*----------------------------------------------------------------------------
	Program : Load.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load existing food
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

#include	"EnterFood.h"

static	int		DebugLoad = 0;

int Load ()
{
	int		rv = 0;

	RunMode = MODE_FOUND;

	sprintf ( WhereClause, "food.Fid = %ld", xfood.xfid );
	if (( rv = LoadFood ( WhereClause, &xfood, 0 )) != 1 )
	{
		if ( DebugLoad )
		{
			sprintf ( msgbuf, "Unknown ID %ld, rv = %d", xfood.xfid, rv );
			SaveError ( msgbuf );
		}
		else
		{
			SaveError ( "Unknown ID" );
		}
		RunMode = MODE_START;
	}

	return ( rv );
}
