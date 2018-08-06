#include "dominion.h"
#include <stdio.h>

// The following is a unit test for the newGame function within the dominion.c/dominon.h file

void testNewGame() {
	struct gameState* gameStateTest;

	gameStateTest = NULL;
	gameStateTest = newGame();
	int success = 1;

	printf("----------------- TESTING FUNCTION: newGame() ---------------\n");
	printf("Test 1: Test for struct initialization\n");
	if (gameStateTest != NULL) {
		printf("newGame(): PASS when test contains a gameState struct not NULL\n");
	} else {
		printf("newGame(): FAIL when test contains a gameState struct not NULL\n");
		success = 0;
	}
	if (success) {
		printf("\n----------------- TESTING SUCCESS ---------------\n");
	} else {
		printf("\n----------------- TESTING FAILURE ---------------\n");
	}
	printf("\n----------------- TESTING COMPLETE for newGame() ---------------\n");
}

int main(int argc, char* argv[]) {
	testNewGame();
	return 0;
}
