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

#include	"EnterRecipe.h"

#define DEBUG
#undef DEBUG

static		int		NumRows;

static int EachRecfood ( XRECFOOD *ptr )
{
	char	FoodWhereClause[128];

	NumRows++;
	if ( NumRows == 1 )
	{
		printf ( "<tr><td colspan='%d'><table border='0' cellpadding='2' width='100%%'>\n", COLUMNS );
		printf ( "<td width='10%%' align='center'>Remove</td>\n" );
		printf ( "<td width='15%%'>Amount</td>\n" );
		printf ( "<td width='15%%'>Serving</td>\n" );
		printf ( "<td width='60%%'>Description</td>\n" );
		printf ( "</tr>\n" );
	}

	sprintf ( FoodWhereClause, "Fid = %ld", ptr->xrffood );
	LoadFood ( FoodWhereClause, &xfood, 0 );

	printf ( "<tr>\n" );
	// printf ( "<tr class='%s'>\n", Class );

	printf ( "<td align='center'><input type='checkbox' name='cb_%ld_%ld'></td>\n", ptr->xrfrecipe, ptr->xrffood );
	printf ( "<td>%.2f</td>\n", ptr->xrfamount );
	printf ( "<td>%s</td>\n", xfood.xfserving );
	printf ( "<td>%s</td>\n", xfood.xfname );
	printf ( "</tr>\n" );

	TotalCalorie += ptr->xrfamount * xfood.xfcalorie;
	TotalCarb    += ptr->xrfamount * xfood.xfcarb;
	TotalProtein += ptr->xrfamount * xfood.xfprotein;
	TotalFat     += ptr->xrfamount * xfood.xffat;
	TotalSodium  += ptr->xrfamount * xfood.xfsodium;
	TotalFiber   += ptr->xrfamount * xfood.xffiber;

	return ( 0 );
}

