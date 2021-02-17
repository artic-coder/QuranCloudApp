![cover_logo](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_cloud.jpg?raw=true "")

# QuranCloud-Application

**_QuranCloudApp_** QuranCloudApp is application to get data from Quran like Ruku,Ayah,Page and also search engine
to search any text in Quran and get lists of Quran types,formats etc. 
which fetches data from **[QuranCloud](https://alquran.cloud/) server** and shows data to user.</br>

**NOTE** : WORKS ON ALL MAJOR OS **_Windows,Linux,MacOS_**. (**Tested** on **Windows 10** and **macOS High Sierra**)</br>
It uses external tool **'CURL'** to fetch data from API ,You need to **install** that if not present in your system
using below commands.</br>
_Linux_ : **'sudo apt-get install curl'**.</br>
_Mac_ : **'brew install curl'**.</br>
_Windows_ : Its uses **Win32 Library** so no need to download anything.</br>


# Features :
1) Search text from Quran in **37 different** languages.</br>
2) Get **114** surahs.</br>
3) Get **6236** ayahs.</br>
4) Get **604** pages.</br>
5) Get whole Quran in **37 different** languages.</br>
6) Output in **english/arabic** format to easily read.</br>
7) Shows Additional data aswell **Surah name,number and Revelation type**.</br>
8) Automatically detects all **errors** from **JSON and API side**.</br>
9) Portability to work on every **major OS** like **_Windows,Linux,Mac_**.</br>
10) Shows lists of Quran type,languages and formats aswell which are supported by API.

# How to compile on windows :
You have to add **_WS-Library_** in your project by adding **'-l "ws2_32'** in compiler option if you are using IDE like **CodeBlocks,DevCPP**.</br>
Or If you are using **Visual Studio** then add this line of code **_#pragma comment(lib, "ws2_32")_**</br>
Or you can compile with **gcc** using this command **_gcc QuranCloudApp.c -o QuranCloudApp.exe -l "ws2_32_**</br>
**_NOTE : ITS NOT NEEDED IF YOU USING OS OTHER THAN WINDOWS, COMPILE NORMALLY_**</br>

# Application Components :

## Searching using keywords : 

![quran_search](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_search.jpg?raw=true "")

## Get Quran surah by number : 

![quran_surah](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_surah.jpg?raw=true "")

## Get Quran ayah by number : 

![quran_ayah](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_ayah.jpg?raw=true "")

## Get Quran page by number : 

![quran_page](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_page.jpg?raw=true "")

## Get whole Quran by language : 

![quran_whole](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_whole.jpg?raw=true "")

## Get list of Quran languages : 

![quran_languages](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_languages.jpg?raw=true "")

## Get list of Quran types : 

![quran_types](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_types.jpg?raw=true "")

## Get list of Quran formats : 

![quran_formats](https://github.com/haseeb-heaven/QuranCloudApp/blob/master/resources/quran_formats.jpg?raw=true "")
