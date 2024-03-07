/*----------------------------------------------------------------------------
	Program : dorpt_dtl.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Create report in selected format
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

static	COLUMN_HEADINGS	ColumnArray [] = 
{
	{ "ID",				"",	INIT_STRING_LEFT },
	{ "amount",			"",	INIT_DOUBLE_RIGHT },
	{ "serving",		"",	INIT_STRING_LEFT },
	{ "name",			"",	INIT_STRING_LEFT },
	{ "calorie",		"",	INIT_DOUBLE_RIGHT_TOTAL },
	{ "carb",			"",	INIT_DOUBLE_RIGHT_TOTAL },
	{ "protein",		"",	INIT_DOUBLE_RIGHT_TOTAL },
	{ "fat",			"",	INIT_DOUBLE_RIGHT_TOTAL },
	{ "sodium",			"",	INIT_DOUBLE_RIGHT_TOTAL },
	{ "fiber",			"",	INIT_DOUBLE_RIGHT_TOTAL },
};

static  int		ColumnCount = sizeof(ColumnArray) / sizeof(COLUMN_HEADINGS);

void dorpt_dtl ()
{
	char	xbuffer[1024];
#define		MAXTOKS		15
	char	*tokens[MAXTOKS];
	int		tokcnt;
	char	Title[80];

	sprintf ( Title, "Nutrition Recipe List" );

	ReportOptions.HeaderRows = 1;
	ReportOptions.Title = Title;
	ReportOptions.Subtitle = "";
	ReportOptions.BreakCount = 3;
	// ReportOptions.Format = ReportFormat;
	switch ( ReportOptions.Format )
	{
		case RPT_FORMAT_CSV:
		case RPT_FORMAT_EXCEL:
		case RPT_FORMAT_HTML:
			ReportOptions.LinesPerPage = 0;
			ReportOptions.WritePageNumbers = 0;
			break;
		case RPT_FORMAT_TEXT:
		case RPT_FORMAT_PDF_VIEW:
		case RPT_FORMAT_PDF_EMAIL:
			ReportOptions.LinesPerPage = 60;
			ReportOptions.WritePageNumbers = 1;
			break;
	}
	sprintf ( ReportOptions.OutputFilename,  "%s/%s_%d", TEMPDIR, "rptrecipe", getpid() );
	strcat ( ReportOptions.OutputFilename, rptextension ( ReportOptions.Format ) );
	ReportOptions.IsStdout = 0;

	fpData = rptinit ( fnData, &ReportOptions, ColumnArray, ColumnCount );

	while ( fgets ( xbuffer, sizeof(xbuffer), fpData ) != (char *)0 )
	{
		tokcnt = GetTokensA ( xbuffer, "|\n\r", tokens, MAXTOKS );

		rptline ( &ReportOptions, ColumnArray, ColumnCount, tokens, tokcnt );
	}

	nsFclose ( fpData );
	rptclose ( &ReportOptions );
}
