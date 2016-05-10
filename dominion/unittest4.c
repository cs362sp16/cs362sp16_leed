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

	a = scoreFor(1, &g);
	assertTrue(a, "Score for first player, should be 0");

	a = scoreFor(2, &g);
	assertTrue(a, "Score for second player, should be 0");

	checkAsserts();
	return 0;
}
