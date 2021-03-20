#include <iostream>
#include <string>
bool deleted = false;
struct Node
{
        int key;
        Node *right;
        Node *left;
        Node *p;
        int d;
};
typedef Node *NodePtr;
class Bst
{
    private:
         Node* root;
        //int height;
        void initialize_node(Node *node, int key);
		void preOrderWalkH(Node *node);
		void inOrderWalkH(Node *node);
		void postOrderWalkH(Node *node);
		NodePtr searchTreeH(NodePtr node, int key);
		NodePtr deleteNodeH(NodePtr node, int key);
		void emptyH(NodePtr node);
    public:
        Bst(void)
        {
            root = nullptr;
        }
        void preOrderWalk(void);
		void inOrderWalk(void);
		void postOrderWalk(void);
		NodePtr searchTree(int key);
		void deleteNode(int key);
		NodePtr minimum(NodePtr node);
		NodePtr maximum(NodePtr node);
		NodePtr successor(NodePtr x);
		NodePtr predecessor(NodePtr x);
		void insert(int key);
		NodePtr return_root(void)
		{
			return root;
		}
		void empty(NodePtr* node);
};
void Bst::empty(NodePtr* node_ref)
{
	emptyH(*node_ref);
	*node_ref = nullptr;
}
void Bst::emptyH(NodePtr node)
{
	if (node == nullptr)
		return;
	emptyH(node->left);
	emptyH(node->right);
	
	std::cout << "Deleting node: " << node->key << std::endl;
	delete node;
}

void Bst::initialize_node(Node *node, int key)
{
	node->key = key;
	node->p = nullptr;
	node->left = nullptr;
	node ->right = nullptr;
}
void Bst::preOrderWalkH(Node *node)
{
	if (node != nullptr)
	{	
		std::cout<< node->key << " ";
		preOrderWalkH(node->left);
		preOrderWalkH(node->right);
	}
}
void  Bst::inOrderWalkH(Node *node)
{	
	if (node!= nullptr)
	{	
		inOrderWalkH(node->left);
		std::cout << node->key << " ";
		inOrderWalkH(node->right);
	}
	
}

void  Bst::postOrderWalkH(Node *node)
{
	if ( node != nullptr)
	{
		postOrderWalkH(node->left);
		postOrderWalkH(node->right);
		std::cout << node->key << " ";
	}
}

NodePtr  Bst::searchTreeH(NodePtr node, int key)
{ 
	if (node == nullptr || key == node->key) {
			return node;
		}

		if (key < node->key) {
			return searchTreeH(node->left, key);
		} 
		return searchTreeH(node->right, key);

}


NodePtr  Bst::deleteNodeH(NodePtr node, int key)
{
	if ( node == nullptr) 
		return node;
	else if (key < node->key)
	{
		//depth_delete++;
		node->left = deleteNodeH(node->left, key);
	}
	else if (key > node->key)
	{
		//depth_delete++;
		node->right = deleteNodeH(node->right, key);
	}
	else
	{
		if(node->left == nullptr && node->right == nullptr && deleted == false)
		{
			delete node;
			node = nullptr;
			deleted = true;
		}
		else if (node->left == nullptr && deleted == false)
		{
			NodePtr temp = node;
			node = node->right;
			delete temp;
			deleted = true;
		}
	else if (node->right == nullptr && deleted == false) {
				NodePtr temp = node;
				node = node->left;
				delete temp;
				deleted = true;
			}
			else {
				NodePtr temp = minimum(node->right);
				node->key = temp->key;
				node->right = deleteNodeH(node->right, temp->key);
			}
		} 
		return node;
}


//public
void  Bst::preOrderWalk(void)
{
	preOrderWalkH(this->root);
}

void  Bst::inOrderWalk(void)
{
	inOrderWalkH(this->root);
}
	
void  Bst::postOrderWalk(void)
{
	postOrderWalkH(this->root);
}

NodePtr  Bst::searchTree(int key)
{
	return searchTreeH(this->root, key);
}
void Bst::deleteNode(int key)
{
	NodePtr temp = deleteNodeH(this->root, key);
	if (temp == nullptr)
		std::cout << "" << std::endl;
}

NodePtr  Bst::minimum(NodePtr node)
{
	//minimum_depth++;
	while (node->left != nullptr)
	 {
			node = node->left;
	 }
	 return node;
}

NodePtr  Bst::maximum(NodePtr node)
{
	//maximum_depth++;
	while (node->right != nullptr) {
			node = node->right;
		}
		return node;
}

NodePtr  Bst::successor(NodePtr x)
{
	
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		NodePtr y = x->p;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->p;
		}
		return y;
}
NodePtr  Bst::predecessor(NodePtr x)
{
		if (x->left != nullptr) {
			return maximum(x->left);
		}

		NodePtr y = x->p;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->p;
		}

		return y;
}
void  Bst::insert(int key)
{
	NodePtr new_node = new Node;
	initialize_node(new_node, key);
	NodePtr y = nullptr;
	NodePtr x = this->root;
	int depth = 0;
	while(x != nullptr)
	{
		depth ++;
		y =x;
		if (new_node->key < x->key)
		{
			x = x ->left;
		}else{
			x = x->right;
		}
	}
	
	new_node ->p = y;
	if (y ==  nullptr)
	{
		root =  new_node;
	}
	else if (new_node ->key < y->key)
	{
		y ->left = new_node;
	}
	else
	{
		y->right = new_node;
	}
	new_node->d = depth;
	std::cout << "\t\tThe depth of the the newly inserted node is " << new_node->d<< std::endl;
}



