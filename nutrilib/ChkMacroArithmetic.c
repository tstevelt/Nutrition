/*----------------------------------------------------------------------------
	Program : ChkMacroArithmetic.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Check macro arithmetic against total calories, within Limit.
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

int ChkMacroArithmetic ( int Calorie, double Carb, double Protein, double Fat, double Limit )
{
	int		TotalCalorie;
	double	Percent;

	TotalCalorie = 4 * Carb + 4 * Protein + 9 * Fat;
	Percent = 100.0 * TotalCalorie / Calorie;
	// sprintf ( ErrorArray[ErrorCount++].Message,  "Macros/Calories %.1f%% ", Percent );
	if ( Percent > 100.0 + Limit || Percent < 100.0 - Limit )
	{
		sprintf ( ErrorArray[ErrorCount++].Message,  "Calories and Macros are out of balance" );
		return ( -1 );
	}
	return ( 0 );
}
