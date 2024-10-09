#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#if __cplusplus >= 201402L
#include <shared_mutex>
#endif

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const ll N = 1e6 + 5;
const ll MOD = 1e9 + 7;

struct Node {
	ll val; 
	ll height;
	Node* left;
	Node* right;
};

Node* makeNode(ll x) {
	Node* newNode = new Node;
	newNode->val = x;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->height = 1;
	return newNode;
}

ll getHeight(Node* root) {
	if (!root) return 0;
	return root->height;
}

void updateHeight(Node* node) {
	if (node) {
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	}
}

void leftRotate(Node* &p) {
	Node* c = p->right;
	Node* t = c->left;

	c->left = p;
	p->right = t;

	updateHeight(p);
	updateHeight(c);

	p = c;

	return;
}

void rightRotate(Node* &p) {
	Node* c = p->left;
	Node* t = c->right;

	c->right = p;
	p->left = t;

	updateHeight(p);
	updateHeight(c);

	p = c;

	return;
}

void rotate(Node* &root) {
	if (!root) return;
	if (getHeight(root->left) - getHeight(root->right) > 1) {
		if ((getHeight(root->left->left) - getHeight(root->left->right) > 0)) {
			rightRotate(root);
		}
		else if ((getHeight(root->left->left) - getHeight(root->left->right) < 0)) {
			leftRotate(root->left);
			rightRotate(root);
		}
	}
	else if (getHeight(root->left) - getHeight(root->right) < -1) {
		if ((getHeight(root->right->right) - getHeight(root->right->left) > 0)) {
			leftRotate(root);
		}
		else if ((getHeight(root->right->right) - getHeight(root->right->left) < 0)) {
			rightRotate(root->right);
			leftRotate(root);
		}
	}
	return;
}

void insert(Node* &root, ll x) {
	if (!root) {
		root = makeNode(x);
		return;
	}


	if (x < root->val) {
		insert(root->left, x);
	}
	else if (x > root->val) {
		insert(root->right, x);
	}

	updateHeight(root);
	
	rotate(root);
}

void delAVL(Node*& root) {
	if (!root) return;
	delAVL(root->left);
	delAVL(root->right);
	delete root;
	root = nullptr;
}


int main() {

	Node* root = nullptr;
	for (int i = 1; i <= 1000000; i++) {
		insert(root, i);
	}
	
	cout << "The height of the tree is: " << root->height << "\n";
	delAVL(root);

	return 0;
}