/*----------------------------------------------------------------------------
	Program : LoadHistfoodCB.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load <table> record into buffer, with CallBack function
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

static  char    Statement[MAXSTATEMENT];

int LoadHistfoodCB ( char * WhereClause, char * OrderByClause, XHISTFOOD *ptrHistfood, int (*CallBack)(), int Verbose )
{
	static	DBY_QUERY     *qryHistfood;

	/*----------------------------------------------------------
		select standard field list by given where clause
	----------------------------------------------------------*/
	snprintf ( Statement, sizeof(Statement),
		"select %s from histfood", FIELDS_HISTFOOD );

	if ( WhereClause != NULL && nsStrlen ( WhereClause ) > 1 && nsStrcmp ( WhereClause, "all" ) != 0 )
	{
		strcat ( Statement, " where " );
		strcat ( Statement, WhereClause );
	}

	if ( OrderByClause != NULL && nsStrlen ( OrderByClause ) > 1 )
	{
		strcat ( Statement, " order by " );
		strcat ( Statement, OrderByClause );
	}

	qryHistfood = dbySelect ( "LoadHistfood", &MySql, Statement, LogFileName );
	if ( qryHistfood == (DBY_QUERY *) 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadHistfood select returned NULL." );
		}
		return ( -1 );
	}
	else if ( qryHistfood->NumRows == 0 )
	{
		if ( Verbose )
		{
			SafeError ( COLOR_ERROR, "LoadHistfood select returned zero rows." );
		}
		return ( 0 );
	}
	else 
	{
		while (( qryHistfood->EachRow = mysql_fetch_row ( qryHistfood->Result )) != NULL )
		{

#ifdef STRUCTURE
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `histfood` (
  `HFhist` int(11) unsigned NOT NULL,
  `HFfood` int(11) unsigned NOT NULL,
  `HFserving` int(11) NOT NULL DEFAULT 1,
  KEY `HFhist` (`HFhist`),
  KEY `HFfood` (`HFfood`),
  CONSTRAINT `histfood_ibfk_1` FOREIGN KEY (`HFhist`) REFERENCES `history` (`Hid`) ON DELETE CASCADE,
  CONSTRAINT `histfood_ibfk_2` FOREIGN KEY (`HFfood`) REFERENCES `food` (`Fid`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;
#endif

			ptrHistfood->xhfhist   =  nsAtol( qryHistfood->EachRow[0] );
			ptrHistfood->xhffood   =  nsAtol( qryHistfood->EachRow[1] );
			ptrHistfood->xhfserving  =  nsAtof( qryHistfood->EachRow[2] );

			if ( CallBack != NULL )
			{
				if ( CallBack ( ptrHistfood ) != 0 )
				{
					break;
				}
			}
		}
	}

	return ( qryHistfood->NumRows );
}
