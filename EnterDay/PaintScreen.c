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

#include	"EnterDay.h"

void PaintScreen ()
{
	int		HaveDate = 0;
	DATEVAL	Today;

	if ( nsStrlen ( HistoryDate ) == 10 )
	{
		HaveDate = 1;
	}

	// printf ( "<table align='center' border='1' cellpadding='4' cellspacing='4' width='95%%'>\n" );
	printf ( "<table class='AppWide'>\n" );

	printf ( "<!--- date --->\n" );
	printf ( "<tr>\n" );

#ifdef DEBUG
#define DEBUG
	printf ( "<td>%ld %s</td>", CookieMember.xmid, CookieMember.xmname );
#endif
	if ( HaveDate == 0 )
	{
		CurrentDateval ( &Today );
				
		printf ( "<!--- date --->\n" );
		printf ( "<td colspan='%d'>Date\n", COLUMNS );
		printf ( "&emsp;<input type='search' name='HistoryDate' size='12' maxlength='10' value='%04d-%02d-%02d'>\n", 
				Today.year4, Today.month, Today.day );
		// printf ( "&nbsp;(yyyy-mm-dd)\n" );
		printf ( "&emsp;<input type='submit' name='submitDate' value='Start/Load Day'>\n" );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );
		RuleRow ( COLUMNS );

		printf ( "<!--- breakfast --->\n" );
		printf ( "<tr class='Breakfast'>\n" );
		printf ( "<td colspan='%d'>Breakfast</td>\n", COLUMNS );
		printf ( "</tr>\n" );
		BlankRow ( "Breakfast", COLUMNS );

		printf ( "<!--- lunch --->\n" );
		printf ( "<tr class='Lunch'>\n" );
		printf ( "<td colspan='%d'>Lunch</td>\n" , COLUMNS);
		printf ( "</tr>\n" );
		BlankRow ( "Lunch", COLUMNS );

		printf ( "<!--- dinner --->\n" );
		printf ( "<tr class='Dinner'>\n" );
		printf ( "<td colspan='%d'>Dinner</td>\n", COLUMNS );
		printf ( "</tr>\n" );
		BlankRow ( "Dinner", COLUMNS );

		printf ( "<!--- snacks --->\n" );
		printf ( "<tr class='Snack'>\n" );
		printf ( "<td colspan='%d'>Snacks</td>\n", COLUMNS );
		printf ( "</tr>\n" );
		BlankRow ( "Snack", COLUMNS );

	}
	else
	{
	// 15 30 30 25
		printf ( "<!--- date --->\n" );
		printf ( "<td width='15%%'>Date</td>\n" );
		printf ( "<td width='30%%'>%s</td>\n", HistoryDate );
		printf ( "<td width='30%%'>&nbsp;</td>\n" );
		printf ( "<td width='25%%'>&nbsp;</td>\n" );
		printf ( "</tr>\n" );
		RuleRow ( COLUMNS );
		printf ( "<input type='hidden' name='HistoryDate' value='%s'>\n", HistoryDate );

		printf ( "<!--- breakfast --->\n" );
		printf ( "<tr class='Breakfast'>\n" );
		printf ( "<td colspan='%d'>Breakfast</td>\n", COLUMNS );
		printf ( "</tr>\n" );

		PaintMeal ( "Breakfast" );

		printf ( "<!--- lunch --->\n" );
		printf ( "<tr class='Lunch'>\n" );
		printf ( "<td colspan='%d'>Lunch</td>\n" , COLUMNS);
		printf ( "</tr>\n" );

		PaintMeal ( "Lunch" );

		printf ( "<!--- dinner --->\n" );
		printf ( "<tr class='Dinner'>\n" );
		printf ( "<td colspan='%d'>Dinner</td>\n", COLUMNS );
		printf ( "</tr>\n" );

		PaintMeal ( "Dinner" );

		printf ( "<!--- snacks --->\n" );
		printf ( "<tr class='Snack'>\n" );
		printf ( "<td colspan='%d'>Snacks</td>\n", COLUMNS );
		printf ( "</tr>\n" );

		PaintMeal ( "Snack" );

		/*----------------------------------------------------------
			totals
		----------------------------------------------------------*/
		RuleRow ( COLUMNS );

		printf ( "<tr>\n" );
		printf ( "<td colspan='%d'>", COLUMNS );
		printf ( "&emsp;Calorie %.2f (%.1f%%)", TotalCalorie, PercentCalorie );
		printf ( "&emsp;Carb %.2f (%.1f%%)", TotalCarb, PercentCarb );
		printf ( "&emsp;Protein %.2f (%.1f%%)", TotalProtein, PercentProtein );
		printf ( "&emsp;Fat %.2f (%.1f%%)", TotalFat, PercentFat );
		printf ( "&emsp;Sodium %.2f (%.1f%%)", TotalSodium, PercentSodium );
		printf ( "&emsp;Fiber %.2f (%.1f%%)", TotalFiber, PercentFiber );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );

		RuleRow ( COLUMNS );

		/*----------------------------------------------------------
			Toolbox
		----------------------------------------------------------*/
		printf ( "<tr><td colspan='%d'>\n", COLUMNS );
		printf ( "<table cellspacing='10'>\n" );

		/*---------------------------------------------------------------------------
			Delete checked
		---------------------------------------------------------------------------*/
		printf ( "<tr>\n" );
		printf ( "<td>" );
		printf ( "<input type='submit' name='submitDelete' value='Delete Checked'>\n" );
		printf ( "</td>" );
		printf ( "<td colspan='%d'>&nbsp;</td>", COLUMNS-1 );
		printf ( "</tr>\n" );

		/*---------------------------------------------------------------------------
			Add food to the day:
				Meal select
				Food input
				Lookup ?
				Servings input
		---------------------------------------------------------------------------*/
		printf ( "<!--- input a food for the day --->\n" );
		printf ( "<tr>\n" );

		printf ( "<td>" );
		printf ( "Add&emsp;<select name='AddMealDescr'>" );
		printf ( "<option value='?'>-- selelct meal --</option>" );
		printf ( "<option value='B'%s>Breakfast</option>", MealDescr == 'B' ? " selected" : "" );
		printf ( "<option value='L'%s>Lunch</option>",     MealDescr == 'L' ? " selected" : "" );
		printf ( "<option value='D'%s>Dinner</option>",    MealDescr == 'D' ? " selected" : "" );
		printf ( "<option value='S'%s>Snack</option>",     MealDescr == 'S' ? " selected" : "" );
		printf ( "</select>" );
		printf ( "</td>\n" );

		printf ( "<td>" );
		printf ( "Food ID&emsp;<input type='search' name='AddFoodID' id='AddFoodID' size='10'>" );
		printf ( "&emsp;<input type='button' name='lookupFood' value='?' onclick='javascript:LookupFood();'>" );
		printf ( "</td>\n" );

		printf ( "<td>" );
		printf ( "Servings&emsp;<input type='search' name='AddFoodServings' size='6' maxlength='6'>" );
		printf ( "</td>\n" );
		printf ( "<td align='center'><input type='submit' name='submitAddFood' value='Add Food'></td>\n" );
		printf ( "</tr>\n" );

		/*---------------------------------------------------------------------------
			Copy entire day
		---------------------------------------------------------------------------*/
		printf ( "<!--- copy day --->\n" );
		printf ( "<tr>\n" );

		printf ( "<td>Date&emsp;<input type='search' name='CopyDayDate' size='12' maxlength='10'></td>\n" );

		printf ( "<td colspan='%d'>&nbsp;</td>\n", COLUMNS-2 );

		printf ( "<td align='center'><input type='submit' name='submitCopyDay' value='Copy Day'></td>\n" );
		printf ( "</tr>\n" );

		/*---------------------------------------------------------------------------
			Copy one meal from a day
		---------------------------------------------------------------------------*/
		printf ( "<!--- copy meal --->\n" );
		printf ( "<tr>\n" );

		printf ( "<td>Date&emsp;<input type='search' name='CopyMealDate' size='12' maxlength='10'></td>\n" );

		printf ( "<td colspan='%d'>", COLUMNS-2 );
		printf ( "Meal&emsp;<select name='CopyMealDescr'>" );
		printf ( "<option value='?'>-- selelct meal --</option>" );
		printf ( "<option value='B'>Breakfast</option>" );
		printf ( "<option value='L'>Lunch</option>" );
		printf ( "<option value='D'>Dinner</option>" );
		printf ( "<option value='S'>Snack</option>" );
		printf ( "</select>" );
		printf ( "</td>\n" );

		printf ( "<td align='center'><input type='submit' name='submitCopyMeal' value='Copy Meal'></td>\n" );
		printf ( "</tr>\n" );

		/*----------------------------------------------------------
			End of Toolbox
		----------------------------------------------------------*/
		printf ( "</td></tr>\n" );
		printf ( "</table>\n" );
	}

	/*----------------------------------------------------------
		Navigation buttons
	----------------------------------------------------------*/
	RuleRow ( COLUMNS );

	printf ( "<tr>" );
	printf ( "<td colspan='%d'>", COLUMNS );

	printf ( "<input type='button' id='buttonMenu' value='Menu' onclick='javascript:window.close();'>\n" );
	if ( HaveDate  )
	{
		printf ( "&emsp;<input type='submit' name='submitPrev' value='Previous Day'>\n" );
		printf ( "&emsp;<input type='submit' name='submitNext' value='Next Day'>\n" );
	}

	printf ( "</td>" );
	printf ( "</tr>" );

	printf ( "</table>\n" );
}
