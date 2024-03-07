/*----------------------------------------------------------------------------
	Program : CreateFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Once recipe is complete, make a new food record from it.
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

#define		DEBUG
#undef		DEBUG

static		double	TotalRecipeCalorie;
static		double	TotalRecipeCarb;
static		double	TotalRecipeProtein;
static		double	TotalRecipeFat;
static		double	NewFoodCalorie;
static		double	NewFoodCarb;
static		double	NewFoodProtein;
static		double	NewFoodFat;

static		double	TotalRecipeSodium;
static		double	NewFoodSodium;
static		double	TotalRecipeFiber;
static		double	NewFoodFiber;
static		char	NewFoodGroup[sizeof(xfood.xfgroup)+1];
static		int		FoodNumber;

static int EachRecfood ( XRECFOOD *ptr )
{
	char	FoodWhereClause[128];

	sprintf ( FoodWhereClause, "Fid = %ld", ptr->xrffood );
	LoadFood ( FoodWhereClause, &xfood, 0 );

	TotalRecipeCalorie += xfood.xfcalorie * ptr->xrfamount;
	TotalRecipeCarb    += xfood.xfcarb    * ptr->xrfamount;
	TotalRecipeProtein += xfood.xfprotein * ptr->xrfamount;
	TotalRecipeFat     += xfood.xffat     * ptr->xrfamount;
	TotalRecipeSodium  += xfood.xfsodium  * ptr->xrfamount;
	TotalRecipeFiber   += xfood.xffiber   * ptr->xrfamount;
	
	FoodNumber++;
	if ( FoodNumber == 1 )
	{
		sprintf ( NewFoodGroup, "%s", xfood.xfgroup );
	}

	return ( 0 );
}

void CreateFood ()
{
	int		rv;

	CreateTimeStamp = time ( NULL );

	TotalRecipeCalorie = TotalRecipeCarb = TotalRecipeProtein = TotalRecipeFat = TotalRecipeSodium = TotalRecipeFiber = 0.0;

	sprintf ( WhereClause, "Rid = %ld", RecipeID );
	LoadRecipe ( WhereClause, &xrecipe, 0 );

	FoodNumber = 0;
	sprintf ( WhereClause, "RFrecipe = %ld", RecipeID );
	LoadRecfoodCB ( WhereClause, NULL, &xrecfood, EachRecfood, 0 );

	if ( FoodNumber == 0 )
	{
		printf ( "Recipe does not have any ingredients" );
		return;
	}

#ifdef DEBUG
	printf ( "TotalRecipeCalorie %.2f TotalRecipeCarb %.2f TotalRecipeProtein %.2f TotalRecipeFat %.2f<br>\n",
		TotalRecipeCalorie, TotalRecipeCarb, TotalRecipeProtein, TotalRecipeFat );
#endif

	NewFoodCalorie = TotalRecipeCalorie / xrecipe.xrserving;
	NewFoodCarb    = TotalRecipeCarb / xrecipe.xrserving;
	NewFoodProtein = TotalRecipeProtein / xrecipe.xrserving;
	NewFoodFat     = TotalRecipeFat / xrecipe.xrserving;
	NewFoodSodium  = TotalRecipeSodium  / xrecipe.xrserving;
	NewFoodFiber   = TotalRecipeFiber   / xrecipe.xrserving;

#ifdef DEBUG
	printf ( "NewFoodCalorie %.2f NewFoodCarb %.2f NewFoodProtein %.2f NewFoodFat %.2f<br>\n",
		NewFoodCalorie, NewFoodCarb, NewFoodProtein, NewFoodFat );
#endif

	sprintf ( Statement, 
"insert into food ( Fname, Frecipe, Fcalorie, Fcarb, Fprotein, Ffat, Fsodium, Ffiber, Fgroup, Fstatus, inserted, Fmember ) \
 values ( '%s', %ld, %.0f, %.0f, %.0f, %.0f, %.0f, %.2f, '%s', 'A', %ld, %ld )",
	xrecipe.xrdescr,
	RecipeID,
	NewFoodCalorie,
	NewFoodCarb,
	NewFoodProtein,
	NewFoodFat,
	NewFoodSodium,
	NewFoodFiber,
	NewFoodGroup,
	CreateTimeStamp,
	xrecipe.xrmember );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif
	
	if (( rv = dbyInsert ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "Could not insert food record<br>\n" );
		return;
	}

	sprintf ( WhereClause, "inserted = %ld", CreateTimeStamp );
	if (( rv = LoadFood ( WhereClause, &xfood, 0 )) != 1 )
	{
		printf ( "Could not load new food<br>\n" );
		return;
	}

	sprintf ( Statement, "update recipe set Rfood = %ld where Rid = %ld", xfood.xfid, RecipeID );

#ifdef DEBUG
	printf ( "%s<br>\n", Statement );
#endif

	if (( rv = dbyUpdate ( "nutrition", &MySql, Statement, 0, LogFileName )) != 1 )
	{
		printf ( "Could not update recipe<br>\n" );
		return;
	}

}
