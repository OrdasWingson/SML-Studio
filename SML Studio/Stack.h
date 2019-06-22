#ifndef STACK_H
#define STACK_H
#include"StackNode.h"

template<typename NODETYPE> class Stack;

template<typename NODETYPE>
class Stack
{
public:
	Stack();
	~Stack();
	void push(const NODETYPE &); //запихнуть значение
	bool pop(NODETYPE &); //вытолкнуть значение
	bool isStackEmpty() const;
	void printStack();
	NODETYPE stackTop();
private:
	StackNode<NODETYPE> *lastNode;
};


template<typename NODETYPE>
Stack<NODETYPE>::Stack() :
	lastNode(0)
{
}

template<typename NODETYPE>
Stack<NODETYPE>::~Stack()
{
	
}

template<typename NODETYPE>
inline void Stack<NODETYPE>::push(const NODETYPE &value)
{
	StackNode<NODETYPE> *newPtr = new StackNode<NODETYPE>(value);

	if (isStackEmpty())
	{
		lastNode = newPtr;
	}
	else
	{
		newPtr->previousNode = lastNode;
		lastNode = newPtr;
	}
}

template<typename NODETYPE>
inline bool Stack<NODETYPE>::pop(NODETYPE &value)
{
	if (isStackEmpty())
		return false;
	else
	{
		StackNode<NODETYPE> *tempPtr = lastNode;
		lastNode = lastNode->previousNode;
		value = tempPtr->data;
		delete tempPtr;
		return true;
	}
}

template<typename NODETYPE>
inline bool Stack<NODETYPE>::isStackEmpty() const
{
	return lastNode == 0;
}

template<typename NODETYPE>
inline void Stack<NODETYPE>::printStack()
{
	if (isStackEmpty())
	{
		cout << "Stack is empty!\n";
		return;
	}

	StackNode<NODETYPE> *currentNode = lastNode;

	while (currentNode != 0)
	{
		cout << currentNode->data;
		currentNode = currentNode->previousNode;
	}
	cout << "\n\n";
}

template<typename NODETYPE>
inline NODETYPE Stack<NODETYPE>::stackTop()
{	
	return lastNode->getData();
}

#endif
