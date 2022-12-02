#ifndef AVL_HPP
#define AVL_HPP
#include <string>

template<typename Type>
class AVL {
protected:
	struct node // struct for storage tree's knot
	{
		Type key;
		unsigned char height;
		node* left;
		node* right;
		node(int k) { 
			key = k; 
			left = right = 0; 
			height = 1; 
		}
	};
	node* root;

	unsigned char height(node* p)
	{
		if (p) {
			return p->height;
		}
		else {
			return 0;
		}
	}

	int bfactor(node* p) //balance factor
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(node* p) // return fix hieght subtree
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	node* rotateright(node* p) // right turn around p
	{
		node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	node* rotateleft(node* q) // left turn around p
	{
		node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	node* balance(node* p) // balance p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // if its balanced
	}

	node* insert(node* p, Type k) // insert k in tree with root in p
	{
		if (!p) return new node(k);
		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	node* findmin(node* p) // find min
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p) // remove min from tree with root in p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(node* p, Type k) // remove k from tree with root in p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	node* nodefind(node* p, Type k) {
		if (p == nullptr) {
			return nullptr;
		}
		if (p->key == k) {
			return p;
		}
		if (k < p->key) {
			return nodefind(p->left, k);
		}
		else {
			return nodefind(p->right, k);
		}
	}

	std::string PrintToStringLRR(node* p) {
		if (p == nullptr) {
			return "null";
		}
		std::string res = " (" + PrintToStringLRR(p->left) + ") " + std::to_string(p->key) + " (" + PrintToStringLRR(p->right) + ") ";
		return res;
	}

	void print_Tree(node* p, int level)
	{
		if (p)
		{
			print_Tree(p->left, level + 1);
			for (int i = 0; i < level; i++) std::cout << "    ";
			std::cout << p->key << "\n";
			print_Tree(p->right, level + 1);
		}
	}

	bool nodefindsubtree(node* p, node* q) {
		if (p == nullptr && q == nullptr) {
			return true;
		}
		if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr)) {
			return false;
		}
		if (p->key != q->key) {
			return false;
		}
		return nodefindsubtree(p->left, q->left) && nodefindsubtree(q->right, p->right);
	}

	node* nodebuildsubtree(node* p) {
		if (p == nullptr) {
			return p;
		}
		node* new_element = new node(p->key);
		new_element->left = nodebuildsubtree(p->left);
		new_element->right = nodebuildsubtree(p->right);
		return new_element;
	}

	int nodemap(int(*f)(int), node* p) {
		if (p == nullptr) {
			return 0;
		}
		p->key = f(p->key);
		nodemap(f, p->left);
		nodemap(f, p->right);
		return 0;
	}

	int nodereduce(Type(*f)(Type, Type), node* p) {
		if (p == nullptr) {
			return 0;
		}
		Type a = nodereduce(f, p->left) + nodereduce(f, p->right);
		return f(a, p->key);
	}

	int nodewhere(bool(*f)(Type), AVL<Type>* n_tree, node* p) {
		if (p == nullptr) {
			return 0;
		}
		if (f(p->key)) {
			n_tree->add(p->key);
		}
		nodewhere(f, n_tree, p->left);
		nodewhere(f, n_tree, p->right);
		return 0;
	}

	int nodegetelement(std::vector<Type>* vec, node* p) {
		if (p == nullptr) {
			return 0;
		}
		vec->push_back(p->key);
		nodegetelement(vec, p->left);
		nodegetelement(vec, p->right);
		return 0;
	}
public:
	AVL() {
		root = nullptr;
	}

	int print(node* p) {
		if (p == nullptr) {
			return 0;
		}
		print(p->left);
		std::cout << p->value << " ";
		print(p->right);
		return 0;
	}

	std::string Print() {
		std::string s = PrintToStringLRR(this->root);
		return s;
	}

	int add(Type k) {
		this->root = insert(this->root, k);
		return 0;
	}

	int delet(Type k) {
		this->root = remove(this->root, k);
		return 0;
	}

	bool find(Type k) {
		if (nodefind(this->root, k) == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	void Print2() {
		print_Tree(this->root, 0);
	}

	bool findsubtree(AVL<Type>* q) {
		return nodefindsubtree(nodefind(this->root, q->root->key), q->root);
	}

	AVL<Type>* buildsubtree(Type k) {
		node* p = nodefind(this->root, k);
		AVL<Type>* new_tree = new AVL<Type>;
		new_tree->root = nodebuildsubtree(p);
		return new_tree;
	}


	int map(Type(*f)(Type)){
		nodemap(f, this->root);
		return 0;
	}

	int reduce(Type(*f)(Type, Type)) {
		return nodereduce(f, this->root);
	}

	AVL<Type>* where(bool(*f)(Type)) {
		AVL<Type>* new_tree = new AVL<Type>;
		nodewhere(f, new_tree, this->root);
		return new_tree;
	}

	std::vector<Type> getelement() {
		std::vector<Type> vec;
		nodegetelement(&vec, this->root);
		return vec;
	}
};


#endif