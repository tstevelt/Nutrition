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

#include	"rptplan.h"

void GetInput ()
{
	int		xa;

	/*----------------------------------------------------------
		get user input
	----------------------------------------------------------*/
	webGetInput ();

	RunMode = MODE_START;
	ReportOptions.Format =  RPT_FORMAT_PDF_VIEW;

	for ( xa = 0; xa < webCount; xa++ )
	{
		webFixHex ( webValues[xa] );
		TrimRightAndLeft ( webValues[xa] );

		if ( nsStrcmp ( webNames[xa], "ReportFormat" ) == 0 )
		{
			ReportOptions.Format = toupper ( webValues[xa][0] );
		}
		else if ( nsStrcmp ( webNames[xa], "Universe" ) == 0 )
		{
			Universe = toupper ( webValues[xa][0] );
		}
		else if ( nsStrcmp ( webNames[xa], "MinFoods" ) == 0 )
		{
			MinFoods = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "MaxFoods" ) == 0 )
		{
			MaxFoods = nsAtoi ( webValues[xa] );
		}
		else if ( nsStrcmp ( webNames[xa], "FTD_Date" ) == 0 )
		{
			sprintf ( FTD_Date, "%s", webValues[xa] );
			if ( lastchr ( FTD_Date, 10 ) == 10 )
			{
				FTD = 1;
			}
		}
		else if ( nsStrcmp ( webNames[xa], "Statistics" ) == 0 )
		{
			Statistics = 1;
		}
		else if ( nsStrcmp ( webNames[xa], "what" ) == 0 )
		{
			if ( nsStrcmp ( webValues[xa], "go" ) == 0 )
			{
				RunMode = MODE_RUN;
			}
			else if ( nsStrcmp ( webValues[xa], "lunch" ) != 0 )
			{
				sprintf ( Statement, "UNKNOWN [%s] [%s]", webNames[xa], webValues[xa] );
				SaveError ( Statement );
			}
		}
		else
		{
			sprintf ( Statement, "UNKNOWN [%s] [%s]", webNames[xa], webValues[xa] );
			SaveError ( Statement );
		}
	}
}
