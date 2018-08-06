#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define MAX_TESTS 5

enum Fails {cardEffectFail = 0, shuffleFail, drawCardFail, handCountFail, deckCountFail, treasureCountFail};  
 
// The following program executes random tests for the Adventurercard

void randomizeGameState(struct gameState* G, int* p) {
	int money[] = {copper, silver, gold};
	// The following code was taken from CS362 Lecture
	int i;
	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)G)[i] = rand() % 256 + 1;
	}
	*p = rand() % (MAX_PLAYERS);
	G->numPlayers = *p;
	G->playedCardCount = rand() % MAX_DECK;
	G->deckCount[*p] = rand() % (MAX_DECK + 1 - 3) + 3;
	G->discardCount[*p] = 0;
	G->handCount[*p] = rand() % (MAX_HAND + 1) ;
	G->whoseTurn = *p;

	int deckMax = G->deckCount[*p];
	int randomTreasurers = rand() % (deckMax + 1 - 3) + 3;
	// Put only treasure cards in the deck with a random amount
	 
	for (i = 0; i < randomTreasurers; i++) {	
		G->deck[*p][i] = money[rand() % 3]; 
	}
}

void testAdventurerCard(struct gameState* post, int* failedTests, int* passedTests, int* p) {
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int choice1 = 0,
	    choice2 = 0,
	    choice3 = 0; 
	int card = adventurer;
	int bonus = 0;
	int handPos = 0;
	int z = 0;
	int drawntreasure = 0;
	int cardDrawn = -1;
	int temphand[MAX_HAND]; 
	int shuffleAmount = 0;
	int shuffled = 0;
	int drawCardFailed = 0;
	int status;

	if (cardEffect(card, choice1, choice2, choice3, post, handPos, &bonus)) {
		failedTests[cardEffectFail]++;
	} else {
		passedTests[cardEffectFail]++;
	}

	

	while(drawntreasure<2){
		if (pre.deckCount[*p] <1){//if the deck is empty we need to shuffle discard and add to deck
	  		if (shuffle(*p, &pre) == 0) {
				shuffled = 1;
				shuffleAmount++;	
			}
		}

		status = drawCard(*p, &pre);
		if (status) {
			drawCardFailed = 1;
		} 
		cardDrawn = pre.hand[*p][pre.handCount[*p]-1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		  	drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			pre.handCount[*p]--; //this should just remove the top card (the most recently drawn one).
			z++;	
		}
      	}

	while(z-1>=0){
		pre.discard[*p][pre.discardCount[*p]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      	}

	// Check if any shuffle errors occurred 
	if (shuffleAmount == 0 && shuffled) {
		failedTests[shuffleFail]++;	
	} else {
		passedTests[shuffleFail]++;
	}

	// Check if any drawCard failures occurred
	if (drawCardFailed) {
		failedTests[drawCardFail]++;
	} else {
		passedTests[drawCardFail]++;	
	}

	// Check if the hand counts match
	if (pre.handCount[*p] != post->handCount[*p]) {
		failedTests[handCountFail]++;
	} else {
		passedTests[handCountFail]++;
	}
	
	// Check if the deck counts match
	if (pre.deckCount[*p] != post->deckCount[*p]) {
		failedTests[deckCountFail]++;
	} else {
		passedTests[deckCountFail]++;
	}	
	
	int i;	
	int preTreasureCount = 0;
	int postTreasureCount = 0;

	// Check if the number of treasures matches
	for (i = 0; i < pre.handCount[*p]; i++) {
		if (pre.hand[*p][i] == copper || pre.hand[*p][i] == silver || pre.hand[*p][i] == gold) {
			preTreasureCount++;
		}
	}
	for (i = 0; i < post->handCount[*p]; i++) {
		if (post->hand[*p][i] == copper || post->hand[*p][i] == silver || post->hand[*p][i] == gold) {
			postTreasureCount++;
		}
	}

	if (preTreasureCount != postTreasureCount) {
		failedTests[treasureCountFail]++;	
	} else {
		passedTests[treasureCountFail]++;
	}

}

int main() {
	int iterations = 9000;
	printf("-------------------- TESTING ADVENTURER CARD ---------------------\n");
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
		testAdventurerCard(G, failedTests, passedTests, p);
		free(G);
		free(p);
	}

	printf("Number of cardEffect() failures: %i\n", failedTests[cardEffectFail]);
	printf("Number of shuffle() failures: %i\n", failedTests[shuffleFail]);
	printf("Number of drawCard() failures: %i\n", failedTests[drawCardFail]);
	printf("Number of handCount failures: %i\n", failedTests[handCountFail]);
	printf("Number of deckCount failures: %i\n", failedTests[deckCountFail]);
	printf("Number of treasureCount failures: %i\n", failedTests[treasureCountFail]);
	printf("\n");

	printf("Number of cardEffect() passes: %i\n", passedTests[cardEffectFail]);
	printf("Number of shuffle() passes: %i\n", passedTests[shuffleFail]);
	printf("Number of drawCard() passes: %i\n", passedTests[drawCardFail]);
	printf("Number of handCount passes: %i\n", passedTests[handCountFail]);
	printf("Number of deckCount passes: %i\n", passedTests[deckCountFail]);
	printf("Number of treasureCount passes: %i\n", passedTests[treasureCountFail]);
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
