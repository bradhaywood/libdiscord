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

typedef struct HTTPResponse {
    char content[256];
    size_t response_code;
} HTTPResponse;

extern struct HTTPResponse http_get(Discord *discord);
extern void discord_init(Discord *discord, char* token, _Bool isbot);
extern void discord_connect(Discord *discord);
#endif
