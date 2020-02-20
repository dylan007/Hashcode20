/*=======================
Author    : Shounak Dey
Filename  : sol.cpp
=======================	*/

#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;

#define PB push_back
#define MK make_pair 
#define SZ(a) (int)(sizeof(a))
#define F first
#define S second
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,n) for(int i=0;i<n;i++)
#define read(n) scanf("%d",&n)
#define readl(n) scanf("%lld",&n)
#define readul(n) scanf("%llu",&n);


#define SORTV(a) sort(a.begin(),a.end())
#define TEST int Test;cin >> Test;while(Test--)
#define gcd(a,b) __gcd(a,b)
#define ffs(a) __builtin_ffs(a) // find first set
#define clz(a) __builtin_clz(a) // count leading zeroes
#define ctz(a) __builtin_ctz(a) // count trailing zeroes
#define popc(a) __builtin_popcount(a) // count set bits
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)


#define error(args...) { vector<string> _v = split(#args, ','); err(_v.begin(), args); }

vector<string> split(const string& s, char c) {
	vector<string> v;
	stringstream ss(s);
	string x;
	while (getline(ss, x, c))
		v.emplace_back(x);
	return move(v);
}

void err(vector<string>::iterator it) {}
template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
	cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
	err(++it, args...);
}

#define LIM 100010

int main()
{
	fast_io;
	
	//INPUT

	ll b,l,d;
	cin >> b >> l >> d;
	vector<double> bs(b);
	REP(i,b)
		cin >> bs[i];
	vector<vector<pair<ll,ll>>> books(l,vector<pair<ll,ll>>());
	vector<double> st(l);
	vector<ll> proc(l,0);
	REP(i,l){
		ll n;
		cin >> n;
		vector<pair<ll,ll>> b(n);
		cin >> st[i] >> proc[i];
		REP(j,n){
			cin >> b[j].S;
			b[j].F = bs[b[j].S];
		}
		sort(b.rbegin(),b.rend());
		books[i] = b;
	}

	//CHECK INPUT
	// for(auto it: st)
	// 	cout << it << " ";
	// cout << endl;
	// for(auto it: proc)
	// 	cout << it << " ";
	// for(auto row: books){
	// 	for(auto it:row)
	// 		cout << it.F << " " << it.S << endl;
	// 	cout << endl;
	// }

	//SCORE EACH LIB
	vector<pair<double,ll>> lscores(l);
	REP(i,l){
		lscores[i].F = 1/st[i];
		ll timeleft = d - st[i];
		ll tbs = books[i].size();
		ll nbp = min(timeleft*proc[i],tbs);
		REP(j,nbp)
			lscores[i].F += books[i][j].F;
		lscores[i].S = i;
	}
	sort(lscores.rbegin(),lscores.rend());
	// for(auto it: lscores)
	// 	cout << it.F << " " << it.S << endl;
	// cout << endl;

	//SIM
	ll day=0;
	vector<ll> libs;
	ll pos=0,curr=st[lscores[0].S];
	vector<pair<ll,vector<ll>>> ret;
	while(day<d){
		curr--;
		if(curr==0){
			ll index = lscores[pos].S;
			ret.PB({index,vector<ll>()});
			ll timeleft = d - st[index];
			ll tbs = books[index].size();
			ll nbp = min(timeleft*proc[index],tbs);
			REP(i,nbp)
				ret[ret.size()-1].S.PB(books[index][i].S);
			pos++;
			curr = st[lscores[pos].S]; 
		}
		day++;
	}
	cout << ret.size() << endl;
	REP(i,ret.size()){
		cout << ret[i].F << " " << ret[i].S.size() << endl;
		for(auto it: ret[i].S)
			cout << it << " ";
		cout << endl;
	}
	return 0;
}