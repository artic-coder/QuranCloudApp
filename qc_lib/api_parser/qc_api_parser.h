#ifndef _QC_API_PARSER_H
#define _QC_API_PARSER_H

/*Include standard libraries.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
BISMILLAH-I-RAHMAAN-E-RAHEEM . IN THE NAME OF GOD MOST POWERFUL AND MERCIFUL.

BRIEF : QC-API-PARSER : Quran Cloud API Parser is JSON Parser for cloud based quran service at (https://alquran.cloud/api)
it is written for  language c/c++.It is specifically made for parsing JSON Data of Quran cloud format and provides efficient methods to
parse data from API easily and it works with all API(s) like Quran-API,Edition-API,Juz-API,Surah-API,Ayah-API,Search-API and more.

*****************************
*******Parser components.****
*****************************

1)Searching tokens --> use QC_SearchToken()  or QC_SearchTokens() methods.
2)Printing all tokens/Keys/Values --> use QC_PrintAllTokens(),QC_PrintAllKeys(),QC_PrintAllValues() methods.
3)Reading JSON file --> use QC_ReadJSON() method.

*****************************
*******API components.****
*****************************
1)Get aayah text and number --> use QC_API_GetAyahText(),QC_API_GetAyahNumber() methods..
2)Get surah name and number --> use QC_API_GetSurahName(),QC_API_GetSurahNumber() methods..
3)Get ruku/juz/manzil/sajda/hizb --> use relevant methods.
4)Get revelation type --> use QC_API_GetRevelationType() method.
5)Get page number --> use QC_API_GetPageNumber() method.
6)Get language of text --> use QC_API_GetLanguage() method.


NOTE : This is parser which works on JSON data and will not work on any other data format like XML,CSV etc.
AIM : The aim of this Parser is to make easy to parse QuranCloud API with ready-made code available with efficient methods that ease your most of the work.

DOCUMENTATION INFO :
All Public methods are well documented but private methods are not documented as it was not necessary to do so.

*****************************
*********FEATURES*********
*****************************
1)Light weight, quick and memory efficient Parser.
2)Search for all keys,values and other data easily.
3)Automatically detects all errors from JSON and API side.
4)Uses only one method in background to search,print and get data and tokens.
5)Wrapped all API-Methods to JSON-Parser for immense speed.
6)Works with all APIs of QuranCloud. including (Edition-API,Quran-API,Juz-API,Surah-API,Ayah-API,Search-API and more)
7)Portability to work on every major OS like Windows,Linux,Mac etc because it uses only standard libraries.

VERSION INFO :
QC-API-Parser Version : V 1.0

V 1.0 -> Dated : 10/02/2019
Written by Abdul HaseeB Mir (haseebmir.hm@gmail.com)
*/

/*Defining NULL constants.*/
#define NUL '\0'
#ifndef NIL
#define NIL 0
#endif // NIL

/*JSON Parser and API Errors.*/
enum ERROR_ENUMS {QC_SUCCESS,QC_INVALID_OBJECT,QC_INVALID_JSON,QC_INVALID_KEY,QC_INVALID_VALUE,QC_EMPTY_STRING,QC_HTTP_ERROR,QC_STATUS_ERROR};
static const char *ERROR_STRING[] = {"SUCCESS","INVALID_OBJECT","INVALID_JSON","INVALID_KEY","INVALID_VALUE","EMPTY_STRING","HTTP_ERROR","STATUS_ERROR"};

/*Search token enums */
enum TOK_ENUM {ALL_TOKENS = 1,ALL_KEYS = 2,ALL_VALUES = 3};
enum SURAH_TYPE {SURAH_ARABIC,SURAH_ENG_ARABIC,SURAH_ENGLISH};

/*API TOKENS*/
enum API_ENUM_PARSER {QC_TEXT,QC_SURAH_AR_NAME,QC_SURAH_AR_ENG_NAME,QC_SURAH_ENG_NAME,QC_REV_TYPE,
               QC_SURAH_NUM,QC_AYAH_NUM,QC_PAGE_NUM,QC_RUKU,QC_JUZ,QC_MANZIL,
               QC_SAJDA,QC_HIZB,QC_LANG
              };

static const char *api_parser_tokens[] =
{
    "text","name","englishName","englishNameTranslation",
    "revelationType","numberInSurah","numberOfAyahs","page",
    "ruku","juz","manzil","sajda","hizbQuarter","language"
};

/*PUBLIC-PARSER-METHODS*/
int QC_PrintAllTokens(const char *,int);
int QC_PrintAllKeys(const char *);
int QC_PrintAllValues(const char *);
int QC_SearchToken(const char *,const char *);
int QC_SearchTokens(const char *,const char **,size_t);
char* QC_ReadJSON(const char *);

/*PUBLIC-API-METHODS*/
int QC_API_GetAyahText(const char *);
int QC_API_GetSurahName(const char *,int);
int QC_API_GetSurahNumber(const char *);
int QC_API_GetAyahNumber(const char *);
int QC_API_GetRuku(const char *);
int QC_API_GetJuz(const char *);
int QC_API_GetManzil(const char *);
int QC_API_GetSajda(const char *);
int QC_API_GetHizb(const char *);
int QC_API_GetPageNumber(const char *);
int QC_API_GetRevelationType(const char *);
int QC_API_GetLanguage(const char *);

/*PRIVATE-METHODS*/
int JSON_Validator(const char *);
int JSON_Parser(const char *,const char **,size_t,bool,int);

#endif // _QC_API_PARSER_H
