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
ll n, m;

ll getTheBound(ll st) {
	set<ll> vis;
	ll bound = 0;

	ll curV = st;
	ll j = -1;
	ll mnDist = 1e9;
	for (auto v : adj[curV]) {
		if (v.second < mnDist) {
			mnDist = v.second;
			j = v.first;
		}
	}
	
	bound += mnDist;
	curV = j;
	vis.insert(curV);
	vis.insert(st);

	while (curV != st) {
		ll j = -1;
		ll mnDist = 1e9;
		for (auto v : adj[curV]) {
			if (v.second < mnDist && vis.find(v.first) == vis.end()) {
				mnDist = v.second;
				j = v.first;
			}
		}
		bound += mnDist;
		curV = j;
		vis.insert(curV);
	}

	return bound;
}

int main() {

	cin >> n >> m;
	for (ll i = 1; i <= m; i++) {
		ll x, y, w;
		cin >> x >> y >> w;
		adj[x].push_back({ y,w });
		adj[y].push_back({ x,w });
	}

	cout << getTheBound(1);


	return 0;
}