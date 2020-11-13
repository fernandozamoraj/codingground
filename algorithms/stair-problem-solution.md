###
Given a number stairs 1-n
and set K or leaps
Find all the possible paths to get from step 1 to n.
For example
lets say you have 10 steps

and you have set K = {2,5}
you get get to 
get there
2,2,2,2,2
5,5
with 15 steps
2,2,2,2,2,5
2,5,2,2,2,2
5,2,2,2,2,2
2,2,5,2,2,2
2,2,2,5,2,2
2,2,2,2,5,2

```c++
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;

int largestIndex;
int pathsCount;

class Node {
private:
	vector<Node*> children;
	int index;
public:

	
	Node(int index) {
		this->index = index;
	}

	void addChild(Node* child) {
		if (!contains(child)) {
			children.push_back(child);
		}
	}

	bool contains(Node* source) {
		bool found = false;
		for (Node* child : children) {
			if (source->index == child->index) {
				found = true;
			}
		}

		return found;
	}

	void printPaths(vector<int> &paths) {
		for (int i = 1; i < paths.size(); i++) {
			cout << ">" << (paths[i] - paths[i - 1]);
		}
		pathsCount++;
		cout << endl;
	}

	void print(vector<int> &paths) {
		vector<Node*> stack;

		paths.push_back(index);

		if (children.size() == 0) {
			printPaths(paths);
		}
		else
			for (int i = 0; i < children.size(); i++) {
				Node* child = children[i];
				child->print(paths);
				
			}
		paths.pop_back();
	}
};

vector<Node*> countDynamic(int n, vector<int> steps) {
	vector<Node*> allNodes;
	Node* root;

	//create all steps
	for (int i = 0; i <= n; i++) {
		Node* newNode = new Node(i);
		allNodes.push_back(newNode);
	}

	//add all steps to required for each step
	//only step zero will have all the variations
	for (int i = 0; i <= n; i++) {
		for (int step : steps) {
			if (i + step <= n) {
				allNodes[i]->addChild(allNodes[i + step]);
			}
		}
	}

	return allNodes;
}

int main() {

	int n = 11;
	vector<int> steps;
	steps.push_back(1);
	steps.push_back(2);
	steps.push_back(6);


	vector<Node*> allNodes = countDynamic(n, steps);
	largestIndex = n;

	vector<int> paths;
	pathsCount = 0;
	//paths are counted in the print but we could create 
	//a way to count them without priting... it will still be recursive though
	//use this approach to print and count non-recursively
	//https://www.geeksforgeeks.org/iterative-program-count-leaf-nodes-binary-tree/
	allNodes[0]->print(paths);
	cout << endl;
	cout << "there are" << pathsCount << " ways" << endl;

	//clean up
	for (size_t i=0; i < allNodes.size(); i++) {
		Node* temp = allNodes[i];
		delete temp;
		allNodes[i] = nullptr;
	}

	int a;
	cin >> a;
	return 0;
}
```