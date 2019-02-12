#ifndef _QC_API_CONNECT_H
#define _QC_API_CONNECT_H

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#define OS_TYPE_WIN
#else
#define OS_TYPE_OTHER
#endif // defined

#ifdef OS_TYPE_WIN
#include<windows.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif // OS_TYPE_WIN

/*
BISMILLAH-I-RAHMAAN-E-RAHEEM . IN THE NAME OF GOD MOST POWERFUL AND MERCIFUL.

BRIEF : QC-API-CONNECT : Quran Cloud API connector connects with cloud based quran service at (https://alquran.cloud/api)
it is written for  language c/c++.It is specifically made for getting data in JSON of Quran cloud format and provides efficient methods to
connect data from API easily and it works with all API(s) like Quran-API,Edition-API,Juz-API,Surah-API,Ayah-API,Search-API and more.

*****************************
*******API components.****
*****************************
1)Connect with API --> use QC_ConnectAPI() method.

NOTE : It uses external tool 'CURL' to fetch data from API ,You need to install that using below commands.
Linux : 'sudo apt-get install curl'.
AIM : The aim of this API connector is to make easy to parse QuranCloud API with ready-made code available with efficient methods that ease your most of the work.

DOCUMENTATION INFO :
All Public methods are well documented but private methods are not documented as it was not necessary to do so.

*****************************
*********FEATURES*********
*****************************
1)Dual Connector Works with windows and other OS also.
2)Fetches data using Win32 Libraries on windows.
3)Fetches data using CURL Tool on other OS like Linux,MAC.
4)Works with large data sets also.

VERSION INFO :
QC-API-Connect Version : V 1.0

V 1.0 -> Dated : 12/02/2019
Written by Abdul HaseeB Mir (haseebmir.hm@gmail.com)
*/

char* QC_ConnectAPI(char *);
#ifdef OS_TYPE_WIN
HINSTANCE hInst;
WSADATA wsaData;
void ParseURL(char*, char*, char*, char*);
SOCKET ConnectServer(char *,WORD);
int GetHeaderLen(char*);
char *ReadURL(char*, long *, char **);
void GetSubStr(char*,char*,int,int);
int FindSubStr(char*,char* substr,int);
int RemSubStr(char*,int,int);
#elif defined(OS_TYPE_OTHER)
void Curl2File(const char *,const char* );
char* ReadJSONData(const char *);
#endif // OS_TYPE_WIN
#endif // _QC_API_CONNECT_H
