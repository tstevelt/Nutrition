/*----------------------------------------------------------------------------
	Program : Logout.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Log out the user.
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

int Logout ()
{
	int			rv = 0;

	RemoveSession ();

	memset ( &CookieMember, '\0', sizeof(XMEMBER) );

	MenuIndex = MENU_INDEX_HOME;

	return ( rv );
}
