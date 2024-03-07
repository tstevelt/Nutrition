/*----------------------------------------------------------------------------
	Program : PaintScreen.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint screen form for user input
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

#include	<errno.h>
#include	"nutrition.h"

#define		NAME_IN_HEADING
#undef		NAME_IN_HEADING
#define		NAME_IN_MENU

void PaintScreen ()
{
	int		xi;
	char	fn[256];
	FILE	*fp;
	char	xbuffer[2048];
//	int		MenuWidth = 15;
	char	*Glyph;

#undef	FIXED_TOP
#define	FIXED_TOP

// Includes over 250 glyphs in font format from the Glyphicon Halflings set. 
// Glyphicons Halflings are normally not available for free, but their creator has made them available for Bootstrap free of cost. 
// As a thank you, we only ask that you include a link back to Glyphicons whenever possible.

// li class='active' for the active option

	
	/*----------------------------------------------------------
		paint menu
	----------------------------------------------------------*/

#ifdef	FIXED_TOP
	printf ( "<nav class='navbar navbar-inverse navbar-fixed-top'>\n" );
#else
	printf ( "<nav class='navbar navbar-inverse'>\n" );
#endif
	printf ( "<div class='container-fluid'>\n" );

	printf ( "<div class='navbar-header'>\n" );
	printf ( "<button type='button' class='navbar-toggle' data-toggle='collapse' data-target='#myNavbar'>\n" );
	printf ( "<span class='icon-bar'></span>\n" );
	printf ( "<span class='icon-bar'></span>\n" );
	printf ( "<span class='icon-bar'></span>                        \n" );
	printf ( "</button>\n" );
#ifdef DEBUG
#define DEBUG
	printf ( "<a class='navbar-brand' href='#'>ID %ld Role %c</a>\n", CookieMember.xmid, CookieMember.xmrole[0] );
#else
	if ( CookieMember.xmid == 0 )
	{
		printf ( "<a class='navbar-brand' href='#'>%s</a>\n", Title );
	}
	else
	{
		printf ( "<a class='navbar-brand' href='#'>%s</a>\n", CookieMember.xmname );
	}
#endif
	printf ( "</div>\n" );	// end navbar-header

	printf ( "<div class='collapse navbar-collapse' id='myNavbar'>\n" );

	printf ( "<ul class='nav navbar-nav'>\n" );

	for ( xi = 1; xi <= MenuCount; xi++ )
	{
		if (( nsStrcmp ( MenuArray[xi].String, "Logout" ) == 0 ) ||
			( nsStrcmp ( MenuArray[xi].String, "Login"  ) == 0 ) ||
			( nsStrcmp ( MenuArray[xi].String, "Signup" ) == 0 ))
		{
			continue;
		}

		if ( CookieMember.xmid == 0 )
		{
			if (( nsStrcmp ( MenuArray[xi].String, "Members"      ) == 0 ) ||
				( nsStrcmp ( MenuArray[xi].String, "Edit Profile" ) == 0 ) ||
				( nsStrcmp ( MenuArray[xi].String, "Admin"        ) == 0 ) ||
				( nsStrcmp ( MenuArray[xi].String, "To Do"        ) == 0 ))
			{
				continue;
			}
		}
		else if ( CookieMember.xmrole[0] != 'A' && nsStrcmp ( MenuArray[xi].String, "Admin" ) == 0 )
		{
			continue;
		}

		printf ( "<li%s><a href='nutrition.cgi?MenuIndex=%d'>%s</a></li>\n",
			MenuArray[xi].PageNumber  == MenuIndex ? " class='active'" : "",
			MenuArray[xi].PageNumber, 
			MenuArray[xi].String );

	}

	printf ( "</ul>\n" );

	printf ( "<ul class='nav navbar-nav navbar-right'>\n" );

	for ( xi = 1; xi <= MenuCount; xi++ )
	{
		if ( CookieMember.xmid == 0 )
		{
			if ( nsStrcmp ( MenuArray[xi].String, "Login"  ) == 0 )
			{
				Glyph = "glyphicon-log-in";
			}
			else if ( nsStrcmp ( MenuArray[xi].String, "Signup" ) == 0 )
			{
				Glyph = "glyphicon-user";
			}
			else
			{
				continue;
			}
		}
		else
		{
			if ( nsStrcmp ( MenuArray[xi].String, "Logout" ) != 0 )
			{
				continue;
			}
			else
			{
				Glyph = "glyphicon-log-out";
			}
		}

		printf ( "<li%s><a href='nutrition.cgi?MenuIndex=%d'><span class='glyphicon %s'></span>&nbsp;%s</a></li>\n",
			MenuArray[xi].PageNumber  == MenuIndex ? " class='active'" : "",
			MenuArray[xi].PageNumber, 
			Glyph,
			MenuArray[xi].String );
	}
	printf ( "</ul>\n" );
	printf ( "</div>\n" );	// end collapse ...

	printf ( "</div>\n" );	// end container-fluid for menu

	printf ( "</nav>\n" );

	/*----------------------------------------------------------
		paint stories
	----------------------------------------------------------*/
