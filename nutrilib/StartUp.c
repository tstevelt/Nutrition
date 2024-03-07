/*----------------------------------------------------------------------------
	Program : StartUp.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint standard beginning of HTML page.
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


#include	"nutriprivate.h"
#include	"nutrilib.h"

void StartUp ( char *Title, char *DbName, int InitDB, int PaintHeader, int WriteMeta, char *OnLoad, int Menu )
{
	WEBPARMS	*ptrWebParms;

	ptrWebParms = webInitParms ();

	/*----------------------------------------------------------
		output first part of HTML ...
	----------------------------------------------------------*/
	webContentHtml ();

    ptrWebParms->WP_Title = Title;
    webStartHead ( ptrWebParms );

	/*--------------------------------------------------------------
		if on load function or not
	--------------------------------------------------------------*/
	if ( OnLoad == (char *)0 )
	{
		ptrWebParms->WP_Class = "inherit";
		webHeadToBody ( ptrWebParms );
	}
	else
	{
		ptrWebParms->WP_Class = "inherit";
		ptrWebParms->WP_OnLoad = OnLoad;
		webHeadToBody ( ptrWebParms );
	}

	printf ( "<link rel='stylesheet' media='not screen' href='member_large.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' media='screen and (min-width: 600px)' href='member_large.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' media='screen and (max-width: 600px)' href='member_small.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' href='nutrition.css?version=%s'>\n", CSS_VERSION );
	
	printf ( "<script src='Nutrition.js'></script>\n" );

	/*--------------------------------------------------------------
		if initialize DB
	--------------------------------------------------------------*/
	if ( nsStrlen( DbName ) > 0 && (InitDB > 0) )
	{
//		if ( StartDb ( DbName ) != 0 )
//		{
//			printf ( "DB [%s], Init %d<br>\n", DbName, InitDB );
//			exit ( 0 );
//		}
		dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );
	}

	/*--------------------------------------------------------------
		paint accounting system header
	--------------------------------------------------------------*/
	if ( PaintHeader )
	{
//		AcctStyle ( NULL );

//		if ( InitDB )
//		{
//			LoadSystem ();
//		}
//		else 
//		{
//			snprintf ( xsystem.xname, sizeof(xsystem.xname), "%s", Title );
//		}

		printf ( "<table align='center' border='0' cellspacing='0' cellpadding='3' width='92%%'>\n" );
		printf ( "<tr class='HeadingRow'>\n" );

		/*--------------------------------------------------------------
			if there is a menu
		--------------------------------------------------------------*/
		printf ( "<td align='left' width='20%%' onClick='javascript:window.close();'>" );
		printf ( "<u>menu</u></td>\n" );

		printf ( "<td align='center' width='60%%'>%s</td>\n", "Nutrition" );

		printf ( "<td width='20%%'>&nbsp;</td>\n" );

		printf ( "</tr>\n" );

		printf ( "</table>\n" );

		printf ( "<p>\n" );
	}

	webFreeParms ( ptrWebParms );
}
