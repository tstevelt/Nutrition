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
#include	<libgen.h>		// for basename()

#include	"shslib.h"
#include	"weblib.h"
#include	"webCookie.h"
#include	"dbylib.h"

#define		MEMBER
#define		FOOD
#define		HISTORY
#define		HISTFOOD
#define		RECIPE
#define		RECFOOD
#include	"filenutri.h"
#include	"nutrilib.h"

#define	SAFETY_ON_DELETE
#ifdef SAFETY_ON_DELETE
TYPE	int		HiddenSafety;
TYPE	int		AnswerSafety;
#endif

extern	char	SessionUnique[20];
extern	XMEMBER		CookieMember;

TYPE	long	MemberID;
TYPE	long	RecipeID;
TYPE	char	MealDescr;
TYPE	long	FoodID;
TYPE	double	FoodServings;
TYPE	char	CopyDayDate[12];
TYPE	char	CopyMealDate[12];
TYPE	char	CopyMealDescr;
TYPE	double	TotalCalorie;
TYPE	double	TotalCarb;
TYPE	double	TotalFat;
TYPE	double	TotalProtein;
TYPE	double	TotalSodium;
TYPE	double	TotalFiber;
TYPE	time_t	CreateTimeStamp;

TYPE	int		RunMode;
#define		MODE_START			11
#define		MODE_FOUND			12
#define		MODE_LOOKUP_RECIPE	13
#define		MODE_INSERT_RECIPE	14
#define		MODE_UPDATE_RECIPE	15
#define		MODE_DELETE_RECIPE	16
#define		MODE_ADD_RECFOOD	17
#define		MODE_DELETE_RECFOOD	18
#define		MODE_CREATE_FOOD	19
#define		MODE_QUIT			20

#define		COLUMNS		4

/*----------------------------------------------------------
	mysql and dbylib stuff
----------------------------------------------------------*/
TYPE  MYSQL   MySql;
TYPE	DBY_OPTIONS	DbyOptions;
TYPE	char		Statement[2048];
TYPE	char		WhereClause[1024];
TYPE	char		OrderByClause[1024];

typedef struct
{
	long	HistID;
	long	FoodID;
} DELETE_RECORD;

#define		MAXDELETE		50
TYPE	DELETE_RECORD	DeleteArray[MAXDELETE];
TYPE	int				DeleteCount;


/*----------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------*/

/* CreateFood.c */
void CreateFood ( void );

/* AddRecfood.c */
void AddRecfood ( void );

/* AddRecipe.c */
void AddRecipe ( void );

/* CalcTotals.c */
void CalcTotals ( void );

/* ChkInput.c */
void ChkInput ( void );

/* CopyDay.c */
void CopyDay ( void );

/* CopyMeal.c */
void CopyMeal ( int Verbose );

/* DeleteRecfood.c */
void DeleteRecfood ( void );

/* DeleteRecipe.c */
int DeleteRecipe ( void );

/* EnterRecipe.c */
int main ( int argc , char *argv []);

/* FindRecipe.c */
void FindRecipe ( void );

/* GetInput.c */
void GetInput ( void );

/* PaintMeal.c */
void PaintMeal ( char *MealDescr );

/* PaintScreen.c */
void PaintScreen ( void );

/* PaintTop.c */
void PaintTop ( int Stage );

/* TakeAction.c */
void TakeAction ( void );

/* UpdateRecipe.c */
void UpdateRecipe ( void );
