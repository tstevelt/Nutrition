/*----------------------------------------------------------------------------
	Program : getdata_food.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Get selected date, output to pipe-delimited file
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

static	int		lineno = 0;

static int EachHistfood ( XHISTFOOD *ptr )
{
	int		xa, ndx;
	char	WhereClauseFood[128];

	for ( xa = 0; xa < Count; xa++ )
	{
		if (( nsStrcmp ( Array[xa].Date, xhistory.xhdate  ) == 0 ) &&
			( Array[xa].FoodID == xhistfood.xhffood ))
		{
			ndx = xa;
			break;
		}
	}

	if ( xfood.xfid != xhistfood.xhffood )
	{
		sprintf ( WhereClauseFood, "Fid = %ld", xhistfood.xhffood );
		LoadFood ( WhereClauseFood, &xfood, 0 );
	}

	if ( xa >= Count )
	{
		sprintf ( Array[Count].Date, "%s", xhistory.xhdate  );
		          Array[Count].FoodID = xhistfood.xhffood;
		sprintf ( Array[Count].Serving, "%s", xfood.xfserving  );
		sprintf ( Array[Count].Name, "%s", xfood.xfname  );
		ndx = Count;
		Count++;
	}

	Array[ndx].FoodAmount += xhistfood.xhfserving;
	Array[ndx].Calorie += xfood.xfcalorie * xhistfood.xhfserving;
	Array[ndx].Carb    += xfood.xfcarb    * xhistfood.xhfserving;
	Array[ndx].Protein += xfood.xfprotein * xhistfood.xhfserving;
	Array[ndx].Fat     += xfood.xffat     * xhistfood.xhfserving;
	Array[ndx].Sodium  += xfood.xfsodium  * xhistfood.xhfserving;
	Array[ndx].Fiber   += xfood.xffiber   * xhistfood.xhfserving;

	return ( 0 );
}

static int EachHistory ( XHISTORY *ptr )
{
	char		WhereClauseDetail[128];

	sprintf ( WhereClauseDetail, "HFhist = '%ld'", xhistory.xhid );
	// printf ( "%s<br>\n", WhereClauseDetail );
	LoadHistfoodCB ( WhereClauseDetail, NULL, &xhistfood, EachHistfood, 0 );

	lineno++;

	return ( 0 );
}

static int cmprec ( RECORD *a, RECORD *b )
{
	int		rv;

	rv = nsStrcmp ( a->Date, b->Date );
	if ( rv < 0 )
	{
		return ( -1 );
	}
	if ( rv > 0 )
	{
		return ( 1 );
	}

	rv = nsStrcmp ( a->Name, b->Name );
	if ( rv < 0 )
	{
		return ( -1 );
	}
	if ( rv > 0 )
	{
		return ( 1 );
	}


	if ( a->Calorie < b->Calorie )
	{
		return ( 1 );
	}
	if ( a->Calorie > b->Calorie )
	{
		return ( -1 );
	}
	return ( 0 );
}

int getdata_food ()
{
	double	Ratio = 0.0;

	Count = 0;
	memset ( Array, '\0', sizeof(Array) );

	sprintf ( WhereClause, "Hmember = %ld and Hdate >= '%s' and Hdate <= '%s'", CookieMember.xmid, StartDate, EndDate );
	// printf ( "%s<br>\n", WhereClause );
	sprintf ( OrderByClause, "Hdate" );
	if ( LoadHistoryCB ( WhereClause, OrderByClause, &xhistory, EachHistory, 0 ) == 0 )
	{
		return ( 0 );
	}

	sprintf ( fnData, "%s/rpthist_%d.data", TEMPDIR, getpid () );
	if (( fpData = fopen ( fnData, "w" )) == (FILE *) 0 )
	{
		SaveError ( "can not create report file" );
		return ( -1 );
	}

	qsort ( Array, Count, sizeof(RECORD), (int(*)()) cmprec );

	for ( int xa = 0; xa < Count; xa++ )
	{
		Ratio = 1000.0 * Array[xa].Protein / (double) Array[xa].Calorie;

		fprintf ( fpData, "%s|%.2f|%s|%s|%.0f|%.0f|%.0f|%.0f|%.0f|%.2f|%.2f\n",
			Array[xa].Date,
			Array[xa].FoodAmount,
			Array[xa].Serving,
			Array[xa].Name,
			Array[xa].Calorie,
			Array[xa].Carb,
			Array[xa].Protein,
			Array[xa].Fat,
			Array[xa].Sodium,
			Array[xa].Fiber,
			Ratio );

	}
	
	nsFclose ( fpData );

	return ( lineno );
}
