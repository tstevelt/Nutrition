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

#include	"rptplan.h"

void PaintScreen ()
{
	int			Count;

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

	printf ( "function Warning ()\n" );
	printf ( "{\n" );
	printf ( "\tvar u = document.getElementById('Universe').value;\n" );
	printf ( "\tif ( u == 'A' )\n" );
	printf ( "\t{\n" );
	printf ( "\t\talert('Takes a while to find good combination, since there are approximately 6000 foods to choose from.');\n" );
	printf ( "\t}\n" );
	printf ( "}\n" );

	printf ( "// end hiding -->\n" );
	printf ( "</script>\n" );


	printf ( "<table class='AppHalf'>\n" );

	printf ( "<tr>\n" );
	printf ( "<td align='center' colspan='2'>\n" );
	printf ( "Daily Food Plan" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	RuleRow ( 2 );

	printf ( "<tr>\n" );
	printf ( "<td colspan='2'>\n" );
	printf ( "Foods for a day which will meet all of %s macro, sodium and fiber targets.", 
			CookieMember.xmid == DEMO_MEMBER ? "member's" : "your" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	if ( CookieMember.xmid == DEMO_MEMBER )
	{
		printf ( "<tr>\n" );
		printf ( "<td colspan='2'>\n" );
		printf ( "Demo member is %s born %s\n", 
				CookieMember.xmgender[0] == 'M' ? "male" : "female",
				CookieMember.xmbirthdate );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		printf ( "<tr>\n" );
		printf ( "<td colspan='2'>\n" );
		printf ( "Signup/Login to see your own daily food plan" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );
	}
	else
	{
		printf ( "<tr>\n" );
		printf ( "<td>Member</td><td>%s</td>\n", CookieMember.xmname );
		printf ( "</tr>\n" );
	}

	printf ( "<tr>\n" );
	printf ( "<td>Calories</td><td>%d</td>\n", CookieMember.xmcalorie );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Carbs</td><td>%d</td>\n", CookieMember.xmcarb );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Protein</td><td>%d</td>\n", CookieMember.xmprotein );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Fat</td><td>%d</td>\n", CookieMember.xmfat );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Sodium</td><td>%d</td>\n", CookieMember.xmsodium );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Fiber</td><td>%d</td>\n", CookieMember.xmfiber );
	printf ( "</tr>\n" );

	RuleRow ( 2 );

	if ( MinFoods < MINFOODS )
	{
		MinFoods = 10;
	}
	if ( MaxFoods < MINFOODS || MaxFoods > MAXFOODS )
	{
		MaxFoods = 15;
	}

	printf ( "<tr>\n" );
	printf ( "<td>Minimum Foods (%d)</td>\n", MINFOODS );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='MinFoods' value='%d'>\n", MinFoods );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Maximum Foods (%d)</td>\n", MAXFOODS );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='MaxFoods' value='%d'>\n", MaxFoods );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ("<tr>\n" );
	printf ("<td>Food Universe</td>\n" );
	printf ("<td>\n" );
	printf ("<select name='Universe' id='Universe' onchange='javascript:Warning();'>\n" );
	printf ("<option value='C'%s>Commonly Selected</option>\n", Universe  != 'A' ? " selected" : "" );
	printf ("<option value='A'%s>All Foods</option>\n",         Universe  == 'A' ? " selected" : "" );
	printf ("</select>\n" );
	printf ("</td>\n" );
	printf ("</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Finish the day (optional, format yyyy-mm-dd)</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='FTD_Date' value='%s'>\n", FTD_Date );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td>Show GA statistics\n" );
	printf ( "&emsp;<input type='button' value='?' onclick='javascript:PopupWindow(600,300,\"ExplainGA.html\");'>\n" );
	printf ( "</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='checkbox' name='Statistics' %s>\n", Statistics ? "checked" : ""  );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	printf ("<tr>\n" );
	printf ("<td>Report Format</td>\n" );
	printf ("<td>\n" );

	printf ("<select name='ReportFormat' id='ReportFormat'>\n" );

	printf ("<option value='%c'%s>View PDF</option>\n", RPT_FORMAT_PDF_VIEW,  ReportOptions.Format  ==  RPT_FORMAT_PDF_VIEW ? " selected" : "" );
	printf ("<option value='%c'%s>Email PDF</option>\n", RPT_FORMAT_PDF_EMAIL,  ReportOptions.Format  ==  RPT_FORMAT_PDF_EMAIL ? " selected" : "" );

//	printf ("<option value='%c'%s>Screen</option>\n", RPT_FORMAT_HTML, ReportOptions.Format  == RPT_FORMAT_HTML ? " selected" : "" );
//	printf ("<option value='%c'%s>Email</option>\n", RPT_FORMAT_EMAIL, ReportOptions.Format  == RPT_FORMAT_EMAIL ? " selected" : "" );
//	printf ("<option value='%c'%s>CSV</option>\n",  RPT_FORMAT_CSV, ReportOptions.Format  == RPT_FORMAT_CSV ? " selected" : "" );
//	printf ("<option value='%c'%s>Text</option>\n", RPT_FORMAT_TEXT, ReportOptions.Format  == RPT_FORMAT_TEXT ? " selected" : "" );
//	printf ("<option value='%c'%s>Excel</option>\n", RPT_FORMAT_EXCEL, ReportOptions.Format  == RPT_FORMAT_EXCEL ? " selected" : "" );

	printf ("</select>\n" );
	printf ("</td>\n" );
	printf ("</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td align='center' colspan='2'>\n" );

	printf ( "<input type='button' value='go' " );
	printf ( "onClick='javascript:what.value=\"go\";runrpt(1200,800);'>\n" );

	printf ( "</td>\n" );
	printf ( "</tr>\n" );
	printf ( "</table>\n" );
}
