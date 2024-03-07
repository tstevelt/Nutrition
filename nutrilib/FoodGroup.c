/*----------------------------------------------------------------------------
	Program : FoodGroup.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint food group select
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

static char *FoodGroupArray [] =
{	"American Indian",
	"Baked Foods",
	"Beans and Lentil",
	"Beverages",
	"Breakfast Cereal",
	"Dairy and Egg",
	"Fast Foods",
	"Fats and Oils",
	"Fish",
	"Fruits",
	"Grains and Pasta",
	"Meats",
	"Nuts and Seeds",
	"Prepared Meals",
	"Restaurant Foods",
	"Snacks",
	"Soups and Sauces",
	"Spices and Herbs",
	"Sweets",
	"Vegetables"
};

static int FoodGroupCount = sizeof(FoodGroupArray) / sizeof(char *);

void PaintFoodGroupSelect ( char *CurrentFoodGroup )
{
	int		xf;

	printf ( "<select name='FoodGroup'>\n" );
	printf ( "<option value='?'>-- select --</option>\n" );
	for ( xf = 0; xf < FoodGroupCount; xf++ )
	{
		printf ( "<option%s>%s</option>\n", 
			nsStrcmp(FoodGroupArray[xf],CurrentFoodGroup) == 0 ? " selected" : "",
			FoodGroupArray[xf] );
	}

	printf ( "</select>\n" );
}
