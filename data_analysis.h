/*
 * data_analysis.h
 *
 *  Created on: Oct 18, 2016
 *      Author: Kevin Hames
 *      Description: Structures and methods used for calculating corporate profit
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#ifndef DATA_ANALYSIS_H_
#define DATA_ANALYSIS_H_

typedef struct currentVariables
{
	int start_region;
	int num_shops;
	double *Revenue;
	double *Expenses;
	double *Overhead;
	double *Profit;
	double RegionProfit;
	bool beChatty;
} currVar;

typedef struct input_data
{
	char *sourceFileName;
	double *values;
	int numObs;
	bool beChatty;
} sourceData;

void *dataFiller(void* sourceIn); // fills revenue and expenses from txt files
void *totProfit(void* currVarIn); // calculates profit for each shop
void *regionProfit(void* currVarIn); // calculated profit for each region
int threads(int numObs, int numRegions, bool chattyl); // uses threads to calculate and print regional and total profits

#endif /* DATA_ANALYSIS_H_ */
