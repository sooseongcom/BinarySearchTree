#include <iostream>
#include <cstring>
#include "TreeNode.h"
#include "BinarySearchTree.h"

using namespace std;

int main(void) {
	BinarySearchTree<int> bst;
	char cmd[100] = { 0 };
	char* buf = 0;
	int inpnum = 0;

	cout << "Type command \"insert <int num>\", \"delete <int num>\", \"print\" or \"exit\"." << endl;
	cout << "===============================" << endl;
	
	while (cin.getline(cmd, 99)) {
		buf = strtok(cmd, " ");

		if (strcmp(buf, "insert") == 0 || strcmp(buf, "i") == 0) {
			buf = strtok(NULL, " ");

			if (buf == NULL) {
				cout << "ERROR: Missing argument to 'insert'" << endl;
				continue;
			}

			inpnum = atoi(buf);
			bst.insert(inpnum);
		}
		else if (strcmp(buf, "delete") == 0 || strcmp(buf, "d") == 0) {
			buf = strtok(NULL, " ");

			if (buf == NULL) {
				cout << "ERROR: Missing argument to 'delete'" << endl;
				continue;
			}

			inpnum = atoi(buf);
			bst.deletion(inpnum);
		}
		else if (strcmp(buf, "print") == 0 || strcmp(buf, "p") == 0) {
			cout << "BST InOrder: " << bst << endl;
		}
		else if (strcmp(buf, "exit") == 0 || strcmp(buf, "d") == EOF) {
			break;
		}
		else {
			cout << "Command not found" << endl;
		}
	}

	return 0;
}