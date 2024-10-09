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

// Hash - Chaining (Closed addressing)

struct Node {
	ll val;
	Node* next;
};

Node* makeNode(ll x) {
	Node* newNode = new Node;
	newNode->val = x;
	newNode->next = NULL;
	return newNode;
}

class HashTable {
	ll pockets;
	Node** control;

public:
	HashTable(ll pockets);
	void insert(ll x);
	void remove(ll x);
	ll search(ll x);
	void display();
	void clean();
	ll hashFunc(ll x) {
		return x % pockets;
	}
};

HashTable::HashTable(ll pockets) {
	this->pockets = pockets;
	control = new Node * [pockets];
	for (ll i = 0; i < pockets; i++) {
		control[i] = nullptr;
	}
}

void HashTable::insert(ll x) {
	ll index = hashFunc(x);
	if (control[index] == nullptr) {
		control[index] = makeNode(x);
	}
	else {
		Node* temp = control[index];
		while (temp && temp->next) {
			temp = temp->next;
		}
		temp->next = makeNode(x);
	}
}

void HashTable::remove(ll x) {
	ll index = hashFunc(x);
	Node* current = control[index];
	Node* previous = nullptr;

	while (current) {
		if (current->val == x) {
			if (previous == nullptr) {
				control[index] = current->next;
			}
			else {
				previous->next = current->next;
			}
			delete current;
			return;
		}
		previous = current;
		current = current->next;
	}
}

ll HashTable::search(ll x) {
	ll index = hashFunc(x);
	Node* current = control[index];
	Node* temp = current;
	while (temp) {
		if (temp->val == x) {
			return index;
		}
		temp = temp->next;
	}
	return -1;
}

void HashTable::display() {
	for (ll i = 0; i < pockets; i++) {
		cout << i << ": ";
		Node* temp = control[i];
		while (temp) {
			cout << temp->val << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

void HashTable::clean() {
	for (ll i = 0; i < pockets; i++) {
		Node* cur = control[i];
		while (cur) {
			Node* temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
	delete[]control;
}

int main() {

	ll a[8] = { 15,11,27,8,12, 37, 89, 42 };
	ll n = sizeof(a) / sizeof(ll);

	HashTable h(10);

	for (ll i = 0; i < n; i++) {
		h.insert(a[i]);
	}

	h.display();
	cout << "The index of 11 is: " << h.search(11) << endl;
	h.remove(12);
	h.display();


	h.clean();
	return 0;
}
