#ifndef DISCORD_H_
#define DISCORD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>

typedef struct _Discord {
    char token[60];
    _Bool bot;
} Discord;

typedef struct _HTTPResponse {
    char content[256];
    size_t response_code;
} HTTPResponse;

extern HTTPResponse http_get(Discord *discord);
extern void discord_init(Discord *discord, char* token, _Bool isbot);
extern void discord_connect(Discord *discord);

void discord_cleanup(Discord *discord) {
    // Nothing to see here yet
}

#endif
