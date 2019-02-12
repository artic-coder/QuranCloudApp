/*
BISMILLAH-I-RAHMAAN-E-RAHEEM . IN THE NAME OF GOD MOST POWERFUL AND MERCIFUL.

BRIEF : QuranCloudApp is application to get data from Quran like Ruku,Ayah,Page and also search engine
to search any text in Quran and get lists of Quran types,formats etc.
which fetches data from [QuranCloud](https://alquran.cloud/) server and shows data to user.

NOTE : WORKS ON ALL MAJOR OS Windows,Linux,MacOS. (Tested on Windows 10 and macOS High Sierra)
It uses external tool 'CURL' to fetch data from API ,You need to install that if not present in your system
using below commands.
Linux : 'sudo apt-get install curl'.
Mac : 'brew install curl'.
Windows : Its uses Win32 Library so no need to download anything.


*****************************
*******App components.*****
*****************************
1) Quran search engine with 37 different languages.
2) Quran Ayah/ruku/Page with 37 different languages. like en,fr,ar.
3) Get complete Quran in 37 different languages.
4) Get Lists all languages in which editions are available.
5) Get Lists all types of editions.
6) Get Lists all formats.

*********************
*******Features.*****
*********************
1) Search text from Quran in 37 different languages.
2) Get 114 surahs.
3) Get 6236 ayahs.
4) Get 604 pages.
5) Get whole Quran in 37 different languages.
6) Output in english/arabic format to easily read.
7) Shows Additional data aswell Surah name,number and Revelation type.
8) Automatically detects all errors from JSON and API side.
9) Portability to work on every major OS like Windows,Linux,Mac.
10) Shows lists of Quran type,languages and formats aswell which are supported by API.
*/

/*Include Parser,URL generator and API Connector.*/
#include "qc_lib/api_parser/qc_api_parser.c"
#include "qc_lib/url_generator/qc_url_generator.c"
#include "qc_lib/api_connector/qc_api_connect.c"

enum API_LIST_TYPE {LANG_LIST,TYPE_LIST,FORMAT_LIST};

/*QuranCloud-API - functions prototypes.*/
void QuranAPI();
void SurahAPI();
void AyahAPI();
void PageAPI();
void SearchAPI();
void ConnectQuranAPI(char *);
void ConnectSurahAPI(char *,char *);
void ConnectPageAPI(char *,char *);
void ConnectAyahAPI(char *,char *,char *);
void ConnectSearchAPI(char*,char*,char*);
void GetAPIList(int);
void ClearScreen();

/*Main method for QuranCloud.*/
int main()
{
    int choice = 0;

    do
    {
        printf("Welcome to QuranCloud App. (V 1.0)\n");
        printf("********DATA********\n");
        printf("1] Search text in Quran.\n");
        printf("2] Get Surah number in Quran.\n");
        printf("3] Get Ayah number in Quran.\n");
        printf("4] Get Page number in Quran.\n");
        printf("5] Get Whole Quran.\n");
        printf("********LISTS********\n");
        printf("6] Get list of Quran languages.\n");
        printf("7] Get list of Quran type.\n");
        printf("8] Get list of Quran format.\n");
        printf("9] Exit  QuranCloud App.\n");

        scanf("%d",&choice);

        switch(choice)
        {
        case 1 :
            while((choice = getchar()) != '\n' && choice != EOF);
            SearchAPI();
            break;

        case 2 :
            while((choice = getchar()) != '\n' && choice != EOF);
            SurahAPI();
            break;

        case 3 :
            while((choice = getchar()) != '\n' && choice != EOF);
            AyahAPI();
            break;

        case 4 :
            while((choice = getchar()) != '\n' && choice != EOF);
            PageAPI();
            break;

        case 5 :
            while((choice = getchar()) != '\n' && choice != EOF);
            QuranAPI();
            break;

        case 6 :
            while((choice = getchar()) != '\n' && choice != EOF);
            GetAPIList(LANG_LIST);
            break;

        case 7 :
            while((choice = getchar()) != '\n' && choice != EOF);
            GetAPIList(TYPE_LIST);
            break;

        case 8 :
            while((choice = getchar()) != '\n' && choice != EOF);
            GetAPIList(FORMAT_LIST);
            break;

        default :
            printf("Wrong choice selected");
        }

        printf("\nHIT ENTER AFTER READING : ");
        char ch = getchar();

        if(ch == '\n' || ch == '\r')
        {
            ClearScreen();
        }

    }
    while(choice != 9);

    printf("ALHAMDULILLAH MAY ALLAH(SWT) BLESS US ALL.\n");
    printf("Visit QuranCloud - 'https://alquran.cloud/api' ");
    return 0;
}

/*Fgets with no newline delimiter.*/
void fgets_s(char *buf,int buflen)
{
    fgets(buf,buflen,stdin);
    strtok(buf,"\n");
}

/*QuranCloud - SearchAPI : Lets you to search text from Quran.*/
void SearchAPI()
{
    char search_text[0x32] = {NUL},surah_num[0x5] = {NUL},quran_edition[0x32] = {NUL};

    puts("Enter keyword to search");
    fgets_s(search_text,0x32);

    puts("Enter surah number [1 - 114]");
    fgets_s(surah_num,0x5);

    puts("Enter quran edition");
    fgets_s(quran_edition,0x32);

    ConnectSearchAPI(search_text,surah_num,quran_edition);
}

/*QuranCloud - QuranAPI : Lets you to get whole Quran.*/
void QuranAPI()
{
    char quran_edition[0x32] = {NUL};

    puts("Enter quran edition");
    fgets_s(quran_edition,0x32);

    ConnectQuranAPI(quran_edition);
}

