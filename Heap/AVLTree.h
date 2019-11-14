#pragma once
#include "BST.h"

namespace Tree
{
	class AVLTree : public BST
	{
		static bool taller;
		static bool smaller;

	public:
		AVLTree()
		{
			root = nullptr;
		}

		bool isEmpty()
		{
			return (root == nullptr);
		}

		void display()
		{
			cout<<"Display Tree : "<<endl;
			InorderTraversal(root);
		}

		void insert(int key, string value)
		{
			BST::insert(key,value);
		}

		// This is recursive version of insert for AVL tree
		Node* insert(Node* p, int key, string value)
		{
			if(p == nullptr)
			{
				p = new Node(key,value);
				if(root == nullptr) 
					root = p;
				taller = true;// forces atleast parent is called
			}
			else
			{
				if(p->getKey() > key)
				{
					p->left = insert(p->left, key, value);
					// From here on p can be unbalanced
					if(taller)
						p = insertionInLeftSubtreeCheck(p);
				}
				else if( p->getKey() < key)
				{
					p->right = insert(p->right, key, value);
					if(taller)
						p = insertionInRightSubtreeCheck(p);
				}
				else
				{
					taller = false;
				}
			}

			return p;
		}

		// Following functions check if trees are balanced or left heavy or right heavy
		Node* insertionInLeftSubtreeCheck(Node* p)
		{
			switch(p->getBalance())
			{
			case 0:
				p->setBalance(1);
				break;
			case 1:
				// tree is unbalanced....time for rotation
				p = insertionLeftBalance(p);
				taller = false;
				break;
			case -1:
				p->setBalance(0);
				taller = false;
				break;
			}
			return p;
		}

		Node* insertionInRightSubtreeCheck(Node* p)
		{
			
			switch(p->getBalance())
			{
			case 0:
				p->setBalance(-1);
				break;
			case 1:
				p->setBalance(0);
				taller = false;
				break;
			case -1:
				// tree is unbalanced....time for rotation.
				p = insertionRightBalance(p);
				taller = false;
				break;
			}
			return p;
		}

		Node* insertionLeftBalance(Node* p)
		{
			Node *a,*b;

			a = p->left;
			if(a->getBalance() == 1)
			{
				a->setBalance(0);
				p->setBalance(0);
				p = RightRotation(p);
			}
			else
			{
				b = a->right;

				if(b != nullptr) 
				{
					switch(b->getBalance())
					{
					case 0:
						p->setBalance(0);
						a->setBalance(0);
						break;
					case 1:
						p->setBalance(-1);
						a->setBalance(0);
						break;
					case -1:
						p->setBalance(0);
						a->setBalance(1);
						break;
					}
				}
				p->left = LeftRotation(a);
				p = RightRotation(p);  

			}
			return p;
		}

		Node* insertionRightBalance(Node* p)
		{
			Node *a,*b;

			a = p->right;
			if(a->getBalance() == -1)
			{
				a->setBalance(0);
				p->setBalance(0);
				p = LeftRotation(p);
			}
			else
			{
				b = a->left;
				if(b != nullptr) 
				{
					switch(b->getBalance())
					{
					case 0:
						p->setBalance(0);
						a->setBalance(0);
						break;
					case 1:
						p->setBalance(0);
						a->setBalance(-1);
						break;
					case -1:
						p->setBalance(1);
						a->setBalance(0);
						break;
					}
				}
				p->right = RightRotation(a);
				p = LeftRotation(p);   

			}
			return p;
		}

		Node* RightRotation(Node *p)
		{
			Node *a = p->left;
			if(p == root) root = a;

			p->left = a!=nullptr ? a->right: nullptr;
			if(a!=nullptr) 
				a->right = p;
			return a;
		}
		Node* LeftRotation(Node *p)
		{
			
			Node *a = p->right;
			
			if(p == root) root = a;

			p->right = a != nullptr ? a->left: nullptr;
			if(a != nullptr) 
				a->left = p;
			return a;
		}


