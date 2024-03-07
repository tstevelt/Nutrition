/*----------------------------------------------------------------------------
	Program : dorpt.c
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

#include	"rptmember.h"

static	COLUMN_HEADINGS	ColumnArray [] = 
{
	{ "ID",		"",	INIT_LONG_CENTER },
	{ "name",	"",	INIT_STRING_LEFT },
	{ "joined",	"",	INIT_STRING_LEFT },
	{ "email",	"",	INIT_STRING_LEFT },
	{ "meals",	"",	INIT_LONG_RIGHT },
	{ "latest",	"",	INIT_STRING_LEFT },
};

static  int		ColumnCount = sizeof(ColumnArray) / sizeof(COLUMN_HEADINGS);

void dorpt ()
{
	char	xbuffer[1024];
#define		MAXTOKS		12
	char	*tokens[MAXTOKS];
	int		tokcnt;
	char	Title[80];
	char	Subtitle[80];

	sprintf ( Title, "Member List" );

	sprintf ( Subtitle, "%s %04d-%02d-%02d - %04d-%02d-%02d",
					IncludeToday == 'Y' ? "Eight Days" : "Seven Days",
					SevenDays.year4, SevenDays.month, SevenDays.day,
					Yesterday.year4, Yesterday.month, Yesterday.day );

	ReportOptions.HeaderRows = 1;
	ReportOptions.Title = Title;
	ReportOptions.Subtitle = Subtitle;
	ReportOptions.BreakCount = 0;
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
	sprintf ( ReportOptions.OutputFilename,  "%s/%s_%d", TEMPDIR, "rptmember", getpid() );
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
