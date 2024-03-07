/*----------------------------------------------------------------------------
	Program : EachFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Update the recipe food record.
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

#include	"updfood.h"

int EachFood ( XFOOD *ptr )
{
	DBY_QUERY	*qry = NULL;
	double		ServingCalorie, ServingCarb, ServingProtein, ServingFat, ServingSodium, ServingFiber;
	char		Fragment[128];
	int			DiffCount, Affected;

	/*----------------------------------------------------------
		print food name and existing macro values
	----------------------------------------------------------*/
	printf ( "%5ld %5ld  %s\n", ptr->xfid, ptr->xfrecipe, ptr->xfname );
	printf ( "%12.12s %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n",	
					" ",
					ptr->xfcalorie,
					ptr->xfcarb,
					ptr->xfprotein,
					ptr->xffat,
					ptr->xfsodium,
					ptr->xffiber );

	/*----------------------------------------------------------
		calculate and display values from recipe ingredients
	----------------------------------------------------------*/
	sprintf ( Statement, "select sum(Fcalorie*RFamount/Rserving), sum(Fcarb*RFamount/Rserving), sum(Fprotein*RFamount/Rserving), \
	sum(Ffat*RFamount/Rserving), sum(Fsodium*RFamount/Rserving), sum(Ffiber*RFamount/Rserving) \
  from recipe, recfood, food \
 where Rid = %ld \
   and Rid = RFrecipe \
   and Fid = RFfood \
 group by Rid;", ptr->xfrecipe );


#ifdef DEBUG
#define DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( qry = dbySelect ( "nutrition", &MySql, Statement, 0 )) == NULL )
	{
		printf ( "%12.12s Recipe not found\n", " " );
		return ( 0 );
	}
	if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
	{
		printf ( "%12.12s Recipe values failed\n", " " );
		return ( 0 );
	}

	ServingCalorie = nsAtof(qry->EachRow[0]);
	ServingCarb    = nsAtof(qry->EachRow[1]);
	ServingProtein = nsAtof(qry->EachRow[2]);
	ServingFat     = nsAtof(qry->EachRow[3]);
	ServingSodium  = nsAtof(qry->EachRow[4]);
	ServingFiber   = nsAtof(qry->EachRow[5]);

	printf ( "%12.12s %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n",	
		" ", ServingCalorie, ServingCarb, ServingProtein, ServingFat, ServingSodium, ServingFiber );

	/*----------------------------------------------------------
		make an update statement based on incorrect values.
	----------------------------------------------------------*/
	
	sprintf ( Statement, "update food set " );

	DiffCount = 0;

	void AddFragment ( char *Field, double New, double Old )
	{
		/*----------------------------------------------------------
			this statement fails due to rounding.  if ( New == Old )
			replaced with dbldiff 0.01, which prevents eternal updates.
		   68     6  Meatloaf
					  193.6200    6.1200   18.3800    9.8800  182.5000    0.0000
					  193.6250    6.1250   18.3750    9.8750  182.5000    0.0000
					 Food is up-to-date
		----------------------------------------------------------*/
		if ( dbldiff ( New, Old, 0.01 ) == 0 )
		{
			return;
		}
		sprintf ( Fragment, "%s = %.2f", Field, New );
		if ( DiffCount )
		{
			nsStrcat ( Statement, ", " );
		}
		nsStrcat ( Statement, Fragment );
		DiffCount++;
	}

	AddFragment ( "Fcalorie", ServingCalorie, xfood.xfcalorie  );
	AddFragment ( "Fcarb",    ServingCarb, xfood.xfcarb  );
	AddFragment ( "Fprotein", ServingProtein, xfood.xfprotein  );
	AddFragment ( "Ffat",     ServingFat, xfood.xffat  );
	AddFragment ( "Fsodium",  ServingSodium, xfood.xfsodium  );
	AddFragment ( "Ffiber",   ServingFiber, xfood.xffiber  );

	if ( DiffCount > 0 )
	{
		sprintf ( Fragment, " where Fid = %ld", xfood.xfid );
		nsStrcat ( Statement, Fragment );
		printf ( "%12.12s %s\n", " ", Statement );
		Affected = dbyUpdate ( "food", &MySql, Statement, 0, LogFileName );
		if ( Affected < 1 )
		{
			printf ( "%12.12s UPDATE FAILED\n", " " );
		}
		else if ( Affected > 1 )
		{
			printf ( "%12.12s UPDATED TOO MANY RECORDS, PROGRAM ABORTED\n", " " );
			exit ( 1 );
		}
	}
	else
	{
		printf ( "%12.12s Food is up-to-date\n", " " );
	}

	printf ( "\n" );

	return ( 0 );
}
