#include "src/discord.h"

int main() {
	struct Discord discord;
	discord_setToken(
		&discord,
		"MY_TOKEN_HERE"
	);

	discord_connect(&discord);
}
