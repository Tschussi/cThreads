/*
 * data_analysis.c
 *
 *  Created on: Oct 18, 2016
 *      Author: Kevin Hames
 *      Description: Methods for threads to run: filling revenue and expense arrays,
 *      calculating profit per shop, and total regional profit.
 */

#include "data_analysis.h"

void *dataFiller(void* sourceIn)
{
	sourceData *source = (sourceData*) sourceIn;  // to access struct
	FILE* myfile = fopen(source->sourceFileName,"r");
	for(int i=0; i<source->numObs; i++)
	{
		fscanf(myfile, "%lf", source->values++);
	}
	fclose(myfile);
	return 0;
}

void *totProfit(void* currVarIn)
{
	currVar *curr = (currVar*) currVarIn;
	for(int m = 0; m<curr->num_shops; m++)
		curr->Profit[m] = curr->Revenue[m]-curr->Expenses[m]- curr->Overhead[m];
	return 0;
}

void *regionProfit(void* currVarIn)
{
	currVar *curr = (currVar*) currVarIn;
	for(int n = curr->start_region; n<(curr->start_region + 1000); n++)
		curr->RegionProfit += curr->Profit[n];
	return 0;
}
