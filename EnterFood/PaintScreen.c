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

#include	"EnterFood.h"

void PaintScreen ()
{
	printf ( "<table class='AppMedium'>\n" );

	printf ( "<tr>\n" );
	printf ( "<th class='maint' colspan='2' align='center'>\n" );
	printf ( "Food Setup</th>\n" );
	printf ( "</tr>\n" );

	/*----------------------------------------------------------
		paint error / messages if any
	----------------------------------------------------------*/
	if ( ErrorCount > 0 )
	{
		for ( int xi = 0; xi < ErrorCount; xi++ )
		{
			printf ( "<tr>\n" );
			printf ( "<td colspan='2'>%s</td>\n", ErrorArray[xi].Message );
			printf ( "</tr>\n" );
		}
	}

	/*------------------------------------------------------------
	generated paint
------------------------------------------------------------*/

/*--------------------
	Row 1
--------------------*/
printf ( "<tr>\n" );
printf ( "<td width='25%%'>\n" );
printf ( "ID</td>\n" );
printf ( "<td width='74%%'>\n" );
if ( RunMode == MODE_START )
{
	printf ( "<input type='search' id='field_fid' name='field_fid' size='14' maxlength='11'>" );
	printf ( "&emsp;Leave blank to insert auto-generated ID.\n" );
}
else
{
	printf ( "%ld", xfood.xfid );
	printf ( "<input type='hidden' name='field_fid' value='%ld'>\n", xfood.xfid );
}
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 2
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Name</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fname' size='43' maxlength='40'" );
if ( nsStrlen ( xfood.xfname ) > 0 )
{
	printf ( " value='%s'", xfood.xfname );
}
printf ( ">\n" );
if ( RunMode == MODE_START )
{
	printf ( "&emsp;Enter something to Find.\n" );
}
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 3
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Serving</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fserving' size='13' maxlength='10'" );
if ( nsStrlen ( xfood.xfserving ) > 0 )
{
	printf ( " value='%s'", xfood.xfserving );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 4
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Calorie</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fcalorie' size='14' maxlength='11'" );
if ( xfood.xfcalorie != 0 )
{
	printf ( " value='%.2f'", xfood.xfcalorie );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 5
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Carbohydrate (grams)</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fcarb'" );
if (  xfood.xfcarb > 0 )
{
	printf ( " value='%.2f'", xfood.xfcarb );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 6
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Protein (grams)</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fprotein'" );
if ( xfood.xfprotein > 0 )
{
	printf ( " value='%.2f'", xfood.xfprotein );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 7
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Fat (grams)</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_ffat'" );
if ( xfood.xffat > 0 )
{
	printf ( " value='%.2f'", xfood.xffat );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 8
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Sodium (mg)</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_fsodium'" );
if ( xfood.xfsodium > 0 )
{
	printf ( " value='%.2f'", xfood.xfsodium );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 9
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Fiber (grams)</td>\n" );
printf ( "<td>\n" );
printf ( "<input type='search' name='field_ffiber'" );
if ( xfood.xffiber > 0 )
{
	printf ( " value='%.2f'", xfood.xffiber );
}
printf ( ">\n" );
printf ( "</td>\n" );
printf ( "</tr>\n" );

/*--------------------
	Row 10
--------------------*/
printf ( "<tr>\n" );
printf ( "<td>\n" );
printf ( "Food Group</td>\n" );
printf ( "<td>\n" );
PaintFoodGroupSelect ( xfood.xfgroup );
printf ( "</td>\n" );
printf ( "</tr>\n" );

	printf ( "<tr>\n" );
	printf ( "<td class='buttons' colspan='2'>\n" );
	switch ( RunMode )
	{
		case MODE_START:
			printf ( "<input type='button' id='buttonMenu' value='menu' onclick='javascript:window.close();'>\n" );
			printf ( "&emsp;<input type='reset'  value='reset'>\n" );
			printf ( "&emsp;<input type='submit' name='submitLookup' value='find'>\n" );
			printf ( "&emsp;<input type='submit' name='submitInsert' value='insert'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
			break;
		case MODE_FOUND:
			printf ( "<input type='button' id='buttonMenu' value='menu' onclick='javascript:window.close();'>\n" );
			printf ( "&emsp;<input type='reset'  value='reset'>\n" );
			printf ( "&emsp;<input type='submit' name='submitClear' value='clear'>\n" );
			printf ( "&emsp;<input type='submit' name='submitUpdate' value='update'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
#ifdef SAFETY_ON_DELETE
			seed_random_with_usec ();
			HiddenSafety = random_range ( 123, 987 );

			printf ( "<input type='hidden' name='HiddenSafety' value='%d'>\n", HiddenSafety );
			printf ( "&emsp;%d", HiddenSafety );
			printf ( "&nbsp;<input type='search' name='AnswerSafety' size='4'>\n" );
			printf ( "&nbsp;" );
#else
			printf ( "&emsp;" );
#endif
			printf ( "<input type='submit' name='submitDelete' value='delete'%s>\n", CookieMember.xmid == DEMO_MEMBER ? " disabled" : "" );
			break;
		default:
			printf ( "Unknown run mode %d", RunMode );
			break;
	}
	printf ( "</td>\n" );
	printf ( "</tr>\n" );
	printf ( "</table>\n" );
}
