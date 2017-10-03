enum Color{ RED, BLACK };

template <class T>
struct Node{
	Color color;
	T key;
	Node* left;
	Node* right;
	Node* parent;

	Node(int k, Color c = Color::RED) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}

	virtual ~Node() {
		delete left;
		delete right;
	}

	void setLeft(Node* x) {
		left = x;
		if (x) x->parent = this;
	}

	void setRight(Node* x) {
		right = x;
		if (x) x->parent = this;
	}

	void setChildren(Node* x, Node* y) {
		setLeft(x);
		setRight(y);
	}

	void replaceWith(Node* x) {
		if (!parent){
			if (x)
				x->parent = nullptr;
		}
		else if (parent->left == this){
			parent->setLeft(x);
		}
		else{
			parent->setRight(x);
		}
		parent = nullptr;
	}

	Node* sibling(){
		return parent->left == this ? parent->right : parent->left;
	}

	Node* uncle(){
		return parent->sibling();
	}

	Node* grandparent(){
		return parent->parent;
	}
};

// left rotation: (a, x, (b, y, c)) ==> ((a, x, b), y, c)
template <class T>
Node* leftRotate(Node* root, Node* x){
	Node* parent = x->parent;
	Node* y = x->right;
	Node* a = x->left;
	Node* b = y->left;
	Node* c = y->right;
	x->replaceWith(y);
	x->setChildren(a, b);
	y->setChildren(x, c);
	if (!parent) root = y;
	return root;
}

// right rotation: (a, x, (b, y, c)) <== ((a, x, b), y, c)
template <class T>
Node* rightRotate(Node* root, Node* y) {
	Node* parent = y->parent;
	Node* x = y->left;
	Node* a = x->left;
	Node* b = x->right;
	Node* c = y->right;
	y->replaceWith(x);
	y->setChildren(b, c);
	x->setChildren(a, y);
	if (!parent) root = x;
	return root;
}
