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

// Test for whoseTurn function
int main(){
	struct gameState g;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	int a = initializeGame(2, k, 4, &g);

	a = shuffle(1,&g);
	assertTrue(a, "Testing shuffle");

	a = whoseTurn(&g);
	assertTrue(a, "Testing whose turn, first player indexed at 0\n");

	checkAsserts();
	return 0;
}
