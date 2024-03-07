/*----------------------------------------------------------------------------
	Program : PaintMeal.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint one of the meals for a day
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

static		int		NumRows;

static	char	*Class;

static int EachMeal ( DBY_QUERY *qry )
{
	NumRows++;
	if ( NumRows == 1 )
	{
		printf ( "<tr><td colspan='%d'><table border='0' cellpadding='2' width='100%%'>\n", COLUMNS );
	}

	printf ( "<tr>\n" );
	// printf ( "<tr class='%s'>\n", Class );

	printf ( "<td width='10%%' align='center'><input type='checkbox' name='cb_%d_%d'></td>\n", nsAtoi(qry->EachRow[0]),  nsAtoi(qry->EachRow[1]) );
	printf ( "<td width='10%%'>%s</td>\n", qry->EachRow[2] );
	printf ( "<td width='10%%'>%s</td>\n", qry->EachRow[3] );
	printf ( "<td width='70%%'>%s</td>\n", qry->EachRow[4] );
	printf ( "</tr>\n" );

	return ( 0 );
}

void PaintMeal ( char *MealDescr )
{
	NumRows = 0;

	Class = MealDescr;

	sprintf ( Statement, 
		"select Hid, HFfood, HFserving, Fserving, Fname \
from history, histfood, food, member \
where Hid = HFhist \
and HFfood = Fid \
and Mid = Hmember \
and Mid = %ld \
and Hdate = '%s' \
and Hdescr = '%s'", 
	xmember.xmid,
	HistoryDate,
	MealDescr );

// printf ( "%s<br>\n", Statement );
	
	dbySelectCB ( "nutrition", &MySql, Statement, EachMeal, LogFileName );

	if ( NumRows > 0 )
	{
		printf ( "</table></td></tr>\n" );
	}

}
