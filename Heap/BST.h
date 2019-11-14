#pragma once

#include <queue>
#include <string>
#include <iostream>


using namespace std;
namespace Tree
{
	class Node
	{
		int key;
		string value;
		int balance;
	public:
		Node *left;
		Node *right;

		Node()
		{
		}

		Node (int key, string value)
		{
			this->key = key;
			this->value = value;
			this->balance = 0;
			this->left = nullptr;
			this->right = nullptr;
		}

		Node (Node &n)
		{
			this->key = n.key;
			this->value = n.value;
		}

		Node& operator=(Node &n)
		{
			this->key = n.key;
			this->value = n.value;
			return *this;
		}

		int getKey()
		{
			return key;
		}

		string getValue()
		{
			return value;
		}

		int getBalance()
		{
			return balance;
		}

		void setKey(int key)
		{
			this->key = key;
		}

		void setValue(string value)
		{
			this->value= value;
		}

		void setBalance(int balance)
		{
			this->balance = balance;
		}
	};

	class BST
	{
	protected:
		Node *root;
	public:
		BST(void);
		~BST(void);

		Node* getRoot()
		{
			return root;
		}

		void insert(int key, string value)
		{
			Node *newNode = new Node(key, value);
			Node *currentNode = root;
			Node *parentNode;

			if(root == nullptr)
			{
				root = newNode;
				return;
			}
			else
			{
				bool isLeftChild = false;
				while(currentNode != nullptr)
				{
					parentNode = currentNode;

					if(currentNode->getKey() > key)
					{
						isLeftChild = true;
						currentNode = currentNode->left;
					}
					else 
					{
						isLeftChild = false;
						currentNode = currentNode->right;
					}
				}

				if(isLeftChild)
					parentNode->left = newNode;
				else
					parentNode->right = newNode;
			}
		}

		Node& findMin()
		{
			Node* current = root;
			Node* minNode;
			while(current != nullptr)
			{
				minNode = current;
				current = current->left;
			}

			return *minNode;
		}

		Node& findMax()
		{
			Node* current = root;
			Node* maxNode;
			while(current != nullptr)
			{
				maxNode = current;
				current = current->right;
			}

			return *maxNode;
		}

		Node* findMin(Node *root)
		{
			Node* current = root;
			Node* minNode;
			while(current != nullptr)
			{
				minNode = current;
				current = current->left;
			}

			return minNode;
		}

		Node* findMax(Node *root)
		{
			Node* current = root;
			Node* maxNode;
			while(current != nullptr)
			{
				maxNode = current;
				current = current->right;
			}

			return maxNode;
		}

		void deleteNode(int key)
		{
			Node* current = root;
			Node* nodeToDelete;
			Node* parent;
			bool isLeftChild = false;
			while(current != nullptr && current->getKey() != key)
			{
				parent = current;
				if(current->getKey() < key)
				{
					isLeftChild = false;
					current = current->right;
				}
				else if(current->getKey() > key)
				{
					isLeftChild = true;
					current = current->left;
				}
				else 
					break;
			}

			nodeToDelete = current;
			if(nodeToDelete->left == nullptr && nodeToDelete->right == nullptr)
			{
				isLeftChild ? parent->left = nullptr: parent->right = nullptr;
			}
			else if(nodeToDelete->left != nullptr && nodeToDelete->right == nullptr)
			{
				if(nodeToDelete == root)
					root = nodeToDelete->left;
				else
					isLeftChild ? parent->left = nodeToDelete->left: parent->right = nodeToDelete->left;
			}
			else if(nodeToDelete->left == nullptr && nodeToDelete->right != nullptr)
			{
				if(nodeToDelete == root)
					root = nodeToDelete->right;
				else
					isLeftChild ? parent->left = nodeToDelete->right: parent->right = nodeToDelete->right;
			}
			else
			{
				// Find InorderSuccessor
				Node* current = nodeToDelete->right;
				Node* parentMinNode = current;
				Node *minNode = current;

				while(current != nullptr)
				{
					parentMinNode = minNode;
					minNode = current;
					current = current->left;
				}
				
				if(minNode != nodeToDelete->right)
				{
					parentMinNode->left = minNode->right; // left mode node may have right subtree
					minNode->right = nodeToDelete->right;
					
				}

				if(nodeToDelete == root)
					root = minNode;
				else
				{
					isLeftChild ? parent->left = minNode: parent->right = minNode;
					
				}

				minNode->left = nodeToDelete->left;
				nodeToDelete->right = nullptr;
			}

			delete(nodeToDelete);
		}

		void InorderTraversal(Node* root)
		{
			if(root == nullptr)
				return;

			InorderTraversal(root->left);
			cout<<root->getKey()<<endl;
			InorderTraversal(root->right);
		}

