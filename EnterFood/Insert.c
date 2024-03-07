/*----------------------------------------------------------------------------
	Program : Insert.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Insert new food into database.  Can specify ID or use auto-increment
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

void Insert ()
{
	time_t	TimeStamp;

	TimeStamp = time ( NULL );

	if ( xfood.xfid > 0 )
	{
		sprintf ( StatementOne,
"insert into food (Fid, Fname, Fserving, Fcalorie, Fcarb, Fprotein, Ffat, Fsodium, Ffiber, Fgroup, Fstatus, Fmember, inserted ) \
 values (%ld, '%s', '%s', %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, '%s', 'A', %ld, %ld)",
xfood.xfid
, xfood.xfname
, xfood.xfserving
, xfood.xfcalorie
, xfood.xfcarb
, xfood.xfprotein
, xfood.xffat
, xfood.xfsodium
, xfood.xffiber
, xfood.xfgroup
, CookieMember.xmid
, TimeStamp
);
	}
	else
	{
		sprintf ( StatementOne, 
"insert into food (Fname, Fserving, Fcalorie, Fcarb, Fprotein, Ffat, Fsodium, Ffiber, Fgroup, Fstatus, Fmember, inserted ) \
 values ('%s', '%s', %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, '%s', 'A', %ld, %ld )",
xfood.xfname
, xfood.xfserving
, xfood.xfcalorie
, xfood.xfcarb
, xfood.xfprotein
, xfood.xffat
, xfood.xfsodium
, xfood.xffiber
, xfood.xfgroup
, CookieMember.xmid
, TimeStamp
);
	}

// printf ( "%s<br>\n", StatementOne );
	if ( dbyInsert ( "food", &MySql, StatementOne, 0, LogFileName ) != 1 )
	{
		SaveError ( "dbyInsert failed" );
		RunMode = MODE_START;
		return;
	}

	// sprintf ( WhereClause, "inserted = %ld", TimeStamp );
	sprintf ( WhereClause, "Fid = (select max(Fid) from food)" );
	LoadFood ( WhereClause, &xfood, 0 );
}
