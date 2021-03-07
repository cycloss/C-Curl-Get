#include <curl/curl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char* ptr;
    size_t len;
} DataStr;

void fatalError(char* formatString, ...);
DataStr* initDataStr();
void freeDataStr(DataStr* dataStr);
size_t writeFunc(char* inData, size_t size, size_t nmemb, DataStr* outData);
CURL* initCurl(char* httpAddress, DataStr* dataStr);
char* parseAddress(int argc, char** argv);
int main(int argc, char* argv[]);