#include "discord.h"

void discord_init(Discord *discord, char* token, _Bool isbot) {
	strcpy(discord->token, token);
    discord->bot = isbot;
}

void discord_connect(Discord *discord) {
	struct HTTPResponse r;
    r = http_get(discord);
	if (r.response_code != 0) {
		printf("There was an error\n");
		exit(1);
	}
	else {
        json_t *root;
        json_error_t error;
        root = json_loads(r.content, 0, &error);
        if (!root) {
            printf("error: on line %d: %s\n", error.line, error.text);
            exit(1);
        }

        const char *wsurl;
        json_t *json_wsurl, *shards;
        shards = json_object_get(root, "shards");
        json_wsurl = json_object_get(root, "url");
        wsurl = json_string_value(json_wsurl);
        printf("Shards: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(shards));
        //strcpy(wsurl, json_string_value(wsurl));
        strcat((char*)wsurl, "?v=6&encoding=json");
        printf("=> Initiating websocket connection to: %s\n", wsurl);
	}
}
