/*----------------------------------------------------------------------------
	Program : PaintTop.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Start HTML output
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

void PaintTop ( int Stage )
{
	WEBPARMS	*ptrWebParms = webInitParms();

	if ( Stage == 1 )
	{
		webContentHtml ();

		ptrWebParms->WP_Title = "Enter Food";
		webStartHead ( ptrWebParms );

		printf ( "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n" );

		printf ( "<link rel='stylesheet' href='nutrition.css?version=%s'>\n", CSS_VERSION );
		printf ( "<link rel='stylesheet' media='not screen' href='member_large.css?version=%s'>\n", CSS_VERSION );
		printf ( "<link rel='stylesheet' media='screen and (min-width: 600px)' href='member_large.css?version=%s'>\n", CSS_VERSION );
		printf ( "<link rel='stylesheet' media='screen and (max-width: 600px)' href='member_small.css?version=%s'>\n", CSS_VERSION );

		printf ( "<script src='Nutrition.js'></script>\n" );
	}
	else if ( Stage == 2 )
	{
		printf ( "</head>\n" );

		// printf ( "<body class='%s' onLoad='javascript:Loaded();'>\n", RunMode == MODE_START ? "start" : "game" );
		printf ( "<body>\n" );
		// printf ( "<div id='PokerDiv' class='game'>\n" );

		ptrWebParms->WP_FormName   = "Nutrition";
		ptrWebParms->WP_FormAction = "EnterFood.cgi";
		ptrWebParms->WP_FormMethod = "POST";
		ptrWebParms->WP_FormOther  = (char *)0;
		webStartForm ( ptrWebParms );

		webFreeParms ( ptrWebParms );

//		printf ( "<input type='hidden' name='MemberID' value='%ld'>\n", xmember.xmid );
	}
}
