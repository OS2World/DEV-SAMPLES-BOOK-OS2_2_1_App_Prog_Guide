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

//extern double averagePrice(STOCKPARMS);
//extern int lowPrice(STOCKPARMS, STOCKRETURN*);
//extern int highPrice(STOCKPARMS, STOCKRETURN*);

