#ifndef STACKNODE_H
#define STACKNODE_H

template<typename TYPE> class Stack;


template<typename TYPE>
class StackNode
{
	friend class Stack<TYPE>;

public:
	StackNode(const TYPE&);
	~StackNode();
	TYPE getData() const;
private:
	TYPE data; //data of node
	StackNode<TYPE> *previousNode; 
};

template<typename TYPE>
StackNode<TYPE>::StackNode(const TYPE& newData) :
	data(newData), previousNode(0)
{

}

template<typename TYPE>
StackNode<TYPE>::~StackNode()
{

}

template<typename TYPE>
TYPE StackNode<TYPE>::getData() const
{
	return data;
}

#endif

