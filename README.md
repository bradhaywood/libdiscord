# Installation

```bash
sh ./autogen.sh
./configure --prefix=/usr/local
make
make install
```

# Building

`cc -o bot bot.c -ldiscord -ljansson -lcurl`

# Dependencies

* libcurl (libcurl4-openssl-dev)
* jansson (https://github.com/akheron/jansson)

# Usage

**Please note that this library is *FAR* from completed. I'll update usage as features are added**

```c
#include <discord/discord.h>

int main() {
    Discord discord;

    // initialise the discord structure
    discord_init(
        &discord,
        "Your_lovely_token", // token
        1 // if this client will act as a bot
    );

    /* pass the discord struct to discord_connect
       which will initialise the gateway */
    discord_connect(&discord);
}
```
