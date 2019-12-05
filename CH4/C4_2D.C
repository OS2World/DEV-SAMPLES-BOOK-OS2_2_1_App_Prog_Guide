/* c4_2d.c - will create the stock.dll file*/

#include <stdio.h>
#include "c4_2d.h"

/* Find the highest stock price */

void highPrice(STOCKPARMS stockparms, STOCKRETURN *stockreturn)
{
int i;

   stockreturn->date = stockreturn->price = 0;
   for (i=0;i<stockparms.numentries;i++) {
      if (stockreturn->price < stockparms.price[i]) {
         stockreturn->price = stockparms.price[i];
         stockreturn->date = stockparms.date[i];
      }
   }

}

/* Find the lowest stock price. */

void lowPrice(STOCKPARMS stockparms, STOCKRETURN *stockreturn)
{
int i;

   stockreturn->date = stockparms.date[0];
   stockreturn->price = stockparms.price[0];
   for (i=1;i<stockparms.numentries;i++) {
      if (stockreturn->price > stockparms.price[i]) {
         stockreturn->price = stockparms.price[i];
         stockreturn->date = stockparms.date[i];
      }
   }

}

/* Find the average stock price */

void averagePrice(STOCKPARMS stockparms, double *average)
{
int i,sum;
double avg;

   sum = 0;
   for (i=0;i<stockparms.numentries;i++)
         sum += stockparms.price[i];
   avg = (double) sum / (double) stockparms.numentries;
   *average = avg;
   return;

}
