#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The following is a unit test for the smithy card function within the dominion.c/dominon.h file

void testSmithyCard() {
	srand(time(NULL));
	int seed = rand();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	//struct gameState* g = malloc(sizeof(struct gameState));
	struct gameState g;
	initializeGame(2, k, seed, &g);
	int choice1 = -1, 
	    choice2 = -1,
	    choice3 = -1;	
	int card = smithy;
	int bonus = 0;
	int handPos = 1;
	int player1 = 0,
	    player2 = 1;
	int initialDeckCount = g.deckCount[player1];
	int initialHandCount = g.handCount[player1];
	int initialDeckCount2 = g.deckCount[player2];
	int initialHandCount2 = g.handCount[player2];
	g.hand[player1][handPos] = smithy;
	int originalSupply[10];
	int i;
	int success = 1;
	for (i = 0; i < 10; i++) {
		originalSupply[i] = g.supplyCount[i]; 
	}
	printf("--------------- TESTING CARD: Smithy ---------------\n");
	printf("Test 1: Call the card function\n");
	if (cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus) == 0) {
		printf("smithyCard(): PASS when test contains return value == 0\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains return value == 0\n");
	}

	printf("Test 2: Check player 1 deck count\n");
	if (g.deckCount[player1] == (initialDeckCount - 3)) {
		printf("smithyCard(): PASS when test contains new deckCount that is 3 less than the previous deckCount\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains new deckCount that is 3 less than the previous deckCount\n");
	}

	printf("Test 3: Check player 1 hand count\n");
	if (g.handCount[player1] == (initialHandCount + 2)) {
		printf("smithyCard(): PASS when test contains handCount that is 2 greater than the previous deckCount\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains handCount that is 2 greater than the previous deckCount\n");
	}

	printf("Test 4: Check played card count\n");
	if (g.playedCardCount == 1) {
		printf("smithyCard(): PASS when test contains playedCardCount of 1\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains playedCardCount of 1\n");
	}

	printf("Test 5: Check if smithy is in played card pile\n");
	if ((g.playedCards[g.playedCardCount - 1]) == smithy) {
		printf("smithyCard(): PASS when test contains smithy in the playedCards pile\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains smithy in the playedCards pile\n");
	}

	printf("Test 6: Check if player 2 deck state is unchanged\n");
	if (g.deckCount[player2] == initialDeckCount2) {
		printf("smithyCard(): PASS when test contains deckCount of player 2 state unchanged\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains deckCount of player 2 state unchanged\n");
	}

	printf("Test 7: Check if player 2 hand state is unchanged\n");
	if (g.handCount[player2] == initialHandCount2) {
		printf("smithyCard(): PASS when test contains handCount of player 2 state unchanged\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains handCount of player 2 state unchanged\n");
	}

	printf("Test 8: Check if victory card supply state is unchanged\n");
	if (g.supplyCount[estate] == 8 && g.supplyCount[duchy] == 8 && g.supplyCount[province] == 8) {
		printf("smithyCard(): PASS when test contains supply of victory card state unchanged\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains supply of victory card state unchanged\n");
	}

	printf("Test 9: Check if kingdom card supply state is unchanged\n");
	int isUnchanged = 1;
	for (i = 0; i < 10; i++) {
		if (g.supplyCount[i] != originalSupply[i]) {
			isUnchanged = 0;
		}
	} 
	if (isUnchanged) {
		printf("smithyCard(): PASS when test contains supply of kingdom cards state unchanged\n");
	} else {
		success = 0;
		printf("smithyCard(): FAIL when test contains supply of kingdom cards state unchanged\n");
	}

	if (success) {
		printf("\n--------------- TESTING SUCCESS ---------------\n\n");
	} else {
		printf("\n--------------- TESTING FAILURE ---------------\n\n");
	}
	printf("\n--------------- TESTING COMPLETE for Smithy ---------------\n\n");
}

int main(int argc, char* argv[]) {
	testSmithyCard();
	return 0;
}
