#include "basicCall.h"

//MUST use http:// or https:// at the start of address arg
int main(int argc, char* argv[]) {
    DataStr* dataStr = initDataStr();
    char* httpAddress = parseAddress(argc, argv);
    CURL* curl = initCurl(httpAddress, dataStr);
    CURLcode code = curl_easy_perform(curl);
    if (code != CURLE_OK) {
        fatalError("Curl code error: %s\n", curl_easy_strerror(code));
    }
    puts(dataStr->ptr);
    curl_easy_cleanup(curl);
    freeDataStr(dataStr);
    return 0;
}

DataStr* initDataStr() {
    DataStr* dataStr = malloc(sizeof(DataStr));
    if (!dataStr) {
        fatalError("Malloc failed for dataStr");
    }
    *dataStr = (DataStr) { NULL, 0 };
    char* ptr = malloc(sizeof(dataStr->len + 1));
    if (!ptr) {
        fatalError("Malloc failed for ptr");
    }
    ptr[0] = '\0';
    dataStr->ptr = ptr;
    return dataStr;
}

void freeDataStr(DataStr* dataStr) {
    free(dataStr->ptr);
    free(dataStr);
}

char* parseAddress(int argc, char** argv) {
    argc -= optind;
    argv += optind;
    if (argc != 1) {
        fatalError("Please provide a single http address");
    }
    return argv[0];
}

CURL* initCurl(char* httpAddress, DataStr* dataStr) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        fatalError("curl failed to init");
    }
    curl_easy_setopt(curl, CURLOPT_URL, httpAddress);
    //sets the callback that will be called as many times as is required to write all data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunc);
    //will pass the dataStr pointer into the writeFunc callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, dataStr);
    return curl;
}

//may be called many times by curl
//ptr is a pointer to the retreived data string
//nmemb is the length of the data
//size is always 1
//last param requires a void pointer which points to the pointer set with CURLOPT_WRITEDATA
size_t writeFunc(char* inData, size_t size, size_t nmemb, DataStr* outData) {
    size_t newLen = outData->len + size * nmemb;
    outData->ptr = realloc(outData->ptr, newLen + 1);
    if (!outData->ptr) {
        fatalError("Realloc of outData ptr failed");
    }
    memcpy(outData->ptr + outData->len, inData, size * nmemb);
    outData->len = newLen;
    outData->ptr[newLen] = '\0';
    return size * nmemb;
}

void fatalError(char* formatString, ...) {
    printf("Fatal error: ");
    va_list args;
    va_start(args, formatString);
    vfprintf(stderr, formatString, args);
    exit(1);
}