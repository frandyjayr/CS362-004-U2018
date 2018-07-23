#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

// The following is a unit test for the isGameOver function within the dominion.c/dominon.h file

void testIsGameOver() {
	struct gameState* g = malloc(sizeof(struct gameState));
	int success = 1;
	// Test 1 to see if province stack is empty	
	g->supplyCount[province] = 0;

	printf("--------------- TESTING FUNCTION: isGameOver() ---------------\n");
	printf("Test 1: Test when province supply is 0\n");
	if (isGameOver(g)) {
		printf("isGameOver(): PASS when gameState contains state->supplyCount[province] == 0\n");
	} else {
		success = 0;
		printf("isGameOver(): FAIL when gameState contains state->supplyCount[province] == 0\n");
	}

	// Test 2 to see if any three piles (not including province) are empty  
	int nonEmpty = 1,
	    empty = 0,
	    i;

	for (i = 0; i < treasure_map + 1; i++) {
		g->supplyCount[i] = nonEmpty;
	} 
	g->supplyCount[copper] = empty;
	g->supplyCount[silver] = empty;
	g->supplyCount[gold] = empty;

	printf("Test 2: Test when 3 supply stacks are empty\n");
	if (isGameOver(g)) {
		printf("isGameOver(): PASS when gameState contains 3 empty stacks\n");
	} else {
		success = 0;
		printf("isGameOver(): FAIL when gameState contains 3 empty stacks\n");
	}

	// Test 3 to see if the game does NOT end if province is nonempty and less than 3 stacks are empty
	for (i = 0; i < treasure_map + 1; i++) {
		g->supplyCount[i] = nonEmpty;
	} 
	g->supplyCount[copper] = empty;
	g->supplyCount[silver] = empty;

	printf("Test 3: Test when 2 supply stacks are empty\n");
	if (!isGameOver(g)) {
		printf("isGameOver(): PASS when gameState contains less than 3 empty stacks and province is non-empty\n");
	} else {
		success = 0;
		printf("isGameOver(): FAIL when gameState contains less than 3 empty stacks and province is non-empty\n");
	}

	if (success) {
		printf("\n-------------- TESTING SUCCESS --------------- \n");
	} else {
		printf("\n-------------- TESTING FAILURE --------------- \n");
	}
	printf("\n-------------- TESTING COMPLETE for isGameOver() --------------- \n");
}

int main(int argc, char* argv[]) {
	testIsGameOver();
	return 0;
}
