#include <stdio.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#define MAX_TESTS 2000
int fail = 0;

void assertTrue(int n){
	if(n == 0){
		fail = 1;
	}
}

void checkAsserts(){
	if(!fail){
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
}

void checkSmithyCard(struct gameState *g, int currentPlayer){
	int returnValue, preDeckCount;

	int preNumCards = numHandCards(g);
	preDeckCount = g->deckCount[currentPlayer];

	// error checking for a deck size less than 3
	if(preDeckCount < 3){
		g->deckCount[currentPlayer] += 3;
		preDeckCount = g->deckCount[currentPlayer];
	}

	returnValue = smithyCardEffect(g, currentPlayer, 0);

	// Test return value of function
	assertTrue(!returnValue);

	// check that 3 cards were picked up and smithy card was discarded
	int postNumCards = numHandCards(g);
	assertTrue(preNumCards+2 == postNumCards);

	int postDeckCount = g->deckCount[currentPlayer];

	// check that 3 cards were removed from the deck
	assertTrue(preDeckCount == (postDeckCount+3));
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
	seed = rand()%10 + 1;
	printf("RANDOM TESTING FOR SMITHY CARD\n");

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

		//make at least 3 cards left in the user's deck
		g.deckCount[p] = rand() % (MAX_DECK+3);

		// fill deck randomly
		for(j=0;j<g.deckCount[p];j++){
			g.deck[p][j] = rand() % treasure_map;
		}
		g.discardCount[p] = floor(Random() * MAX_DECK);
		for(j=0;j < g.handCount[p];j++){
			g.discard[p][j] = rand() % treasure_map;
		}
		g.handCount[p] = floor(Random() * MAX_HAND);

		// give smithy card
		g.hand[p][0] = smithy;
		for(j=1;j < g.handCount[p];j++){
			g.hand[p][j] = rand() % treasure_map;
		}

		checkSmithyCard(&g,p);
	}
	checkAsserts();
	printf("COMPLETED RANDOM TESTING\n");
	return 0;
}

