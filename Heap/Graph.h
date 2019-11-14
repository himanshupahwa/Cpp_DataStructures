#pragma once
#include <iostream>
#include <string>
#include <map>

#define MAX_VERTICES 30


using namespace std;

enum WarshallStates 
{
	INITIAL,
	WAITING,
	VISITED
};

enum DijkstraStates 
{
	TEMPORARY,
	PERMANENT
};


class Vertex
{
	int vertexID;
	string vertexName;

public:
	double Distance;
	int Predecessor;
	WarshallStates WState;
	DijkstraStates DState;

	int getVertexID()
	{
		return vertexID;
	}

	void setVertexID( int vertexID)
	{
		this->vertexID = vertexID;
	}

	string getVertexName()
	{
		return vertexName;
	}

	void setVertexName ( string vertexName )
	{
		this->vertexName = vertexName;
	}

};

class Edge
{
	int weight;
public:
	Vertex *v1;
	Vertex *v2;

	int getWeight()
	{
		return weight;
	}

	void setWeight( int weight )
	{
		this->weight = weight;
	}
};

class DirectedGraph
{
	
	map<int,Vertex*> vertexList;
	int AdjMatrix[MAX_VERTICES][MAX_VERTICES];
public :
	int N;
	int E;

	DirectedGraph()
	{
		N = 0;
		E = 0;
		for(int row = 0; row < MAX_VERTICES ; row++)
		{
			for(int col = 0; col < MAX_VERTICES; col++)
			{
				AdjMatrix[row][col] = 0;
			}
		}
	}

	void insertVertex(int vertexID)
	{
		if(vertexList.find(vertexID) == vertexList.end())
		{
			Vertex *newVertex = new Vertex();
			newVertex->setVertexName(to_string(vertexID));
			newVertex->setVertexID(vertexList.size());

			vertexList[vertexID] = newVertex;
			N++;
		}
		else
		{
			cout<<"Vertex already in vertex list...."<<endl;
		}
	}

	void InsertEdge ( int v1ID, int v2ID )
	{
		if(v1ID == v2ID)
		{
			cout<<"vertex ids cannot be same"<<endl;
			return;
		}
		
		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v1ID<<" "<<endl;
			insertVertex(v1ID);
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v2ID<<" "<<endl;
			insertVertex(v2ID);
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		AdjMatrix[row][col] = 1;
		E++;
	}

	void InsertEdgeWeighted ( int v1ID, int v2ID, int weight )
	{
		if(v1ID == v2ID)
		{
			cout<<"vertex ids cannot be same"<<endl;
			return;
		}
		
		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v1ID<<" "<<endl;
			insertVertex(v1ID);
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v2ID<<" "<<endl;
			insertVertex(v2ID);
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		AdjMatrix[row][col] = weight;
		E++;
	}

	void DeleteEdge ( int v1ID, int v2ID)
	{
		if(v1ID == v2ID)
		{
			cout<<"vertex ids cannot be same"<<endl;
			return;
		}

		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return;
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return;
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		AdjMatrix[row][col] = 0;
		E--;
	}

	bool EdgeExists(int v1ID, int v2ID )
	{
		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return false;
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return false;
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		return (AdjMatrix[row][col] > 0);
	}


	int outDegree( int v1ID )
	{

		int row = vertexList[v1ID]->getVertexID();

		int outDegreeCounter = 0;
		for(int col = 0; col < N; col++)
		{
			outDegreeCounter = AdjMatrix[row][col] == 1? outDegreeCounter+1:outDegreeCounter;
		}

		return outDegreeCounter;
	}

	int inDegree( int v1ID )
	{
		int col = vertexList[v1ID]->getVertexID();

		int inDegreeCounter = 0;
		for(int row = 0; row < MAX_VERTICES; row++)
		{
			inDegreeCounter = AdjMatrix[row][col] == 1? inDegreeCounter+1:inDegreeCounter;
		}

		return inDegreeCounter;
	}


	void PrintAdjMatrix()
	{
		for(int row = 0; row < N ; row++)
		{
			for(int col = 0; col < N; col++)
			{
				cout<<AdjMatrix[row][col]<<" ";
			}
			cout<<endl;
		}
	}

	void findShortedPath(int vertexId)
	{
		for(map<int,Vertex*>::iterator v = vertexList.begin(); v!= vertexList.end(); v++)
		{
			Vertex *vertex = v->second;
			vertex->Distance = numeric_limits<float>::max();
			vertex->Predecessor = -1;
			vertex->WState = WarshallStates::INITIAL;
		}

		bfs(vertexId);
		backTracePaths(vertexId);
	}

	void backTracePaths(int vertexId)
	{
		int startVertexId  = getVertex(vertexId)->getVertexID();

		// back track to get to the start node
		for(map<int,Vertex*>::iterator v = vertexList.begin(); v!= vertexList.end(); v++)
		{
			Vertex* node = v->second;
			if(node->Distance == numeric_limits<float>::max())
				cout<<vertexId<<" Node is not connected to "<<node->getVertexID()<<endl;
			else
			{
				int *path = new int[vertexList.size()];
				int nodeID = node->getVertexID();
				Vertex* backTrackVertex = node;
				path[0] = nodeID;
				int pathCounter = 0;
				while(nodeID != startVertexId)
				{
					nodeID = backTrackVertex->Predecessor;
					pathCounter++;

					path[pathCounter] = nodeID;
					backTrackVertex  =  getVertex(nodeID);
				}

				for(int index = pathCounter; index >= 0; index--)
				{
					cout<<getVertex(path[index])->getVertexName()<<"-->"; 
				}
				cout<<endl;
			}
		}
	}
	Vertex* tempVertexWithMinPL()
	{
		Vertex* minVertex = nullptr;
		float min = numeric_limits<float>::max();
		for(map<int,Vertex*>::iterator v = vertexList.begin(); v!= vertexList.end(); v++)
		{
			if(v->second->DState == TEMPORARY && v->second->Distance < min)
			{
				minVertex = v->second;
			}
		}

		return minVertex;
	}

