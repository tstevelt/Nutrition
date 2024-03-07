/*----------------------------------------------------------------------------
	Program : GetInput.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Get user input from screen or QUERY_STRING
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

void GetInput ()
{
	int		xa;

	/*----------------------------------------------------------
		get user input
	----------------------------------------------------------*/
	webGetInput ();

	RunMode = MODE_START;

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );
		TrimRightAndLeft ( webValues[xa] );

// printf ( "%s %s<br>\n", webNames[xa],  webValues[xa] );

		/*------------------------------------------------------------
	generated getinput
------------------------------------------------------------*/
if ( nsStrcmp ( webNames[xa], "field_fid" ) == 0 )
{
xfood.xfid = nsAtoi ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fname" ) == 0 )
{
sprintf ( xfood.xfname, "%s", webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fserving" ) == 0 )
{
sprintf ( xfood.xfserving, "%s", webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fcalorie" ) == 0 )
{
xfood.xfcalorie = nsAtof ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fcarb" ) == 0 )
{
// sprintf ( xfood.xfcarb, "%s", webValues[xa] );
xfood.xfcarb = nsAtof ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fprotein" ) == 0 )
{
// sprintf ( xfood.xfprotein, "%s", webValues[xa] );
xfood.xfprotein = nsAtof ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_ffat" ) == 0 )
{
// sprintf ( xfood.xffat, "%s", webValues[xa] );
xfood.xffat = nsAtof ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_fsodium" ) == 0 )
{
// sprintf ( xfood.xfsodium, "%s", webValues[xa] );
xfood.xfsodium = nsAtof ( webValues[xa] );
}
else if ( nsStrcmp ( webNames[xa], "field_ffiber" ) == 0 )
{
// sprintf ( xfood.xffiber, "%s", webValues[xa] );
xfood.xffiber = nsAtof ( webValues[xa] );
}

		else if ( nsStrcmp ( webNames[xa], "FoodGroup" ) == 0 )
		{
			sprintf ( xfood.xfgroup, "%s", webValues[xa] );
		}

		else if ( nsStrcmp ( webNames[xa], "submitLoad" ) == 0 )
		{
			RunMode = MODE_LOAD;
		}
		else if ( nsStrcmp ( webNames[xa], "submitLookup" ) == 0 )
		{
			RunMode = MODE_LOOKUP;
		}
		else if ( nsStrcmp ( webNames[xa], "submitInsert" ) == 0 )
		{
			RunMode = MODE_INSERT;
		}
		else if ( nsStrcmp ( webNames[xa], "submitUpdate" ) == 0 )
		{
			RunMode = MODE_UPDATE;
		}

#ifdef SAFETY_ON_DELETE
		else if ( nsStrcmp ( webNames[xa], "HiddenSafety" ) == 0 )
		{
			HiddenSafety = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "AnswerSafety" ) == 0 )
		{
			AnswerSafety = nsAtoi ( webValues[xa] );
		}
#endif
		else if ( nsStrcmp ( webNames[xa], "submitDelete" ) == 0 )
		{
			RunMode = MODE_DELETE;
		}
		else if ( nsStrcmp ( webNames[xa], "submitClear" ) == 0 )
		{
			RunMode = MODE_CLEAR;
		}
		else
		{
			sprintf ( StatementOne, "UNKNOWN [%s] [%s]", webNames[xa], webValues[xa] );
			SaveError ( StatementOne );
		}

	}
	
}
