#include "qc_url_generator.h"

/***************************************************************************/
/*********************-PUBLIC-METHODS-**********************************/
/***************************************************************************/
/**
 * @description - Generate URL for Quran API.
 * @param - edition is an edition identifier. Example: en.asad for Muhammad Asad's english translation
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT :  http://api.alquran.cloud/v1/quran/{{edition}}
 */

char *QC_GenerateQuranURL(char* edition)
{
    static char quran_url[MAX_URL] = {'\0'};
    memset(quran_url,NIL,sizeof(quran_url));

    size_t edition_len = (edition == NULL) ? NIL : strlen(edition);

    if(edition_len == NIL)
    {
        printf("ERROR : Invalid parameters detected.\n");
        return base_url;
    }

    /*Append URL with api option.*/
    AppendBaseAPI(quran_url,API_QURAN);

    /*Append edition data.*/
    strcat(quran_url,edition);

    return quran_url;
}


/**
 * @description - Generate URL for search API.
 * @param - search - text to search.
 * surah - Enter a surah number (between 1 and 114) to search a specific surah or 'all' to search all the text.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT :  http://api.alquran.cloud/v1/search/keyword/surah/edition or language
 */

char *QC_GenerateSearchURL(char* search,char* surah,char* edition)
{
    static char search_url[MAX_URL] = {'\0'};
    memset(search_url,NIL,sizeof(search_url));

    size_t search_len = (search == NULL) ? NIL : strlen(search),
    surah_len = (surah == NULL) ? NIL : strlen(surah),
    edition_len = (edition == NULL) ? NIL : strlen(edition);

    if(search_len == NIL || surah_len == NIL || edition_len == NIL)
    {
        printf("ERROR : Invalid parameters detected.\n");
        return base_url;
    }

    /*Append URL with api option.*/
    AppendBaseAPI(search_url,API_SEARCH);

    /*Append search keyword.*/
    strcat(strcat(search_url,search),"/");

    /*Append surah data.*/
    strcat(strcat(search_url,surah),"/");

    /*Append edition data.*/
    strcat(search_url,edition);

    return search_url;
}

/**
 * @description - Generate URL for Edition API.
 * @param - format - Specify a format. 'text' or 'audio.
 * language - A 2 digit language code. Example: 'en', 'fr', etc.
 * type - A valid type. Example - 'versebyverse', 'translation' etc.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT :  http://api.alquran.cloud/v1/edition?&language=&type=
 */

char *QC_GenerateEditionURL(char* format,char* language,char* type)
{
    static char edition_url[MAX_URL] = {'\0'};
    memset(edition_url,NIL,sizeof(edition_url));

    size_t format_len = (format == NULL) ? NIL : strlen(format),
    language_len = (language == NULL) ? NIL : strlen(language),
    type_len = (type == NULL) ? NIL : strlen(type);

    /*Append URL with api option.*/
    strcat(strcpy(edition_url,base_url),api_url_tokens[API_EDITION]);

    /*Append edition format.*/
    if(format_len != NIL)
        strcat(strcat(strcat(edition_url,"?format"),"="),format);

    /*Append edition language.*/
    if(language_len != NIL)
        strcat(strcat(strcat(edition_url,"&language"),"="),language);

    /*Append edition type.*/
    if(type_len != NIL)
        strcat(strcat(strcat(edition_url,"&type"),"="),type);

    return edition_url;
}

/**
 * @description - Generate URL for ayah API.
 * @param -
 * reference - here can be the ayah number or the surah:ayah. For instance, 262 or 2:255 will both get you Ayat Al Kursi.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.
 * editions - list of editions for multiple results. [Either edition or list of editions must be provided, not both at same time].
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT :  http://api.alquran.cloud/v1/ayah/{{reference}}/editions/{{edition}},{{edition}}
 */

char *QC_GenerateAyahURL(char* reference,char* edition,char* editions)
{
    static char ayah_url[MAX_URL] = {'\0'};
    memset(ayah_url,NIL,sizeof(ayah_url));

    size_t reference_len = (reference == NULL) ? NIL : strlen(reference),
    edition_len = (edition == NULL) ? NIL : strlen(edition),
    editions_len = (editions == NULL) ? NIL : strlen(editions);

    if(reference_len == NIL)
    {
        printf("ERROR : Invalid parameters detected.\n");
        return base_url;
    }

    /*Append URL with api option.*/
    AppendBaseAPI(ayah_url,API_AYAH);

    /*Append reference.*/
    strcat(ayah_url,reference);

    /*Append edition data for single result.*/
    if(edition_len != NIL)
    strcat(strcat(ayah_url,"/"),edition);

    /*Append editions data multiple result.*/
    else if(editions_len != NIL)
    strcat(strcat(ayah_url,"/editions/"),editions);

    return ayah_url;
}

