/*----------------------------------------------------------------------------
	Program : LoadMemberCB.c
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

int LoadMemberCB ( char * WhereClause, char * OrderByClause, XMEMBER *ptrMember, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryMember;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from member", FIELDS_MEMBER );

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

	qryMember = dbySelect ( "LoadMember", &MySql, Statement, LogFileName );
	if ( qryMember == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadMember select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryMember->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadMember select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryMember->EachRow = mysql_fetch_row ( qryMember->Result )) != NULL )
		{
// FIELDS_MEMBER  "Mid,Mname,Mpassword,Mgender,Mbirthdate,Mweight,Mipaddr,Mcalorie,Mcarb,Mprotein,Mfat,Mstatus,Mrole,Memail"
//                 0   1     2         3       4          5       6       7        8     9        10   11      12    13     14      15      16
// FIELDS_MEMBER  "Mid,Mname,Mpassword,Mgender,Mbirthdate,Mweight,Mipaddr,Mcalorie,Mcarb,Mprotein,Mfat,Mstatus,Mrole,Memail,Mheight,Mactive,Mdiet"

			ptrMember->xmid        =  nsAtol( qryMember->EachRow[0] );
			snprintf ( ptrMember->xmname, sizeof(ptrMember->xmname), "%s", qryMember->EachRow[1] );
			snprintf ( ptrMember->xmpassword, sizeof(ptrMember->xmpassword), "%s", qryMember->EachRow[2] );
			ptrMember->xmgender[0] =  qryMember->EachRow[3][0];
			snprintf ( ptrMember->xmbirthdate, sizeof(ptrMember->xmbirthdate), "%s", qryMember->EachRow[4] );
			ptrMember->xmweight    =  nsAtoi( qryMember->EachRow[5] );
			snprintf ( ptrMember->xmipaddr, sizeof(ptrMember->xmipaddr), "%s", qryMember->EachRow[6] );
			ptrMember->xmcalorie =  nsAtoi( qryMember->EachRow[7] );
			ptrMember->xmcarb    =  nsAtoi( qryMember->EachRow[8] );
			ptrMember->xmprotein =  nsAtoi( qryMember->EachRow[9] );
			ptrMember->xmfat     =  nsAtoi( qryMember->EachRow[10] );
			ptrMember->xmstatus[0] =  qryMember->EachRow[11][0];
			ptrMember->xmrole[0] =  qryMember->EachRow[12][0];
			snprintf ( ptrMember->xmemail, sizeof(ptrMember->xmemail), "%s", qryMember->EachRow[13] );
			ptrMember->xmheight  =  nsAtoi( qryMember->EachRow[14] );
			ptrMember->xmactive[0] =  qryMember->EachRow[15][0];
			ptrMember->xmdiet[0] =  qryMember->EachRow[16][0];
			ptrMember->xinserted =  nsAtol( qryMember->EachRow[17] );
			ptrMember->xmsodium  =  nsAtoi( qryMember->EachRow[18] );
			ptrMember->xmfiber   =  nsAtoi( qryMember->EachRow[19] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrMember ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryMember->NumRows );
}
