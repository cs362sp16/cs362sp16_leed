#include <stdio.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#define MAX_TESTS 2000
int fail = 0;
int cardDiscard = 0;

int assertTrue(int n){
	if(n == 0){
		fail = 1;
		return 1;
	}
	return 0;
}

void checkAsserts(){
	if(fail){
		printf("FAILED TESTS DETECTED\n");
		printf("FAILED DISCARD: %d times\n",cardDiscard);
	}
}

void checkVillageCard(struct gameState *g, int currentPlayer){
	int returnValue, preDeckCount, preNumActions, postNumActions;

	int preNumCards = numHandCards(g);
	preDeckCount = g->deckCount[currentPlayer];

	// By default each player only gets 1 action per turn
	g->numActions = 1;
	preNumActions = g->numActions;
	
	returnValue = cardEffect(village,0,0,0,g,0,0);

	// Test return value of function
	assertTrue(!returnValue);

	// check that 1 card was picked up and village was discarded from hand
	int postNumCards = numHandCards(g);
	assertTrue(preNumCards == postNumCards);

	int postDeckCount = g->deckCount[currentPlayer];

	// check that 1 card was removed from the deck
	if(assertTrue(preDeckCount == (postDeckCount+1))){
		cardDiscard++;
	}

	postNumActions = g->numActions;
	assertTrue(preNumActions == (postNumActions-2));
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
	printf("RANDOM TESTING FOR VILLAGE CARD\n");

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
		g.deckCount[p] = rand() % (MAX_DECK+1);

		// fill deck randomly
		for(j=0;j<g.deckCount[p];j++){
			g.deck[p][j] = rand() % treasure_map;
		}
		g.discardCount[p] = floor(Random() * MAX_DECK);
		for(j=0;j < g.handCount[p];j++){
			g.discard[p][j] = rand() % treasure_map;
		}
		g.handCount[p] = floor(Random() * MAX_HAND);

		// give village
		g.hand[p][0] = village;
		for(j=1;j < g.handCount[p];j++){
			g.hand[p][j] = rand() % treasure_map;
		}

		checkVillageCard(&g,p);
	}
	checkAsserts();
	printf("COMPLETED RANDOM TESTING\n");
	return 0;
}

