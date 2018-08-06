#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The following is a unit test for the village card function within the dominion.c/dominon.h file

void testVillageCard() {
	srand(time(NULL));
	int seed = rand();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	struct gameState g;
	initializeGame(2, k, seed, &g);
	int choice1 = -1, 
	    choice2 = -1,
	    choice3 = -1;	
	int card = village;
	int bonus = 0;
	int handPos = 1;
	int player1 = 0;
	int player2 = 1;
	int initialDeckCount = g.deckCount[player1];
	int initialHandCount = g.handCount[player1];
	int initialDeckCount2 = g.deckCount[player2];
	int initialHandCount2 = g.handCount[player2];
	g.hand[player1][handPos] = village;
	int originalSupply[10];
	int i;
	int success = 1;
	for (i = 0; i < 10; i++) {
		originalSupply[i] = g.supplyCount[i];
	}

	printf("--------------- TESTING CARD: village ---------------\n");
	printf("Test 1: Call the card function\n"); 
	if (cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus) == 0) {
		printf("villageCard(): PASS when test contains return value == 0\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains return value == 0\n");
	}

	printf("Test 2: Check player 1 deck count\n"); 
	if (g.deckCount[player1] == (initialDeckCount - 1)) {
		printf("villageCard(): PASS when test contains new deckCount that is 1 less than the previous deckCount\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains new deckCount that is 1 less than the previous deckCount\n");
	}

	printf("Test 3: Check player 1 hand count\n"); 
	if (g.handCount[player1] == initialHandCount) {
		printf("villageCard(): PASS when test contains handCount that is equal to the previous deckCount\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains handCount that is equal to the previous deckCount\n");
	}

	printf("Test 4: Check played card count\n"); 
	if (g.playedCardCount == 1) {
		printf("villageCard(): PASS when test contains playedCardCount of 1\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains playedCardCount of 1\n");
	}

	printf("Test 5: Check number of actions\n"); 
	if (g.numActions == 3) {
		printf("villageCard(): PASS when test contains numActions == 3\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains numActions == 3\n");
	}

	printf("Test 6: Check to see if village card is in the played cards pile\n"); 
	if (g.playedCards[g.playedCardCount - 1] == village) {
		printf("villageCard(): PASS when test contains village card in the playedCards pile\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains village card in the playedCards pile\n");
	}

	printf("Test 7: Check to see if player 2 deck count state is unchanged\n"); 
	if (g.deckCount[player2] == initialDeckCount2) {
		printf("villageCard(): PASS when test contains deckCount of player 2 state unchanged\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains deckCount of player 2 state unchanged\n");
	}

	printf("Test 8: Check to see if player 2 hand count state is unchanged\n"); 
	if (g.handCount[player2] == initialHandCount2) {
		printf("villageCard(): PASS when test contains handCount of player 2 state unchanged\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains handCount of player 2 state unchanged\n");
	}

	printf("Test 9: Check to see if victory card supply state is unchanged\n"); 
	if (g.supplyCount[estate] == 8 && g.supplyCount[duchy] == 8 && g.supplyCount[province] == 8) {
		printf("villageCard(): PASS when test contains supply of victory card state unchanged\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains supply of victory card state unchanged\n");
	}

	printf("Test 10: Check to see if kingdom card supply state is unchanged\n"); 
	int isUnchanged = 1;
	for (i = 0; i < 10; i++) {
		if (g.supplyCount[i] != originalSupply[i]) {
			isUnchanged = 0;
		}
	} 
	if (isUnchanged) {
		printf("villageCard(): PASS when test contains supply of kingdom cards state unchanged\n");
	} else {
		success = 0; 
		printf("villageCard(): FAIL when test contains supply of kingdom cards state unchanged\n");
	}	
	if (success) {
		printf("\n--------------- TESTING SUCCESS --------------- \n\n");
	} else {
		printf("\n--------------- TESTING FAILURE --------------- \n\n");
	}
	printf("\n--------------- TESTING COMPLETE for village --------------- \n\n");
}

int main(int argc, char* argv[]) {
	testVillageCard();
	return 0;
}
