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
	struct NodeSample* next;
}NodeSample;

typedef struct AAA{
	char att[LENGTH];
	int Yes;
	int No;
	struct AAA *next;
}AAA;

typedef struct Tree_Node{
	char root[LENGTH];
	char leaf[LENGTH];
	char branch_name[4][LENGTH];
	struct Tree_Node *childNode[4];
	
}Tree_Node;

#endif
