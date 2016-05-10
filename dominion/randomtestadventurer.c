#include <stdio.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"

//int adventurerCardEffect(struct gameState *state, int currentPlayer, int *temphand){

int main(){
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	//int i,n,r,p;
	struct gameState g;

	SelectStream(2);
	PutSeed(3);

	printf("Tesing adventurer card\n");
	printf("RANDOM TESTS\n");

	
	return 0;
}
