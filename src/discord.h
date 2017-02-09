#ifndef DISCORD_H
#define DISCORD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>

typedef struct Discord {
    char token[60];
    _Bool bot;
} Discord;

extern void discord_init(struct Discord *discord, char* token, _Bool isbot);
extern void discord_connect(struct Discord *discord);

#include "http.h"
#include "connection.h"

#endif
