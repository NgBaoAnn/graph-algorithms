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

// Hash - Linear probing (Open addressing)

class HashTable {
	ll pockets;
	ll* control;

public:
	HashTable(ll pockets);
	~HashTable();
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
	control = new ll[pockets];
	// Initialize control array to mark all pockets as empty (-1)
	for (ll i = 0; i < pockets; ++i) {
		control[i] = -1;
	}
}

HashTable::~HashTable() {
	delete[] control;
}

void HashTable::insert(ll x) {
	ll index = hashFunc(x);
	while (control[index] != -1) {
		index = (index + 1) % pockets;
	}
	control[index] = x;
}

void HashTable::remove(ll x) {
	ll index = hashFunc(x);
	// Linear probing to find the element
	while (control[index] != x) {
		index = (index + 1) % pockets;
	}
	control[index] = -1; // Mark as empty
}

ll HashTable::search(ll x) {
	ll index = hashFunc(x);
	// Linear probing to find the element
	while (control[index] != x) {
		index = (index + 1) % pockets;
		if (index == pockets - 1) {
			return -1;
		}
	}
	return index;
}

void HashTable::display() {
	for (ll i = 0; i < pockets; ++i) {
		std::cout << "Pocket " << i << ": " << control[i] << std::endl;
	}
}

int main() {

	ll a[8] = { 15,11,27,8,12, 37, 89, 42 };
	ll n = sizeof(a) / sizeof(ll);

	HashTable h(15);

	for (ll i = 0; i < n; i++) {
		h.insert(a[i]);
	}

	h.display();

	cout << h.search(13);

	return 0;
}
