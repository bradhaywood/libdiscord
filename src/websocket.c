#include "discord.h"

void wsclient_new(Discord *discord, const char *url) {
    printf("=> Connecting to WebSocket URL: %s\n", url);

	CURL *curl;
	CURLcode res;
	HTTPResponse r;
	
	curl = curl_easy_init();
	if(curl) {
        struct curl_slist *chunk = NULL;
        string s;
        init_string(&s);

        // set up headers
        char* base64EncodeOutput, *wskey = "Hello World";
        Base64Encode(wskey, strlen(wskey), &base64EncodeOutput);
        printf("wskey: %s\n", base64EncodeOutput);
        chunk = curl_slist_append(chunk, "Connection: Upgrade");
        chunk = curl_slist_append(chunk, "Host: gateway.discord.gg");
        chunk = curl_slist_append(chunk, "Upgrade: websocket");
        chunk = curl_slist_append(chunk, wskey);
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        /* always cleanup */
        free(s.ptr);
        curl_slist_free_all(chunk);
        curl_easy_cleanup(curl);
    }
}
