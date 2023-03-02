#include<stdlib.h>
#include<stdio.h>

// for an example usage of the stack i included some code to diplay how it could be used 
// to check it out set below value to of #define UsageExample to 1
// to see debug messages set define #debugMode to 1


 // #define UsageExample 1
 // #define DebugMode 1

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
* AKA Node 1 refers to node 0, Node 2 to Node 1 and so on.
*		
*		+-------------------------------+
*		|	  pointer to nothing 		|
*		|	-------------------------	|		Node 0
*		|	  data from current node	|
*		+-------------------------------+
*		+-------------------------------+
*		|	  pointer to Node above		|
*		|	-------------------------	|		Node 1
*		|	  data from current node	|
*		+-------------------------------+
*		+-------------------------------+
*		|	  pointer to Node above		|				
*		|	-------------------------	|		Node 2
*		|	  data from current node	|
*		+-------------------------------+
* 
push(): It inserts an element to the top of the stack. It takes O(1) time, as each node is inserted at the head/top of the linked list.
pop(): It removes an element from the top of the stack. It takes O(1) time, as the top always points to the newly inserted node.
peek(): It returns the top element of the stack.
size(): It returns the size of the stack, i.e., the total number of items in a stack.
isEmpty(): Returns a boolean value. It returns true if the stack is empty. Else, it returns false.
*/

// Initializing the general structure of our Node 

struct dataNode
{
	int dataThatIsStoredInNode;		// a integer to hold the data that we add to the node
	struct dataNode *pointerToNextNode;		// a pointer that points to the next node, by bointing to itselve.
};

struct dataNode *topNode;		// initilizing a standard node for working with the stack, here the top most node
struct dataNode *nextTopNode;		// initilizing a standard node for working with the stack, here node below the top most node
struct dataNode *temporaryNode;		// initilizing a standard node for working with the stack, here a temporary node where we can stor some data

int numberOfNodesInitialised;		// a integer for keeping track of the amount of created nodes

// the first stack opperator push to stack / add a node to the top of the stack
void push(int dataToStore) {
	if (topNode == NULL) 		//in case this is the first Node
	{
		topNode = (struct dataNode * )malloc(1 * sizeof(struct dataNode));		//reserve the memory necesary for storing all data for the new node
		topNode -> pointerToNextNode = NULL;		// make shure that pointer in the top most node is empty as ther will never be a node to point to
		topNode->dataThatIsStoredInNode = dataToStore;		// add the data that we want to store to the top most node
	}
	else		// if the previous condition is not fullfilled
	{
		temporaryNode = (struct dataNode * )malloc(1 * sizeof(struct dataNode));		//reserve the memory necesary for storing all data for the new node
		temporaryNode -> pointerToNextNode = topNode;		// take the pointer that points to the previous node and add it to this node
		temporaryNode -> dataThatIsStoredInNode = dataToStore;		// add the data that we want to store to the top most node 
		topNode = temporaryNode;		//make this temporary node our top most node by handing over the pointer from the temp node struktur to the top node struktur
	}
	numberOfNodesInitialised++;			// no matter wich case was executed befor we created a new node and therfor increase our counter 'numberOfNodesInitialised' by one unit
	#if DebugMode == 1
		printf("DBGMSG | Created a new node at the top of the Stack\n");
	#endif // DebugMode == 1
}
// a stack opperator to return the data value of the top most node
int peek(void) {
	return topNode->dataThatIsStoredInNode;		//return the data that is present if we acces the pointer of the top most node
}
// a stack opperator to return th data value of the top most node and remove the node from the stack
int pop(void) {
	int valueFromPopedNode = 0;		//initialise a var to later store the data from the top node
	nextTopNode = topNode;		// hand over the pointer from the future next (node that we holde to know where the previous node is), to get the top most node
	if (nextTopNode == NULL)		//if the next top node pointer is empety we know that the stck is empety 
	{
	#if DebugMode == 1
		printf("DBGMSG | Cant pop Value from Stack as stack is empty");
	#endif // DebugMode == 1
	return  -1;
	}
	else		//if the pointer is not equal to null 
	{
		nextTopNode = nextTopNode->pointerToNextNode;		 //get and return the pointer that points to the next node in the stack
	}
	valueFromPopedNode = topNode->dataThatIsStoredInNode;		// get the data value that is stored in the node and add ist to our variable we created before
	free(topNode);		// free the allocated memory
	topNode = nextTopNode;		//make the next node in the stack the now top most node in the stack 
	numberOfNodesInitialised--;		// decrease the value of the numberOfNodesInitialised variabele by one
	return valueFromPopedNode;		// retrn the value valueFromPopedNode
}
// a stack opperator to return the current ammounts of nodes in the stack
int size(void) {
	return numberOfNodesInitialised;		//return the variable counter numberOfNodesInitialised
}
// a stack opperator to check if the stack is empety if so return 1 else return 0
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
// a non essential oppertor to print the whole structure of the current stack
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
			printf("The stack is \n\n");
			printf("+--------+\n");
		while (nextTopNode != NULL)
		{
			printf("|    %d   |\n", nextTopNode->dataThatIsStoredInNode);
			printf("+--------+\n");
			nextTopNode = nextTopNode->pointerToNextNode;
		}
		printf("|  NULL  |\n");
		printf("+--------+\n\n");
		}
		

	#endif // DisplayStackFunktion == 1
	return;
}
// a example of how to use all opperators 
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

