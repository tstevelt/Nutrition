/*----------------------------------------------------------------------------
	Program : PaintDemoMsg.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Paint message to tell people they can login as a demo user.
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

void PaintDemoMsg ()
{
	printf ( "<h3>Demonstrator data is available</h3>\n" );
	printf ( "Login with name 'demo' and password 'demo' in order to see everything" );
}
