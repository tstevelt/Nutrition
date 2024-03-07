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

#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <libgen.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <sys/types.h>

#include	"shslib.h"
#include	"weblib.h"
#include	"webCookie.h"
#include	"dbylib.h"

#define		ROLE_MEMBER		'M'
#define		ROLE_ADMIN		'A'

#define		MEMBER
#define		FOOD
#define		HISTORY
#define		HISTFOOD
#define		RECIPE
#define		RECFOOD
#include	"filenutri.h"
#include	"nutrilib.h"

#define		MEMBER_COOKIE_NAME		"member"
#define		MEMBER_COOKIE_LIFE_TIME	(86400*30)
extern	char	SessionUnique[20];

TYPE	char	SessionFileName[256];

extern	XMEMBER		CookieMember;

#define		URL_NAME		"nutrition.silverhammersoftware.com"

#define		RW_DIRECTORY	"/var/local/webstate/nutrition"

#define		MAX_SHORT_STRING	256
#define		MAX_LONG_STRING		2048
#define		MAXPAGES			20

TYPE	char	Title[MAX_LONG_STRING];
TYPE	char	Footer[MAX_LONG_STRING];
TYPE	char	*Remote_Address;
TYPE	char	*ErrorClass;

typedef struct
{
	int		PageNumber;
	char	String[MAX_SHORT_STRING];
} CONTENT_RECORD;

TYPE	CONTENT_RECORD	MenuArray[MAXPAGES];
TYPE	int				MenuCount;
TYPE	int				MenuIndex;

TYPE	CONTENT_RECORD	PageArray[MAXPAGES];
TYPE	int				PageCount;
TYPE	int				PageIndex;


#define		MODE_UNKNOWN				101
#define		MODE_LOGIN					102
#define		MODE_SAVE_SIGNUP					103
#define		MODE_VERIFY					104
#define		MODE_CONTACT				105
#define		MODE_LOGOUT					106
#define		MODE_SAVE_PROFILE			107
#define		MODE_SEND_MESSAGE_TO_MEMBER	108
#define		MODE_FORGOT					109
#define		MODE_PAINT_PASSWORD			110
#define		MODE_SAVE_PASSWORD			111
#define		MODE_CHANGE_PASSWORD		112
#define		MODE_CHANGE_EMAIL			113
#define		MODE_PAINT_BLOG				114
#define		MODE_SAVE_BLOG				115
#define		MODE_SEND_EMAIL				116


/*----------------------------------------------------------
menu 1 Home
menu 2 About
menu 3 Edit Profile
menu 4 Admin
menu 5 Signup
menu 6 Login
menu 7 Logout
----------------------------------------------------------*/
#define	MENU_INDEX_HOME			1
#define	MENU_INDEX_ABOUT		2
#define	MENU_INDEX_PROFILE		3
#define	MENU_INDEX_ADMIN		4
#define	MENU_INDEX_SIGNUP		5
#define	MENU_INDEX_LOGIN		6
#define	MENU_INDEX_LOGOUT		7

TYPE	int		RunMode;

TYPE	DATEVAL	dvToday;
TYPE	char	*SignupName;
TYPE	char	*SignupEmail;
TYPE	char	*SignupPassword;
TYPE	char	*SignupBirthdate;
TYPE	char	SignupGender;
TYPE	short	SignupWeight;
TYPE	short	SignupHeight;
TYPE	short	SignupCalorie;
TYPE	short	SignupCarb;
TYPE	short	SignupProtein;
TYPE	short	SignupFat;
TYPE	short	SignupSodium;
TYPE	short	SignupFiber;
TYPE	char	SignupActivityLevel;
TYPE	char	SignupDiet;
TYPE	char	SignupAllowCookie;
TYPE	char	*ConfirmPassword;
TYPE	char	*ContactSubject;
TYPE	char	*ContactMessage;
TYPE	char	*ContactCaptcha;
TYPE	char	*EmailSubject;
TYPE	char	*EmailMessage;
TYPE	char	EmailPrivacy;
TYPE	long	VerifyID;
TYPE	char	*VerifyIPaddr;
TYPE	time_t	VerifyTime;
TYPE	char	*LoginEmail;
TYPE	char	*LoginPassword;
TYPE	char	LogoutSelect;
TYPE	char	*ForgotEmail;
TYPE	char	*ForgotString;
TYPE	long	FromMemberID;
TYPE	long	ToMemberID;

typedef struct
{
	long	DepartmentID;
	long	SubscribeID;
	char	Subscribe;
} SUBSCRIBE_RECORD;

#define		MAX_DEPARTMENTS		5
TYPE	SUBSCRIBE_RECORD		SubscribeArray[MAX_DEPARTMENTS];
TYPE	int						SubscribeCount;

#define		MAX_EMAIL		50
TYPE	long		EmailMembersArray[MAX_EMAIL];
TYPE	int			EmailMembersCount;

/*----------------------------------------------------------
	mysql and dbylib stuff
----------------------------------------------------------*/
TYPE  MYSQL   MySql;
TYPE	DBY_OPTIONS	DbyOptions;
TYPE	char		WhereClause[1024];
TYPE	char		OrderByClause[1024];

/*------------------------------
:.,$d
:r ! mkproto -p *.c
------------------------------*/

/* ChkInput.c */
void ChkInput ( void );

/* Forgot.c */
int Forgot ( void );

/* GetContents.c */
void GetContents ( int Index );

/* GetInput.c */
void GetInput ( void );

/* Login.c */
int Login ( void );

/* Logout.c */
int Logout ( void );

/* nutrition.c */
int main ( int argc , char *argv []);

/* PaintBottom.c */
void PaintBottom ( void );

/* PaintDemoMsg.c */
void PaintDemoMsg ( void );

/* PaintPassword.c */
void PaintPassword ( void );

/* PaintProfile.c */
void PaintProfile ( void );

/* PaintScreen.c */
void PaintScreen ( void );

/* PaintSignup.c */
void PaintSignup ( void );

/* PaintSpecial.c */
void PaintSpecial ( int FunctionCode );

/* PaintTop.c */
void PaintTop ( void );

/* PaintWelcome.c */
void PaintWelcome ( void );

/* SaveEmail.c */
int SaveEmail ( void );

/* SavePassword.c */
void SavePassword ( void );

/* SaveProfile.c */
void SaveProfile ( void );

/* SendEmail.c */
void SendEmail ( void );

/* Signup.c */
int Signup ( void );

/* TakeAction.c */
void TakeAction ( void );

/* Verify.c */
int Verify ( void );
