#include <iostream>
#include <queue>
#include <stack>
//
// ## Level Order Traversal
// ## Height of tree
// ## Deletion of node in bst
// ## Check if a binary tree is BST - Method 1
// check if each node falls within expected range
// ## Check if a binary tree is BST - Method 2 
// (in order traversal - check sorted order)
// ##
// 
//
using namespace std;

class Node {
    public:
        int key;
        int value;
        int height;
        int diameter;
        Node *left;
        Node *right;

        Node( int k, int v );
        void printData( void );
        void findHeight( void );
        void findDiameter( void );
        void getNodesAtLevel( int currentLevel, int desiredLevel,
                    queue<Node *> *resultQ );
};

class Tree {
    protected:
        Node *root;
        Node *insert( Node *n, int k, int v);
        int findHeight( Node *n);
        Node *_removeNode( Node *root, int key);
        Node * findMin(Node *n);
    public:
        void addNode( int k, int v);
        void removeNode( int k);
        Tree ( Node *n);
        Tree ( void );
        void printNodesAtLevel( int level );
        void preOrderPrint( Node *n);
        void inOrderPrint( Node *n);
        void postOrderPrint( Node *n);
		void preOrderIterativePrint( Node *n);
		void inOrderIterativePrint( Node *n);
		void postOrderIterativePrint( Node *n);
        void levelOrderPrint() ;
        void levelOrderMarkerPrint() ;
        void printTree();
        void printRoot();
        int height();
};

Node::Node( int k, int v) {
    value = v;
    key = k;
    right = left = NULL;
}

void 
Node::printData(void) {
    cout << "Key:" << key << " Val:" << value ;
    cout << "\t\tLeft : " << ((left) ? (left->key) : 0xFFFF) ;
    cout << "\t\tRight : " << ((right) ? (right->key) : 0xFFFF);
    cout << "\t\tHeight : " << height; 
    cout << "\t\tDiameter : " << diameter; 
    cout << endl;
}

int
Tree::height() {
    return findHeight( root );
}

// ## Height of tree
//
// Height of a node is defined as the number of edges from a node to the 
// farthest leaf descendant. If a node has no children, then, it's height is 0.
// Thus the number of levels is a tree is equal to its height.
// By extension, if the root is NULL, the height is -1.
// The height of a node is the max of the heights of its left, right sub-trees.
// 
// Height of the tree is -1 if the root node is NULL.
// For a root node with no children, it is 0.
// and so on..
int 
Tree::findHeight( Node *n) {
    int leftHeight, rightHeight, currHeight;

    if ( !n ) {
       return -1;
    }
    leftHeight = findHeight( n->left );
    rightHeight = findHeight( n->right );
    currHeight = max(leftHeight, rightHeight) + 1;

    return currHeight;
}

// Deletion::
// There are three cases for bst node deletion.
//
// Case 1: Deleting a node that has no children.
//
// Deletion of a leaf node is very simple. Just remove the link
// from parent and free the memory.
//
// Case 2: Deleting a node with single child 
//
// Link the only child to parent and we are done.
//
// Case 3: Deleting a node with two children
//
// If there are two children, it is tricky.
// Find the smallest node in the right sub-tree ( or the 
// largest node in the left sub-tree).
// Copy over the value of the found node to the "to-be-deleted" node.
// Now, the problem definition just changed to "delete the found node".
// Since the "found node" is lower than the earlier node, it is more
// likely, that it has less children and becomes either Case-1 or Case-2.
// In fact, due to the property below, it __will__ become either 
// case-1 or case-2.
// 
// Property used:
// In a right subtree, the minimum value node will not have a left child.
// In a left subtree, the maximum value node will not have a right child.
// 
void
Tree::removeNode(int key) {
    root = _removeNode(root, key);
}

