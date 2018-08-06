#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

// The following is a unit test for the kingdomCards function within the dominion.c/dominon.h file

void testKingdomCards() {
	int k1 = 1;
	int k2 = 2;
	int k3 = 3;
	int k4 = 4;
	int k5 = 5;
	int k6 = 6;
	int k7 = 7;
	int k8 = 8;
	int k9 = 9;
	int k10 = 10;

	int success = 1;
	int* k = malloc(10 * sizeof(int));

	k = kingdomCards(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10);

	printf("--------------- TESTING FUNCTION: kingdomCards() ---------------\n");
	printf("Test 1: Test array slot 1 is correct\n");
	if (k[0] == 1) {
		printf("kingdomCards(): PASS when test contains k[0] == 1\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[0] == 1\n");
	}

	printf("Test 2: Test array slot 2 is correct\n");
	if (k[1] == 2) {
		printf("kingdomCards(): PASS when test contains k[1] == 2\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[1] == 2\n");
	}

	printf("Test 3: Test array slot 3 is correct\n");
	if (k[2] == 3) {
		printf("kingdomCards(): PASS when test contains k[2] == 3\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[2] == 3\n");
	}

	printf("Test 4: Test array slot 4 is correct\n");
	if (k[3] == 4) {
		printf("kingdomCards(): PASS when test contains k[3] == 4\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[3] == 4\n");
	}

	printf("Test 5: Test array slot 5 is correct\n");
	if (k[4] == 5) {
		printf("kingdomCards(): PASS when test contains k[4] == 5\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[4] == 5\n");
	}

	printf("Test 6: Test array slot 6 is correct\n");
	if (k[5] == 6) {
		printf("kingdomCards(): PASS when test contains k[5] == 6\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[5] == 6\n");
	}

	printf("Test 7: Test array slot 7 is correct\n");
	if (k[6] == 7) {
		printf("kingdomCards(): PASS when test contains k[6] == 7\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[6] == 7\n");
	}

	printf("Test 8: Test array slot 8 is correct\n");
	if (k[7] == 8) {
		printf("kingdomCards(): PASS when test contains k[7] == 8\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[7] == 8\n");
	}

	printf("Test 9: Test array slot 9 is correct\n");
	if (k[8] == 9) {
		printf("kingdomCards(): PASS when test contains k[8] == 9\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[8] == 9\n");
	}

	printf("Test 10: Test array slot 10 is correct\n");
	if (k[9] == 10) {
		printf("kingdomCards(): PASS when test contains k[9] == 10\n");
	} else {
		success = 0;
		printf("kingdomCards(): FAIL when test contains k[9] == 10\n");
	}

	if (success) {
		printf("\n--------------- TESTING SUCCESS ---------------\n");

	} else {
		printf("\n--------------- TESTING FAILURE ---------------\n");

	}
	printf("\n--------------- TESTING COMPLETE for kingdomCards() ---------------\n");
}

int main(int argc, char* argv[]) {
	testKingdomCards();
	return 0;
}