		// This is recursive version of insert for AVL tree
		Node* deleteNode(Node* p, Node* parent, int key)
		{
			if(p == nullptr)
			{
				cout<<"Node not found"<<endl;
				smaller = false;
				return nullptr;
			}


			if(p->getKey() > key)
			{
				// left
				p->left = deleteNode ( p->left, p, key);
				if(smaller)
				{
					// Check balances and do things appropriately.....
					p = deletionInLeftSubtreeCheck(p);
				}
			}
			else if(p->getKey() < key)
			{
				//right
				p->right = deleteNode ( p->right,p, key);
				if(smaller)
				{
					// Check balances and do things appropriately.....
					p = deletionInRightSubtreeCheck(p);
				}
			}
			else
			{
				// Delete and update verify new balances....
				if(p->left == nullptr && p->right == nullptr)
				{
					parent->left == p ? parent->left = nullptr: parent->right = nullptr;
					delete(p);
					p = nullptr;
				}
				else if(p->left !=nullptr && p->right == nullptr)
				{
					parent->left == p ? parent->left = p->left: parent->right = p->left;
					delete(p);
					p = nullptr;
				}
				else
				{
					// find inorder successor
					Node *rChild = p->right;
					Node *lChildParent = rChild;
					while(rChild->left!=nullptr)
					{
						lChildParent = rChild;
						rChild = rChild->left;
					}
					p->setKey(rChild->getKey());
					p->setValue(rChild->getValue());
					if(lChildParent == rChild)
					{
						p->right = nullptr;
					}
					
					lChildParent->left = rChild->right;
					
					delete(rChild);
				}

				smaller = true;
				
			}

			return p;
		}


		Node* deletionInLeftSubtreeCheck(Node* p)
		{
			if( p == nullptr ) {
				smaller = false;
				return p;
			}
			switch(p->getBalance())
			{
			case 0:
				p->setBalance(-1);
				smaller = false;
				break;
			case 1:
				p->setBalance(0);
				break;
			case -1:
				
				p = deletionRightBalance(p);
				
				break;
			}
			return p;
		}

		Node* deletionInRightSubtreeCheck(Node* p)
		{
			if( p == nullptr ) {
				smaller = false;
				return p;
			}
			switch(p->getBalance())
			{
			case 0:
				p->setBalance(1);
				smaller = false;
				break;
			case 1:
				p = deletionLeftBalance(p);
				break;
			case -1:
				// tree is unbalanced....time for rotation.
				p->setBalance(0);
				break;
			}
			return p;
		}

		Node* deletionLeftBalance(Node* p)
		{
			Node *a,*b;

			a = p->left;
			if(a->getBalance() == 0)
			{
				a->setBalance(1);
				//p->setBalance(0);
				smaller = false;
				p = RightRotation(p);
			}
			else if (a->getBalance() == 1)
			{
				a->setBalance(0);
				p->setBalance(0);
				p = RightRotation(p);
			}
			else
			{
				b = a->right;

				if(b != nullptr) 
				{
					switch(b->getBalance())
					{
					case 0:
						p->setBalance(0);
						a->setBalance(0);
						break;
					case 1:
						p->setBalance(0);
						a->setBalance(1);
						break;
					case -1:
						p->setBalance(-1);
						a->setBalance(0);
						break;
					}
					b->setBalance(0);
				}
				
				p->left = LeftRotation(a);
				p = RightRotation(p);  

			}
			return p;
		}

		Node* deletionRightBalance(Node* p)
		{
			Node *a,*b;

			a = p->right;
			if(a->getBalance() == 0)
			{
				a->setBalance(-1);
				smaller = false;
				p = LeftRotation(p);
			}
			else if (a->getBalance() == -1)
			{
				a->setBalance(0);
				p->setBalance(0);
				p = LeftRotation(p);
			}
			else
			{
				b = a->left;
				if(b != nullptr) 
				{
					switch(b->getBalance())
					{
					case 0:
						p->setBalance(0);
						a->setBalance(0);
						break;
					case 1:
						p->setBalance(0);
						a->setBalance(-1);
						break;
					case -1:
						p->setBalance(1);
						a->setBalance(0);
						break;
					}
					b->setBalance(0);
				}
				
				p->right = RightRotation(a);
				p = LeftRotation(p);   

			}
			return p;
		}

	};
}