/*QuranCloud - SurahAPI : Lets you to get specific surah from Quran.*/
void SurahAPI()
{
    char surah_num[0x5] = {NUL},quran_edition[0x32] = {NUL};

    puts("Enter surah number [1 - 114]");
    fgets_s(surah_num,0x5);

    puts("Enter quran edition");
    fgets_s(quran_edition,0x32);

    ConnectSurahAPI(surah_num,quran_edition);
}

/*QuranCloud - SurahAPI : Lets you to get specific surah from Quran.*/
void PageAPI()
{
    char page_num[0x5] = {NUL},quran_edition[0x32] = {NUL};

    puts("Enter page number [1 - 604]");
    fgets_s(page_num,0x5);

    puts("Enter quran edition");
    fgets_s(quran_edition,0x32);

    ConnectPageAPI(page_num,quran_edition);
}

/*QuranCloud - AyahAPI : Lets you to get specific ayah from Quran.*/
void AyahAPI()
{
    char ayah_num[0xF] = {NUL},quran_edition[0x32] = {NUL},quran_editions[0x32] = {NUL};
    int edition_type;
    puts("Enter ayah number/reference [1 - 6236]");
    fgets_s(ayah_num,0xF);

    puts("Choose 1)Single edition\t2)Multiple Editions");
    scanf("%d",&edition_type);

    if(edition_type == 1)
    {
        while((edition_type = getchar()) != '\n' && edition_type != EOF);
        puts("Enter quran edition");
        fgets_s(quran_edition,0x32);
    }

    else
    {
        while((edition_type = getchar()) != '\n' && edition_type != EOF);
        puts("Enter quran editions");
        fgets_s(quran_editions,0x32);
    }

    ConnectAyahAPI(ayah_num,quran_edition,quran_editions);
}

/*QuranCloud - ConnectQuranAPI : Connects with Quran API */
void ConnectQuranAPI(char *quran_edition)
{
    /*Generate URL for search.*/
    char *url = QC_GenerateQuranURL(quran_edition);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
    {
        for(int index = 2; index <= 6; ++index)
        {
            if(index == 5)
                continue;
            else
                QC_SearchToken(json_string,api_parser_tokens[index]);
        }

        /*Search for all token in json file.*/
        QC_SearchToken(json_string,api_parser_tokens[QC_TEXT]);
    }
}

/*QuranCloud - ConnectSearchAPI : Connects with Search API */
void ConnectSearchAPI(char *search_text,char *surah_num,char *quran_edition)
{
    /*Generate URL for search.*/
    char *url = QC_GenerateSearchURL(search_text,surah_num,quran_edition);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
    {
        char *token_keys[] = {api_parser_tokens[QC_TEXT],api_parser_tokens[QC_SURAH_AR_NAME],
                              api_parser_tokens[QC_SURAH_ENG_NAME],api_parser_tokens[QC_REV_TYPE],
                              api_parser_tokens[QC_SURAH_NUM]
                             };
        size_t token_lens = sizeof(token_keys)/sizeof(token_keys[0]);

        /*Search for all token in json file.*/
        QC_SearchTokens(json_string,token_keys,token_lens);
    }
}

/*QuranCloud - ConnectSearchAPI : Connects with Surah API */
void ConnectSurahAPI(char *surah_num,char *quran_edition)
{
    /*Generate URL for search.*/
    char *url = QC_GenerateSurahURL(surah_num,quran_edition,NULL,NULL);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
    {
        for(int index = 2; index <= 6; ++index)
        {
            if(index == 5)
                continue;
            else
                QC_SearchToken(json_string,api_parser_tokens[index]);
        }

        /*Search for all token in json file.*/
        QC_SearchToken(json_string,api_parser_tokens[QC_TEXT]);
    }
}

/*QuranCloud - ConnectAyahAPI : Connects with Ayah API */
void ConnectAyahAPI(char *reference,char *quran_edition,char *quran_editions)
{
    /*Generate URL for search.*/
    char *url = QC_GenerateAyahURL(reference,quran_edition,quran_editions);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
    {
        for(int index = 2; index <= 6; ++index)
        {
            if(index == 5)
                continue;
            else
                QC_SearchToken(json_string,api_parser_tokens[index]);
        }

        /*Search for all token in json file.*/
        QC_SearchToken(json_string,api_parser_tokens[QC_TEXT]);
    }
}

/*QuranCloud - ConnectPageAPI : Connects with Page API */
void ConnectPageAPI(char *page_num,char *quran_edition)
{
    /*Generate URL for search.*/
    char *url = QC_GeneratePageURL(page_num,quran_edition,NULL,NULL);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
    {
        for(int index = 2; index <= 6; ++index)
        {
            if(index == 5)
                continue;
            else
                QC_SearchToken(json_string,api_parser_tokens[index]);
        }

        /*Search for all token in json file.*/
        QC_SearchToken(json_string,api_parser_tokens[QC_TEXT]);
    }
}

/*QuranCloud - GetAPIList : Connects with API to show list*/
void GetAPIList(int list_type)
{
    char *list_str = (list_type == LANG_LIST) ? "/language" : (list_type == TYPE_LIST) ? "/type" : "/format";

    /*Generate URL for search.*/
    char *url = strcat(QC_GenerateEditionURL(NULL,NULL,NULL),list_str);

    /*Connect to QuranCloud API.*/
    char *json_string = QC_ConnectAPI(url);
    ClearScreen();

    if(json_string != NULL)
        puts(json_string);
}

void ClearScreen()
{
    system("cls||clear");
}
