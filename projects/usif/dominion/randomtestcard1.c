#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 6

enum Fails {cardEffectFail = 0, discardCardFail, numActionsFail, drawCardFail, handCountFail, deckCountFail};  

// The following program executes random tests for the Villagecard

void randomizeGameState(struct gameState* G, int* p) {
	// The following code was taken from CS362 Lecture
	int i;
	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)G)[i] = rand() % 256 + 1;
	}
	*p = rand() % (MAX_PLAYERS);
	G->numPlayers = *p;
	G->playedCardCount = rand() % MAX_DECK;
	G->deckCount[*p] = rand() % (MAX_DECK + 1);
	G->discardCount[*p] = rand() % (MAX_DECK + 1);
	G->handCount[*p] = rand() % (MAX_HAND + 1 - 1) + 1;
	G->whoseTurn = *p;
}

void testVillageCard(struct gameState* post, int* failedTests, int* passedTests, int* p) {
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int choice1 = 0,
	    choice2 = 0,
	    choice3 = 0; 
	int card = village;
	int bonus = 0;
	int handPos = 0;

	if (cardEffect(card, choice1, choice2, choice3, post, handPos, &bonus)) {
		failedTests[cardEffectFail]++;
	} else {
		passedTests[cardEffectFail]++;
	}

	// Call Draw card 
	if (drawCard(*p, &pre)) {
		failedTests[drawCardFail]++;
	} else {
		passedTests[drawCardFail]++;
	}

	// Increase number of actions by two
	pre.numActions = pre.numActions + 2;


	// Discard card and check for failures
	if (discardCard(handPos, *p, &pre, 0)) {
		failedTests[discardCardFail]++;	
	} else {
		passedTests[discardCardFail]++;
	}

	// Check to see if the number of actions is the same
	if (pre.numActions != post->numActions) {
		failedTests[numActionsFail]++;
	} else {
		passedTests[numActionsFail]++;
	}

	// Check to see if the player succesfully drew the right amount of cards
	if (pre.handCount[*p] != post->handCount[*p]) {
		failedTests[handCountFail]++;
	} else {
		passedTests[handCountFail]++;
	}

	// Check to see if the number of cards in the deck are the same
	if (pre.deckCount[*p] != post->deckCount[*p]) {
		failedTests[deckCountFail]++;
	} else {
		passedTests[deckCountFail]++;
	}
	
}

int main() {
	int iterations = 9000;
	printf("-------------------- TESTING VILLAGE CARD ---------------------\n");
	printf("NUMBER OF ITERATIONS: %i\n\n", iterations);
	srand(time(NULL));
	int* failedTests = malloc(sizeof(int) *	MAX_TESTS);
	int* passedTests = malloc(sizeof(int) * MAX_TESTS);
	int numberOfFailures = 0;
	int i;

	for (int i = 0; i < iterations; i++) {
		struct gameState *G = malloc(sizeof(struct gameState));
		int* p = malloc(sizeof(int));
		randomizeGameState(G,p);
		testVillageCard(G, failedTests, passedTests, p);
		free(G);
		free(p);
	}

	printf("Number of cardEffect() failures: %i\n", failedTests[cardEffectFail]);
	printf("Number of drawCard() failures: %i\n", failedTests[drawCardFail]);
	printf("Number of discardCard() failures: %i\n", failedTests[discardCardFail]);
	printf("Number of numActions failures: %i\n", failedTests[numActionsFail]);
	printf("Number of handCount failures: %i\n", failedTests[handCountFail]);
	printf("Number of deckCount failures: %i\n", failedTests[deckCountFail]);
	printf("\n");

	printf("Number of cardEffect() passes: %i\n", passedTests[cardEffectFail]);
	printf("Number of drawCard() passes: %i\n", passedTests[drawCardFail]);
	printf("Number of discardCard() passes: %i\n", passedTests[discardCardFail]);
	printf("Number of numActions passes: %i\n", passedTests[numActionsFail]);
	printf("Number of handCount passes: %i\n", passedTests[handCountFail]);
	printf("Number of deckCount passes: %i\n", passedTests[deckCountFail]);
	printf("\n");

	for (i = 0; i < MAX_TESTS; i++) {
		numberOfFailures = numberOfFailures + failedTests[i];
	}

	if (numberOfFailures == 0) {
		printf("RANDOM TESTS SUCCESSFULL!\n");
	} else {
		printf("RANDOM TESTS FAILURE!\n");	
	}
	return 0;	
	
}
