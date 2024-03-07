/*----------------------------------------------------------------------------
	Program : FixFoodCSV.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Read input file, standardize, output to food.csv file
				Modify as needed to cleanup new lists of food from 
				external sites.

	Who		Date		Modification
	---------------------------------------------------------------------

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

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<stdint.h>
#include	<errno.h>
#include	"shslib.h"

#define	MAXTOK		15

static	FILE	*ifp;
static	FILE	*ofp;
static	char	xbuffer[1024];
static	char	*tokens[MAXTOK];
static	int		tokcnt;
static	int		lineno;
static	int		found;

static void WriteAsIs ()
{
	fprintf ( ofp, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.10s|%s\n",
		tokens[0],
		tokens[1],
		tokens[2],
		tokens[3],
		tokens[4],
		tokens[5],
		tokens[6],
		tokens[7],
		tokens[8],
		tokens[9],
		strlen(tokens[10]) ? tokens[10] : "each",
		tokens[11] );
}

// WriteNuumbers ( 1.0, tokens[10], Calorie, Carb, Protein, Fat, Sodium, Fiber, Weight );
static void WriteNuumbers ( double Factor, char *Serving, double Calorie, double Carb, double Protein, double Fat, double Sodium, double Fiber, double Weight )
{
	Calorie = Factor * Calorie * Weight / 100.0;
	Carb    = Factor * Carb    * Weight / 100.0;
	Protein = Factor * Protein * Weight / 100.0;
	Fat     = Factor * Fat     * Weight / 100.0;
	Sodium  = Factor * Sodium  * Weight / 100.0;
	Fiber   = Factor * Fiber   * Weight / 100.0;
	
	fprintf ( ofp, "%s|%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%s|%.10s|%s\n",
		tokens[0],
		tokens[1],
		tokens[2],
		Calorie,
		Carb,
		Protein,
		Fat,
		Sodium,
		Fiber,
		tokens[9],
		strlen(tokens[10]) ? tokens[10] : "each",
		tokens[11] );
}

int main ( int argc, char *argv[] )
{
	int		Length;
	double	Calorie, Carb, Protein, Fat, Sodium, Fiber, Weight;

	if (( ifp = fopen ( argv[1], "r" )) == NULL )
	{
		printf ( "Cannot open %s\n", argv[1] );
		exit ( 1 );
	}
	
	if (( ofp = fopen ( "food.csv", "w" )) == NULL )
	{
		printf ( "Cannot create food.csv\n" );
		exit ( 1 );
	}

	lineno = found = 0;
	while ( fgets ( xbuffer, sizeof(xbuffer), ifp ) != NULL )
	{
		if (( tokcnt = GetTokensD ( xbuffer, "|\n\r", tokens, MAXTOK )) < 12 )
		{
			continue;
		}

		lineno++;

		if ( lineno == 1 )
		{
			WriteAsIs ();
			continue;
		}
		
		if (( Length = atoi ( tokens[11] )) > 40 )
		{
			continue;
		}

		Calorie = atof(tokens[3]);
		Carb    = atof(tokens[4]);
		Protein = atof(tokens[5]);
		Fat     = atof(tokens[6]);
		Sodium  = atof(tokens[7]);
		Fiber   = atof(tokens[8]);
		Weight  = atof(tokens[9]);

/*---------------------------------------------------------------------------
==> MyFoodDataToLoad.csv <==
0  1    2          3        4   5       6   7      8     9      10      11
ID|name|FoodGroup|Calories|Carb|Protein|Fat|Sodium|Fiber|Weight|Serving|Length
168061|Acorn Stew (Apache)|American Indian|95|9.22|6.81|3.47|130|0.7|0||19
168992|Agave Cooked (Southwest)|American Indian|135|32|0.99|0.29|13|10.6|0||24
168993|Agave Dried (Southwest)|American Indian|341|81.98|1.71|0.69|14|15.6|0||23
---------------------------------------------------------------------------*/

		if ((( strncasecmp ( tokens[2], "Meats", 5 ) == 0 ) || ( strncasecmp ( tokens[2], "Fish", 4 ) == 0 )) && 
			( strncasecmp ( tokens[10], "1 oz",  4 ) == 0 ))
		{
			found++;

			WriteNuumbers ( 4.0, "4 OZ", Calorie, Carb, Protein, Fat, Sodium, Fiber, Weight );
		}
		else if ((( strncasecmp ( tokens[2], "Meats", 5 ) == 0 ) || ( strncasecmp ( tokens[2], "Fish", 4 ) == 0 )) && 
			     ( strncasecmp ( tokens[10], "3 oz",  4 ) == 0 ))
		{
			found++;

			WriteNuumbers ( 1.333, "4 OZ", Calorie, Carb, Protein, Fat, Sodium, Fiber, Weight );
		}
		else
		{
			WriteNuumbers ( 1.0, tokens[10], Calorie, Carb, Protein, Fat, Sodium, Fiber, Weight );
		}
	}

	fclose ( ifp );
	fclose ( ofp );

	printf ( "found %d\n", found );

	return ( 0 );
}
