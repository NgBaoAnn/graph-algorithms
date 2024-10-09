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
#define el cout << "\n"

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const ll N = 1e6 + 5;
const ll MOD = 1e9 + 7;

vector<pii> adj[N];
ll parent[N];
ll sz[N];
ll dist[N];
ll n, m;

struct edge {
	ll u, v;
	ll w;
};

bool cmp(edge a, edge b) {
	return a.w > b.w;
}

void make_set(ll u) {
	parent[u] = u;
	sz[u] = 1;
}

ll find_set(ll u) {
	return u == parent[u] ? u : parent[u] = find_set(parent[u]);
}

bool Union(ll u, ll v) {
	u = find_set(u);
	v = find_set(v);

	if (u != v) {
		if (sz[u] < sz[v]) {
			swap(u, v);
		}
		parent[v] = u;
		sz[u] += sz[v];
		return true;
	}
	else {
		return false;
	}
}

int main() {

	cin >> n >> m;

	vector<edge> edges;

	for (ll i = 1; i <= m; i++) {
		ll x, y, w; cin >> x >> y >> w;
		adj[x].push_back({ y, w });
		adj[y].push_back({ x, w });
		edge tmp;
		tmp.u = x;
		tmp.v = y;
		tmp.w = w;
		edges.push_back(tmp);
	}

	for (ll i = 1; i <= n; i++) make_set(i);

	sort(edges.begin(), edges.end(), cmp);

	vector<edge> mst;
	ll dMST = 0;

	while (mst.size() < n - 1 && edges.size() > 0) {
		edge tmp = edges[edges.size() - 1];
		if (Union(tmp.u, tmp.v)) {
			mst.push_back(tmp);
			dMST += tmp.w;
		}
		edges.pop_back();
	}

	cout << "Weight of MST is: " << dMST << "\n";
	cout << "Edges include: \n";
	for (auto x : mst) {
		cout << x.u << " " << x.v << " " << x.w << "\n"; 
	}

	return 0;
}