/*----------------------------------------------------------------------------
	Program : Evaluate.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Command line program to compare member to their target.

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

#define		MAIN
#include	"Evaluate.h"

typedef struct
{
	char	Date[12];
	double	Calorie;
	double	Carb;
	double	Protein;
	double	Fat;
	double	Sodium;
	double	Fiber;
} RECORD;

#define		MAXDAYS		30
static	RECORD	Array[MAXDAYS];
static	int		Count = 0;

static	RECORD	Minimum;
static	RECORD	Maximum;
static	RECORD	Member;

int main ( int argc, char *argv[] )
{
//	int		rv;
	DBY_QUERY	*qry;
	int		SkipToday = 1;
	char	Fragment[128];
	DATEVAL	Today;
	int		ndx;
	double	DayFitness, TotalFitness;

	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	getargs ( argc, argv );

	Minimum.Calorie = Maximum.Calorie = xmember.xmcalorie;
	Minimum.Carb = Maximum.Carb = xmember.xmcarb;
	Minimum.Protein = Maximum.Protein = xmember.xmprotein;
	Minimum.Fat = Maximum.Fat = xmember.xmfat;
	Minimum.Sodium = Maximum.Sodium = xmember.xmsodium;
	Minimum.Fiber = Maximum.Fiber = xmember.xmfiber;

	CurrentDateval ( &Today );
	if ( SkipToday == 1 )
	{
		sprintf ( Fragment, " and Hdate != '%04d-%02d-%02d'", Today.year4, Today.month, Today.day );
	}
	else
	{
		Fragment[0] = '\0';
	}

	sprintf ( Statement, "select Hdate, sum(Fcalorie*HFserving), sum(Fcarb*HFserving), sum(Fprotein*HFserving), \
sum(Ffat*HFserving), sum(Fsodium*HFserving), sum(Ffiber*HFserving) \
from history, histfood, food where Hid = HFhist and Fid = HFfood \
and Hmember = %ld %s group by Hdate order by Hdate desc", xmember.xmid, Fragment );

	if (( qry = dbySelect ( "nutrition", &MySql, Statement, 0 )) == NULL )
	{
		printf ( "No history for member %ld\n", xmember.xmid );
		return ( 0 );
	}
	while (( qry->EachRow = mysql_fetch_row ( qry->Result )) != NULL )
	{
		if ( Count >= MAXDAYS )
		{
			break;
		}
		sprintf ( Array[Count].Date, "%s", qry->EachRow[0] );
		Array[Count].Calorie = nsAtof(qry->EachRow[1]);
		Array[Count].Carb    = nsAtof(qry->EachRow[2]);
		Array[Count].Protein = nsAtof(qry->EachRow[3]);
		Array[Count].Fat     = nsAtof(qry->EachRow[4]);
		Array[Count].Sodium  = nsAtof(qry->EachRow[5]);
		Array[Count].Fiber   = nsAtof(qry->EachRow[6]);

		printf ( "%s %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n",	
			 Array[Count].Date, 
			 Array[Count].Calorie, Array[Count].Carb, Array[Count].Protein, 
			 Array[Count].Fat, Array[Count].Sodium, Array[Count].Fiber );

		if ( Minimum.Calorie > Array[Count].Calorie )
		{
			Minimum.Calorie = Array[Count].Calorie;
		}
		if ( Maximum.Calorie < Array[Count].Calorie )
		{
			Maximum.Calorie = Array[Count].Calorie;
		}

		if ( Minimum.Carb > Array[Count].Carb )
		{
			Minimum.Carb = Array[Count].Carb;
		}
		if ( Maximum.Carb < Array[Count].Carb )
		{
			Maximum.Carb = Array[Count].Carb;
		}

		if ( Minimum.Protein > Array[Count].Protein )
		{
			Minimum.Protein = Array[Count].Protein;
		}
		if ( Maximum.Protein < Array[Count].Protein )
		{
			Maximum.Protein = Array[Count].Protein;
		}

		if ( Minimum.Fat > Array[Count].Fat )
		{
			Minimum.Fat = Array[Count].Fat;
		}
		if ( Maximum.Fat < Array[Count].Fat )
		{
			Maximum.Fat = Array[Count].Fat;
		}

		if ( Minimum.Sodium > Array[Count].Sodium )
		{
			Minimum.Sodium = Array[Count].Sodium;
		}
		if ( Maximum.Sodium < Array[Count].Sodium )
		{
			Maximum.Sodium = Array[Count].Sodium;
		}

		if ( Minimum.Fiber > Array[Count].Fiber )
		{
			Minimum.Fiber = Array[Count].Fiber;
		}
		if ( Maximum.Fiber < Array[Count].Fiber )
		{
			Maximum.Fiber = Array[Count].Fiber;
		}

		Count++;

	}
	
	dbyClose ( &MySql );

	printf ( "Normalized\n" );

	Member.Calorie = (xmember.xmcalorie - Minimum.Calorie) / (Maximum.Calorie -  Minimum.Calorie);
	Member.Carb    = (xmember.xmcarb    - Minimum.Carb   ) / (Maximum.Carb    -  Minimum.Carb   );
	Member.Protein = (xmember.xmprotein - Minimum.Protein) / (Maximum.Protein -  Minimum.Protein);
	Member.Fat     = (xmember.xmfat     - Minimum.Fat    ) / (Maximum.Fat     -  Minimum.Fat    );
	Member.Sodium  = (xmember.xmsodium  - Minimum.Sodium ) / (Maximum.Sodium  -  Minimum.Sodium );
	Member.Fiber   = (xmember.xmfiber   - Minimum.Fiber  ) / (Maximum.Fiber   -  Minimum.Fiber  );

	printf ( "%-10.10s %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n",	
		 xmember.xmname, 
		 Member.Calorie, Member.Carb, Member.Protein, 
		 Member.Fat, Member.Sodium, Member.Fiber );

	for ( ndx = 0; ndx < Count; ndx++ )
	{
		Array[ndx].Calorie = (Array[ndx].Calorie - Minimum.Calorie) / (Maximum.Calorie -  Minimum.Calorie);
		Array[ndx].Carb    = (Array[ndx].Carb    - Minimum.Carb   ) / (Maximum.Carb    -  Minimum.Carb   );
		Array[ndx].Protein = (Array[ndx].Protein - Minimum.Protein) / (Maximum.Protein -  Minimum.Protein);
		Array[ndx].Fat     = (Array[ndx].Fat     - Minimum.Fat    ) / (Maximum.Fat     -  Minimum.Fat    );
		Array[ndx].Sodium  = (Array[ndx].Sodium  - Minimum.Sodium ) / (Maximum.Sodium  -  Minimum.Sodium );
		Array[ndx].Fiber   = (Array[ndx].Fiber   - Minimum.Fiber  ) / (Maximum.Fiber   -  Minimum.Fiber  );

	}

	TotalFitness = 0.0;

	for ( ndx = 0; ndx < Count; ndx++ )
	{
		DayFitness  = (Array[ndx].Calorie - Member.Calorie) * (Array[ndx].Calorie - Member.Calorie);
		DayFitness += (Array[ndx].Carb    - Member.Carb   ) * (Array[ndx].Carb    - Member.Carb   );
		DayFitness += (Array[ndx].Protein - Member.Protein) * (Array[ndx].Protein - Member.Protein);
		DayFitness += (Array[ndx].Fat     - Member.Fat    ) * (Array[ndx].Fat     - Member.Fat    );
		DayFitness += (Array[ndx].Sodium  - Member.Sodium ) * (Array[ndx].Sodium  - Member.Sodium );
		DayFitness += (Array[ndx].Fiber   - Member.Fiber  ) * (Array[ndx].Fiber   - Member.Fiber  );

		DayFitness /= 6.0;
		TotalFitness += DayFitness;

		printf ( "%s %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\n",	
			 Array[ndx].Date, 
			 Array[ndx].Calorie, Array[ndx].Carb, Array[ndx].Protein, 
			 Array[ndx].Fat, Array[ndx].Sodium, Array[ndx].Fiber,
			 1.0 - DayFitness );
	}

	printf ( "Average Fitness %9.4f\n", 1.0 - (TotalFitness / (double) Count) );

	return ( 0 );
}