Node * 
Tree::_removeNode(Node *n, int key) {

    if ( ! n ) {
        return NULL;
    }
    if ( key < n->key ) {
        n->left = _removeNode( n->left, key );
        return n;
    }
    if ( key > n->key ) {
        n->right = _removeNode( n->right, key );
        return n;
    }
    if ( n->key == key ) {

        // Case 1: No Child
        if ( (!n->left) && (!n->right) ) {
            delete n;
            return NULL;
        }
        // Case 2a: No left child`
        if (!n->left) {
			// Save the pointer to right
			// and then delete the node.
            Node *child = n->right;
            delete n;
            return child;
        }
        // Case 2b: No right child
        if (!n->right) {
			// Save the pointer to left
			// and then delete the node.
            Node *child = n->left;
            delete n;
            return child;
        }
        // Case 3: Has both children
        Node *min = findMin(n->right);
        n->value = min->value;
        n->key = min->key;
        n->right = _removeNode(n->right, min->value);
        return n;
    }
    return n;
}

// FIXME:
//  Finding the min in BST should be simpler.
//  From root, keep going left until there is no further left.
Node *
Tree::findMin(Node *n) {
    Node *leftMin, *rightMin, *minOfNodeAndLeft;

    if ( !n ) {
        return NULL;
    }

    leftMin = findMin( n->left );
    rightMin = findMin( n->right );

    if ( ( !leftMin ) && ( !rightMin ) ) {
        return n;
    }
	// Find the smallest of all three..
    minOfNodeAndLeft = n;
    if ( leftMin ) {
        if ( leftMin->key <= n->key ) {
            minOfNodeAndLeft = leftMin;
        }
    }
    if ( rightMin ) {
        if ( rightMin->key <= minOfNodeAndLeft->key ) {
            return rightMin;
        }
    }
    return minOfNodeAndLeft;
}

void
Tree::printRoot() {
    cout << "Printing the root element" << endl;
    root->printData();
    cout << endl;
}

Tree::Tree( Node *n) {
    root = n;
}

Tree::Tree( void ) {
    root = NULL;
}


void Tree::preOrderPrint( Node *n) {
    n->printData();
    if (n->left) {
        preOrderPrint(n->left);
    }
    if (n->right) {
        preOrderPrint(n->right);
    }
}
// Pre-order iterative print uses a stack to store the nodes while printing.
// It imitates the preOrderPrint procedure.
//
// We first processthe current node. Now, we need to process the left-sub-tree 
// and then come back and process the right subtree. As we need to come back 
// to process the right sub-tree, we need to store the current node on a 
// stack before going into the left-subtree. 
//
// After completing the left sub-tree processing, pop the element and go to its
// right subtree.
//
// Continue this process until the stack is empty.
// 
#ifdef OLD_METHOD
void Tree::preOrderIterativePrint( Node *n) {

	stack<Node *> printStack;
	
	if (!n) { return; }

	while (1) {
		while (n) {
			n->printData();
			printStack.push(n);
			n = n->left;
		}
		if ( printStack.empty() ) { break; }
		n = printStack.top();
		printStack.pop();
		n = n->right;
	}
}
#else

void Tree::preOrderIterativePrint( Node *n ) {

    if( not n ) { return; }
    
    stack<Node *> printStack;
    printStack.push(n);
    while( not printStack.empty() ) {
        n = printStack.top();
        printStack.pop();
        n->printData();
        // ****** CRITICAL COMMENT **********
        // Pre-order implies Node, Left, Right
        // Since we are pushing to stack, we should so
        // 1. Visit Node.
        // 2. Push right
        // 3. Push left
        // so that when we pop, left comes out first.
        if( n->right ) {
            printStack.push( n->right );
        }
        if( n->left ) {
            printStack.push( n->left );
        }
    }
}
#endif
    
void Tree::inOrderPrint( Node *n) {
    if (n->left) {
        inOrderPrint(n->left);
    }
    n->printData();
    if (n->right) {
        inOrderPrint(n->right);
    }
}

