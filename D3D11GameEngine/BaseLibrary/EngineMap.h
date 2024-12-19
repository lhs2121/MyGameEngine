#pragma once
#include "Interface.h"

template<typename T>
struct Pair
{
	Pair()
	{
	}
	Pair(int _First, T _Second) : First(_First), Second(_Second)
	{
	}
	int First;
	T Second;
};

template<typename T>
struct Bucket
{
	Pair<T> pair;
	Bucket* Left = nullptr;
	Bucket* Right = nullptr;
};

template<typename T>
class Map
{
public:
	Map() {};
	~Map() {};
	void Insert(Pair<T>&& _Pair)
	{
		if (Root == nullptr)
		{
			Bucket<T>* NewBucket = new Bucket<T>();
			(*NewBucket).pair = _Pair;
			Root = NewBucket;

			return;
		}

		Bucket<T>* NewBucket = AllocBucket(_Pair.First, Root);
		if (NewBucket != nullptr)
		{
			NewBucket->pair = _Pair;

		}
	}

private:
	Bucket<T>* AllocBucket(int CompareKey, Bucket<T>* _Bucket)
	{
		if (CompareKey == _Bucket->pair.First)
		{
			return nullptr;
		}

		if (CompareKey > _Bucket->pair.First)
		{
			if (_Bucket->Right == nullptr)
			{
				_Bucket->Right = new Bucket<T>();
				return _Bucket->Right;
			}
			return AllocBucket(CompareKey, _Bucket->Right);
		}

		if (CompareKey < _Bucket->pair.First)
		{
			if (_Bucket->Left == nullptr)
			{
				_Bucket->Left = new Bucket<T>();
				return _Bucket->Left;
			}
			return AllocBucket(CompareKey, _Bucket->Left);
		}

		return nullptr;
	}

	Bucket<T>* Root = nullptr;
};