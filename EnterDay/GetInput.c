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

#include	"EnterDay.h"

void GetInput ()
{
	int		xa;
	char	*tokens[4];

	RunMode = MODE_GET_DATE;
	if ( webGetInput () != 0 )

	{
		printf ( "cgiIntergrate: Input error!<br>\n" );
	}

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );

		// printf ( "%s=%s<br>\n", webNames[xa], webValues[xa] );

		if ( nsStrcmp (webNames[xa], "HistoryDate" ) == 0 )
		{
			sprintf ( HistoryDate, "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "MemberID" ) == 0 )
		{
			MemberID = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp (webNames[xa], "submitDate" ) == 0 )
		{
			RunMode = MODE_DO_DATE;
		}
		else if ( nsStrcmp ( webNames[xa], "AddMealDescr" ) == 0 )
		{
			MealDescr = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "AddFoodID" ) == 0 )
		{
			FoodID = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "AddFoodServings" ) == 0 )
		{
			FoodServings = nsAtof ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "submitAddFood" ) == 0 )
		{
			RunMode = MODE_ADD_FOOD;
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
		else if ( nsStrcmp ( webNames[xa], "submitDelete" ) == 0 )
		{
			RunMode = MODE_DELETE;
		}

		else if ( nsStrcmp ( webNames[xa], "CopyDayDate" ) == 0 )
		{
			sprintf ( CopyDayDate, "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "CopyMealDate" ) == 0 )
		{
			sprintf ( CopyMealDate, "%s", webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "CopyMealDescr" ) == 0 )
		{
			CopyMealDescr = webValues[xa][0];
		}
		else if ( nsStrcmp ( webNames[xa], "submitCopyMeal" ) == 0 )
		{
			RunMode = MODE_COPY_MEAL;
		}
		else if ( nsStrcmp ( webNames[xa], "submitCopyDay" ) == 0 )
		{
			RunMode = MODE_COPY_DAY;
		}

		else if ( nsStrcmp ( webNames[xa], "submitPrev" ) == 0 )
		{
			RunMode = MODE_PREV_DAY;
		}
		else if ( nsStrcmp ( webNames[xa], "submitNext" ) == 0 )
		{
			RunMode = MODE_NEXT_DAY;
		}

		else
		{
			printf ( "Unknown input %s=%s<br>\n", webNames[xa], webValues[xa] );
		}
	}
}
