/*----------------------------------------------------------------------------
	Program : EachFood.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Standardize food serving and update.
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

#include	"FixFood.h"

int EachFood ( XFOOD *ptr )
{
	char	UpperServing[sizeof(xfood.xfserving)+1];
	char	*cp;

	VisitCount++;

	/*----------------------------------------------------------
		print food name and existing macro values
	----------------------------------------------------------*/
	if ( Debug )
	{
		printf ( "%5ld %-40.40s %-10.10s\n", ptr->xfid, ptr->xfname, ptr->xfserving );
	}

	sprintf ( UpperServing, "%s", nsStrToUpcase(ptr->xfserving) );


/*---------------------------------------------------------------------------
 5280 Sugar Substitute Saccharin Liquid        1 teaspoon
  5281 Sugar Substitute Stevia Liquid           1 teaspoon
  AWS </home/tms/src/Nutrition/FixFood>$ go | grep tablesp 
    369 Cake Batter Raw Chocolate                1 tablespo
	  370 Cake Batter Raw Not Chocolate            1 tablespo
	    428 Coconut Cream Cake Puerto Rican Style    1 tablespo
---------------------------------------------------------------------------*/
	if (( cp = nsStrnstr ( UpperServing, "TEASPOON", 8 )) != NULL )
	{
		sprintf ( cp, "TSPN" );
	}
	else if (( cp = nsStrnstr ( UpperServing, "TABLESPO", 8 )) != NULL )
	{
		sprintf ( cp, "TBSP" );
	}

	for ( int ndx = 0; ndx < nsStrlen(UpperServing); ndx++ )
	{
		if ( UpperServing[ndx] == '\'' )
		{
			UpperServing[ndx] = '.';
		}
		else if ( UpperServing[ndx] < 32 || UpperServing[ndx] > 127 )
		{
			UpperServing[ndx] = '.';
		}
	}

	if ( nsStrncmp ( UpperServing, "1 ", 2 ) == 0 )
	{
		sprintf ( Statement, "update food set Fserving = '%-.8s' where Fid = %ld", &UpperServing[2], ptr->xfid );
		if ( Debug )
		{
			printf ( "%s\n", Statement );
		}
	}
	else if ( nsStrcmp ( ptr->xfserving, UpperServing ) != 0 )
	{
		sprintf ( Statement, "update food set Fserving = '%-.10s' where Fid = %ld", UpperServing, ptr->xfid );
		if ( Debug )
		{
			printf ( "%s\n", Statement );
		}
	}
	else
	{
		return ( 0 );
	}

	if ( dbyUpdate ( "nutrition", &MySql, Statement, 0, LogFileName ) != 1 )
	{
		printf ( "FAILED: %s\n", Statement );
		ErrorCount++;
	}
	else
	{
		UpdateCount++;
	}

	return ( 0 );
}
