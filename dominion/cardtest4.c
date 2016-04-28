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

	// great hall card = 16, player 0
	a = customHand(0,&g,16);

	// total cards are 6
	totalCard = numHandCards(&g);

	// call cardEffect with random parameters
	int temp[10];
	a = cardEffect(16,1,2,3,&g,5,temp);
	
	totalCard = numHandCards(&g);
	assertTrue(totalCard == 6, "village gets 1 card, should have 6 cards");
		
	assertTrue(g.numActions == 2, "Add 1 actions for a total of 2 actions");

	checkAsserts();
	return 0;
}
