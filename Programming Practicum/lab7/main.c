#include "main.h"


int main(int argc, char const *argv[])
{

	node *root = newNode(5);
	root->left = newNode(4);
	root->right = newNode(12);
	root->right->left = newNode(13);
	root->right->right = newNode(2);
	root->left->left = newNode(8);


	printf("Size of the tree is %d\n",size(root));

	printf("Maximum depth of the tree is %d\n", maxDepth(root) );
	printPreorder(root);
	printf("\n");
	printInorder(root);
	printf("\n");

	node* bst = NULL;
	int input;
	scanf("%d", &input);
	while(input != -999){
		bst = insertBST(bst, input);
		scanf("%d", &input);
	}

	printInorder(bst);

	return 0;
}
