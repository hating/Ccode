#ifndef id3_h
#define id3_h
#define LENGTH 10

typedef struct Sample {
	int number;
	char outlook[LENGTH];
	char temperate[LENGTH];
	char humidity[LENGTH];
	char wind[LENGTH];
	char playTennis[LENGTH];
}Sample;

typedef struct NodeSample {
	Sample sample;
	NodeSample* next;
}NodeSample;

typedef struct AAA{
	char att[LENGTH];
	int Yes;
	int No;
	AAA *next;
}AAA;

typedef struct Rules{
	char rule1[LENGTH];
	char rule2[LENGTH];
	char rule3[LENGTH];
	char rule4[LENGTH];
	char result[LENGTH];
	Rules *next;
}Rules;


#endif
