#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	Node *next;
};
typedef struct Node Node;


Node *ReverseList(Node *head)
{
	if (head == NULL || head->next == NULL)
		return NULL;
	Node *t, *p;
	p = head->next;
	head->next = NULL;
	while (p)
	{
		t = p->next;
		p->next = head->next;
		head->next = p;
		p = t;
	}
	return head;
}

void printList(Node *head)
{
	Node *ptr = head->next;

	if (head == NULL || head->next == NULL)
		return;

ode *ptr = head->next;

	while (ptr)
	{
		printf("%d  ", ptr->data);
		ptr = ptr->next;
	}
}

int main()
{
	Node head, node1, node2, node3;

	head.next = &node1;

	node1.data = 1;
	node1.next = &node2;

	node2.data = 2;
	node2.next = &node3;

	node3.data = 3;
	node3.next = NULL;

	Node *newhead = ReverseList(&head);

	printList(newhead);

	printf("\n");
	system("pause");
}
