/*----------------------------------------------------------------------------
	Program : getdata_smry.c
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

#include	"rptrecipe.h"

static	int		lineno = 0;

int		ServingCalorie;
int		ServingCarb;
int		ServingProtein;
int		ServingFat;
int		ServingSodium;
double	ServingFiber;

static void CalcServingData ( long RecipeID )
{
	DBY_QUERY	*qry = NULL;

	sprintf ( Statement, "select sum(Fcalorie*RFamount/Rserving), sum(Fcarb*RFamount/Rserving), sum(Fprotein*RFamount/Rserving), \
	sum(Ffat*RFamount/Rserving), sum(Fsodium*RFamount/Rserving), sum(Ffiber*RFamount/Rserving) \
  from recipe, recfood, food \
 where Rid = %ld \
   and Rid = RFrecipe \
   and Fid = RFfood \
 group by Rid;", RecipeID );


#ifdef DEBUG
#define DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( qry = dbySelect ( "nutrition", &MySql, Statement, 0 )) == NULL )
	{
		return;
	}
	if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
	{
		return;
	}

	ServingCalorie = nsAtof(qry->EachRow[0]);
	ServingCarb    = nsAtof(qry->EachRow[1]);
	ServingProtein = nsAtof(qry->EachRow[2]);
	ServingFat     = nsAtof(qry->EachRow[3]);
	ServingSodium  = nsAtof(qry->EachRow[4]);
	ServingFiber   = nsAtof(qry->EachRow[5]);
}

static int EachRecipe ( XRECIPE *ptr )
{
	double	Ratio = 0.0;

	CalcServingData ( xrecipe.xrid );	

	Ratio = 1000.0 * ServingProtein / (double) ServingCalorie;

	fprintf ( fpData, "%ld|%s|%d|%d|%d|%d|%d|%d|%.2f|%.2f\n",
		xrecipe.xrid,
		xrecipe.xrdescr,
		xrecipe.xrserving,
		ServingCalorie,
		ServingCarb,
		ServingProtein,
		ServingFat,
		ServingSodium,
		ServingFiber,
		Ratio );
	
	lineno++;

	return ( 0 );
}

int getdata_smry ()
{
	sprintf ( fnData, "%s/rptrecipe_%d.data", TEMPDIR, getpid () );
	if (( fpData = fopen ( fnData, "w" )) == (FILE *) 0 )
	{
		SaveError ( "can not create report file" );
		return ( -1 );
	}

	sprintf ( WhereClause, "Rid > 0" );
	sprintf ( OrderByClause, "Rdescr" );
	LoadRecipeCB ( WhereClause, OrderByClause, &xrecipe, EachRecipe, 0 );

	nsFclose ( fpData );

	return ( lineno );
}

