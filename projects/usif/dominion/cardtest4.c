#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// The following is a unit test for the adventurer card function within the dominion.c/dominon.h file

void testAdventurerCard() {
	srand(time(NULL));
	int seed = rand();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	struct gameState g;
	initializeGame(2, k, seed, &g);
	int choice1 = -1, 
	    choice2 = -1,
	    choice3 = -1;	
	int card = adventurer;
	int bonus = 0;
	int handPos = 1;
	int player1 = 0;
	int player2 = 1;
	int initialHandCount = g.handCount[player1];
	int initialHandCount2 = g.handCount[player2];
	int initialDeckCount2 = g.deckCount[player2];
	int originalSupply[10];
	int i;
	int success = 1;
	for (i = 0; i < 10; i++) {
		originalSupply[i] = g.supplyCount[i];
	}

	printf("--------------- TESTING CARD: Adventurer ---------------\n");
	printf("Test 1: Call card function\n");
	if (cardEffect(card, choice1, choice2, choice3, &g, handPos, &bonus) == 0) {
		printf("adventurerCard(): PASS when test contains return value == 0\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains return value == 0\n");
	}

	printf("Test 2: Check player 1 hand count\n");
	if (g.handCount[player1] == (initialHandCount + 1)) {
		printf("adventurerCard(): PASS when test contains handCount that is 1 more than the previous handCount\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains handCount that is 1 more than the previous handCount\n");
	}

	printf("Test 3: Check played card count\n");
	if (g.playedCardCount == 1) {
		printf("adventurerCard(): PASS when test contains playedCardCount of 1\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains playedCardCount of 1\n");
	}

	printf("Test 4: Check first card player 1 draws\n");
	int newCard1 = g.hand[player1][g.handCount[player1] - 2];
	if (newCard1 == copper || newCard1 == silver || newCard1 == gold) {
		printf("adventurerCard(): PASS when test contains the first new card that is copper, silver, or gold\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains the first new card that is copper, silver, or gold\n");
	}

	printf("Test 5: Check second card player 1 draws\n");
	int newCard2 = g.hand[player1][g.handCount[player1] - 1];
	if (newCard2 == copper || newCard2 == silver || newCard2 == gold) {
		printf("adventurerCard(): PASS when test contains the second new card that is copper, silver, or gold\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains the second new card that is copper, silver, or gold\n");
	}

	printf("Test 6: Check player 2 deck count state is unchanged\n");
	if (g.deckCount[player2] == initialDeckCount2) {
		printf("adventurerCard(): PASS when test contains deckCount of player 2 state unchanged\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains deckCount of player 2 state unchanged\n");
	}

	printf("Test 7: Check player 2 hand count state is unchanged\n");
	if (g.handCount[player2] == initialHandCount2) {
		printf("adventurerCard(): PASS when test contains handCount of player 2 state unchanged\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains handCount of player 2 state unchanged\n");
	}

	printf("Test 8: Check victory card state supply is unchanged\n");
	if (g.supplyCount[estate] == 8 && g.supplyCount[duchy] == 8 && g.supplyCount[province] == 8) {
		printf("adventurerCard(): PASS when test contains victory card state unchanged\n");
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains victory card state unchanged\n");
	}

	printf("Test 9: Check kingdom card state supply is unchanged\n");
	int isUnchanged = 1;
	for (i = 0; i < 10; i++) {
		if (g.supplyCount[i] != originalSupply[i]) {
			isUnchanged = 0;
		}
	}  
	if (isUnchanged) {
		printf("adventurerCard(): PASS when test contains supply of kingdom cards state unchanged\n"); 
	} else {
		success = 0;
		printf("adventurerCard(): FAIL when test contains supply of kingdom cards state unchanged\n"); 
	}

	if (success) {
		printf("\n\n---------------- TESTING SUCCESS --------------- \n");
	} else {
		printf("\n\n---------------- TESTING FAILURE --------------- \n");
	}
	printf("\n\n---------------- TESTING COMPLETE for Adventurer --------------- \n");
	
}

int main(int argc, char* argv[]) {
	testAdventurerCard();
	return 0;
}