/**
 * @description - Generate URL for Edition API.
 * @param - format - juz - Juz number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a juz by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/juz/{{juz}}/{{edition}}
 */

 char *QC_GenerateJuzURL(char *juz,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(juz,edition,offset,limit,API_JUZ);
 }


 /**
 * @description - Generate URL for Surah API.
 * @param - format - surah - Surah number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a surah by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/surah/{{surah}}/{{edition}}
 */

 char *QC_GenerateSurahURL(char *surah,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(surah,edition,offset,limit,API_SURAH);
 }

 /**
 * @description - Generate URL for Manzil API.
 * @param - format - Manzil - Manzil number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a Manzil by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/Manzil/{{Manzil}}/{{edition}}
 */

 char *QC_GenerateManzilURL(char *Manzil,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(Manzil,edition,offset,limit,API_MANZIL);
 }

  /**
 * @description - Generate URL for Ruku API.
 * @param - format - Ruku - Ruku number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a Ruku by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/Ruku/{{Ruku}}/{{edition}}
 */

 char *QC_GenerateRukuURL(char *ruku,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(ruku,edition,offset,limit,API_RUKU);
 }

  /**
 * @description - Generate URL for Page API.
 * @param - format - Page - Page number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a Page by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/Page/{{Page}}/{{edition}}
 */

 char *QC_GeneratePageURL(char *Page,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(Page,edition,offset,limit,API_PAGE);
 }

   /**
 * @description - Generate URL for Hizb API.
 * @param - format - Hizb - Hizb number.
 * edition - is an edition identifier. Example: en.asad for Muhammad Asad's english translation.

  Optional Parameters:
 * offset - Offset ayahs in a Hizb by the given number
 * limit - This is the number of ayahs that the response will be limited to.
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT : http://api.alquran.cloud/v1/Hizb/{{Hizb}}/{{edition}}
 */

 char *QC_GenerateHizbURL(char *Hizb,char *edition,char* offset ,char* limit)
 {
     return GenerateCommonURL(Hizb,edition,offset,limit,API_HIZB);
 }

 /**
 * @description - Generate URL for sajda API.
 * @param - edition is an edition identifier. Example: en.asad for Muhammad Asad's english translation
* @return - On valid parameters it returns generated URL otherwise returns base URL.
* URL - FORMAT :  http://api.alsajda.cloud/v1/sajda/{{edition}}
 */

char *QC_GenerateSajdaURL(char* edition)
{
    static char sajda_url[MAX_URL] = {'\0'};
    memset(sajda_url,NIL,sizeof(sajda_url));

    size_t edition_len = (edition == NULL) ? NIL : strlen(edition);

    if(edition_len == NIL)
    {
        printf("ERROR : Invalid parameters detected.\n");
        return base_url;
    }

    /*Append URL with api option.*/
    AppendBaseAPI(sajda_url,API_SAJDA);

    /*Append edition data.*/
    strcat(sajda_url,edition);

    return sajda_url;
}


/***************************************************************************/
/*********************-PRIVATE-METHODS-********************************/
/***************************************************************************/

/**
 * @description - Append API with base URL.
 */

void AppendBaseAPI(char *url,int api_type)
{
    if(api_type < 0 || api_type > API_SAJDA)
    {
        printf("ERROR : Invalid API type detected.\n");
    }

    else
    {
        /*Append URL with api option.*/
        strcat(strcat(strcpy(url,base_url),api_url_tokens[api_type]),"/");
    }
}

/**
 * @description - Generate common URL for most API(s) like - "juz,surah,manzil,ruku,page,hizb"
 */
char *GenerateCommonURL(char *api_name,char *edition,char* offset ,char* limit,int api_type)
{
    static char api_url[MAX_URL] = {'\0'};
    memset(api_url,NIL,sizeof(api_url));

    size_t api_name_len = (api_name == NULL) ? NIL : strlen(api_name),
    edition_len = (edition == NULL) ? NIL : strlen(edition),
    offset_len = (offset == NULL) ? NIL : strlen(offset),
    limit_len = (limit == NULL) ? NIL : strlen(limit);

    /*Append URL with api option.*/
    AppendBaseAPI(api_url,api_type);

     if(api_name_len == NIL || edition_len == NIL){
        printf("ERROR : Invalid parameters detected.\n");
        return base_url;
     }

    /*Append api_name type.*/
    strcat(strcat(api_url,api_name),"/");

    /*Append edition.*/
    strcat(api_url,edition);

    /*Append offset.*/
    if(offset_len != NIL)
        strcat(strcat(strcat(api_url,"?offset"),"="),offset);

    /*Append limit.*/
    if(limit_len != NIL)
        strcat(strcat(strcat(api_url,"&limit"),"="),limit);

    return api_url;
}

/**
 * @description - Show output from URL using curl tool."
 */

void ShowCurl(const char *url)
{
    char curl_cmd[0x64] = "curl ";
    strcat(curl_cmd,url);
    system(curl_cmd);
}

void SaveCurl(const char *url,const char* file_name)
{
    char curl_cmd[0xC8] = "curl ";
    strcat(strcat(strcat(curl_cmd,url)," 1> "),file_name);
    system(curl_cmd);
}
