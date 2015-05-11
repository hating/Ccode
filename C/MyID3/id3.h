#ifndef id3.h
#define id3.h
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
	NodeSample* next=NULL;
}NodeSample;

#endif
