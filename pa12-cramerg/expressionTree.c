#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

#ifndef BUILDTREE_OFF
TreeNode * buildExpressionTree(Scanner * s) {

	//FILL IN
	Token cur = nextToken(s);
	while (cur.type == T_RPAREN) {cur = nextToken(s);}
	if (cur.type == T_VAL) {return buildTreeNode(cur);}
	if (cur.type == T_ADD || cur.type == T_DIV || cur.type == T_MUL || cur.type == T_SUB) {return buildTreeNode(cur);}
	else if (cur.type == T_LPAREN) {
		TreeNode* exp1 = buildExpressionTree(s);
		TreeNode* op = buildExpressionTree(s);
		TreeNode* exp2 = buildExpressionTree(s);
		//cur = nextToken(s); //get rid of right parenthesis
		op->left = exp1;
		op->right = exp2;
		return op;
	}
	else {
		printf("Input string not valid.\n");
		exit(1);
	}
}
#endif

#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr) {
	
	//FILL IN
	if (t == NULL) {return;}
	makePostFix(t->left, fptr);
	makePostFix(t->right, fptr);
	if (t->t.type == T_VAL)
	{
		fprintf(fptr, "%f ", t->t.value);
	}
	else {
		switch (t->t.type) {
			case T_ADD: fprintf(fptr, "+ "); break;
			case T_SUB: fprintf(fptr, "- "); break;
			case T_MUL: fprintf(fptr, "* "); break;
			case T_DIV: fprintf(fptr, "/ "); break;
			default: exit(1);
		}
	}
	return;
}
#endif
