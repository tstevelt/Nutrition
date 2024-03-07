/*----------------------------------------------------------------------------
	Program : ChkInput.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Validate user input
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

#include	"EnterFood.h"

int ChkInput ()
{
	int		rv = 0;
	int		ndx, xo;
	XFOOD	TestFood;
	
	switch ( RunMode )
	{
		case MODE_LOOKUP:
			if ( xfood.xfid > 0 )
			{
				RunMode = MODE_LOAD;
				break;
			}
			for ( ndx = 0, xo = 0; ndx < FieldCount; ndx++ )
			{
				if ( lastchr ( FieldArray[ndx].buffer, FieldArray[ndx].length ) > 0 )
				{
					xo++;
				}
			}
			if ( xo == 0 )
			{
				SaveError ( "Please enter something to search for." );
				RunMode = MODE_START;
				rv++;
			}
			break;

		case MODE_LOAD:
			if ( xfood.xfid == 0 )
			{
				SaveError ( "Enter an ID to load" );
				RunMode = MODE_START;
				rv++;
			}
			break;

		case MODE_INSERT:
			if ( xfood.xfid > 0 )
			{
				sprintf ( WhereClause, "food.Fid = %ld", xfood.xfid );
				if ( LoadFood ( WhereClause, &TestFood, 0 ) == 1 )
				{
					SaveError ( "Food ID is already in use" );
					rv++;
					RunMode = MODE_START;
					break;
				}
			}
			/* fall-through */
		case MODE_UPDATE:
			for ( ndx = 0; ndx < FieldCount; ndx++ )
			{
				// if ( FieldArray[ndx].required && lastchr ( FieldArray[ndx].buffer, FieldArray[ndx].length ) == 0 )
				/*( fixit
				if ( xfood.xfid == 0 )
				{
					sprintf ( msgbuf, "%s is required", FieldArray[ndx].label );
					SaveError ( msgbuf );
					rv++;
				}
				*/
			}
			if ( xfood.xfgroup[0] == '?' )
			{
				SaveError ( "Please assign a food group" );
				rv++;
			}
			if ( rv > 0 && RunMode == MODE_INSERT )
			{
				RunMode = MODE_START;
			}
			else if ( rv > 0 && RunMode == MODE_UPDATE )
			{
				RunMode = MODE_FOUND;
			}
			break;

		case MODE_DELETE:
#ifdef SAFETY_ON_DELETE
			if ( HiddenSafety != AnswerSafety )
			{
				SaveError ( "Safety mis-match" );
				RunMode = MODE_FOUND;
				rv++;
				break;
			}
#endif
			for ( ndx = 0; ndx < FkCount; ndx++ )
			{
				sprintf ( WhereClause, "%s = %ld", FkArray[ndx].child_field, xfood.xfid );
				if ( dbySelectCount ( &MySql, FkArray[ndx].child_table, WhereClause, LogFileName ) > 0 )
				{
					sprintf ( msgbuf, "Food has %s records", FkArray[ndx].english );
					SaveError ( msgbuf );
					RunMode = MODE_FOUND;
					rv++;
				}
			}
			break;
	}

	return ( rv );
}
