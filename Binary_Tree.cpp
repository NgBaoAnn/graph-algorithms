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

// BST

struct BstNode {
	ll val;
	BstNode* left;
	BstNode* right;
};

BstNode* makeNode(ll val) {
	BstNode* newNode = new BstNode;
	newNode->val = val;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

BstNode* insert(BstNode* &root, ll data) {
	if (root == nullptr) {
		root = makeNode(data);
		return root;
	}
	else if (data < root->val) {
		root->left = insert(root->left, data);
	}
	else if (data > root->val) {
		root->right = insert(root->right, data);
	}
	return root;
}

void removeTree(BstNode* &root) {
	if (root == nullptr) return;

	removeTree(root->left);
	removeTree(root->right);
	delete root;
}

bool checkBST(BstNode* root, ll left, ll right) {
	if (root == nullptr) return 1;

	if (root->val <= left || root->val >= right) return false;

	return checkBST(root->left, left, root->val) && checkBST(root->right, root->val, right);
}

BstNode* findX(BstNode* root, ll x) {
	if (!root || root->val == x) return root;

	if (x < root->val) return findX(root->left, x);
	else return findX(root->right, x);
}

void showLeafNodes(BstNode* root) {
	if (root == nullptr) return;
	
	if (root->left == nullptr && root->right == nullptr) {
		cout << root->val << " ";
	}

	showLeafNodes(root->left);
	showLeafNodes(root->right);
}

ll getHeight(BstNode* root) {
	if (root == nullptr) return 0;
	return 1 + max(getHeight(root->left), getHeight(root->right));
}

BstNode* getClosest(BstNode* root, ll x) {
	if (!root) return nullptr;

	if (x < root->val) {
		if (!root->left) {
			return root;
		}
		else {
			if (abs(root->val - x) < abs(getClosest(root->left, x)->val - x)) {
				return root;
			}
			else return getClosest(root->left, x);
		}
	}
	else {
		if (!root->right) {
			{
				return root;
			}
		}
		else {
			if (abs(root->val - x) < abs(getClosest(root->right, x)->val - x)) {
				return root;
			}
			else return getClosest(root->right, x);
		}
	}

}

BstNode* findKLargest(BstNode* root, ll k) {
	if (!root) return nullptr;
	
	ll cnt = 0;
	stack<BstNode*> st;
	BstNode* cur = root->right;
	st.push(root);
	while (cur || st.size() > 0) {
		while (cur) {
			st.push(cur);
			cur = cur->right;
		}
		cnt += 1;
		BstNode* temp = st.top();
		st.pop();
		if (cnt == k) return temp;
		cur = temp->left;
	}
}

BstNode* findKLargest2(BstNode* root, ll& k) {
	if (!root) return nullptr;
	BstNode* res = findKLargest2(root->right, k);
	if (res) return res;

	--k;
	if (k == 0) return root;
	return findKLargest2(root->left, k);
}

BstNode* lca(BstNode* root, ll x, ll y) {
	if (!root) return root;

	if (root->val < x && root->val < y) {
		return lca(root->right, x, y);
	}
	if (root->val > x && root->val > y) {
		return lca(root->left, x, y);
	}
	return root;
}

BstNode* deleteANode(BstNode* &root, ll k) {
	if (!root) return root;
	if (root->val < k) {
		root->right = deleteANode(root->right, k);
	}
	else if (root->val > k) {
		root->left = deleteANode(root->left, k);
	}
	else {
		if (!root->left && !root->right) {
			delete root;
			root = nullptr;
			return root;
		}
		else if (!root->left) {
			BstNode* temp = root;
			root = root->right;
			delete temp;
			return root;
		}
		else if (!root->right) {
			BstNode* temp = root;
			root = root->left;
			delete temp;
			return root;
		}

		BstNode* cur = root->right;
		while (cur->left) {
			cur = cur->left;
		}
		root->val = cur->val;
		root->right = deleteANode(root->right, root->val);
	}
	return root;
}

void deleteANode2(BstNode*& root, ll k) {
	if (!root) return;
	if (root->val < k) {
		deleteANode(root->right, k);
	}
	else if (root->val > k) {
		deleteANode(root->left, k);
	}
	else {
		if (!root->left && !root->right) {
			delete root;
			root = nullptr;
			return;
		}
		else if (!root->left) {
			BstNode* temp = root;
			root = root->right;
			delete temp;
			return;
		}
		else if (!root->right) {
			BstNode* temp = root;
			root = root->left;
			delete temp;
			return;
		}
		else {
			BstNode* cur = root->right;
			while (cur->left) {
				cur = cur->left;
			}
			root->val = cur->val;
			deleteANode(root->right, root->val);
		}
	}
	return;
}

void browse(BstNode* root) {
	if (root == nullptr) return;

	browse(root->left);
	cout << root->val << " ";
	browse(root->right);
}


int main() {
	BstNode* root;
	root = nullptr;
	
	ll n = 1;
	cout << "Enter the sequence: ";
	while (cin >> n) {
		if (n == 0) break;
		root = insert(root, n);
	}
	cout << "The tree is: ";
	browse(root);
	cout << "\n";;

	deleteANode2(root, 77);
	browse(root);
	
	// Test case: 77 49 15 64 105 83 120 0

	return 0;
}





