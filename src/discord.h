#ifndef DISCORD_H_
#define DISCORD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jansson.h>
#include <curl/curl.h>

#define RESPONSE_OK 0
#define SSL_ERROR 60

static char* API_URL = "https://discordapp.com/api";

typedef struct _string {
  char *ptr;
  size_t len;
} string;

typedef struct _wsclient {
    CURL *curl;    
} wsclient;

typedef struct _Discord {
    char token[60];
    _Bool bot;
    wsclient client;
} Discord;

typedef struct _HTTPResponse {
    char content[256];
    size_t response_code;
} HTTPResponse;

void init_string(string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, string *s);

extern HTTPResponse http_get(Discord *discord);
extern void discord_init(Discord *discord, char* token, _Bool isbot);
extern void discord_connect(Discord *discord);
extern void discord_cleanup(Discord *discord);
#endif
