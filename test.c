#include "src/discord.h"

int main() {
	struct Discord discord;
	discord_init(
		&discord,
		"Mjc1NzI2Mzg2OTYwNzkzNjAw.C32ypA.FbkHlm1Ika86Jyo8zD0YY1aZTNE", // token
        true // is bot?
	);

	discord_connect(&discord);
}
