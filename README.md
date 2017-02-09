# Building

`cc -o bot bot.c -lcurl -ljansson`

# Dependencies

* libcurl (libcurl4-openssl-dev)
* jansson (https://github.com/akheron/jansson)

# Usage

**Please note that this library is *FAR* from completed. I'll update usage as features are added**

```c
#include "src/discord.h"

int main() {
    struct Discord discord;

    // initialise the discord structure
    discord_init(
        &discord,
        "Your_lovely_token", // token
        true // if this client will act as a bot
    );

    /* pass the discord struct to discord_connect
       which will initialise the gateway */
    discord_connect(&discord);
}
```
