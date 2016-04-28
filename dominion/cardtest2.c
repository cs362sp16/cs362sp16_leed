#include <stdio.h>
#include "dominion.h"

int fail = 0;

void assertTrue(int n,char *msg){
	if(n == 0){
		printf("FAILED ASSERT: %s\n", msg);
		fail = 1;
	}
}

void checkAsserts(){
	if(!fail){
		printf("TEST SUCCESSFULLY COMPLETED\n");
	}
}

// Test for scoreFor function for each player
int main(){
	struct gameState g;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	int a = initializeGame(2, k, 4, &g);
	assertTrue(a==0, "Initialize game");

	// initial cards are 5
	int totalCard = numHandCards(&g);

	// smithy card = 13, player 0
	a = customHand(0,&g,13);

	// total cards are 6
	totalCard = numHandCards(&g);

	// smithy card should add 3 cards and take away the smithy card
	a = smithyCardEffect(&g,0,5);
	totalCard = numHandCards(&g);
	assertTrue(totalCard == 8, "smithy adds 3 cards, should have 8 cards");
	
	checkAsserts();
	return 0;
}
