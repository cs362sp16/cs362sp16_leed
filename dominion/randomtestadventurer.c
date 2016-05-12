#include <stdio.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#define MAX_TESTS 2000
int fail = 0;
// return value check
int error1 = 0;
// deck count
int error2 = 0;
// discard count
int error3 = 0;

int assertTrue(int n){
	if(n == 0){
		fail = 1;
		return 1;
	}
	else{
		return 0;
	}
}

void checkAsserts(){
	if(!fail){
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
	else{
		if(error1 > 0){
			printf("FAILED FUNCTION RETURN VALUE\n");
		}
		if(error2 > 0){
			printf("FAILED DECK COUNT\n");
		}
		if(error3 > 0){
			printf("FAILED DISCARD COUNT\n");
		}
	}
}

void checkAdventurerCard(struct gameState *g, int currentPlayer){
	int returnValue, preDiscardCount, preDeckCount;

	int preNumCards = numHandCards(g);
	preDiscardCount = g->discardCount[currentPlayer];
	preDeckCount = g->deckCount[currentPlayer];

	returnValue = adventurerCardEffect(g, currentPlayer);

	// Test return value of function
	if(assertTrue(!returnValue)){
		error1++;
	}

	// check that 2 cards were picked up
	int postNumCards = numHandCards(g);
	if(assertTrue(preNumCards+2 == postNumCards)){
		error2++;
	}

	int postDiscardCount = g->discardCount[currentPlayer];
	int postDeckCount = preDeckCount - g->deckCount[currentPlayer] - 2;

	if(assertTrue(postDiscardCount == (preDiscardCount + postDeckCount))){
		error3++;
	}
}

int main(int argc, char *argv[]){
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	int i,j,n,p, players, seed;
	struct gameState g;
	if(argc < 2){
		printf("Enter seed number in command line\n");
		exit(0);
	}


	SelectStream(rand()%10 + 1);
	PutSeed((rand()%10) + 1);
	seed = rand()%10 + 1;
	printf("Tesing adventurer card\n");

	for(n = 0;n < MAX_TESTS; n++){
		for(i=0;i<sizeof(struct gameState);i++){
			((char*)&g)[i] = floor(Random() * 256);
		}
		// have 2-4 players
		players = rand() %3 + 2;

		initializeGame(players, k, seed, &g);

		// set up game state
		p = rand() % players;
		g.whoseTurn = p;
		g.deckCount[p] = rand() % (MAX_DECK+1);
		for(j=0;j<g.deckCount[p];j++){
			g.deck[p][j] = rand() % treasure_map;
		}
		g.discardCount[p] = floor(Random() * MAX_DECK);
		for(j=0;j < g.handCount[p];j++){
			g.discard[p][j] = rand() % treasure_map;
		}
		g.handCount[p] = floor(Random() * MAX_HAND);
		g.hand[p][0] = adventurer;
		for(j=1;j < g.handCount[p];j++){
			g.hand[p][j] = rand() % treasure_map;
		}

		checkAdventurerCard(&g,p);

	}
	checkAsserts();
	printf("COMPLETED RANDOM TESTING\n");
	return 0;
}
