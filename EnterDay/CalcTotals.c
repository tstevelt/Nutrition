/*----------------------------------------------------------------------------
	Program : CalcTotals.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Calculate total macros for the day.
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

void CalcTotals ()
{
	DBY_QUERY       *qry;

	TotalSodium = TotalFiber = TotalCalorie = TotalCarb = TotalFat = TotalProtein = 0.0;
	PercentSodium = PercentFiber = PercentCalorie = PercentCarb = PercentFat = PercentProtein = 0.0;

	sprintf ( Statement, "select sum(HFserving*Fcalorie), sum(HFserving*Fcarb), sum(HFserving*Fprotein), sum(HFserving*Ffat), \
sum(HFserving*Fsodium), sum(HFserving*Ffiber) from food, history, histfood \
where Fid = HFfood  and Hid = HFhist \
and Hdate = '%s' \
and Hmember = %ld",
		HistoryDate, xmember.xmid );

#ifdef DEBUG
#define DEBUG
	printf ( Statement );
#endif

	qry = dbySelect ( "nutrition", &MySql, Statement, LogFileName );

	if ( qry == NULL )
	{
		return;
	}

	if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
	{
		return;
	}

	TotalCalorie = nsAtof(qry->EachRow[0]);
	TotalCarb    = nsAtof(qry->EachRow[1]);
	TotalProtein = nsAtof(qry->EachRow[2]);
	TotalFat     = nsAtof(qry->EachRow[3]);
	TotalSodium  = nsAtof(qry->EachRow[4]);
	TotalFiber   = nsAtof(qry->EachRow[5]);

	PercentCalorie = 100.0 * TotalCalorie / (double) xmember.xmcalorie;
	PercentCarb    = 100.0 * TotalCarb / (double) xmember.xmcarb;
	PercentProtein = 100.0 * TotalProtein / (double) xmember.xmprotein;
	PercentFat     = 100.0 * TotalFat / (double) xmember.xmfat;
	PercentSodium  = 100.0 * TotalSodium  / (double) xmember.xmsodium;
	PercentFiber   = 100.0 * TotalFiber   / (double) xmember.xmfiber;
}
