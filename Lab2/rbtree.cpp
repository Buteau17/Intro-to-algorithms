#include <iostream>

using namespace std;


struct Node {
	int data; 
	Node *parent; 
	Node *left; 
	Node *right;
	int color; 
};

typedef Node *NodePtr;

class rbtree {
private:
	NodePtr root;
	NodePtr NIL;

	void InOrderTraversal(NodePtr node) {
		if (node != NIL) {
			InOrderTraversal(node->left);
			cout<<node->data<<" ";
			InOrderTraversal(node->right);
		} 
	}

	NodePtr searchTree(NodePtr node, int Key) {
		if (node == NIL || Key == node->data) {
			return node;
		}

		if (Key < node->data) {
			return searchTree(node->left, Key);
		} 
		return searchTree(node->right, Key);
	}

	void RedBlackTransplant(NodePtr m, NodePtr n){
		if (m->parent == nullptr) {
			root = n;
		} else if (m== m->parent->left){
			n->parent->left = n;
		} else {
			n->parent->right = m;
		}
		n->parent = m->parent;
	}

	void deleteNode(NodePtr node, int key) {
		
		NodePtr z = NIL;
		NodePtr x, y;
		while (node != NIL){
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (z == NIL) {
		
			return;
		} 

		y = z;
		int y_original_color = y->color;
		if (z->left == NIL) {
			x = z->right;
			RedBlackTransplant(z, z->right);
		} else if (z->right == NIL) {
			x = z->left;
			RedBlackTransplant(z, z->left);
		} else {
			y = minimumKey(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			} else {
				RedBlackTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			RedBlackTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0){
			NodePtr s;
			while (x != root && x->color == 0) {
				if (x == x->parent->left) {
					s = x->parent->right;
					if (s->color == 1) {
				
						s->color = 0;
						x->parent->color = 1;
						Lrotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == 0 && s->right->color == 0) {
						
						s->color = 1;
						x = x->parent;
					} else {
						if (s->right->color == 0) {
							
							s->left->color = 0;
							s->color = 1;
							Lrotate(s);
							s = x->parent->right;
						} 

						
						s->color = x->parent->color;
						x->parent->color = 0;
						s->right->color = 0;
						Rrotate(x->parent);
						x = root;
					}
				} else {
					s = x->parent->left;
					if (s->color == 1) {
						
						s->color = 0;
						x->parent->color = 1;
						Rrotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == 0 && s->right->color == 0) {
						
						s->color = 1;
						x = x->parent;
					} else {
						if (s->left->color == 0) {
							
							s->right->color = 0;
							s->color = 1;
							Lrotate(s);
							s = x->parent->left;
						} 

						
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						Rrotate(x->parent);
						x = root;
					}
				} 
			}
			x->color = 0;
		
			}
		}
	
	void print(NodePtr root) {
		
	   	if (root != NULL) {
           string c = root->color?"red":"black";
		   print(root->left);
		   if (root->parent==nullptr){
			cout<<"key: "<<root->data <<" parent:   color: " <<c<<endl;

		   }
		   else{
			cout<<"key: " <<root->data <<" parent: " <<root->parent->data<<" color: " <<c<<endl;

		   }
		   
		   print(root->right);
		}
	}

public:
	rbtree() {
		NIL = new Node;
		NIL->color = 0;
		NIL->left = nullptr;
		NIL->right = nullptr;
		root = NIL;
	}

	void inorder() {
		InOrderTraversal(this->root);
	}

	NodePtr searchTree(int k) {
		return searchTree(this->root, k);
	}

	NodePtr minimumKey(NodePtr node) {
		while (node->left != NIL) {
			node = node->left;
		}
		return node;
	}

	NodePtr maximumKey(NodePtr node) {
		while (node->right != NIL) {
			node = node->right;
		}
		return node;
	}

	NodePtr Successor(NodePtr x) {
		if (x->right != NIL) {
			return minimumKey(x->right);
		}
		NodePtr y = x->parent;
		while (y != NIL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	NodePtr Predecessor(NodePtr x) {
		if (x->left != NIL) {
			return maximumKey(x->left);
		}

		NodePtr y = x->parent;
		while (y != NIL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	void Lrotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != NIL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void Rrotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != NIL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void insertNode(int key) {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = NIL;
		node->right = NIL;
		node->color = 1; 

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != NIL) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		if (node->parent == nullptr){
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}
	
			NodePtr u;
			while (node->parent->color == 1) {
				if (node->parent == node->parent->parent->right) {
					u = node->parent->parent->left; 
					if (u->color == 1) {

						u->color = 0;
						node->parent->color = 0;
						node->parent->parent->color = 1;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							Rrotate(node);
						}
						node->parent->color = 0;
						node->parent->parent->color = 1;
						Lrotate(node->parent->parent);
					}
				} 
				else {
					u = node->parent->parent->right; 

					if (u->color == 1) {
						u->color = 0;
						node->parent->color = 0;
						node->parent->parent->color = 1;
						node = node->parent->parent;	
					} else {
						if (node == node->parent->right) {
							node= node->parent;
							Lrotate(node);
						}
						node->parent->color = 0;
						node->parent->parent->color = 1;
						Rrotate(node->parent->parent);
					}
				}
			if (node== root) {
				break;
			}
		}
		root->color = 0;
	}
		

	NodePtr getRoot(){
		return this->root;
	}

	void deleteNode(int data) {
		deleteNode(this->root, data);
	}

	void Print() {
	    if (root) {
    		print(this->root);
	    }
	}
	};

int main() {
	rbtree tree;
	int t, op, n, r;
	cin>>t;
	while (t--) {
		
		cin>>op>>n;
		if (op==1){
			cout<<"Insert: ";
		}
		else {
			cout<<"Delete: ";
			}
		

		for (int i=0; i<n ; i++){
			cin>>r;
			if (i!=0){
				cout<<", ";
			}
			cout<<r;
			if (op==1){
				tree.insertNode(r);
			}
			else{
				tree.deleteNode(r);
			}
			
		}
		cout<<"\n";
		tree.Print();

	}
	return 0;
}

