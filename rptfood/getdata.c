/*----------------------------------------------------------------------------
	Program : getdata.c
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

#include	"rptfood.h"

static	int		lineno = 0;

char *ltos ( long number )
{
	static	char	buffer[20];

	sprintf ( buffer, "%ld", number );
	return ( buffer );
}

int EachFood ( XFOOD *ptr )
{
	double	Ratio = 1000.0 * xfood.xfprotein / (double) xfood.xfcalorie;

	fprintf ( fpData, "%ld|%s|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n",
		xfood.xfid,
		xfood.xfrecipe > 0 ? ltos(xfood.xfrecipe) : " ",
		xfood.xfname,
		xfood.xfserving,
		xfood.xfcalorie,
		xfood.xfcarb,
		xfood.xfprotein,
		xfood.xffat,
		xfood.xfsodium,
		xfood.xffiber,
		Ratio );
	
	lineno++;

	return ( 0 );
}

int getdata ()
{
	sprintf ( fnData, "%s/rptfood_%d.data", TEMPDIR, getpid () );
	if (( fpData = fopen ( fnData, "w" )) == (FILE *) 0 )
	{
		SaveError ( "can not create report file" );
		return ( -1 );
	}

	sprintf ( WhereClause, "Fid > 0" );
	if ( Universe == 'C' )
	{
		nsStrcat ( WhereClause, " and Fstatus = 'A'" );
	}
	sprintf ( OrderByClause, "Fname" );
	LoadFoodCB ( WhereClause, OrderByClause, &xfood, EachFood, 0 );

	nsFclose ( fpData );

	return ( lineno );
}

