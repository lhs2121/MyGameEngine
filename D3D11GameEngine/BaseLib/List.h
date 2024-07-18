#pragma once

struct Node
{
	~Node();
	void* ObjectPtr = nullptr;
	Node* PrevPtr = nullptr;
	Node* NextPtr = nullptr;
};
class List
{
	~List();
public:
	void Add(int _Size, void* NewPtr);
	void Delete(int _Index);

	Node* FirstNode = nullptr;
};