#include <stdio.h>
#include "dominion.h"

int fail = 0;

void assertTrue(int n,char *msg){
	if(n != 0){
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
	assertTrue(a, "Initialize game");


	// adventurer card = 7, player 0
	a = customHand(0,&g,7);
	int b = handCard(5, &g);

	int temphand[10];
	a = adventurerCardEffect(&g, 0, temphand);
	assertTrue(a, "Testing adventurer card");
	
	int c = handCard(5, &g);
	assertTrue(b == c, "adventurer card should be replaced with a treasure card");

	checkAsserts();
	return 0;
}
