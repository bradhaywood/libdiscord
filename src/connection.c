#include "discord.h"
void discord_init(struct Discord *discord, char* token, _Bool isbot) {
	strcpy(discord->token, token);
    discord->bot = isbot;
}

void discord_connect(struct Discord *discord) {
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

        json_t *data, *wsurl, *shards;
        shards = json_object_get(root, "shards");
        wsurl  = json_object_get(root, "url");
        printf("Shards: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(shards));
        printf("WS URL: %s\n", json_string_value(wsurl));
		printf("%s\n", r.content);
	}
}
