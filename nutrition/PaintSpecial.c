/*----------------------------------------------------------------------------
	Program : PaintSpecial.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Content Management System special functions
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

#include	"nutrition.h"

void PaintSpecial ( int FunctionCode )
{
	switch ( FunctionCode )
	{
		case 1:
			if ( CookieMember.xmid == 0 )
			{
				PaintDemoMsg ();
			}
			else
			{
				PaintWelcome ();
			}
			break;

		case 5:
			PaintSignup ();
			break;

		case 3:
			PaintProfile ();
			break;

		default:
			printf ( "Unknown function code %d<br>\n", FunctionCode );
			break;
	}
}
