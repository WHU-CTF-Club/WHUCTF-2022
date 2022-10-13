#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

long long const MAXN = 1000001, MAXM = 5000001;
long long const INF = 0x3FFFFFFFFFFFFFFFF;

long long n, m, s;
long long dis[MAXN];
bool visited[MAXN] = { 0 };
vector<pair<long long, long long> > g[MAXN];
queue<long long> q;
bool inqueue[MAXN] = { 0 };

void SPFA(long long S) {
	for (register long long i = 1; i <= n; ++i)	dis[i] = INF;
	dis[S] = 0;
	q.push(S);
	inqueue[S] = true;
	while (!q.empty()) {
		long long mn = q.front();
		q.pop();
		inqueue[mn] = false;
		for (register unsigned long long j = 0; j < g[mn].size(); ++j) {
			long long& v = g[mn][j].first, & w = g[mn][j].second;
			if (dis[v] > dis[mn] + w) {
				dis[v] = dis[mn] + w;
				if (!inqueue[v])
					q.push(v);
			}
		}
	}
}

int checktable[61] =
{
	0x3FE21, 0x9104, 0x6C499, 0x9A096, 0x8BFC9, 0x82130, 0x740D,
	0x1072A, 0x0F2D9E, 0x0B0955, 0x7CE3D, 0x7DF75, 0x5A514, 0x1C89B,
	0x1DD7E, 0x94FCA, 0x66CBA, 0x3E740, 0x0EBF57, 0x835C9, 0x2B99A,
	0x569C6, 0x0B9EB2, 0x0C5285, 0x0EE905, 0x0CDB4C, 0x0C0954,
	0x9F7A3, 0x573B1, 0x26458, 0x0CAE7C, 0x20DE0, 0x0DFE30, 0x0F2D9E,
	0x0C54FA, 0x0B328F, 0x0CD4F1, 0x215F9, 0x130C3, 0x7C21, 0x27C42,
	0x1BB23, 0x1E8C9, 0x816C1, 0x7AF14, 0x8FC04, 0x0DC7D4, 0x0BCF92,
	0x0AF726, 0x0EC163, 0x40E95, 0x97EC1, 0x0A8417, 0x51AAB, 0x1C35F,
	0x7F4B8, 0x25599, 0x4652C, 0x81115, 0x0CC863, 0x825D8
};

int main() {
	freopen("data.dat", "r", stdin);
	scanf("%lld %lld", &n, &m);
	for (register long long i = 1; i <= m; ++i) {
		long long a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);
		g[a].push_back(make_pair(b, c));
	}
	SPFA(1);

	for (int i = 0; i < 61; ++i)
		std::cout << static_cast<char>(dis[checktable[i]] / 3 ^ 14);

	return 0;
}
