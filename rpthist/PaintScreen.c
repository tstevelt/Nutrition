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

#include	"rpthist.h"

void PaintScreen ()
{
	int			Count;
	DATEVAL		Today, Yesterday;

	if (( Count = dbySelectCount ( &MySql, "food", "Fid > 0", LogFileName )) == 0 )
	{
		SaveError ( "No food found" );
		return;
	}

	printf ( "<script language='JavaScript1.1'>\n" );
	printf ( "<!-- hide code from non-js browsers\n" );

	printf ( "function runrpt(width,height)\n" );
	printf ( "{\n" );
	// printf ( "var options = 'screenX=10,screenY=10,width=' + width + ',height=' + height + ',resizable=1,menubar=1,scrollbars=1';\n" );
	// printf ( "window.open ( '', 'results', options );\n" );
	// printf ( "window.open ( '', '_self', options );\n" );
	printf ( "window.document.rptform.what.value = 'go';\n" );
	// printf ( "window.document.rptform.target = 'results';\n" );
	printf ( "window.document.rptform.submit();\n" );
	printf ( "}\n" );

	printf ( "// end hiding -->\n" );
	printf ( "</script>\n" );


	printf ( "<table class='AppHalf'>\n" );

	printf ( "<tr>\n" );
	printf ( "<td align='center' colspan='2'>\n" );
	printf ( "History List" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Date</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='EndDate'" );
	if ( nsStrlen ( EndDate ) == 0 )
	{
		CurrentDateval ( &Today );
		DateAdd ( &Today, -1, &Yesterday );
		printf ( " value='%04d-%02d-%02d'", Yesterday.year4, Yesterday.month, Yesterday.day );
	}
	printf ( ">\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );
	
	printf ( "<tr>\n" );
	printf ( "<td>Duration</td>\n" );
	printf ( "<td>\n" );
	printf ( "<select name='Duration'>\n" );
	printf ( "<option value='1'>Day</option>\n" );
	printf ( "<option value='7'>Week Ending</option>\n" );
	printf ( "</select>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>How much detail?</td>\n" );
	printf ( "<td>\n" );
	printf ( "<select name='DayMealFood'>\n" );
	printf ( "<option value='D'>Day</option>\n" );
	printf ( "<option value='M'>Meal</option>\n" );
	printf ( "<option value='F'>Food</option>\n" );
	printf ( "</select>\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	rptPaintFormat ( "Report Format", RPT_FORMAT_HTML );

	printf ( "<tr>\n" );
	printf ( "<td align='center' colspan='2'>\n" );

	printf ( "<input type='button' value='go' " );
	printf ( "onClick='javascript:what.value=\"go\";runrpt(1200,800);'>\n" );

	printf ( "</td>\n" );
	printf ( "</tr>\n" );
	printf ( "</table>\n" );
}