	// find all smallest paths from a vertex
	void dijkstra(int vertexID)
	{
		for(map<int,Vertex*>::iterator v = vertexList.begin(); v!= vertexList.end(); v++)
		{
			Vertex *vertex = v->second;
			vertex->Distance = numeric_limits<float>::max();
			vertex->Predecessor = -1;
			vertex->DState = DijkstraStates::TEMPORARY;
		}

		int startVertexID = vertexList[vertexID]->getVertexID();

		vertexList[vertexID]->Distance = 0;

		while(true)
		{
			Vertex* currNode = tempVertexWithMinPL();
			if(currNode == nullptr)
				break;

			currNode->DState = PERMANENT;

			for(int col = 0; col < N; col++)
			{
				if(AdjMatrix[currNode->getVertexID()][col] > 0)
				{
					Vertex* edgeEndVertex = getVertex(col);
					if(edgeEndVertex->DState == TEMPORARY)
					{
						edgeEndVertex->Predecessor = currNode->getVertexID();
						edgeEndVertex->Distance = currNode->Distance + AdjMatrix[currNode->getVertexID()][col];
						edgeEndVertex->DState = TEMPORARY;
						//nodeQueue.push(edgeEndVertex);
					}
				}
			}
		}


		backTracePaths(vertexID);
	}

	Vertex* getVertex(int vertexID)
	{
		for(map<int, Vertex*>::iterator v = vertexList.begin(); v != vertexList.end(); v++)
		{
			if(v->second->getVertexID() == vertexID)
				return v->second;
		}
		return nullptr;
	}

	void bfs(int startVertexId)
	{
		Vertex* start = vertexList[startVertexId];
		start->Distance = 0;
		queue<Vertex*> nodeQueue;
		nodeQueue.push(start);
		
		while(!nodeQueue.empty())
		{
			Vertex *currNode = nodeQueue.front();
			nodeQueue.pop();
			currNode->WState = WarshallStates::VISITED;

			for(int col = 0; col < N; col++)
			{
				if(AdjMatrix[currNode->getVertexID()][col] == 1)
				{
					Vertex* edgeEndVertex = getVertex(col);
					if(edgeEndVertex->WState == INITIAL)
					{
						edgeEndVertex->Predecessor = currNode->getVertexID();
						edgeEndVertex->Distance = currNode->Distance+1;
						edgeEndVertex->WState = WarshallStates::WAITING;
						nodeQueue.push(edgeEndVertex);
					}
				}
			}
		}
	}

};

class UnDirectedGraph
{
	
	map<int,Vertex*> vertexList;
	int AdjMatrix[MAX_VERTICES][MAX_VERTICES];
public :
	int N;
	int E;

	UnDirectedGraph()
	{
		N = 0;
		E = 0;
		for(int row = 0; row < MAX_VERTICES ; row++)
		{
			for(int col = 0; col < MAX_VERTICES; col++)
			{
				AdjMatrix[row][col] = 0;
			}
		}
	}

	void insertVertex(int vertexID)
	{
		if(vertexList.find(vertexID) == vertexList.end())
		{
			Vertex *newVertex = new Vertex();
			newVertex->setVertexName(to_string(vertexID));
			newVertex->setVertexID(vertexList.size());

			vertexList[vertexID] = newVertex;
			N++;
		}
		else
		{
			cout<<"Vertex already in vertex list...."<<endl;
		}
	}

	void InsertEdge ( int v1ID, int v2ID )
	{
		if(v1ID == v2ID)
		{
			cout<<"vertex ids cannot be same"<<endl;
			return;
		}
		
		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v1ID<<" "<<endl;
			insertVertex(v1ID);
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list...adding one.."<<v2ID<<" "<<endl;
			insertVertex(v2ID);
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		AdjMatrix[row][col] = 1;
		AdjMatrix[col][row] = 1;
		E++;
		E++;
	}


	void DeleteEdge ( int v1ID, int v2ID)
	{
		if(v1ID == v2ID)
		{
			cout<<"vertex ids cannot be same"<<endl;
			return;
		}

		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return;
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return;
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		AdjMatrix[row][col] = 0;
		AdjMatrix[col][row] = 0;
		E--;
		E--;
	}

	bool EdgeExists(int v1ID, int v2ID )
	{
		if(vertexList.find(v1ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return false;
		}

		if(vertexList.find(v2ID) == vertexList.end())
		{
			cout<<"Vertex does not exist in list..."<<endl;
			return false;
		}

		int row = vertexList[v1ID]->getVertexID();
		int col = vertexList[v2ID]->getVertexID();

		return (AdjMatrix[row][col] > 0);
	}


	int degree( int v1ID )
	{

		int row = vertexList[v1ID]->getVertexID();

		int degreeCounter = 0;
		for(int col = 0; col < N; col++)
		{
			degreeCounter = AdjMatrix[row][col] == 1? degreeCounter+1:degreeCounter;
		}

		return degreeCounter;
	}

	
	void PrintAdjMatrix()
	{
		for(int row = 0; row < N ; row++)
		{
			for(int col = 0; col < N; col++)
			{
				cout<<AdjMatrix[row][col]<<" ";
			}
			cout<<endl;
		}
	}
};