/*----------------------------------------------------------------------------
	Program : Lookup.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Lookup food by selected criteria (string fields only)
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

static XFOOD LookupFood;

static int MyEachFood ( XFOOD *ptrFood )
{
	static int firstpass = 1;

	if ( firstpass )
	{
		firstpass = 0;

		printf ( "<table class='AppWide'>\n" );
		printf ( "<tr>\n" );

		printf ( "<td>ID</td>\n" );
printf ( "<td>Name</td>\n" );
printf ( "<td>Serving</td>\n" );
printf ( "<td>Calorie</td>\n" );
printf ( "<td>Protein</td>\n" );

		printf ( "</tr>\n" );
	}

	printf ( "<tr>\n" );
	printf ( "<td>" );
printf ( "<a href='EnterFood.cgi?submitLoad=load&field_fid=%ld'>%ld</a>", ptrFood->xfid, ptrFood->xfid );
printf ( "</td>\n" );
printf ( "<td>%s</td>\n", ptrFood->xfname );
printf ( "<td>%s</td>\n", ptrFood->xfserving );
printf ( "<td>%.2f</td>\n", ptrFood->xfcalorie );
printf ( "<td>%.2f</td>\n", ptrFood->xfprotein );
	printf ( "</tr>\n" );

	return ( 0 );
}

int Lookup ()
{
	int		ndx, rv;
	int		xo;
	char	Fragment[128];

	memset ( WhereClause, '\0', sizeof(WhereClause) );

	for ( ndx = 0, xo = 0; ndx < FieldCount; ndx++ )
	{
		if ( FieldArray[ndx].keyfield )
		{
			continue;
		}

		if ( lastchr ( FieldArray[ndx].buffer, FieldArray[ndx].length ) > 0 )
		{
			sprintf ( Fragment, "%s like '%%%s%%'", FieldArray[ndx].name,  FieldArray[ndx].buffer );

			if ( xo )
			{
				nsStrcat ( WhereClause, " and " );
			}
			nsStrcat ( WhereClause, Fragment );
			xo++;
		}
	}

	rv = LoadFoodCB ( WhereClause, "Fname", &LookupFood, (int(*)()) MyEachFood, 1 );

    if ( rv < 0 )
    {
        SaveError ( "Oops!" );
    }
    else if ( rv == 0 )
    {
        SaveError ( "Nothing matches search criteria entered." );
    }

    return ( rv );
}
