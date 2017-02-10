#include "discord.h"
#include <curl/curl.h>
#include "curl_codes.h"

static char* API_URL = "https://discordapp.com/api";

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  	s->len = 0;
  	s->ptr = malloc(s->len+1);
  	if (s->ptr == NULL) {
    	fprintf(stderr, "malloc() failed\n");
    	exit(EXIT_FAILURE);
  	}
	s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
	size_t new_len = s->len + size*nmemb;
	s->ptr = realloc(s->ptr, new_len+1);
	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
  	}

	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}

struct HTTPResponse http_get(Discord *discord) {
	CURL *curl;
	CURLcode res;
	struct HTTPResponse r;
	
	curl = curl_easy_init();
	if(curl) {
		char gateway_url[100];
		strcpy(gateway_url, API_URL);
        
        if (discord->bot)
            strcat(gateway_url, "/gateway/bot");
        else
            strcat(gateway_url, "/gateway");

		struct curl_slist *chunk = NULL;
		struct string s;
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
	    free(s.ptr);

		/* always cleanup */
		curl_slist_free_all(chunk);
		curl_easy_cleanup(curl);

		return r;
	}

	return r;
}
