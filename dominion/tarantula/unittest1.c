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
// Unit test for initializeGame
int main(){
	struct gameState g;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	int a = initializeGame(2, k, 4, &g);
	assertTrue(a, "Test for duplicates in kingdom cards in initializeGame()");
	
	int k2[10] = {smithy,smithy,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	a = initializeGame(3, k2, 4, &g);
	assertFalse(a, "Duplicate card, should fail");
	
	a = initializeGame(20, k, 4, &g);
	assertFalse(a, "Test above max players allowed, should fail");
	
	checkAsserts();
	return 0;
}
