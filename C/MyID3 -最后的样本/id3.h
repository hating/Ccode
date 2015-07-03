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

double lg2(double n);
AAA *addNodeAAA(AAA *Ahead,char *s);
AAA *find(char *compare,AAA *source);
double val_entropy(NodeSample *head);
int att_val(char branchs[][20],NodeSample *head,char *attrid);
double att_entropy(int loop,NodeSample *head);
NodeSample *pick_items(char *attrid,char *branchs,NodeSample *head);
Tree_Node *ID3(NodeSample *head);
void interface(void);
void readDrillorTestSample(char *file);
void inputDrillSample(void);
void inputTestSample(void);
void printResult(Tree_Node *Result,int num);
Tree_Node *showRules(void);
void match(NodeSample *node,Tree_Node *tree);
void showTestResult(Tree_Node *tree);
void statistics(void);
void exitProgram(void);

#endif
