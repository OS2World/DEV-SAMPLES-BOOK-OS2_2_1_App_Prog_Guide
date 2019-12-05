typedef struct _stockParms
{
   int  date[255];
   int  price[255];
   int  numentries;
} STOCKPARMS;

typedef struct _stockReturn
{
   int  date;
   int  price;
} STOCKRETURN;

extern void highPrice(STOCKPARMS, STOCKRETURN *);
extern void lowPrice(STOCKPARMS, STOCKRETURN *);
extern void averagePrice(STOCKPARMS, double *);

