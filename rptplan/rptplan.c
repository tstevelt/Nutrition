/*----------------------------------------------------------------------------
	Program : rptplan.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Generate a meal plan for one day, meeting member's requirements.

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
#include	"rptplan.h"

int	UseErrorSys = 1;

int main ( int argc, char *argv[] )
{
	WEBPARMS	*ptrWebParms;
	char		WhereClause[128];
	COOKIE_RECORD	MyCookie;
#define		MEMBER_COOKIE_NAME		"member"
	extern	char	SessionUnique[20];
	char	Fragment[24];

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
		CookieMember.xmid = DEMO_MEMBER;
	}
	else
	{
		sprintf ( SessionUnique, "%s", MyCookie.UserName );

		ReadSession ();
	}

	if ( CookieMember.xmid == 0 )
	{
		CookieMember.xmid = DEMO_MEMBER;
	}

	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	sprintf ( WhereClause, "Mid = %ld", CookieMember.xmid );
	LoadMember ( WhereClause, &CookieMember, 0 );

	GetInput ();

	ChkInput ();

	switch ( RunMode  )
	{
		case MODE_START:
			StartUp ( "Daily Food Plan", "nutrition", 1, 1, 1, NULL, 0 );

			ptrWebParms = webInitParms ();

			ptrWebParms->WP_FormName   = "rptform";
			ptrWebParms->WP_FormAction = "rptplan.cgi";
			ptrWebParms->WP_FormMethod = "POST";
			ptrWebParms->WP_FormOther  = (char *)0;
			webStartForm ( ptrWebParms );

			webFreeParms ( ptrWebParms );

			printf ( "<input type=hidden name='what' value='lunch'>\n" );

			break;

		case MODE_RUN:
			ReportUp ( "Daily Food Plan", "nutrition", NULL, ReportOptions.Format, "Daily Food Plan" );
			break;
	}

	switch ( RunMode )
	{
		case MODE_START:
			PaintScreen ();
			printf ( "</form>\n" );
			break;

		case MODE_RUN:
			sprintf ( ReportOptions.OutputFilename,  "%s/%s_%d", TEMPDIR, "rptplan", getpid() );
			switch ( ReportOptions.Format )
			{
				case RPT_FORMAT_PDF_EMAIL:
				case RPT_FORMAT_PDF_VIEW:
					break;
				default:
					strcat ( ReportOptions.OutputFilename, rptextension ( ReportOptions.Format ) );
					break;
			}

			if ( FTD )
			{
				sprintf ( Fragment, "-ftd %s", FTD_Date );
			}
			else
			{
				Fragment[0] = '\0';
			}

			sprintf ( Cmdline, "/usr/local/bin/GenMealPlan -member %ld -db %s -minfoods %d -maxfoods %d %s %s %s > %s", 
					CookieMember.xmid, 
					Universe == 'A' ? "all" : "common",
					MinFoods,
					MaxFoods,
					Fragment,
					Universe == 'A' ? "-generations 200" : "",
					Statistics ? "-s" : "",
					ReportOptions.OutputFilename );
			system ( Cmdline );

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
					fprintf ( fpBody, "Daily Food Plan\n" );
					fprintf ( fpBody, "%s\n", "Nutrition" );
					nsFclose ( fpBody );

rptdeliv ( CookieMember.xmemail, CookieMember.xmemail, "Daily Food Plan", fnBody, ReportOptions.OutputFilename, ReportOptions.Format, 0 );

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
													
			break;

		default :
			sprintf ( Statement, "RunMode %d not finished.", RunMode );
			SaveError ( Statement );
			break;
	}


//	ErrorSysLoaded ( "Loaded" );

	printf ( "</body>\n" );
	printf ( "</html>\n" );

	dbyClose ( &MySql );

	return ( 0 );
}
