#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "linkedlist.h"

void removeListNode(ListNode** h) {
	ListNode* toRemove = *h;
	*h = toRemove->next;
	free(toRemove);
}

ListNode* sortLL(long*arr) {
	ListNode* head = NULL;
	for (int i = 0; i < 256; i++) {
		if (arr[i] != 0) {
			addListNode(&head, buildListNode(i, arr[i]));
		}		
	}
	return head;	
}

ListNode* buildListNode(int ascii, long freq) {
	ListNode* ret = malloc(sizeof(ListNode));
	ret->next = NULL;
	ret->ptr = malloc(sizeof(TreeNode));
	ret->ptr->label = ascii;
	ret->ptr->count = freq;
	ret->ptr->left = NULL;
	ret->ptr->right = NULL;
	return ret;	
}



void addListNode(ListNode** head, ListNode* add) {
	if (*head == NULL) {
		*head = add;
		return;
	}
	//ListNode** cur = head;
	while (*head != NULL) {
		if ((*head)->ptr->count > add->ptr->count) { //if current node is more frequent than node to be added
			ListNode* temp = *head;
			*head = add;
			(*head)->next = temp;
			return;
		}
		else if ((*head)->ptr->count == add->ptr->count) { //if counts are equal
			if ((*head)->ptr->label > add->ptr->label) { //if ASCII of node to be added is smaller
				ListNode* temp = *head;
				*head = add; 
				(*head)->next = temp;
				return;
			}
		}
		head = &((*head)->next);
	}
	*head = add;
	return;
}

void sorted(ListNode* head, char* file) {
	if (head == NULL) {return;}
	FILE* f = fopen(file, "w");
	if (f == NULL) {
		printf("can't open sorted file.\n");
		exit(1);
	}
	ListNode* cur = head;
	while (cur != NULL) {
		fprintf(f, "%c:%ld\n",(char)cur->ptr->label,cur->ptr->count);
		cur = cur->next;
	}
	fclose(f);
}
