#include "src/discord.h"

int main() {
	struct Discord discord;
	discord_setToken(
		&discord,
		"Mjc1NzI2Mzg2OTYwNzkzNjAw.C3uH-Q.5SLBAIJ5Icz1L9rYbXRjhHcNsYw"
	);

	discord_connect(&discord);
}