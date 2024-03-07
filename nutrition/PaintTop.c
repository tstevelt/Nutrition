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

#include	"nutrition.h"

void PaintTop ()
{
	WEBPARMS	*ptrWebParms = webInitParms();

	// cgiPagePart ( PP_CGI_START, 0, NULL );
	webContentHtml ();

	ptrWebParms->WP_Title = URL_NAME;
	//cgiPagePart ( PP_HEAD_START_HTML5, 1, ptrWebParms );
	webStartHead ( ptrWebParms );


	printf ( "<script type='text/javascript'>\n" );
	printf ( "function RunPage ( Number )\n" );
	printf ( "{\n" );
	printf ( "var elem = document.getElementById ( 'MenuIndex' );\n" );
	printf ( "elem.value = Number;\n" );
	printf ( "document.member_form.submit();\n" );
	printf ( "}\n\n" );

	printf ( "function CheckCookie ()\n" );
	printf ( "{\n" );
	printf ( "\tvar elemCB   = document.getElementById('SignupAllowCookie');\n" );
	printf ( "\tvar elemWhat = document.getElementById('what');\n" );
	printf ( "\tvar elemForm = document.getElementById('member_form');\n" );

	printf ( "\tif ( ! elemCB.checked )\n" );
	printf ( "\t{\n" );
	printf ( "\t\talert ( 'Website requires cookies in order keep you logged in.' );\n" );
	printf ( "\t\treturn;\n" );
	printf ( "\t}\n" );
	printf ( "\telemWhat.value = 'SubmitSignup';\n" );
	printf ( "\telemForm.submit();\n" );
	printf ( "}\n" );

	printf ( "</script>\n" );

	printf ( "<meta name='description' content='Nutrition' lang='en-US'/>\n" );
	printf ( "<meta name='robots' content='noodp,noydir'/>\n" );

	printf ( "<meta name='viewport' content='width=device-width, initial-scale=1'>\n" );
	printf ( "<meta name='keywords' content='nutrition'/>\n");
	printf ( "<meta property='og:title' content='Nutrition'/>\n" );
	printf ( "<meta property='og:description' content='nutrition'/>\n" );
	printf ( "<meta property='og:url' content='http://nutrition.silverhammersoftware.com'/>\n" );
	printf ( "<meta property='og:type' content='website'/>\n" );
	printf ( "<meta property='og:site_name' content='Nutrition'/>\n" );

	printf ( "<link rel='canonical' href='http://nutrition.silverhammersoftware.com'/>\n" );

	/*---------------------------------------------------------------------------
		!!! NOTE:  META VIEWPORT MUST BE BEFORE CSS STYLE SHEETS !!!
	---------------------------------------------------------------------------*/


	printf ( "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>\n" );
	printf ( "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js'></script>\n" );
	printf ( "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>\n" );
	printf ( "<link rel='stylesheet' href='my_navbar_colors.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' media='not screen' href='member_large.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' media='screen and (min-width: 600px)' href='member_large.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' media='screen and (max-width: 600px)' href='member_small.css?version=%s'>\n", CSS_VERSION );
	printf ( "<link rel='stylesheet' href='nutrition.css?version=%s'>\n", CSS_VERSION );
	
	printf ( "<script src='Nutrition.js'></script>\n" );

	// cgiPagePart ( PP_HEAD_TO_BODY_CSS, 0, NULL );
	webHeadToBody ( ptrWebParms );

	ptrWebParms->WP_FormName   = "member_form";
	ptrWebParms->WP_FormAction = "nutrition.cgi";
	ptrWebParms->WP_FormMethod = "POST";
	ptrWebParms->WP_FormOther  = (char *)0;
	// cgiPagePart (  PP_FORM_START, 4, ptrWebParms );
	webStartForm ( ptrWebParms );

	webFreeParms ( ptrWebParms );


}
