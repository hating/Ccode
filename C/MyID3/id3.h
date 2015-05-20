#ifndef id3_h
#define id3_h
#define LENGTH 10

typedef struct Sample {
	int number;
	char item[4][LENGTH];
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

typedef struct Tree_Node{
	char Yes_or_No[LENGTH];
	char attrid[LENGTH];
	char attrvalue[LENGTH]; 
	Tree_Node *childNode[4];
}Tree_Node;
#endif