// The principle is the same as preOrder Iterative print. The only change is the 
// place at which we print the current node. Print the data in the current node
// after completing the left sub-tree.
//
#ifdef OLD_METHOD
void Tree::inOrderIterativePrint( Node *n) {

	stack<Node *> printStack;
	
	if (!n) { return; }

	while (1) {
		while (n) {
			printStack.push(n);
			n = n->left;
		}
		if ( printStack.empty() ) { break; }
		n = printStack.top();
		printStack.pop();
		n->printData();
		n = n->right;
	}
}
#else
void Tree::inOrderIterativePrint( Node *n) {

    stack<Node*> printStack;

    while( ( not printStack.empty() ) or ( n != NULL ) ) {
        if( n != NULL ) {
            printStack.push(n);
            n = n->left;
        } else {
            n = printStack.top();
            printStack.pop();
            n->printData();
            n = n->right;
        }
    }
}
#endif

void Tree::postOrderPrint( Node *n) {
    if (n->left) {
        postOrderPrint(n->left);
    }
    if (n->right) {
        postOrderPrint(n->right);
    }
    n->printData();
}

void Tree::postOrderIterativePrint( Node *n) {
	stack<Node *> pS1, pS2;

	if (!n) { return; }

	pS1.push(n);
	while ( ! pS1.empty() ) {
		n = pS1.top();
		pS1.pop();
		pS2.push(n);

		if (n->left) {
			pS1.push(n->left);
		}
		if (n->right) {
			pS1.push(n->right);
		}
	}

	while ( !pS2.empty() ) {
		n = pS2.top();
		pS2.pop();
		n->printData();
	}

}

void
Tree::printTree( void ) {

    cout << "Printing the tree in preorder" << endl;
    preOrderPrint(root);
	cout << "Printing again using iterative proc" << endl;
	preOrderIterativePrint(root);
	cout << "Printing again using iterative proc" << endl;
	//preOrderIterativePrint2(root);
    cout << endl;

    cout << "Printing the tree in inorder" << endl;
    inOrderPrint(root);
	cout << "Printing again using iterative proc" << endl;
	inOrderIterativePrint(root);
    cout << endl;

    cout << "Printing the tree in postorder" << endl;
    postOrderPrint(root);
	cout << "Printing again using iterative proc" << endl;
	postOrderIterativePrint(root);
    cout << endl;

    cout << "Level Order Traversal" << endl;
    levelOrderPrint();
    cout << endl;
}

void
Node::findHeight() {

    if( ( left ) && ( right ) ) {
        height = max( left->height, right->height ) + 1;
    }
    if( ( !left ) && ( right ) ) {
        height = right->height  + 1;
    }
    if( ( left ) && ( !right ) ) {
        height = left->height + 1;
    }
    if( ( !left ) && ( !right ) ) {
        height = 0;
    }
}

void
Node::findDiameter() {
    int leftDiameter=0, rightDiameter=0 ;

    if( left ) {
        leftDiameter = left->diameter;
    }
    if( right ) {
        rightDiameter = right->diameter;
    }
    
    diameter = max( leftDiameter, rightDiameter );
    diameter = max( diameter, height );
      
}
        
Node * Tree::insert( Node *n, int k, int v) {
    if ( ! n ) {
        n = new Node(k, v);
        n->height = 0;
        n->diameter = 0;
		return n;
    } 
	if ( k < n->key ) {
        n->left = insert( n->left, k, v );
        n->findHeight();
        n->findDiameter();
		return n;
    } 
	if ( k > n->key ) {
        n->right = insert( n->right, k, v );
        n->findHeight();
        n->findDiameter();
		return n;
	}
    // Found a node with the same key.
    // Replace data.
    n->value = v;
    return n;
}

void  Tree::addNode( int k, int v) {
    root = insert( root, k, v );
    root->findHeight();
    root->findDiameter();
}

