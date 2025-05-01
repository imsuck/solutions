#include <bits/stdc++.h>
#define newl '\n'
const int N = 2e5 + 10;
const long long INF = 1e18;

struct Node {
	long long f[4][4],lazy;
	Node() : f(),lazy(0) {
		///assume val equals to zero
		for(int i = 1; i < 3; ++i) {
			for(int j = 1; j < 3; ++j) {
				f[i][j] = -INF;
			}
		}
	}
	Node operator + (const Node &other) const {
		Node ans;
		for(int i = 0;i < 4;++i){
		    for(int j = 0;j < 4;++j){
		        ans.f[i][j] = -INF;
		    }
		}
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				for(int k = 0; k < 4; ++k) {
					for(int l = 0; l < 4; ++l) {
						if((j == 1 && k == 2) || (j == 2 && k == 1) || (j == 3 && k == 3)) {
							ans.f[i][l] = std::max(ans.f[i][l],f[i][j] + other.f[k][l]);
						}
					}
				}
			}
		}
		return ans;
	}
};
struct SegmentTree {
	int n, lg;
	std::vector<Node> st;
	SegmentTree(int _n) : n(_n), st(n * 4  + 10,Node()) {

	}
	void apply(int id,long long lazy) {
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) {
				st[id].f[i][j] -= (i == 1) * lazy;
				st[id].f[i][j] += (i == 2) * lazy;
				st[id].f[i][j] -= (j == 1) * lazy;
				st[id].f[i][j] += (j == 2) * lazy;
			}
		}
		st[id].lazy += lazy;
	}
	void up(int id) {
		st[id] = st[id << 1] + st[id << 1 | 1];
	}
	void down(int id) {
		apply(id << 1,st[id].lazy);
		apply(id << 1 | 1,st[id].lazy);
		st[id].lazy = 0;
	}
	void update(int l,int r,int u,int v,long long val,int id = 1) {
		if(u <= l && r <= v) {
			apply(id,val);
			return;
		}
		down(id);
		int mid = (l + r) / 2;
		if(v <= mid) {
			update(l,mid,u,v,val,id << 1);
		} else if(u > mid) {
			update(mid + 1,r,u,v,val,id << 1 | 1);
		} else {
			update(l,mid,u,v,val,id << 1);
			update(mid + 1,r,u,v,val,id << 1 | 1);
		}
		up(id);
	}
};
long long a[N + 1],n,q;

void readData() {
	std::cin >> n >> q;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
}
void solve() {
	SegmentTree st(n);
	for(int i = 1; i <= n; ++i) {
		st.update(1,n,i,i,a[i]);
	}
	for(int i = 1;i <= q;++i){
	    int l,r,x;
	    std::cin >> l >> r >> x;
	    st.update(1,n,l,r,x);
	    std::cout << st.st[1].f[3][3] << newl;
	}
}
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	readData();
	solve();
    return 0;
}
