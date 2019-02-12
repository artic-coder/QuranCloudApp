#include "qc_api_connect.h"

char* QC_ConnectAPI(char *api_url)
{
    #ifdef OS_TYPE_WIN
    long fileSize;
    char *headerBuffer = NULL;

    if (WSAStartup(0x101, &wsaData) != 0)
        return NULL;

    char *json_buf = ReadURL(api_url, &fileSize, &headerBuffer);
    WSACleanup();

    #elif defined(OS_TYPE_OTHER)

    /*Save data to file.*/
    const char *file_name = "qc_data.json";
    Curl2File(api_url,file_name);

    /*Read data back from file.*/
    char *json_buf = ReadJSONData(file_name);
     remove(file_name);
    #endif // OS_TYPE_WIN

    return json_buf;
}

#ifdef OS_TYPE_WIN
/*QuranCloud - ParseURL : Parses the URL.*/
void ParseURL(char* mUrl, char* server, char* filepath, char* filename)
{
    int pos;
    char* url = mUrl;
    LPCSTR http_str = "http://",https_str = "https://";
    char http_buf[0xF] = {NULL},https_buf[0xF] = {NULL};

    GetSubStr(url,http_buf,0,7);
    GetSubStr(url,https_buf,0,8);

    if(!strcmp(http_buf,http_str))
    {
        RemSubStr(url,0,7);
    }

    else if(!strcmp(https_buf,https_str))
    {
        RemSubStr(url,0,8);
    }

    pos = FindSubStr(url,"/",FALSE);

    if (pos != -1)
    {
        GetSubStr(url,server,0,pos);
        GetSubStr(url,filepath,pos,-1);
        pos = FindSubStr(filepath,"/",TRUE);
        GetSubStr(filepath,filename,pos+1,-1);
    }

    else
    {
        server = url;
        filepath = "/";
        filename = "";
    }
}

/*QuranCloud - ConnectServer : Connects with QuranCloud server.*/
SOCKET ConnectServer(char *szServerName, WORD portNum)
{
    struct hostent *hp;
    unsigned int addr;
    struct sockaddr_in server;
    SOCKET conn;

    conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (conn == INVALID_SOCKET)
        return NULL;

    if(inet_addr(szServerName)==INADDR_NONE)
    {
        hp=gethostbyname(szServerName);
    }
    else
    {
        addr=inet_addr(szServerName);
        hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
    }

    if(hp==NULL)
    {
        closesocket(conn);
        return NULL;
    }

    server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
    server.sin_family=AF_INET;
    server.sin_port=htons(portNum);
    if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
    {
        closesocket(conn);
        return NULL;
    }
    return conn;
}

/*QuranCloud - GetHeaderLen : Get length of header data from server.*/
int GetHeaderLen(char *content)
{
    const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
    char *findPos;
    int ofset = -1;

    findPos = strstr(content, srchStr1);
    if (findPos != NULL)
    {
        ofset = findPos - content;
        ofset += strlen(srchStr1);
    }

    else
    {
        findPos = strstr(content, srchStr2);
        if (findPos != NULL)
        {
            ofset = findPos - content;
            ofset += strlen(srchStr2);
        }
    }
    return ofset;
}

/*QuranCloud - ReadURL : Read data from URL.*/
char *ReadURL(char *url, long *bytesReturnedOut, char **headerOut)
{
    const int bufSize = 4096;
    char *readBuffer = NULL;
    char sendBuffer[bufSize], tmpBuffer[bufSize];
    readBuffer = calloc(0xC350,sizeof(char));

    if(readBuffer == NULL)
    {
        perror("MEMORY ERROR : ");
        exit(EXIT_FAILURE);
    }

    char *tmpResult=NULL, *result = NULL;
    SOCKET conn;
    char* server[MAX_PATH] = {NULL}, filepath[MAX_PATH] = {NULL}, filename[MAX_PATH] = {NULL};
    long totalBytesRead, thisReadSize, headerLen;


    ParseURL(url, server, filepath, filename);
    /*Connect with server at 8080 PORT.*/
    conn = ConnectServer(server, 80);
      /*Connect with server and send GET request.*/
    sprintf(tmpBuffer, "GET %s HTTP/1.0", filepath);
    strcpy(sendBuffer, tmpBuffer);
    strcat(sendBuffer, "\r\n");
    sprintf(tmpBuffer, "Host: %s", server);
    strcat(sendBuffer, tmpBuffer);
    strcat(sendBuffer, "\r\n");
    strcat(sendBuffer, "\r\n");
    send(conn, sendBuffer, strlen(sendBuffer), 0);

     /*Connect with server and get received bytes */

    totalBytesRead = 0;
    while(1)
    {
        memset(readBuffer, 0, bufSize);
        thisReadSize = recv (conn, readBuffer, bufSize, 0);

        if ( thisReadSize <= 0 )
            break;

        tmpResult = (char*)realloc(tmpResult, thisReadSize+totalBytesRead);

        memcpy(tmpResult+totalBytesRead, readBuffer, thisReadSize);
        totalBytesRead += thisReadSize;
    }

    headerLen = GetHeaderLen(tmpResult);
    long contenLen = totalBytesRead-headerLen;
    result = calloc(contenLen+1,sizeof(char));
    memcpy(result, tmpResult+headerLen, contenLen);
    result[contenLen] = 0x0;
    char *myTmp;

    myTmp = calloc(headerLen+1,sizeof(char));
    strncpy(myTmp, tmpResult, headerLen);
    myTmp[headerLen] = NULL;
    free(tmpResult);
    *headerOut = myTmp;

    bytesReturnedOut = contenLen;
    closesocket(conn);
    free(myTmp);

    return result;
}

/*StringHelperMethods : Get substring of given string.*/
void GetSubStr(char* str,char* substr,int pos_begin,int pos_end)
{
    size_t len = lstrlen(str),i = pos_begin;

    if(pos_end < pos_begin && pos_end != -1)
        substr = NULL;

    if(pos_end == -1)
    {
        strcpy(substr,str+pos_begin);
    }

    else
    {
        int pos_len = pos_end-pos_begin;
        strncpy(substr,str+pos_begin,pos_len);
        substr[pos_len] = '\0';
    }
}

/*StringHelperMethods : Remove substring from given string.*/
int RemSubStr(char* str,int pos_begin,int pos_end)
{
    for(int index  = pos_begin; index < pos_end; ++index)
    {
        memmove(&str[pos_begin], &str[pos_begin + 1], strlen(str) - pos_begin);
    }
}

/*StringHelperMethods : Find substring in given string.*/
int FindSubStr(char* str,char* substr,int last_chr)
{
    char *ptr = NULL;
    ptr = (last_chr) ? strrchr(str,substr[0]) :strstr(str,substr);
    int pos = -1;

    if(ptr)
        pos = (int)(ptr-str);

    return pos;
}

#elif defined(OS_TYPE_OTHER)
/*Read json data from JSON file.*/
char* ReadJSONData(const char *filename)
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
    json_buf[file_size+1] = 0;
    return json_buf;
}

/*Save data from CURL to file.*/
void Curl2File(const char *url,const char* file_name)
{
    char curl_cmd[0xC8] = "curl ";
    strcat(strcat(strcat(curl_cmd,url)," 1> "),file_name);
    system(curl_cmd);
}

#endif // OS_TYPE_WIN
