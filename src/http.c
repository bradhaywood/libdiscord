#include "discord.h"

HTTPResponse http_get(Discord *discord) {
	CURL *curl;
	CURLcode res;
	HTTPResponse r;
	
	curl = curl_easy_init();
	if(curl) {
		char gateway_url[100];
		strcpy(gateway_url, API_URL);
        
        if (discord->bot)
            strcat(gateway_url, "/gateway/bot");
        else
            strcat(gateway_url, "/gateway");

		struct curl_slist *chunk = NULL;
		string s;
    	init_string(&s);

    	char auth[100];
    	strcpy(auth, "Authorization: Bot ");
    	strcat(auth, discord->token);
    	chunk = curl_slist_append(chunk, auth);
    	chunk = curl_slist_append(chunk, "User-Agent: libdiscord");

		printf("=> Attempting to connect to %s\n", gateway_url);
		curl_easy_setopt(curl, CURLOPT_URL, gateway_url);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		/* Perform the request, res will get the return code */

		res = curl_easy_perform(curl);
		if (res != RESPONSE_OK) {
			char* errormsg;
			switch(res) {
				case SSL_ERROR:
					strcpy(errormsg, "Peer certificate cannot be authenticated with known CA certificates");
					break;
				default:
					strcpy(errormsg, "Unknown error code");
					break;
			}

			printf("libcurl error: %s\n", errormsg);
			free(errormsg);
			
			strcpy(r.content, errormsg);
			r.response_code = res;
			return r;
		}

		strcpy(r.content, s.ptr);
		r.response_code = res;
	    //FIXME: free(s.ptr);

		/* always cleanup */
		curl_slist_free_all(chunk);
		curl_easy_cleanup(curl);

		return r;
	}

	return r;
}
