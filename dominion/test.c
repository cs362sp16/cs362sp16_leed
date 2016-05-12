#include <stdio.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"

int main(){
	int i,n,p;
	struct gameState g;
	SelectStream(2);
	PutSeed(3);

	printf("Tesing adventurer card\n");
	printf("RANDOM TESTS\n");

	for(n = 0;n < 100; n++){
		for(i=0;i<sizeof(struct gameState);i++){
			((char*)&g)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		g.deckCount[p] = floor(Random() * MAX_DECK);
		g.discardCount[p] = floor(Random() * MAX_DECK);
		g.handCount[p] = floor(Random() * MAX_HAND);
		drawCard(p, &g);
	}
	return 0;
}
