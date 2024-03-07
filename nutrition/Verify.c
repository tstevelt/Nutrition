/*----------------------------------------------------------------------------
	Program : Verify.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Respond to verification email, bump status if okay.
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

#include	"nutrition.h"

static  char    Statement[MAXSTATEMENT];

int Verify ()
{
	DBY_QUERY     *qryMember;
	int			rv = 0;
	long		Affected;

	/*----------------------------------------------------------
		select name and status by  id and ipaddr
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select Mname, Mstatus from member where member.Mid = %ld and Mipaddr = '%s'",
			VerifyID, VerifyIPaddr );

	qryMember = dbySelect ( "Verify", &MySql, Statement, LogFileName );
	if ( qryMember == (DBY_QUERY *) 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "1. Verify select returned NULL." );
		rv = -1;
	}
	else if ( qryMember->NumRows == 0 )
	{
		sprintf ( ErrorArray[ErrorCount++].Message, "Verify select returned zero rows." );
		sprintf ( ErrorArray[ErrorCount++].Message, "Did you verify from the same computer that you signed up on?" );
		rv = -2;
	}
	else 
	{
		/*---------------------------------------------------------
			check status
		----------------------------------------------------------*/
		qryMember->EachRow = mysql_fetch_row ( qryMember->Result );
		switch ( qryMember->EachRow[1][0] )
		{
			case 'P':
				/*----------------------------------------------------------
					update to 'V'
				----------------------------------------------------------*/
				snprintf ( Statement, sizeof(Statement),
					"update member set Mstatus = 'V' where member.Mid = %ld", VerifyID );

				Affected = dbyUpdate ( "Verify", &MySql, Statement, 0, LogFileName );
				if ( Affected == 0 )
				{
					sprintf ( ErrorArray[ErrorCount++].Message, "Verify failed." );
					rv = -3;
				}
				else
				{
					ErrorClass = "good";
					sprintf ( ErrorArray[ErrorCount++].Message, "Thank you for verifying your email, %s", qryMember->EachRow[0] );
					sprintf ( ErrorArray[ErrorCount++].Message, "Please 'Login' and Use 'Edit Profile' to enter your gender," );
					sprintf ( ErrorArray[ErrorCount++].Message, "weight and macro nutrients." );
				}
				break;

			case 'V':
				sprintf ( ErrorArray[ErrorCount++].Message, "%s is already verified!", qryMember->EachRow[0] );
				break;

			default:	
				sprintf ( ErrorArray[ErrorCount++].Message, "Unknown member.Mstatus [%c]", qryMember->EachRow[1][0] );
				rv = -4;
				break;
		}
	}

	return ( rv );
}
