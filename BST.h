#include <iostream>
using namespace std;
template<class T>
struct node{
	node() :key(0), left(0), right(0), parent(0){}
	node(T x) :key(x), left(0), right(0), parent(0){}
	~node() {
		delete left;
		delete right;
	}

	node* left;
	node* right;
	node* parent; //parent is optional, it's helpful for succ/pred
	T key;
};

template<class T>
node<T>* insert(node<T>* tree, T k){
	node<T>* root(tree);
	node<T>* x = new node<T>(k);
	node<T>* parent(0);
	while (tree){
		parent = tree;
		if (k < tree->key)
			tree = tree->left;
		else
			tree = tree->right;
	}
	x->parent = parent;
	if (parent == 0)
		return x;
	else if (k < parent->key)
		parent->left = x;
	else
		parent->right = x;
	return root;
}

template<class T>
void print(T k){
	cout << k << ' ';
}

// easy implemented by using functional approach
// FÎªº¯ÊýÖ¸Õë
template<class T, class F>
void in_order_walk_help(node<T>* tree, F f){
	if (tree){
		in_order_walk_help(tree->left, f);
		f(tree->key);
		in_order_walk_help(tree->right, f);
	}
}

template<class T, class F>
void in_order_walk(node<T> *tree, F f){
	in_order_walk_help(tree, f);
	cout << endl;
}

template<class T>
node<T>* search(node<T> *tree, T key){
	while (tree && tree->key != key){
		if (key < tree->key) tree = tree->left;
		else tree = tree->right;
	}
	return tree;
}

template<class T>
node<T>* min(node<T> *x){
	while (x && x->left)
		x = x->left;
	return x;
}

template<class T>
node<T>* max(node<T> *x){
	while (x && x->right)
		x = x->right;
	return x;
}

template<class T>
node<T>* succ(node<T> *x){
	if (x){
		if (x->right) return min(x->right);
		//find an ancestor, whose left child contains x
		node<T>* p = x->parent;
		while (p && p->right == x){
			x = p;
			p = p->parent;
		}
	}
	return p;
}

template<class T>
node<T>* pred(node<T> *x){
	if (x){
		if (x->left) return max(x->left);
		//find an ancestor, whose right child contains x
		node<T>* p = x->parent;
		while (p && p->left == x){
			x = p;
			p = p->parent;
		}
		return p;
	}
}

template<class T>
void remove_node(node<T>* x){
	if (x)
		x->left = x->right = 0;
	delete x;
}

// if x has only one child: just splice x out
// if x has two children: use min(right) to replace x
// @return root of the tree
template<class T>
node<T>* del(node<T>* t, T k){
	node<T>* p = search(t, k);
	if (!p)
		return t;
	node<T>* root(t);
	node<T>* old_p(p);
	node<T>* parent(p->parent);

	if (p->left == 0)
		p = p->right;
	else if (p->right == 0)
		p = p->left;
	else{
		node<T>* y = min(p->right);
		p->key = y->key;
		if (y->parent != p)
			y->parent->left = y->right;
		else
			p->right = y->right;
		remove_node(y);
		return root;
	}
	if (p)
		p->parent = parent;
	if (!parent)
		root = p; //remove node of a tree
	else
	if (parent->left == old_p)
		parent->left = p;
	else
		parent->right = p;

	remove_node(old_p);
	return root;
}
