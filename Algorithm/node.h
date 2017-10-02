template<class T>
struct node {
	node(T x) :key(x), left(0), right(0), parent(0){}
	~node() {
		delete left;
		delete right;
	}

	node* left;
	node* right;
	node* parent;	// optional
	T key;
};