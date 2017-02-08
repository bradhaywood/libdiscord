#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "http/http.h"

void discord_setToken(struct Discord *discord, char* token) {
	strcpy(discord->token, token);
}

void discord_connect(struct Discord *discord) {
	struct HTTPResponse r = http_get(discord);
	if (r.response_code != 0) {
		printf("There was an error\n");
		exit(1);
	}
	else {
		printf("%s\n", r.content);
	}
}

