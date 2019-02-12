/*QC-API-PARSER : Parser for Quran Cloud API. "http://api.alquran.cloud/"
made specifically and shows exact errors from Quran cloud json data.*/

#include "qc_api_parser.h"

/************************************************************************************/
/*********************-PUBLIC-PARSER-METHODS-**********************************/
/************************************************************************************/

/**
 * @description - Print all tokens from JSON data in KEY:VALUE format.
 * @param - json_str - string containing json data.
 * token_type - Type of token to print Keys or Values. Use TOK_ENUM Enum to provide values.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_PrintAllTokens(const char *json_str,int token_type)
{
    return JSON_Parser(json_str,NULL,NIL,false,token_type);
}

/**
 * @description - Search for single token from JSON data.
* @param - json_str - string containing json data.
* token_key - Token key to search.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_SearchToken(const char *json_str,const char *token_key)
{
    return JSON_Parser(json_str,&token_key,1,true,false);
}

/**
 * @description - Search for multiple tokens from JSON data.
 * @param - json_str - string containing json data.
* token_keys - List of token keys to search.
* token_lens - Length of token keys.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_SearchTokens(const char *json_str,const char **token_keys,size_t token_lens)
{
    return JSON_Parser(json_str,token_keys,token_lens,true,false);
}

/**
 * @description - Read json data from JSON file.
 * @param - filename - Name of file containing JSON data.
  * @return - On success it returns JSON_BUFFER otherwise returns NULL.
 */

char* QC_ReadJSON(const char *filename)
{
    FILE *fp = fopen(filename,"rb");
    char *json_buf = NULL;
    long file_size = 0L;

    if(fp == NULL)
    {
        perror("ERROR OCCURRED : ");
        exit(EXIT_FAILURE);
    }

    else
    {
        /*Get the file size by seeking to EOF.*/
        fseek(fp,0,SEEK_END);
        file_size = ftell(fp);
        rewind(fp);

        json_buf = calloc(file_size+1,sizeof(char));
        fread(json_buf,1,file_size,fp);
        fclose(fp);
    }
    json_buf[file_size+1] = NUL;

    if(JSON_Validator(json_buf) != QC_SUCCESS)
        return NULL;
    return json_buf;
}

/*********************************************************************************/
/*********************-PUBLIC-API-METHODS-**********************************/
/********************************************************************************/

/**
 * @description - Get text containing ayah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetAyahText(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_TEXT]);
}

/**
 * @description - Get name of surah in arabic,english etc.
* @param - json_str - string containing json data.
* surah_type - Type of surah in Arabic,English, etc use Enum 'SURAH_TYPE' to provide values.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetSurahName(const char *json_str,int surah_type)
{
    int qc_surah = (surah_type == SURAH_ARABIC) ? QC_SURAH_AR_NAME : (surah_type == SURAH_ENG_ARABIC) ? QC_SURAH_AR_ENG_NAME : QC_SURAH_ENG_NAME;
    return QC_SearchToken(json_str,api_parser_tokens[qc_surah]);
}

/**
 * @description - Get surah number of ayah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetSurahNumber(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_SURAH_NUM]);
}

/**
 * @description - Get ayah number of ayah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetAyahNumber(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_AYAH_NUM]);
}

/**
 * @description - Get page number of ayah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetPageNumber(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_PAGE_NUM]);
}

/**
 * @description - Get revelation type of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetRevelationType(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_REV_TYPE]);
}

/**
 * @description - Get ruku number of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetRuku(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_RUKU]);
}

/**
 * @description - Get juz of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetJuz(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_JUZ]);
}

/**
 * @description - Get manzil of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetManzil(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_MANZIL]);
}

/**
 * @description - Get manzil of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetSajda(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_SAJDA]);
}

/**
 * @description - Get hizb of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetHizb(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_HIZB]);
}

/**
 * @description - Get language of surah.
* @param - json_str - string containing json data.
* @return - On success it returns QC_SUCCESS otherwise returns ERROR occurred.
 */

int QC_API_GetLanguage(const char *json_str)
{
    return QC_SearchToken(json_str,api_parser_tokens[QC_LANG]);
}

/****************************************************************************/
/****************-PRIVATE-METHODS-**************************************/
/****************************************************************************/

/**
 * @description - Parse all the tokens from JSON.
 */

