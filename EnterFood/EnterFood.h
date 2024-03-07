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

#define	SAFETY_ON_DELETE

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
#define		MODE_LOAD			102
#define		MODE_LOOKUP			103
#define		MODE_INSERT			104
#define		MODE_FOUND			105
#define		MODE_UPDATE			106
#define		MODE_DELETE			107
#define		MODE_CLEAR			199
TYPE	int		RunMode;

TYPE	COOKIE_RECORD	*AcctCookie;
#ifdef SAFETY_ON_DELETE
TYPE	int		HiddenSafety;
TYPE	int		AnswerSafety;
#endif

#ifdef MAIN
FIELD_RECORD	FieldArray [] = 
{
/*------------------------------------------------------------
	generated field array
------------------------------------------------------------*/
{ 1, 1, 5, (char *)&xfood.xfid, sizeof(xfood.xfid), "Fid", "Fid",  },
{ 1, 0, 2, xfood.xfname, sizeof(xfood.xfname), "Fname", "Fname",  },
{ 1, 0, 2, xfood.xfserving, sizeof(xfood.xfserving), "Fserving", "Fserving",  },
{ 0, 0, 7, (char *)&xfood.xfcalorie, sizeof(xfood.xfcalorie), "Fcalorie", "Fcalorie",  },
{ 0, 0, 7, (char *)&xfood.xfcarb, sizeof(xfood.xfcarb), "Fcarb", "Fcarb",  },
{ 0, 0, 7, (char *)&xfood.xfprotein, sizeof(xfood.xfprotein), "Fprotein", "Fprotein",  },
{ 0, 0, 7, (char *)&xfood.xffat, sizeof(xfood.xffat), "Ffat", "Ffat",  },
{ 0, 0, 5, (char *)&xfood.xinserted, sizeof(xfood.xinserted), "inserted", "inserted",  },
{ 0, 0, 5, (char *)&xfood.xfrecipe, sizeof(xfood.xfrecipe), "Frecipe", "Frecipe",  },
{ 0, 0, 7, (char *)&xfood.xfsodium, sizeof(xfood.xfsodium), "Fsodium", "Fsodium",  },
{ 0, 0, 7, (char *)&xfood.xffiber, sizeof(xfood.xffiber), "Ffiber", "Ffiber",  },
{ 1, 0, 5, (char *)&xfood.xfmember, sizeof(xfood.xfmember), "Fmember", "Fmember",  },
};
int		FieldCount = sizeof(FieldArray)/sizeof(FIELD_RECORD);
FK_RECORD		FkArray [] =
{
	{ "T_child_table", "T_child_field", "T_english" }
};
int		FkCount = sizeof(FkArray)/sizeof(FK_RECORD);
#else
extern	FIELD_RECORD	FieldArray [];
extern	int				FieldCount;
extern	FK_RECORD		FkArray [];
extern	int				FkCount;
#endif

/*----------------------------------------------------------
	mysql and dbylib stuff
----------------------------------------------------------*/
TYPE  MYSQL   MySql;
TYPE	DBY_OPTIONS	DbyOptions;
TYPE	char		Statement[2048];
TYPE	char		StatementOne[2048];
TYPE	char		WhereClause[1024];
TYPE	char		OrderByClause[1024];

/*----------------------------------------------------------
	hacks
----------------------------------------------------------*/
TYPE	char	msgbuf[256];

/*----------------------------------------------------------
:.,d
:r! mkproto -p *.c
----------------------------------------------------------*/
/* EnterFood.c */

/* ChkInput.c */
int ChkInput ( void );

/* Delete.c */
int Delete ( void );

/* EnterFood.c */
void ErrorSysLoaded ( char *FunctionName );
int main ( int argc , char *argv []);

/* GetInput.c */
void GetInput ( void );

/* Insert.c */
void Insert ( void );

/* Load.c */
int Load ( void );

/* Lookup.c */
int Lookup ( void );

/* PaintScreen.c */
void PaintScreen ( void );

/* PaintTop.c */
void PaintTop ( int Stage );

/* Update.c */
void Update ( void );
int main ( int argc , char *argv []);

/* ChkInput.c */
int ChkInput ( void );

/* Delete.c */
int Delete ( void );

/* Load.c */
int Load ( void );

/* Lookup.c */
int Lookup ( void );

/* GetInput.c */
void GetInput ( void );

/* Insert.c */
void Insert ( void );

/* PaintScreen.c */
void PaintScreen ( void );

/* Update.c */
void Update ( void );
