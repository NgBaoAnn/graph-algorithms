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

ll n, m;
ll parent[1005];
ll sz[1005];

void init() {
	for (ll i = 1; i <= n; i++) {
		parent[i] = i;
		sz[i] = i;
	}
}

// Find the representation of an element
ll find(ll u) {
	if (u == parent[u]) {
		return u;
	}
	else return parent[u] = find(parent[u]);
}

bool Union(ll u, ll v) {
	ll u1 = find(u);
	ll v1 = find(v);
	if (u1 == v1) {
		return false;
	}
	if (sz[u1] < sz[v1]) {
		parent[u1] = v1;
		sz[v1] += sz[u1];
	}
	else {
		parent[v1] = u1;
		sz[u1] += sz[v1];
	}
	return true;
}

int main() {

    // n is the number of vertices, m is the number of edges
	cin >> n >> m;
	init(); // Now there are n idependent components (thanh phan lien thong)

	ll totalComponents = n;
	bool isCyclical = false;

	// Input in edge list (not adjacent list)
	for (ll i = 1; i <= m; i++) {
		ll x, y; cin >> x >> y;
		bool check = Union(x, y);
		if (check) --totalComponents;
		else isCyclical = true;
	}

	if (isCyclical) {
		cout << "The graph has cycle!";
	}
	else {
		cout << "The graph doesn't have any cycles!";
	}

	return 0;
}