// ## Level Order Traversal
// For the below example,
//
//                        10
//           5                         15
//    2            9              14            
// 1      4                   12
// 
// the output should be:
// 10, 5, 15, 2, 9, 14, 1, 4, 12.
//
// In a binary tree, to perform a level order traversal, we need to be
// able to remember more than one node. 
// 
//  To get to node 15 after visiting 5, we push all children nodes of 10 to a queue
// when visiting 10 and pop them one after another and visit them.
//
// So the strategy used is storing all the elements in level "L+1" when walking
// visiting level "L".
// Follow this strategy across all levels. 
//
// There are two stages to the level tree traversal algorithm:
//  (1) Discovering the nodes
//  (2) Visiting the nodes
// When visiting nodes at level "L", discover their children and push the children's
// addresses to the queue.
// By the time all nodes of level "L" are complete, all nodes at level "L+1" have
// been discovered too. Now we can start visiting the nodes at level "L+1".
// 
// To store nodes at level L+1 and retreieve them in order later, we need some FIFO
// mechanism like c++ queue.
void Tree::levelOrderPrint() {
    queue<Node *> printQ;
    Node * n;

    if (root == NULL) { return; }

    printQ.push(root);
    while ( !printQ.empty() ) {

        // Do not forget to pop.
        Node *n = printQ.front();
        printQ.pop();
        n->printData();

        if (n->left) { 
            printQ.push(n->left);
        }
        if (n->right) {
            printQ.push(n->right);
        }
    }
}

// This function runs level order print with a demarcation line after each level.
// To find out that a level has completed, it adds a magic node.
#define MAGIC_NODE 0xdeadbeef
void Tree::levelOrderMarkerPrint() {
    queue<Node *> printQ;
    Node * n;
	Node *marker;
	int level = 0;
	int nodes_at_this_level = 0;

    if (root == NULL) { return; }

	marker = (Node *) MAGIC_NODE;
    printQ.push(root);
    printQ.push(marker);

	printf("Level %d ...\n", level);
    while ( !printQ.empty() ) {
        Node *n = printQ.front();

		if ( n == marker) { 
			if ( nodes_at_this_level == 0 ) {
				printf("No nodes in level %d \n\n", level);
				break;
			}
			printf("Number of nodes in level %d is %d\n\n", 
					level, nodes_at_this_level);
			level++;
			printf("Level %d ...\n", level);
			printQ.pop();
			printQ.push(marker);
			nodes_at_this_level = 0;
			continue;
		}
		nodes_at_this_level++;
        n->printData();
        if (n->left) { 
            printQ.push(n->left);
        }
        if (n->right) {
            printQ.push(n->right);
        }
        printQ.pop();
    }
}

void
Node::getNodesAtLevel( int currentLevel, int desiredLevel, 
                        queue<Node *> *resultQ ) {
    if( currentLevel == desiredLevel ) {
        resultQ->push( this );
        return;
    }
    if( left ) {
        left->getNodesAtLevel( currentLevel+1, desiredLevel, resultQ );
    } 
    if( right ) {
        right->getNodesAtLevel( currentLevel+1, desiredLevel, resultQ );
    } 
}

void
Tree::printNodesAtLevel( int level ) {
    
    queue< Node *> resultQ;
    root->getNodesAtLevel( 0, level, &resultQ );
    cout << "Printing Nodes at Level:" << level << endl;
    while ( ! resultQ.empty() ) {
        Node *n = resultQ.front();
        resultQ.pop();
        cout << n->key << endl;
    }
    cout << endl;
    
}

// As this is a simple bst and not a balanced bst,
// the order in which elements are added determines
// the structure of the tree.
// 
int main(int argc, char **argv) {
    int i, max;
    Tree *t = new Tree( );
    max = 3;
    for ( i=0; i<= max; i++) {
        t->addNode(i, i*i);
    }
    for ( i=-1*max; i< 0; i++) {
        t->addNode(i, i*i);
    }
    cout << "Height of the tree is " << t->height() << endl;
    cout << "Removing keys 2 and -3" << endl;
    //t->removeNode(2);
    //t->removeNode(-3);
    cout << "Height of the tree is " << t->height() << endl;
    cout << "Removing key 0" << endl;
    //t->removeNode(0);
    cout << "Height of the tree is " << t->height() << endl;
    //t->removeNode(-5);
    cout << "Height of the tree is " << t->height() << endl;
    t->printTree();
    t->levelOrderMarkerPrint();
    t->printNodesAtLevel(2);
}
