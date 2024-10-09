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

set<ll> adj[N];
ll degree[N];
ll dist[N];
ll n, m;

int main() {

	cin >> n >> m;

	for (ll i = 1; i <= m; i++) {
		ll x, y; cin >> x >> y;
		adj[x].insert(y);
		adj[y].insert(x);
		degree[x]++;
		degree[y]++;
	}

	for (ll i = 1; i <= n; i++) {
		if (degree[i] & 1) {
			cout << "No euler cycle!";
			return 0;
		}
	}

	vector<ll> EC;
	stack<ll> st;
	st.push(1);
	while (!st.empty()) {
		ll v = st.top();
		if (adj[v].size() != 0) {
			ll y = *adj[v].begin();
			st.push(y);
			adj[v].erase(y);
			adj[y].erase(v);
		}
		else {
			EC.push_back(v);
			st.pop();
		}
	}

	cout << "The Euler cycle is: ";
	for (auto x : EC) cout << x << " ";


	return 0;
}