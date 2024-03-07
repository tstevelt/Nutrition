/*--------------------------------------------------------
	filenutri.h for schema nutrition.schema
--------------------------------------------------------*/
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
#ifndef FILENUTRI_H
#define FILENUTRI_H

#ifndef TYPE
#ifdef MAIN
#define  TYPE   /* */
#else
#define  TYPE   extern
#endif
#endif

#ifdef FOOD
#define TABLE_food 1
typedef struct
{
	unsigned long	xfid;
	char 	xfname[41];
	char 	xfserving[11];
	double	xfcalorie;
	double	xfcarb;
	double	xfprotein;
	double	xffat;
	double	xfsodium;
	double	xffiber;
	long	xinserted;
	long	xfrecipe;
	unsigned long	xfmember;
	char 	xfgroup[17];
	char 	xfstatus[2];
} XFOOD;
TYPE XFOOD xfood;
#define FIELDS_FOOD  "Fid,Fname,Fserving,Fcalorie,Fcarb,Fprotein,Ffat,Fsodium,Ffiber,inserted,Frecipe,Fmember,Fgroup,Fstatus"
#endif

#ifdef HISTFOOD
#define TABLE_histfood 2
typedef struct
{
	unsigned long	xhfhist;
	unsigned long	xhffood;
	double	xhfserving;
} XHISTFOOD;
TYPE XHISTFOOD xhistfood;
#define FIELDS_HISTFOOD  "HFhist,HFfood,HFserving"
#endif

#ifdef HISTORY
#define TABLE_history 3
typedef struct
{
	unsigned long	xhid;
	unsigned long	xhmember;
	char 	xhdescr[11];
	char 	xhdate[12];
	long	xinserted;
} XHISTORY;
TYPE XHISTORY xhistory;
#define FIELDS_HISTORY  "Hid,Hmember,Hdescr,Hdate,inserted"
#endif

#ifdef MEMBER
#define TABLE_member 4
typedef struct
{
	unsigned long	xmid;
	char 	xmname[31];
	char 	xmpassword[43];
	char 	xmgender[2];
	char 	xmbirthdate[12];
	unsigned short	xmweight;
	char 	xmipaddr[17];
	unsigned short	xmcalorie;
	unsigned short	xmcarb;
	unsigned short	xmprotein;
	unsigned short	xmfat;
	char 	xmstatus[2];
	char 	xmrole[2];
	char 	xmemail[81];
	unsigned short	xmheight;
	char 	xmactive[2];
	char 	xmdiet[2];
	long	xinserted;
	unsigned short	xmsodium;
	unsigned short	xmfiber;
} XMEMBER;
TYPE XMEMBER xmember;
#define FIELDS_MEMBER  "Mid,Mname,Mpassword,Mgender,Mbirthdate,Mweight,Mipaddr,Mcalorie,Mcarb,Mprotein,Mfat,Mstatus,Mrole,Memail,Mheight,Mactive,Mdiet,inserted,Msodium,Mfiber"
#endif

#ifdef RECFOOD
#define TABLE_recfood 5
typedef struct
{
	unsigned long	xrfrecipe;
	unsigned long	xrffood;
	double	xrfamount;
} XRECFOOD;
TYPE XRECFOOD xrecfood;
#define FIELDS_RECFOOD  "RFrecipe,RFfood,RFamount"
#endif

#ifdef RECIPE
#define TABLE_recipe 6
typedef struct
{
	unsigned long	xrid;
	char 	xrdescr[41];
	unsigned short	xrserving;
	unsigned long	xrfood;
	long	xinserted;
	unsigned long	xrmember;
} XRECIPE;
TYPE XRECIPE xrecipe;
#define FIELDS_RECIPE  "Rid,Rdescr,Rserving,Rfood,inserted,Rmember"
#endif

#endif
