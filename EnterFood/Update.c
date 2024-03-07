/*----------------------------------------------------------------------------
	Program : Update.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Update the food record.
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

void Update ()
{
	time_t	TimeStamp;
	int		Affected;

	TimeStamp = time ( NULL );

	if ( xfood.xfid > 0 )
	{
		sprintf ( StatementOne,
"update food set Fname = '%s', Fserving = '%s', Fcalorie = %.2f, Fcarb = %.2f, Fprotein = %.2f, Ffat = %.2f, \
 Fsodium = %.2f, Ffiber = %.2f, Fgroup = '%s'  where Fid = %ld",
xfood.xfname
, xfood.xfserving
, xfood.xfcalorie
, xfood.xfcarb
, xfood.xfprotein
, xfood.xffat
, xfood.xfsodium
, xfood.xffiber
, xfood.xfgroup
, xfood.xfid );
	}

	Affected = dbyUpdate ( "food", &MySql, StatementOne, 0, LogFileName );
	
	if ( Affected < 0 )
	{
		SaveError ( "dbyUpdate failed" );
		RunMode = MODE_FOUND;
		return;
	}
	else if ( Affected == 0 )
	{
		SaveError ( "No changes" );
		RunMode = MODE_FOUND;
		return;
	}
	else
	{
		sprintf ( StatementOne, "update food set updated = %ld where Fid = %ld", TimeStamp, xfood.xfid );
		dbyUpdate ( "food", &MySql, StatementOne, 0, LogFileName );
	}

	sprintf ( WhereClause, "Fid = %ld", xfood.xfid );
	LoadFood ( WhereClause, &xfood, 0 );
}
