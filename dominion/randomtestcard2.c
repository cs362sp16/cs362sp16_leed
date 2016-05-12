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
	if(fail){
		printf("FAILED TESTS DETECTED\n");
	}
}

void checkCouncilRoomCard(struct gameState *g, int currentPlayer){
	int returnValue, preDeckCount, preNumBuys, postNumBuys;

	int preNumCards = numHandCards(g);
	preDeckCount = g->deckCount[currentPlayer];
	preNumBuys = g->numBuys;

	returnValue = cardEffect(council_room,0,0,0,g,0,0);

	// Test return value of function
	assertTrue(!returnValue);

	// check that 4 cards were picked up and smithy card was discarded
	int postNumCards = numHandCards(g);
	assertTrue(preNumCards+4 == postNumCards);

	int postDeckCount = g->deckCount[currentPlayer];

	// check that 3 cards were removed from the deck
	assertTrue(preDeckCount == (postDeckCount+4));

	postNumBuys = g->numBuys;
	assertTrue(preNumBuys == (postNumBuys+1));
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
	seed = atoi(argv[1]);
	printf("RANDOM TESTING FOR COUNCIL ROOM CARD\n");

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

		//make at least 4 cards left in the user's deck
		g.deckCount[p] = rand() % (MAX_DECK+4);

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
		g.hand[p][0] = council_room;
		for(j=1;j < g.handCount[p];j++){
			g.hand[p][j] = rand() % treasure_map;
		}

		checkCouncilRoomCard(&g,p);
	}
	checkAsserts();
	printf("COMPLETED RANDOM TESTING\n");
	return 0;
}

