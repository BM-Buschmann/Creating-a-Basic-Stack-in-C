#include<stdlib.h>
#include<stdio.h>

// for an example usage of the stack i included some code to diplay how it could be used 
// to check it out set below value to of #define UsageExample to 1
// to see debug messages set define #debugMode to 1


 #define UsageExample 1
 #define DebugMode 1

#ifndef DebugMode
	#define DebugMode 0
#endif // !debugMode
#ifndef UsageExample
	#define UsageExample 0
#endif // !UsageExample
#if UsageExample == 1
#define DisplayStackFunktion 1
#endif // UsageExample == 1
#ifndef DisplayStackFunktion
	#define DisplayStackFunktion 0
#endif // !DisplayStackFunktion




/*
* the following example of a stack implementation is based on a linked list. Where every node stores the adres of the next node.
* AKA Node 0 refers to node 1, Node 1 to Node 2 and so on.

push(): It inserts an element to the top of the stack. It takes O(1) time, as each node is inserted at the head/top of the linked list.
pop(): It removes an element from the top of the stack. It takes O(1) time, as the top always points to the newly inserted node.
peek(): It returns the top element of the stack.
size(): It returns the size of the stack, i.e., the total number of items in a stack.
isEmpty(): Returns a boolean value. It returns true if the stack is empty. Else, it returns false.
*/

struct dataNode
{
	int dataThatIsStoredInNode;
	struct dataNode *pointerToNextNode;
};

struct dataNode *topNode;
struct dataNode *nextTopNode;
struct dataNode *temporaryNode;

int numberOfNodesInitialised;

void push(int dataToStore) {
	if (topNode == NULL) {
		topNode = (struct dataNode * )malloc(1 * sizeof(struct dataNode));
		topNode -> pointerToNextNode = NULL;
		topNode -> dataThatIsStoredInNode = dataToStore;
	}
	else
	{
		temporaryNode = (struct dataNode * )malloc(1 * sizeof(struct dataNode));
		temporaryNode -> pointerToNextNode = topNode;
		temporaryNode -> dataThatIsStoredInNode = dataToStore;
		topNode = temporaryNode;
	}
	numberOfNodesInitialised++;
	#if DebugMode == 1
		printf("DBGMSG | Created a new node at the top of the Stack\n");
	#endif // DebugMode == 1
}
int peek(void) {
	return topNode->dataThatIsStoredInNode;
}
int pop(void) {
	int valueFromPopedNode = 0; 
	nextTopNode = topNode;
	if (nextTopNode == NULL)
	{
	#if DebugMode == 1
		printf("DBGMSG | Cant pop Value from Stack as stack is empty");
	#endif // DebugMode == 1
	return  -1;
	}
	else
	{
		nextTopNode = nextTopNode->pointerToNextNode;
	}
	valueFromPopedNode = topNode->dataThatIsStoredInNode;
	free(topNode);
	topNode = nextTopNode;
	numberOfNodesInitialised--;
	return valueFromPopedNode;
}
int size(void) {
	return numberOfNodesInitialised;
}
int isEmpty() {
	if (topNode == NULL)
	{
		#if DebugMode == 1
				printf("DBGMSG | Stack is empty\n");
		#endif // DebugMode == 1
		return 1;
	}
	else
	{
		#if DebugMode == 1
				printf("DBGMSG | Stack is not yet empty\n");
		#endif // DebugMode == 1
		return 0;
	}
}
void display() {
	#if DisplayStackFunktion == 1
		nextTopNode = topNode;

		if (nextTopNode == NULL)
		{
			#if DebugMode == 1
					printf("DBGMSG | Cant displayStack as stack is empty");
			#endif // DebugMode == 1
			return;
		}
		else
		{
			printf("The stack is \n");
		while (nextTopNode != NULL)
		{
			printf("%d--->", nextTopNode->dataThatIsStoredInNode);
			nextTopNode = nextTopNode->pointerToNextNode;
		}
		printf("NULL\n\n");
		}
		

	#endif // DisplayStackFunktion == 1
	return;
}

int main() {
	#if UsageExample == 1
		int choice, value;
		printf("\nImplementation of Stack using a Linked List\n");
		while (1) {
			printf("1. Push\n2. Pop\n3. Peek\n4. Size\n5. Display The Current Stack\n6. Pop Until Stack Is Empty\n7. Exit\n");
			printf("\nEnter your choice : ");
			scanf_s("%d", &choice);
			switch (choice) {
			case 1:
				printf("\nEnter the value to insert: ");
				scanf_s("%d", &value);
				push(value);
				break;
			case 2:
				printf("Popped element is :%d\n", pop());
				break;
			case 3:
				printf("Top element in the Stack is :%d\n", peek());
				break;
			case 4:
				printf("Size of current Stack is :%d\n", size());
				break;
			case 5:
				display();
				break;
			case 6:
				while (isEmpty() == 0)
				{
					printf("Popped element is :%d\n", pop());
				}
				break;
			case 7:
				exit(0);
				break;
			default:
				printf("\nWrong Choice\n");
			}
		}
	#endif // UsageExample == 1
	#if UsageExample == 0 && DebugMode == 1
			printf("DBGMSG | Example Code for the ''Linked List stack'' is defined as 0 therfor the example will not run.\n ALL other debugMessages for This Linked List stack will still be executed");
	#endif // UsageExample == 0;

	return;
}

