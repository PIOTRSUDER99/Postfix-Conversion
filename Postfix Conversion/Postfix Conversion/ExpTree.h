#ifndef ExpTree_h
#define ExpTree_h

#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

struct node
{
	string data;
	node* left;
	node* right;
	bool isOperator;
	int value;
	node();
	node(string _data, node* _left, node* _right, bool isOperator);
	~node();
	node(const node &other);
	node& operator=(const node &other);
};

class ExpTree {

public:
	ExpTree();
	~ExpTree();

	void CreateTree(vector<string> postFix);
	void SetVariableValues(vector<int> values);
	int EvaluateTree();
	void inOrderTraversalandPrint(ostream &out);

private:
	node* root;
	node* createNode(string data, bool isOperator);
	bool isOperator(string s); //Returns false for parentheses
	void deleteTree(node* root);
	void listNodesWithOperands(node* root, vector<node*> *Nodes);
	int computeTree(node* root);
	void printTree(ostream &out, node *root);
};

#endif /* ExpTree_h */