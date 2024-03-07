/*----------------------------------------------------------------------------
	Program : rpthist.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Report of foods eaten for a day or a week.  

	Who		Date		Modification
	---------------------------------------------------------------------

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

#define		MAIN
#include	"rpthist.h"

int	UseErrorSys = 1;


int main ( int argc, char *argv[] )
{
	WEBPARMS	*ptrWebParms;
	char		WhereClause[128];
	COOKIE_RECORD	MyCookie;
#define		MEMBER_COOKIE_NAME		"member"
	extern	char	SessionUnique[20];

//xxxxxxxxxxxxx

//	PaintTop ( 1 );

	/*----------------------------------------------------------
		cookie stuff has to be written before html starts.
	----------------------------------------------------------*/
	/*----------------------------------------------------------
		get cookie
	----------------------------------------------------------*/
	if ( webParseCookie ( MEMBER_COOKIE_NAME, &MyCookie ) != 0 )
	{
		webContentHtml ();
		printf ( "Please LOGIN<br>\n" );
		exit ( 0 );
	}
	else
	{
		sprintf ( SessionUnique, "%s", MyCookie.UserName );
	}


	ReadSession ();
	if ( CookieMember.xmid == 0 )
	{
		webContentHtml ();
		printf ( "Please LOGIN<br>\n" );
		exit ( 0 );
	}

//	StartMySQL ( &MySql, "nutrition" );
//	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

//	PaintTop ( 2 );

//xxxxxxxxxxxxx

	GetInput ();

	switch ( RunMode  )
	{
		case MODE_START:
			StartUp ( "Nutrition History List", "nutrition", 1, 1, 1, NULL, 0 );

			ptrWebParms = webInitParms ();

			ptrWebParms->WP_FormName   = "rptform";
			ptrWebParms->WP_FormAction = "rpthist.cgi";
			ptrWebParms->WP_FormMethod = "POST";
			ptrWebParms->WP_FormOther  = (char *)0;
			webStartForm ( ptrWebParms );

			webFreeParms ( ptrWebParms );

			printf ( "<input type=hidden name='what' value='lunch'>\n" );

			break;

		case MODE_RUN:
			ReportUp ( "History List", "nutrition", NULL, ReportOptions.Format, "history" );
			break;
	}

	switch ( RunMode )
	{
		case MODE_START:
			PaintScreen ();
			printf ( "</form>\n" );
			break;

		case MODE_RUN:
			if ( ChkInput () != 0 )
			{
				break;
			}

			if (( DayMealFood == 'D' && getdata_day  () > 0 ) ||
				( DayMealFood == 'M' && getdata_meal () > 0 ) ||
				( DayMealFood == 'F' && getdata_food () > 0 ))
			{
				sortdata ();

				switch ( DayMealFood )
				{
					case 'D':
						dorpt_day ();
						break;
					case 'M':
						dorpt_meal ();
						break;
					case 'F':
						dorpt_food ();
						break;
				}

				switch ( ReportOptions.Format )
				{
					case RPT_FORMAT_CSV:
					case RPT_FORMAT_EXCEL:
					case RPT_FORMAT_TEXT:
					case RPT_FORMAT_PDF_EMAIL:
					case RPT_FORMAT_PDF_VIEW:
						sprintf ( fnBody, "%s/body_%d.txt", TEMPDIR, getpid() );
						if (( fpBody = fopen ( fnBody, "w" )) == (FILE *)0 )
						{
							printf ( "Cannot create %s for output\n", fnBody );
							break;
						}
						fprintf ( fpBody, "History List\n" );
						fprintf ( fpBody, "%s\n", "Nutrition" );
						nsFclose ( fpBody );

snprintf ( WhereClause, sizeof(WhereClause), "Mid = %ld", CookieMember.xmid );
LoadMember ( WhereClause, &xmember, 0 );
rptdeliv ( xmember.xmemail, xmember.xmemail, "History List", fnBody, ReportOptions.OutputFilename, ReportOptions.Format, 0 );

						unlink ( fnBody );
						break;
			 
					case RPT_FORMAT_HTML:
						rptcat ( ReportOptions.OutputFilename );
						
				}
#ifdef DEBUG
#define DEBUG
				printf ( "%s<br>\n", fnData );
				printf ( "%s<br>\n", ReportOptions.OutputFilename );
#else
				unlink ( fnData );
				unlink ( ReportOptions.OutputFilename );
#endif
													
			}
			break;

		default :
			sprintf ( StatementOne, "RunMode %d not finished.", RunMode );
			SaveError ( StatementOne );
			break;
	}


//	ErrorSysLoaded ( "Loaded" );

	printf ( "</body>\n" );
	printf ( "</html>\n" );

	dbyClose ( &MySql );

	return ( 0 );
}