int main()
{
	int option = -1;
	Bst tree;
	//tree.insert(3);
	//tree.insert(1);
	//tree.insert(8);
	//tree.insert(9);
	//tree.insert(2);
	//tree.insert(6);
	while (option != 0)
	{
		std::cout << "---------------------MENU------------------------" << std::endl;
		std::cout << "1. Insert new node" << std::endl;
		std::cout << "2. Delete a node" << std::endl;
		std::cout << "3. Search key value" << std::endl;
		std::cout << "4. Find minimum key value" << std::endl;
		std::cout << "5. Find maximum key value" << std::endl;
		std::cout << "6. Find successor of a node" << std::endl;
		std::cout << "7. Find predecesor of a node" << std::endl;
		std::cout << "8. Print preorder, inorder and postorder traversal" << std::endl;
		std::cout << "9. Delete all nodes" << std::endl;
		std::cout << "0. Exit program" << std::endl; 
		std::cout << std::endl << "Please, select an option from menu: ";
		
		std::cin >> option;
		
		switch (option)
		{
		case 1:
		{
			int key;
			std::cout << "Enter key value: " ;
			std::cin >> key;
			tree.insert(key);
			break;
		}
		case 2:
		{
			int key;
			std::cout << "Enter key value you wish to delete: " ;
			std::cin >> key;
			NodePtr t = tree.searchTree(key);
			int depths;
			if (t == nullptr)
			{
				std::cout << "\t\tKey not found!" << std::endl;
			}
			else
			{
				depths = t->d;
			    tree.deleteNode(key);
				std::cout << "\t\tKey was found at depth " << depths << " and deleted! " << std::endl;
			}
			
			break;
	    }
		case 3:
		{
			int key;
			std::cout << "Enter key value you wish to find: " ;
			std::cin >> key;
			NodePtr temp = tree.searchTree(key);
			if (temp->key == key)
			{
				std::cout << "\t\tKey was found at depth " << temp ->d<< "." << std::endl;
			}else{
				std::cout << "\t\tKey not found!" << std::endl;
			}
		break;
	    }
		case 4:
		{
			if (tree.return_root() == nullptr)
			{
				std::cout << "Tree is empty" << std::endl;
			}
			else
			{
				NodePtr temp = tree.minimum(tree.return_root());
				std::cout << "\t\tThe minimum value in the tree is " << temp->key ;
				std::cout << " and it was found at depth " << temp->d << std::endl;
			}
		break;
	    }
		case 5:
		{
			if (tree.return_root() == nullptr)
			{
				std::cout << "\t\tTree is empty" << std::endl;
			}
			else
			{
				NodePtr temp = tree.maximum(tree.return_root());
				std::cout << "\t\tThe maximum value in the tree is " << temp->key ;
				std::cout << " and it was found at depth " << temp->d << std::endl;
			}
		break;
	    }
		case 6:
		{
			int keys;
			std::cout << "Enter key which you would like to find the successor of: " ;
			std::cin >> keys;
			NodePtr temp = tree.searchTree(keys);
			NodePtr x = tree.successor(temp);
			
			std::cout << "\t\tThe successor of " << keys << " is " << x->key;
			std::cout << " and It was found at depth " << x->d << std::endl;	
		break;
	    }
		case 7:
		{
			int keys;
			std::cout << "Enter key which you would like to find the  predecessor of: " ;
			std::cin >> keys;
			NodePtr temp = tree.searchTree(keys);
			NodePtr x = tree.predecessor(temp);
			
			std::cout << "The predecesor of " << keys << " is " << x->key ;
			std::cout << " and it was found at depth " << x->d << std::endl;	
		break;
	     }
		case 8:
		{
			std::cout << "\t\tInorder traversal" << std::endl << "\t\t";
			tree.inOrderWalk();
		    std::cout << std::endl <<  "\t\tPreorder traversal" << std::endl << "\t\t";
		    tree.preOrderWalk();
			std::cout << std::endl << "\t\tPostorder traversal" << std::endl << "\t\t";
			tree.postOrderWalk();
			std::cout << std::endl;
			break;
		}
		case 9:
		{
			std::cout << "Deleteting all the nodes..." << std::endl;
			NodePtr root = tree.return_root();
			tree.empty(&root);
			if (root == nullptr)
				std::cout << "Tree is empty now!" << std::endl;
		}
		break;
		case 0:
		{
			std::cout << std::endl << "GoodBye!" << std::endl;
			return 0;
			break;
		}
		default:
		{
			std::cout << "Please select an available option!" << std::endl;
			break;
		
	  }
  }
    
}
return 0;
}

