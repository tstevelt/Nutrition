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
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netinet/tcp.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<signal.h>
#include	<time.h>
#include	<errno.h>

#ifdef	APPLE
#include   <mysql.h>
#include   <errmsg.h>
#else
#include   <mysql/mysql.h>
#include   <mysql/errmsg.h>
#endif

#include	"shslib.h"
#include	"weblib.h"
#include	"webCookie.h"
#include	"dbylib.h"
#include	"rptlib.h"

#define		MEMBER
#define		FOOD
#define		HISTORY
#define		HISTFOOD
#define		RECIPE
#define		RECFOOD
#include	"filenutri.h"
#include	"nutrilib.h"

extern	XMEMBER		CookieMember;

#define		MODE_START			101
#define		MODE_RUN			102

#define		MODE_QUIT			199
TYPE	int		RunMode;

TYPE	int		FTD;
TYPE	char	FTD_Date[12];
TYPE	int		MinFoods;
TYPE	int		MaxFoods;
TYPE	char	Universe;
TYPE	int		Statistics;

TYPE	char	rptname[21];
//TYPE	char	title[51];

TYPE    char	Cmdline[2048];
TYPE	char	fnData[256];
TYPE	FILE	*fpData;
TYPE	char	fnBody[256];
TYPE	FILE	*fpBody;
TYPE	REPORT_OPTIONS		ReportOptions;

/*----------------------------------------------------------
    mysql and dbylib stuff
----------------------------------------------------------*/
TYPE  MYSQL   MySql;
TYPE    DBY_OPTIONS DbyOptions;
TYPE    char        Statement[2048];
TYPE    char        WhereClause[1024];
TYPE    char        OrderByClause[1024];

#define		 SaveError		printf 

typedef struct
{
	char	Date[12];
	char	Meal[11];
	int		SortField;
	double	Calorie;
	double	Carb;
	double	Protein;
	double	Fat;
	double	Sodium;
	double	Fiber;

	long	FoodID;
	double	FoodAmount;
	char	Serving[11];
	char	Name[41];
} RECORD;

#define		MAXFOODPERWEEK		7*4*20
TYPE	RECORD	Array[MAXFOODPERWEEK];
TYPE	int		Count;

/*----------------------------------------------------------
:.,$d
:r! mkproto -p *.c
----------------------------------------------------------*/

/* ChkInput.c */
int ChkInput ( void );

/* GetInput.c */
void GetInput ( void );

/* PaintScreen.c */
void PaintScreen ( void );

/* rptplan.c */
int main ( int argc , char *argv []);

/* sortdata.c */
void sortdata ( void );