void PaintScreen ()
{
	printf ( "<table class='AppWide'>\n" );

#ifdef DEBUG
	printf ( "<tr><td colspan='2'>Member ID %ld Name %s RunMode %d RecipeID %ld</td></tr>\n", 
			CookieMember.xmid, CookieMember.xmname, RunMode, RecipeID );
#endif

	printf ( "<tr>\n" );
	printf ( "<th class='maint' colspan='2' align='center'>\n" );
	printf ( "Recipe Setup</th>\n" );
	printf ( "</tr>\n" );

	if ( RecipeID == 0 )
	{
		RunMode = MODE_START;
	}

	/*--------------------
		Row 1
	--------------------*/
	printf ( "<tr>\n" );
	printf ( "<td width='25%%'>\n" );
	printf ( "Recipe ID</td>\n" );
	printf ( "<td width='74%%'>\n" );
	if ( RunMode == MODE_START )
	{
		printf ( "<input type='search' id='RecipeID' name='RecipeID' size='14' maxlength='11'>" );
		printf ( "&emsp;Leave blank to insert auto-generated ID.\n" );
	}
	else
	{
		printf ( "%ld", xrecipe.xrid );
		printf ( "<input type='hidden' name='RecipeID' value='%ld'>\n", xrecipe.xrid );
	}
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	/*--------------------
		Row 2
	--------------------*/
	printf ( "<tr>\n" );
	printf ( "<td>\n" );
	printf ( "Description</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='Rdescr' size='43' maxlength='40'" );
	if ( nsStrlen ( xrecipe.xrdescr ) > 0 )
	{
		printf ( " value='%s'", xrecipe.xrdescr );
	}
	printf ( ">\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	/*--------------------
		Row 3
	--------------------*/
	printf ( "<tr>\n" );
	printf ( "<td>\n" );
	printf ( "Servings</td>\n" );
	printf ( "<td>\n" );
	printf ( "<input type='search' name='Rserving' size='9' maxlength='6'" );
	if ( xrecipe.xrserving > 0 )
	{
		printf ( " value='%d'", xrecipe.xrserving );
	}
	printf ( ">\n" );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	RuleRow ( COLUMNS );

	TotalCalorie = TotalCarb = TotalProtein = TotalFat = TotalSodium = TotalFiber = 0.0;

	sprintf ( WhereClause, "RFrecipe = %ld", RecipeID );
	LoadRecfoodCB ( WhereClause, NULL, &xrecfood, EachRecfood, 0 );

	/*----------------------------------------------------------
		totals
	----------------------------------------------------------*/
	RuleRow ( COLUMNS );

	printf ( "<tr>\n" );
	printf ( "<td>Recipe Totals</td>" );
	printf ( "<td colspan='%d'>", COLUMNS-1 );
	printf ( "Calorie %.2f", TotalCalorie );
	printf ( "&emsp;Carb %.2f", TotalCarb );
	printf ( "&emsp;Protein %.2f", TotalProtein );
	printf ( "&emsp;Fat %.2f", TotalFat );
	printf ( "&emsp;Sodium %.2f", TotalSodium );
	printf ( "&emsp;Fiber %.2f", TotalFiber );
	printf ( "</td>\n" );
	printf ( "</tr>\n" );

	if ( xrecipe.xrserving > 1 )
	{
		printf ( "<tr>\n" );
		printf ( "<td>One Serving</td>" );
		printf ( "<td colspan='%d'>", COLUMNS-1 );
		printf ( "Calorie %.2f", TotalCalorie / xrecipe.xrserving );
		printf ( "&emsp;Carb %.2f", TotalCarb / xrecipe.xrserving );
		printf ( "&emsp;Protein %.2f", TotalProtein / xrecipe.xrserving );
		printf ( "&emsp;Fat %.2f", TotalFat / xrecipe.xrserving );
		printf ( "&emsp;Sodium %.2f", TotalSodium / xrecipe.xrserving );
		printf ( "&emsp;Fiber %.2f", TotalFiber / xrecipe.xrserving );
		printf ( "</td>\n" );
		printf ( "</tr>\n" );
	}

	RuleRow ( COLUMNS );

	printf ( "<tr>\n" );
	printf ( "<td class='buttons' colspan='4'>\n" );
	switch ( RunMode )
	{
		case MODE_START:
			printf ( "<input type='reset'  value='reset'>\n" );
			printf ( "&emsp;<input type='submit' name='submitLookup' value='find'>\n" );
			printf ( "&emsp;<input type='submit' name='submitInsert' value='insert'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
			break;
		case MODE_FOUND:
			printf ( "<input type='submit' name='submitQuit' value='quit'>\n" );
			printf ( "&emsp;<input type='submit' name='submitDeleteRecfood' value='Remove Checked'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
			printf ( "&emsp;<input type='submit' name='submitUpdate' value='update'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
#ifdef SAFETY_ON_DELETE
			shs_seed_random ();
			HiddenSafety = random_range ( 123, 987 );

			printf ( "<input type='hidden' name='HiddenSafety' value='%d'>\n", HiddenSafety );
			printf ( "&emsp;%d", HiddenSafety );
			printf ( "&nbsp;<input type='search' name='AnswerSafety' size='4'>\n" );
			printf ( "&nbsp;" );
#endif
			printf ( "&emsp;<input type='submit' name='submitDeleteRecipe' value='delete recipe'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );

			printf ( "</tr>\n" );

			/*---------------------------------------------------------------------------
				Add food to the day:
					Food input
					Lookup ?
					Servings input
			---------------------------------------------------------------------------*/
			printf ( "<!--- input a food for the recipe --->\n" );
			printf ( "<tr>\n" );

			printf ( "<td colspan='4'>" );
			printf ( "Food ID&emsp;<input type='search' name='AddRecfoodID' id='AddFoodID' size='10'>" );
			printf ( "&emsp;<input type='button' name='lookupFood' value='?' onclick='javascript:LookupFood();'>" );

			printf ( "&emsp;Amount&emsp;<input type='search' name='AddRecfoodServings' size='6' maxlength='6'>" );
			printf ( "&emsp;<input type='submit' name='submitAddRecfood' value='Add Food'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
			printf ( "</td></tr>\n" );

			if ( xrecipe.xrfood == 0 )
			{
				printf ( "<tr>\n" );
				printf ( "<td colspan='4'>\n" );
				printf ( "<input type='submit' name='submitCreateFood' value='Copy To Food List'>\n" );
				printf ( "</td>\n" );
				printf ( "</tr>\n" );
			}
			else
			{
				sprintf ( WhereClause, "Fid = %ld", xrecipe.xrfood );
				LoadFood ( WhereClause, &xfood, 0 );
				printf ( "<tr>\n" );
				printf ( "<td colspan='4'>\n" );
				if ( xfood.xinserted == CreateTimeStamp )
				{
					printf ( "Okay. Food ID %ld", xrecipe.xrfood );
				}
				else
				{
					printf ( "A food item has already been created from this recipe. Food ID %ld", xrecipe.xrfood );
				}
				printf ( "</td>\n" );
				printf ( "</tr>\n" );
			}

			break;
		default:
			printf ( "PaintScreen: Unknown run mode %d", RunMode );
			break;
	}
	printf ( "</td>\n" );
	printf ( "</tr>\n" );



	printf ( "</table>\n" );
}
