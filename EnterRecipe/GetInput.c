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

#include	"EnterRecipe.h"

void GetInput ()
{
	int		xa;
	char	*tokens[4];

	RunMode = MODE_START;
	if ( webGetInput () != 0 )

	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

		// printf ( "%s=%s<br>\n", webNames[xa], webValues[xa] );

		if ( nsStrcmp ( webNames[xa], "MemberID" ) == 0 )
		{
			MemberID = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp (webNames[xa], "RecipeID" ) == 0 )
		{
			RecipeID = nsAtol ( webValues[xa] );
		}
		else if ( nsStrcmp (webNames[xa], "submitLookup" ) == 0 )
		{
			RunMode = MODE_LOOKUP_RECIPE;
		}
		else if ( nsStrcmp (webNames[xa], "submitInsert" ) == 0 )
		{
			RunMode = MODE_INSERT_RECIPE;
		}
		else if ( nsStrcmp (webNames[xa], "submitUpdate" ) == 0 )
		{
			RunMode = MODE_UPDATE_RECIPE;
		}
		else if ( nsStrcmp ( webNames[xa], "submitDeleteRecipe" ) == 0 )
		{
			RunMode = MODE_DELETE_RECIPE;
		}
		else if ( nsStrcmp ( webNames[xa], "submitDeleteRecfood" ) == 0 )
		{
			RunMode = MODE_DELETE_RECFOOD;
		}
		else if ( nsStrcmp (webNames[xa], "submitQuit" ) == 0 )
		{
			RunMode = MODE_QUIT;
		}
		else if ( nsStrcmp ( webNames[xa], "Rdescr" ) == 0 )
		{
			sprintf ( xrecipe.xrdescr, "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "Rserving" ) == 0 )
		{
			xrecipe.xrserving = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "Rfood" ) == 0 )
		{
			xrecipe.xrfood = nsAtoi ( webValues[xa] );
		}

		else if ( nsStrncmp ( webNames[xa], "cb_", 3 ) == 0 )
		{
			if ( DeleteCount >= MAXDELETE )
			{
				printf ( "Can only delete %d at a time<br>\n", MAXDELETE );
			}
			else
			{
				GetTokensD ( webNames[xa], "_", tokens, 4 );
				DeleteArray[DeleteCount].HistID = nsAtol ( tokens[1] );
				DeleteArray[DeleteCount].FoodID = nsAtol ( tokens[2] );
				DeleteCount++;
			}
		}
		else if ( nsStrcmp ( webNames[xa], "HiddenSafety" ) == 0 )
		{
			HiddenSafety = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "AnswerSafety" ) == 0 )
		{
			AnswerSafety = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "AddRecfoodID" ) == 0 )
		{
			FoodID = nsAtol ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "AddRecfoodServings" ) == 0 )
		{
			FoodServings = nsAtof ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "submitAddRecfood" ) == 0 )
		{
			RunMode = MODE_ADD_RECFOOD;
		}
		else if ( nsStrcmp ( webNames[xa], "submitCreateFood" ) == 0 )
		{
			RunMode = MODE_CREATE_FOOD;
		}

		else
		{
			printf ( "Unknown input %s=%s<br>\n", webNames[xa], webValues[xa] );
		}
	}
}