int JSON_Parser(const char * json_str,const char **search_keys,size_t search_len,bool search_json,int print_tokens)
{
    int token_status = NIL,search_index = NIL;
    size_t json_len = (json_str == NULL) ? NIL : strlen(json_str);

    /*Check for valid JSON format.*/
    token_status =  JSON_Validator(json_str);

    if(token_status == QC_SUCCESS)
    {
        /*Allocate memory to copy original string.*/
        char *json_buf = calloc(json_len+1,sizeof(char));

        if(json_buf == NULL)
        {
            perror("ERROR OCCURRED : ");
            exit(EXIT_FAILURE);
        }

        /*Make copy of original string.*/
        strcpy(json_buf,json_str);
        json_buf[json_len] = NUL;

        /*Start tokenizing with starting token '{'*/
        char *ptr_json = strtok(json_buf,"{");
        int tok_pos = (int)(ptr_json-json_buf),token_len = NIL;

        while((ptr_json = strtok(json_buf+tok_pos,":")) != NULL && tok_pos <= json_len-0x18)
        {
            /*Buffer to store key and values.*/
            char json_key[0x32] = {NUL},json_value[0x7D0] = {NUL};
            int delim_count = NIL,key_index = NIL,value_index = NIL;

            /*Parse the string with ':' token to get key and value.*/
            ptr_json = strtok(json_buf+tok_pos,":");

            /*Parse till next token found and store in key and value buffers.*/
            while(*ptr_json++ != ',')
            {
                if(isalnum(*ptr_json) || isspace(*ptr_json) || *ptr_json == '\"')
                {
                    if(*ptr_json == '\"')
                        delim_count++;
                    else if(delim_count == NIL)
                        json_key[key_index++] = *ptr_json;
                    else
                        json_value[value_index++] = *ptr_json;
                }
            }

            /*Print all tokens in Key:Value format is selected.*/
            if(print_tokens == ALL_TOKENS)
                printf("Key : %s\tValue : %s\n",json_key,json_value);
            else if(print_tokens == ALL_KEYS)
                printf("Key : %s\n",json_key);
            else if(print_tokens == ALL_VALUES)
                printf("Value : %s\n",json_value);

            /*Search from all tokens is selected.*/
            if(search_json)
            {
                if(!strcmp(json_key,search_keys[search_index]))
                {
                    printf("%s : %s\n",json_key,json_value);
                    search_index++;/*Reset search index later.*/
                    search_index = (search_index >= search_len) ? 0 : search_index;
                }
            }

            /*Get position for token.*/
            tok_pos = (int)(ptr_json-json_buf);
        }
        free(json_buf);
    }
    return token_status;
}

/**
 * @description - Check for valid JSON string.
 */

int JSON_Validator(const char *json_str)
{
    int valid_status = QC_SUCCESS;
    size_t json_len = (json_str == NULL) ? NIL : strlen(json_str);
    char *ptr = NULL;

    if(json_str == NULL || json_str[0] == NUL)
    {
        valid_status = QC_EMPTY_STRING;
    }

    else if(json_str[0] != '{' ||  json_str[json_len-1] != '}'){
        printf("INVALID ENCLOSING BRACES.\n");
        valid_status = QC_INVALID_JSON;
    }

    else if((ptr = strstr(json_str,"code")) != NULL)
    {
        while(!isdigit(*ptr))
            ptr++;

        char http_buf[0x5] = {NUL};
        sprintf(http_buf,"%.*s",3,ptr);

        if(*http_buf != '2')/*If http code not equal to 2xx.*/
        {
            printf("HTTP ERROR CODE : %s\n",http_buf);
            valid_status = QC_HTTP_ERROR;
        }

        if((ptr = strstr(json_str,"status")) != NULL)/*If http status not equal to OK.*/
        {
            ptr+=strlen("status")+3;
            if(ptr[0] != 'O' && ptr[1] != 'K')
            {
                valid_status = QC_STATUS_ERROR;

                printf("STATUS ERROR : \"");
                while(*ptr != ',')
                    putchar(*ptr++);
                printf("\n");
            }

            else if(strstr(json_str,":") == NULL) /*If key-value separator not found.*/
                valid_status = QC_INVALID_KEY;

            else  if(strstr(json_str,"endpoint") != NULL) /*If invalid endpoint found*/
                valid_status = QC_INVALID_OBJECT;

        }
        else
        {
            printf("STATUS TYPE NOT FOUND\n");
            valid_status = QC_INVALID_JSON;
        }
    }

    else
    {
        printf("STATUS CODE NOT FOUND\n");
        valid_status = QC_INVALID_JSON;
    }

     /*Print error in the end if occurred any.*/
    if(valid_status != QC_SUCCESS)
    {
        printf("ERROR OCCURRED : '%s'\n",ERROR_STRING[valid_status]);
    }

    return valid_status;
}
