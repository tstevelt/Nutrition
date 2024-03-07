/*----------------------------------------------------------------------------
	Program : LoadFoodCB.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load <table> record into buffer, with CallBack function
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

#include	"nutriprivate.h"
#include	"nutrilib.h"

static  char    Statement[MAXSTATEMENT];

int LoadFoodCB ( char * WhereClause, char * OrderByClause, XFOOD *ptrFood, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryFood;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from food", FIELDS_FOOD );

	if ( WhereClause != NULL && nsStrlen ( WhereClause ) > 1 && nsStrcmp ( WhereClause, "all" ) != 0 )
	{
		strcat ( Statement, " where " );
		strcat ( Statement, WhereClause );
	}

	if ( OrderByClause != NULL && nsStrlen ( OrderByClause ) > 1 )
	{
		strcat ( Statement, " order by " );
		strcat ( Statement, OrderByClause );
	}

	qryFood = dbySelect ( "LoadFood", &MySql, Statement, LogFileName );
	if ( qryFood == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadFood select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryFood->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadFood select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryFood->EachRow = mysql_fetch_row ( qryFood->Result )) != NULL )
		{
/*---------------------------------------------------------------------------
< #define FIELDS_FOOD  "Fid,Fname,Fserving,Fcalorie,Fcarb,Fprotein,Ffat,Fsodium,Ffiber,inserted,Frecipe,Fmember"
---
> #define FIELDS_FOOD  "Fid,Fname,Fserving,Fcalorie,Fcarb,Fprotein,Ffat,Fsodium,Ffiber,inserted,Frecipe,Fmember,Fgroup,Fstatus"

---------------------------------------------------------------------------*/
			ptrFood->xfid      =  nsAtol( qryFood->EachRow[0] );
			snprintf ( ptrFood->xfname, sizeof(ptrFood->xfname), "%s", qryFood->EachRow[1] );
			snprintf ( ptrFood->xfserving, sizeof(ptrFood->xfserving), "%s", qryFood->EachRow[2] );
			ptrFood->xfcalorie =  nsAtof( qryFood->EachRow[3] );
			ptrFood->xfcarb    =  nsAtof( qryFood->EachRow[4] );
			ptrFood->xfprotein =  nsAtof( qryFood->EachRow[5] );
			ptrFood->xffat     =  nsAtof( qryFood->EachRow[6] );
			ptrFood->xfsodium  =  nsAtof( qryFood->EachRow[7] );
			ptrFood->xffiber   =  nsAtof( qryFood->EachRow[8] );
			ptrFood->xinserted =  nsAtol( qryFood->EachRow[9] );
			ptrFood->xfrecipe  =  nsAtoi( qryFood->EachRow[10] );
			ptrFood->xfmember  =  nsAtol( qryFood->EachRow[11] );
			snprintf ( ptrFood->xfgroup, sizeof(ptrFood->xfgroup), "%s", qryFood->EachRow[12] );
			snprintf ( ptrFood->xfstatus, sizeof(ptrFood->xfstatus), "%s", qryFood->EachRow[13] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrFood ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryFood->NumRows );
}
