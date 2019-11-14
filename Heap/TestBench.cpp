// Heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ArrayHeapImpl.h"
#include "BST.h"
#include "AVLTree.h"
#include "Graph.h"

using namespace Heap;
using namespace Tree;

bool AVLTree::taller = false;
bool AVLTree::smaller = false;

void HeapTest()
{
	Heap::ArrayHeapImpl heap(20);

	heap.insert(10);
	heap.insert(12);
	heap.insert(42);
	heap.insert(35);
	heap.insert(16);
	heap.insert(88);
	heap.insert(42);
	heap.insert(7);

	heap.displayHeap();
}


void BSTTest()
{
	BST tree;

	tree.insert(10,"1");
	tree.insert(12,"2");
	tree.insert(42,"3");
	tree.insert(35,"4");
	tree.insert(16,"5");
	tree.insert(88,"6");
	tree.insert(43,"7");
	tree.insert(7,"8");

	cout<<"DFS TRAVERSAL:"<<endl;
	tree.dfs(tree.getRoot());
	cout<<"BFS TRAVERSAL:"<<endl;
	queue<Tree::Node *> depthNodes;
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);

	cout<<"KthNode "<<endl;
	int kthIndex = 0;
	for(int index = 1; index <= 8; index++)
	{
		kthIndex = 0;
		tree.KthNode(tree.getRoot(), index, &kthIndex);
	}
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.deleteNode(43);
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.deleteNode(42);
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.deleteNode(7);
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

}




void AVLTest()
{
	AVLTree tree;

	tree.insert(tree.getRoot() ,10,"1");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,12,"2");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,42,"3");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,35,"4");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,16,"5");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,88,"6");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,43,"7");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());

	tree.insert(tree.getRoot() ,7,"8");
	cout<<"TREE INORDER TRAVERSAL"<<endl;
	tree.InorderTraversal(tree.getRoot());
	
	//tree.deleteNode(tree.getRoot(), 16);
	cout<<"BFS Result"<<endl;
	queue<Tree::Node*> depthNodes;
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);


	tree.deleteNode(tree.getRoot(), nullptr, 16);
	cout<<"BFS Result"<<endl;
	depthNodes.pop();
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);

	tree.insert(tree.getRoot() ,16,"5");
	cout<<"BFS Result"<<endl;
	depthNodes.pop();
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);

	tree.deleteNode(tree.getRoot(), nullptr, 12);
	cout<<"BFS Result"<<endl;
	depthNodes.pop();
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);

	tree.insert(tree.getRoot() ,12,"2");
	cout<<"BFS Result"<<endl;
	depthNodes.pop();
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);

	// Delete the root itself
	tree.deleteNode(tree.getRoot(), nullptr, tree.getRoot()->getKey());
	cout<<"BFS Result"<<endl;
	depthNodes.pop();
	depthNodes.push(tree.getRoot());
	tree.bfs(depthNodes);
}


void TestDirectedGraphBuild()
{
	DirectedGraph dGraph;

	dGraph.InsertEdge(0,2);
	dGraph.InsertEdge(0,1);
	dGraph.InsertEdge(1,3);
	dGraph.InsertEdge(1,4);
	dGraph.InsertEdge(1,5);
	dGraph.InsertEdge(2,6);
	dGraph.InsertEdge(2,7);
	dGraph.InsertEdge(3,4);
	dGraph.InsertEdge(3,4);
	dGraph.InsertEdge(4,7);
	dGraph.InsertEdge(4,1);
	dGraph.InsertEdge(5,6);
	dGraph.InsertEdge(6,7);
	dGraph.InsertEdge(7,0);

	dGraph.PrintAdjMatrix();

	cout<<"In degree vertex 0-->"<<dGraph.inDegree(0)<<endl;
	cout<<"In degree vertex 1-->"<<dGraph.inDegree(1)<<endl;
	cout<<"In degree vertex 2-->"<<dGraph.inDegree(2)<<endl;
	cout<<"In degree vertex 3-->"<<dGraph.inDegree(3)<<endl;

	cout<<"Out degree vertex 0-->"<<dGraph.outDegree(0)<<endl;
	cout<<"Out degree vertex 1-->"<<dGraph.outDegree(1)<<endl;
	cout<<"Out degree vertex 2-->"<<dGraph.outDegree(2)<<endl;
	cout<<"Out degree vertex 3-->"<<dGraph.outDegree(3)<<endl;

	dGraph.findShortedPath(0);
}

void TestDirectedGraphBuildWithWeights()
{
	DirectedGraph dGraph;

	dGraph.InsertEdgeWeighted(0,2,2);
	dGraph.InsertEdgeWeighted(0,1,3);
	dGraph.InsertEdgeWeighted(1,3,1);
	dGraph.InsertEdgeWeighted(1,4,11);
	dGraph.InsertEdgeWeighted(1,5,10);
	dGraph.InsertEdgeWeighted(2,6,6);
	dGraph.InsertEdgeWeighted(2,7,2);
	dGraph.InsertEdgeWeighted(3,4,12);
	dGraph.InsertEdgeWeighted(3,4,3);
	dGraph.InsertEdgeWeighted(4,7,4);
	dGraph.InsertEdgeWeighted(4,1,5);
	dGraph.InsertEdgeWeighted(5,6,1);
	dGraph.InsertEdgeWeighted(6,7,2);
	dGraph.InsertEdgeWeighted(7,0,2);

	dGraph.PrintAdjMatrix();

	dGraph.dijkstra(0);
}

void TestUnDirectedGraphBuild()
{
	UnDirectedGraph dGraph;

	dGraph.InsertEdge(0,2);
	dGraph.InsertEdge(0,1);
	dGraph.InsertEdge(1,3);
	dGraph.InsertEdge(3,4);

	dGraph.PrintAdjMatrix();

	cout<<"degree vertex 0-->"<<dGraph.degree(0)<<endl;
	cout<<"degree vertex 1-->"<<dGraph.degree(1)<<endl;
	cout<<"degree vertex 2-->"<<dGraph.degree(2)<<endl;
	cout<<"degree vertex 3-->"<<dGraph.degree(3)<<endl;


}


int _tmain(int argc, _TCHAR* argv[])
{

	HeapTest();

	//BSTTest();

	//AVLTest();

	//TestDirectedGraphBuild();

	//TestDirectedGraphBuildWithWeights();
	////TestUnDirectedGraphBuild();

	getchar();
	return 0;
}


