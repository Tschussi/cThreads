/*
 ============================================================================
 Name        : project2.c
 Author      : Kevin Hames
 Version     :
 Copyright   : Copyright 2016
 Description : Returns profits per region and total profit for a corporate
 company given .txt files filled with revenue and expenses for each shop.
 ============================================================================
 */

#include "data_analysis.h"

int main(void) {
	int shops = 1000; // shops per region
	int regions = 5; // # of regions
	bool debug = 0; // print debug statements
	threads(shops,regions,debug);
	return EXIT_SUCCESS;
}
