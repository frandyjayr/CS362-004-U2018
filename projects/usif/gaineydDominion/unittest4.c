#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

// The following is a unit test for the supplyCount function within the dominion.c/dominon.h file

void testSupplyCount() {
	struct gameState* g = malloc(sizeof(struct gameState));
	int success = 1;
	int card1 = 1,
	    card2 = 2,
            card3 = 3;
	g->supplyCount[card1] = -1;
	g->supplyCount[card2] = 0;
	g->supplyCount[card3] = 1;

	printf("--------------- TESTING FUNCTION: supplyCount() ---------------\n");
	printf("Test 1: Test negative number supply\n");
	if (supplyCount(card1, g) == -1) {
		printf("supplyCount(): PASS when test contains state->supplyCount[card1] == -1\n");
	} else {
		success = 0;
		printf("supplyCount(): FAIL when test contains state->supplyCount[card1] == -1\n");
	}
	
	printf("Test 2: Test zero supply\n");
	if (supplyCount(card2, g) == 0) {
		printf("supplyCount(): PASS when test contains state->supplyCount[card2] == 0\n");
	} else {
		success = 0;
		printf("supplyCount(): FAIL when test contains state->supplyCount[card2] == 0\n");
	}
	
	printf("Test 3: Test positive number supply\n");
	if (supplyCount(card3, g) == 1) {
		printf("supplyCount(): PASS when test contains state->supplyCount[card3] == 1\n");
	} else {
		success = 0;
		printf("supplyCount(): FAIL when test contains state->supplyCount[card3] == 1\n");
	}	

	if (success) {
		printf("\n--------------- TESTING SUCCESS ---------------\n");
	} else {
		printf("\n--------------- TESTING FAILURE ---------------\n");
	}
	printf("\n--------------- TESTING COMPLETE for supplyCount() ---------------\n");
	
}

int main(int argc, char* argv[]) {
	testSupplyCount();
	return 0;
}
