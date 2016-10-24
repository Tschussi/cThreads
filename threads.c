/*
 * threads.c
 *
 *  Created on: Oct 18, 2016
 *      Author: Kevin Hames
 *      Description: Uses threads to calculate corporate profits from revenue and expense sheets
 */

#include "data_analysis.h"

int threads(int numObs, int numRegions, bool chattyl)
{
	// Variables to be used
	double revTotal, profitTot;
	int threadCount = 0;
	int numThreads = numRegions + 3; // 1 per region, expenses, and revenue
	int totalSize = numObs * numRegions;
	sourceData revenue;
	sourceData expenses;
	currVar corporate;
	currVar region[numRegions];
	pthread_t thr[numThreads];
	pthread_attr_t attr[numThreads];

	if(chattyl) // prints # of threads and total number of shops
		printf("numThreads = %i\t TotalSize = %i\n", numThreads, totalSize);

	for(int i =0; i<numThreads;i++) // setting attributes for threads
	{
		pthread_attr_init(&attr[i]);
		threadCount++;
	}

	// setting up data struct variables
	corporate.start_region = 0;
	corporate.num_shops = totalSize;
	corporate.Revenue = (double *) malloc(sizeof(double)*totalSize);
	corporate.Expenses = (double *) malloc(sizeof(double)*totalSize);
	corporate.Overhead = (double *) malloc(sizeof(double)*totalSize);
	corporate.Profit = (double *) malloc(sizeof(double)*totalSize);

	revenue.values = corporate.Revenue;
	revenue.numObs = totalSize;
	revenue.sourceFileName = "revenue.txt";

	expenses.values = corporate.Expenses;
	expenses.numObs = totalSize;
	expenses.sourceFileName = "expenses.txt";

	// Threads to read in revenue and expense values from txt files
	if(pthread_create(&thr[0],&attr[0], dataFiller, (void *) &revenue)==-1)
		perror("revenue failed");
	if(pthread_create(&thr[1], &attr[1], dataFiller, (void *) &expenses)==-1)
		perror("expenses failed");

	for(int k=0; k<2; k++)
	{
		pthread_join(thr[k],NULL);
	}

	if(chattyl) // checks to make sure revenue and expense arrays were populated correctly
	{
		printf("Revenue and Expenses\n");
		for(int a=0; a < 10; a++)
		{
			printf("%lf\t", corporate.Revenue[a]);
			printf("%lf\n", corporate.Expenses[a]);
		}
	}

	// OVERHEAD -------------------------------------------------------------------

	for(int j=0; j<totalSize; j++)
		revTotal += corporate.Revenue[j];

	if(chattyl) // checks total revenue
		printf("Total Revenue = %lf\n", revTotal);

	for(int l=0; l < totalSize;l++)
		corporate.Overhead[l] = corporate.Revenue[l] / revTotal * 1234567;

	if(chattyl) // checks to make sure overhead array was populated correctly
	{
		printf("Overhead\n");
		for(int b=0; b < 10; b++)
			printf("%lf\n", corporate.Overhead[b]);
	}

	// PROFIT ---------------------------------------------------------------------

	// Total Profit
	if(pthread_create(&thr[2],&attr[2], totProfit, (void *) &corporate)==-1)
		perror("Total Profit failed");

	pthread_join(thr[2],NULL);

	if(chattyl) // checks to make sure profit array was populated correctly
	{
		printf("Profit\n");
		for(int c = 0; c<10; c++)
			printf("%lf\n", corporate.Profit[c]);
	}
	// Regional Profit
	for(int p=0; p<numRegions;p++) // parameters for regional profit calculation
	{
		region[p].Profit = corporate.Profit;
		region[p].start_region = 1000*p;
	}

	// create regional calculation threads
	if(pthread_create(&thr[3],&attr[3], regionProfit, (void *) &region[0])==-1)
			perror("Region 1 Profit failed");
	if(pthread_create(&thr[4],&attr[4], regionProfit, (void *) &region[1])==-1)
			perror("Region 2 Profit failed");
	if(pthread_create(&thr[5],&attr[5], regionProfit, (void *) &region[2])==-1)
			perror("Region 3 Profit failed");
	if(pthread_create(&thr[6],&attr[6], regionProfit, (void *) &region[3])==-1)
			perror("Region 4 Profit failed");
	if(pthread_create(&thr[7],&attr[7], regionProfit, (void *) &region[4])==-1)
				perror("Region 5 Profit failed");

	for(int q=3;q<8;q++) // wait on threads
		pthread_join(thr[q],NULL);

	for(int r=0;r<numRegions;r++) // Print out regional and total Profit
	{
		printf("Region %i profit is %lf\n", r+1 , region[r].RegionProfit);
		profitTot += region[r].RegionProfit;
	}
	printf("The total profit is %lf", profitTot);

	return 0;
}