		void KthNode(Node* root, int k, int* kthIndex)
		{
			if(root == nullptr)
				return;

			KthNode(root->left, k, kthIndex);
			(*kthIndex)++;
			if(*kthIndex == k)
			{
				cout<<root->getKey()<<endl;
				return;
			}
			KthNode(root->right,k,kthIndex);
		}

		void PreOrderTraversal(Node* root)
		{
			if(root == nullptr)
				return;

			cout<<root->getKey()<<endl;
			PreOrderTraversal(root->left);
			PreOrderTraversal(root->right);
		}

		void PostOrderTraversal(Node* root)
		{
			if(root == nullptr)
				return;

			PostOrderTraversal(root->left);
			PostOrderTraversal(root->right);
			cout<<root->getKey()<<endl;
		}

		void dfs(Node* root)
		{
			if(root == nullptr)
				return;

			dfs(root->left);
			cout<<root->getKey()<<endl;
			dfs(root->right);
		}

		void bfs(queue<Node *> depthNodes)
		{
			int noOfNodes = depthNodes.size();
			
			int counter = 0;
			for(int index = 0; index < noOfNodes ; index++)
			{
				int deficeit = 0;
				cout<<depthNodes.front()->getKey()<<"\t";
				depthNodes.front()->left != nullptr ? depthNodes.push(depthNodes.front()->left): deficeit++;
				depthNodes.front()->right != nullptr ? depthNodes.push(depthNodes.front()->right) : deficeit++;
				depthNodes.pop();
				//noOfNodes-=deficeit;
				
			}

			if(!depthNodes.empty())
			{
				cout<<endl;
				bfs(depthNodes);
			}
			else
			{
				cout<<endl;
				return;
			}

		}


		void findNearestNode(Node *root, int target, int *bestDelta, Node* nearestNode)
		{
			if(root == nullptr)
				return ;

			int currentDelta = root->getKey() - target;

			if(*bestDelta > currentDelta)
			{
				*bestDelta = currentDelta;
				nearestNode = root;
			}
			else
			{
				if(root->getKey() > target)
					findNearestNode(root->left, target, bestDelta, nearestNode);
				else
					findNearestNode(root->right, target, bestDelta, nearestNode);
			}
		}


		bool IsBST(Node *root, int nodeMin, int nodeMax)
		{
			if(root == nullptr)
				return true;

			int nodeValue = root->getKey();

			if(nodeValue >= nodeMax || nodeValue <= nodeMin)
				return false;
			else
			{
				bool isLeftSubtreeValid = IsBST(root->left, nodeMin, nodeValue);
				bool isRightSubtreeValid = IsBST(root->right, nodeValue, nodeMax);

				return (isLeftSubtreeValid && isRightSubtreeValid);
			}
		}

		
		Node* inOrderSuccessor(Node* root, Node* startNode)
		{
			Node* currentNode = startNode;
			if(currentNode == nullptr)
				return currentNode;

			if(currentNode->right == nullptr)
			{
				// It could be a case that this node itself is in left subtree of main tree 
				// and then in order successor will be some parent.
				Node* tempNode = root;
				Node* successor = nullptr;
				while(tempNode)
				{
					if(startNode->getKey() > tempNode->getKey())
					{
						tempNode = tempNode->right;
					}
					else if(startNode->getKey() < tempNode->getKey())
					{
						successor = tempNode;
						tempNode = tempNode->left;
					}
					else
						break;
				}

				return successor;
			}
			else
			{
				// Find the left most child of the right node.
				currentNode = currentNode->right;
				while(currentNode->left != nullptr)
				{
					currentNode = currentNode->left;
				}
				return currentNode;
			}

		}

		bool covers( Node* root, Node* p)
		{
			if(root == nullptr)
				return false;
			if(root == p)
				return true;

			return (covers(root->left, p) || covers(root->right,p));
		}

		// May not be a BST but is binary tree
		Node* commanAncestor ( Node* root, Node* p, Node* q)
		{
			bool is_p_on_left = covers(root, p);
			bool is_q_on_left = covers(root, q);

			// If p and q are both on left and right of node root, then we have common ancestor as root
			if(is_p_on_left != is_q_on_left)
			{
				return root;
			}

			// If p is on left and q is on left then 
			if(is_p_on_left && is_q_on_left)
			{
				return commanAncestor ( root->left, p, q);
			}
			else // If p is on right and q is on right move to right
			{
				return commanAncestor ( root->right, p, q);
			}
		}

		Node* commanAncestorWrapper( Node* root, Node* p, Node* q )
		{
			if(!covers(root,p) || !covers(root, q))
			{
				return nullptr;
			}

			return commanAncestor(root, p, q);
		}

	};

}