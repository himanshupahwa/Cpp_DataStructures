#pragma once

#include <vector>
#include <queue>
#include <math.h> 

#include <iostream>
using namespace std;

namespace Heap
{
	class Node
	{
	private:
		int key;
	public:
		Node ( )
		{
		}

		Node ( int value )
		{
			key = value;
		}

		int getKey()
		{
			return key;
		}

		void SetValue(int value)
		{
			key = value;
		}

		Node& operator=(Node &n)
		{
			this->key = n.key;
			return *this;
		}
	};

	class ArrayHeapImpl
	{
		Node* heapArray;
		int maxSize;     // Size of this array
		int currentSize; // Number of nodes in the array
	public:

		ArrayHeapImpl(int size)
		{
			this->maxSize = size;
			this->currentSize = 0;
			heapArray = new Node[maxSize];
		}

		int getSize()
		{
			return currentSize;
		}

		bool isEmpty()
		{
			return ( currentSize == 0);
		}

		bool insert(int value)
		{
			if(currentSize == maxSize)
				return false;

			Node newNode(value);
			heapArray[currentSize] = newNode; // Push the node to bottom of heap
			// Trickle up the node inserted to top of heap
			trickleUp(currentSize);
			currentSize++; // increment post trickleUp

			return true;
		}

		void trickleUp(int idx) // index of node that needs to be tricked up
		{
			int parentIdx = (idx-1)/2;
			Node nodeToInsert = heapArray[idx];

			// loop as long as we havet reacged the root abd idx parent is less than new node
			while(idx > 0 && heapArray[parentIdx].getKey() < nodeToInsert.getKey()) // This logic is for min heap
			{
				heapArray[idx] = heapArray[parentIdx];
				idx = parentIdx;
				parentIdx = (parentIdx - 1)/2;
			}

			heapArray[idx] = nodeToInsert;
		}

		int remove()
		{
			Node node = heapArray[0];
			currentSize--;
			heapArray[0] = heapArray[currentSize];

			trickleDown(0);

		}

		void trickleDown(int idx)
		{
			int largerChildIdx;

			Node top = heapArray[idx];

			while(idx < currentSize/2) // will run as long as idx is not at the bottom of the row ( has atleast one child)
			{
				int leftChildIdx = 2*idx + 1;
				int rightChildIdx = 2*idx + 2;

				if(heapArray[leftChildIdx].getKey() < heapArray[rightChildIdx].getKey())
					largerChildIdx = rightChildIdx;
				else
					largerChildIdx = leftChildIdx;

				if(top.getKey() > heapArray[largerChildIdx].getKey())
					break;
				
				heapArray[idx] = heapArray[largerChildIdx];
				idx = largerChildIdx;
			}
		}

		void displayHeap()
		{
			int heapIdx					= 0;
			int maxDepth				= (int)ceil(log(currentSize));
			int nodeCountAtMaxDepth		= (int)(4*pow(2,maxDepth));
			int prevDepth = 0;
			queue<int> queue;
			queue.push(heapIdx);
			while(!queue.empty())
			{
				int heapIdx = queue.front();
				queue.pop();
				int currentIdxValue = heapArray[heapIdx].getKey();

				
				int currentDepth = (int) (log(heapIdx+1)/log(2));
				if(prevDepth < currentDepth)
					cout<<endl;

				prevDepth = currentDepth;

				int tabCount = nodeCountAtMaxDepth / (currentDepth+1);
				for(int index = 0; index < tabCount; index++)
					cout<<"  ";
				cout<<currentIdxValue;

				int leftChildIdx = 2*heapIdx + 1;
				int rightChildIdx = 2*heapIdx + 2;

				if(leftChildIdx < currentSize)
					queue.push(leftChildIdx);

				if(rightChildIdx < currentSize)
					queue.push(rightChildIdx);
			}
		}

	};
}