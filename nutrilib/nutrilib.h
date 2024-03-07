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


#define		RW_DIRECTORY	"/var/local/webstate/nutrition"
#define		TEMPDIR			"/var/local/tmp"

#define		MEMBER
#define		FOOD
#define		HISTORY
#define		HISTFOOD
#define		RECIPE
#define		RECFOOD
#include	"filenutri.h"


#define		CSS_VERSION		"2023032601"
#define		DEMO_MEMBER		104


#ifdef MAIN
TYPE	char	*LogFileName = "/var/local/webstate/nutrition.log";
#else
TYPE	char	*LogFileName;
#endif

#define	ACTIVE_SEDENTARY	'1'
#define	ACTIVE_LOW			'2'
#define	ACTIVE_ACTIVE		'3'
#define	ACTIVE_HIGH			'4'

#define	DIET_STANDARD		'S'
#define	DIET_LOW_CARB		'L'
#define	DIET_MODERATE		'M'
#define	DIET_LOW_FAT		'F'
#define	DIET_PALEO			'P'
#define	DIET_CONLEY			'C'

#define		MINFOODS	3
#define		MAXFOODS	30

/*----------------------------
:.,$d
:r ! mkproto -p *.c
----------------------------*/

/* BlankRow.c */
void BlankRow ( char *Class , int Columns );

/* ChkMacroArithmetic.c */
int ChkMacroArithmetic ( int Calorie , double Carb , double Protein , double Fat , double Limit );

/* FoodGroup.c */
void PaintFoodGroupSelect ( char *CurrentFoodGroup );

/* LoadFood.c */
int LoadFood ( char *WhereClause , XFOOD *ptrFood , int PrintErrors );

/* LoadFoodCB.c */
int LoadFoodCB ( char *WhereClause , char *OrderByClause , XFOOD *ptrFood , int (*CallBack )(), int Verbose );

/* LoadHistfood.c */
int LoadHistfood ( char *WhereClause , XHISTFOOD *ptrHistfood , int PrintErrors );

/* LoadHistfoodCB.c */
int LoadHistfoodCB ( char *WhereClause , char *OrderByClause , XHISTFOOD *ptrHistfood , int (*CallBack )(), int Verbose );

/* LoadHistory.c */
int LoadHistory ( char *WhereClause , XHISTORY *ptrHistory , int PrintErrors );

/* LoadHistoryCB.c */
int LoadHistoryCB ( char *WhereClause , char *OrderByClause , XHISTORY *ptrHistory , int (*CallBack )(), int Verbose );

/* LoadMember.c */
int LoadMember ( char *WhereClause , XMEMBER *ptrMember , int PrintErrors );

/* LoadMemberCB.c */
int LoadMemberCB ( char *WhereClause , char *OrderByClause , XMEMBER *ptrMember , int (*CallBack )(), int Verbose );

/* LoadRecfood.c */
int LoadRecfood ( char *WhereClause , XRECFOOD *ptrRecfood , int PrintErrors );

/* LoadRecfoodCB.c */
int LoadRecfoodCB ( char *WhereClause , char *OrderByClause , XRECFOOD *ptrRecfood , int (*CallBack )(), int Verbose );

/* LoadRecipe.c */
int LoadRecipe ( char *WhereClause , XRECIPE *ptrRecipe , int PrintErrors );

/* LoadRecipeCB.c */
int LoadRecipeCB ( char *WhereClause , char *OrderByClause , XRECIPE *ptrRecipe , int (*CallBack )(), int Verbose );

/* ReportUp.c */
void ReportUp ( char *Title , char *DbName , char *OnLoad , char ReportFormat , char *ReportName );

/* RuleRow.c */
void RuleRow ( int Columns );

/* SessionFuncs.c */
void WriteSession ( void );
void ReadSession ( void );
void RemoveSession ( void );

/* Spacer.c */
void Spacer ( int Number );

/* StartUp.c */
void StartUp ( char *Title , char *DbName , int InitDB , int PaintHeader , int WriteMeta , char *OnLoad , int Menu );
