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


#define el cout << "\n";
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const ll N = 1e6 + 5;
const ll MOD = 1e9 + 7;

struct Heap {
	vector<ll> data;
};

void insert(Heap* heap, ll key) {
	heap->data.push_back(key);
	ll idx = heap->data.size() - 1;
	ll pa = (idx - 1) / 2;
	while (pa >= 0 && heap->data[idx] > heap->data[pa]) {
		swap(heap->data[idx], heap->data[pa]);
		idx = pa;
		pa = (idx - 1) / 2;
	}
	if (pa == 0 && heap->data[idx] > heap->data[pa]) swap(heap->data[idx], heap->data[pa]);
	return;
}

void del(Heap* heap) {
	ll n = heap->data.size();
	swap(heap->data[0], heap->data[--n]);
	ll idx = 0;
	while (idx * 2 + 1 < n) {
		ll nxt = idx * 2 + 2 < n && heap->data[idx * 2 + 2] > heap->data[idx * 2 + 1] ?
			idx * 2 + 2 : idx * 2 + 1;
		if (heap->data[idx] > heap->data[nxt]) break;
		swap(heap->data[idx], heap->data[nxt]);
		idx = nxt;
	}
	heap->data.pop_back();
	return;
}

void heapify(ll a[], ll n, ll i) {
	ll l = 2 * i + 1;
	ll r = 2 * i + 2;
	ll largest = i;
	if (l < n && a[largest] < a[l]) largest = l;
	if (r < n && a[largest] < a[r]) largest = r;
	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void heapSort(ll a[], ll n) {
	for (ll i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}
	for (ll i = n - 1; i >= 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

int main() {

	ll a[1000];
	ll n; cin >> n;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	heapSort(a, n);
	for (ll i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	
	return 0;
}

/*
void insert(Heap*& root, ll key) {
	root->data.push_back(key);
	ll i = root->data.size() - 1;
	ll pa = (i - 1) / 2;
	// Heapfiy
	while (pa >= 0 && root->data[i] > root->data[pa]) {
		swap(root->data[i], root->data[pa]);
		i = pa;
		pa = (i - 1) / 2;
	}
	if (pa == 0 && root->data[i] > root->data[pa]) {
		swap(root->data[i], root->data[pa]);
	}
}

void delNode(Heap*& root) {
	if (root->data.size() == 0) return;
	ll n = root->data.size();
	swap(root->data[0], root->data[--n]);

	// Heapify
	ll idx = 0;
	while (2 * idx + 1 < n) {
		ll nxt = 2 * idx + 2 < n && root->data[2 * idx + 2] > root->data[2 * idx + 1] ?
			2 * idx + 2 : 2 * idx + 1;
		if (root->data[nxt] < root->data[idx]) break;
		swap(root->data[nxt], root->data[idx]);
		idx = nxt;
	}
	root->data.pop_back();
}
*/