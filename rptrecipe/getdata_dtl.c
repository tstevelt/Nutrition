/*----------------------------------------------------------------------------
	Program : getdata_dtl.c
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

#define DEBUG
#undef DEBUG

static int EachRecipe ( XRECIPE *ptr )
{
	DBY_QUERY	*qry = NULL;

sprintf ( Statement, 
"select RFamount, Fserving, Fname, \
RFamount*Fcalorie, RFamount*Fcarb, RFamount*Fprotein, RFamount*Ffat, RFamount*Fsodium, RFamount*Ffiber \
from recipe, recfood, food where Rid = RFrecipe and Fid = RFfood and Rid = %ld", ptr->xrid );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif
	if (( qry = dbySelect ( "nutrition", &MySql, Statement, 0 )) == NULL )
	{
		return ( 0 );
	}
	while (( qry->EachRow = mysql_fetch_row ( qry->Result )) != NULL )
	{
		fprintf ( fpData, "%ld|%s|serves %d| |%.2f|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n",
			ptr->xrid,
			ptr->xrdescr,
			ptr->xrserving,
			nsAtof(qry->EachRow[0]),
			qry->EachRow[1],
			qry->EachRow[2],
			nsAtof(qry->EachRow[3]),
			nsAtof(qry->EachRow[4]),
			nsAtof(qry->EachRow[5]),
			nsAtof(qry->EachRow[6]),
			nsAtof(qry->EachRow[7]),
			nsAtof(qry->EachRow[8])
			);
	}
	
	lineno++;


	return ( 0 );
}

int getdata_dtl ()
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

