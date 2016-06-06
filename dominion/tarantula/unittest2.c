#include <stdio.h>
#include "dominion.h"

int fail = 0;

void assertFalse(int n, char *msg){
	if(n != 0){
		printf("ASSERT FALSE PASSED: %s\n", msg);
	}
}

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

// Unit Test for shuffle function
int main(){
	struct gameState g;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	int a = initializeGame(2, k, 4, &g);
	assertTrue(a, "Test for duplicates in kingdom cards in initializeGame()");
	
	a = shuffle(1,&g);
	assertTrue(a, "Test shuffle for 1st player");

	a = shuffle(3,&g);
	assertFalse(a, "Test shuffle for 3rd player, should fail");

	checkAsserts();
	return 0;
}