//	printf ( "<div class='container'>\n" );
	
#ifdef	FIXED_TOP
	printf ( "<div class='topspacer'>&nbsp;</div>\n" );
#endif

	/*----------------------------------------------------------
		paint error / messages if any
	----------------------------------------------------------*/
	if ( ErrorCount > 0 )
	{
		printf ( "<div class='%s'>\n", ErrorClass );
		for ( xi = 0; xi < ErrorCount; xi++ )
		{
			printf ( "%s<br>\n", ErrorArray[xi].Message );
		}
		printf ( "</div>\n" );
	}


	switch ( RunMode )
	{
		case MODE_PAINT_PASSWORD:
			PaintSpecial ( RunMode );
			break;

		default:
			for ( xi = 0; xi < PageCount; xi++ )
			{
				printf ( "<div class='story'>\n" );

				if ( nsStrncmp ( PageArray[xi].String, "sf=", 3 ) == 0 )
				{
					int		FunctionCode;
					FunctionCode = nsAtoi ( &PageArray[xi].String[3] );

					printf ( "<!-- start of special function %d -->\n", FunctionCode );

					PaintSpecial ( FunctionCode );

					printf ( "<!-- end of special function %d -->\n", FunctionCode );
				}
				else
				{
					printf ( "<!-- start contents of %s -->\n", PageArray[xi].String );
					snprintf ( fn, sizeof(fn), "%s/%s", RW_DIRECTORY, PageArray[xi].String );
					if (( fp = fopen ( fn, "r" )) == (FILE *)0 )
					{
#ifdef DEBUG
#define DEBUG
						printf ( "Cannot open %s, errno %d\n", fn, errno );
#else
						printf ( "Cannot open %s\n", PageArray[xi].String );
#endif
					}
					else
					{
						while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != (char *)0 )
						{
							printf ( "%s", xbuffer );
						}

						nsFclose ( fp );
					}
					printf ( "<!-- end of %s -->\n", PageArray[xi].String );
				}
				printf ( "</div>\n" );
			}

			/*----------------------------------------------------------
				stories cell end here 
			----------------------------------------------------------*/
			break;
	}

//	printf ( "</div>\n" );	// end container for stories



#ifdef STUFF

#ifdef NAME_IN_HEADING
	if ( CookieMember.xmid == 0 )
	{
		printf ( "Not logged in." );
	}
	else
	{
		printf ( "%s", CookieMember.xmname );
	}
#endif

	printf ( "<hr>\n" );

#endif

	printf ( "<div class='footer'>\n" );
	printf ( "<a target='shs' href='http://www.silverhammersoftware.com'>%s</a>\n", Footer );
	printf ( "</div>\n" );
	printf ( "<br>\n" );
	printf ( "<br>\n" );
}
