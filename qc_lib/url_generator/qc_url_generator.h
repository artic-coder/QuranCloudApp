#ifndef _QC_URL_GENERATOR_H
#define _QC_URL_GENERATOR_H

/*Include standard libraries.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
BISMILLAH-I-RAHMAAN-E-RAHEEM . IN THE NAME OF GOD MOST POWERFUL AND MERCIFUL.

BRIEF : QC-URL-GENERATOR : Quran Cloud API URL GENERATOR is URL generator for cloud based quran service at (https://alquran.cloud/api)
it is written for  language c/c++.It is specifically made for generating URL for Quran cloud format and provides efficient methods to
show URL from API easily and it works with all API(s) like Quran-API,Edition-API,Juz-API,Surah-API,Ayah-API,Search-API and more.

*****************************
*******URL components.****
*****************************
1)Generate Quran API URL --> use QC_GenerateQuranURL() method.
2)Generate Edition API URL --> use QC_GenerateEditionURL() method.
3)Generate Search API URL --> use QC_GenerateSearchURL() method.
4)Generate Surah/Ayah/Ruku API URL --> use QC_GenerateSurahURL(),QC_GenerateAyahURL(),QC_GenerateRukuURL() methods.
5)Generate Juz/Manzil/Hizb/Sajda/Page API URL --> use QC_GenerateJuzURL(),QC_GenerateManzilURL(),QC_GenerateHizbURL(),QC_GenerateSajdaURL(),QC_GeneratePageURL() methods.

NOTE : This is url generator which and does not connect to QuranCloud API to fetch data. Is uses EXTERNAL TOOL 'CURL' to show data.
AIM : The aim of this generator is to make easy to make applications for QuranCloud API with ready-made code available with efficient methods that ease your most of the work.

DOCUMENTATION INFO :
All Public methods are well documented but private methods are not documented as it was not necessary to do so.

*****************************
*********FEATURES*********
*****************************
1)Easy to use and sophisticated methods.
2)Wrapped most URL generation to common method  for immense speed.
3)Works with all APIs of QuranCloud. including (Edition-API,Quran-API,Juz-API,Surah-API,Ayah-API,Search-API and more)
4)Portability to work on every major OS like Windows,Linux,Mac etc because it uses only standard libraries.
5)Shows direct output using 'curl' tool. (Need to install first using 'sudo apt-get install curl.' command).

VERSION INFO :
QC-URL-GENERATOR Version : V 1.0

V 1.0 -> Dated : 12/02/2019
Written by Abdul HaseeB Mir (haseebmir.hm@gmail.com)
*/

/*Defining NULL constants.*/
#ifndef NIL
#define NIL 0
#endif // NIL

/*Base URL for QuranCloud API.*/
const char *base_url = "http://api.alquran.cloud/v1/";

/*PUBLIC-API-METHODS*/
char *QC_GenerateEditionURL(char*,char*,char*);
char *QC_GenerateQuranURL(char*);
char *QC_GenerateJuzURL(char *,char *,char*,char*);
char *QC_GenerateSurahURL(char*,char*,char*,char*);
char *QC_GenerateAyahURL(char*,char*,char*);
char *QC_GenerateSearchURL(char*,char*,char*);
char *QC_GenerateManzilURL(char *,char *,char*,char*);
char *QC_GenerateRukuURL(char *,char *,char*,char*);
char *QC_GeneratePageURL(char *,char *,char*,char*);
char *QC_GenerateHizbURL(char *,char *,char*,char*);
char *QC_GenerateSajdaURL(char*);

/*PRIVATE-METHODS*/
void AppendBaseAPI(char *,int);
char *GenerateCommonURL(char *,char*,char* ,char*,int);
void ShowCurl(const char *);
void SaveCurl(const char *url,const char*);

enum{MAX_URL = 0xFF};
enum API_ENUM_URL {API_EDITION,API_QURAN,API_JUZ,API_SURAH,API_AYAH,API_SEARCH,API_MANZIL,API_RUKU,API_PAGE,API_HIZB,API_SAJDA};
const char *api_url_tokens[] = {"edition","quran","juz","surah","ayah","search","manzil","ruku","page","hizbQuarter","sajda"};
#endif /*_QC_URL_GENERATOR_H*/
