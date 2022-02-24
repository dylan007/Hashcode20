/*=======================
Author    : Shounak Dey
File      : sol
=======================*/

#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PB push_back
#define MK make_pair
#define SZ(a) (int)(sizeof(a))
#define F first
#define S second
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define REP(i, n) for (int i = 0; i < n; i++)
#define read(n) scanf("%d", &n)
#define readl(n) scanf("%lld", &n)
#define readul(n) scanf("%llu", &n);

#define SORTV(a) sort(a.begin(), a.end())
#define TEST     \
    int Test;    \
    cin >> Test; \
    while (Test--)
#define gcd(a, b) __gcd(a, b)
#define ffs(a) __builtin_ffs(a)       // find first set
#define clz(a) __builtin_clz(a)       // count leading zeroes
#define ctz(a) __builtin_ctz(a)       // count trailing zeroes
#define popc(a) __builtin_popcount(a) // count set bits
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)

#define error(args...)                         \
    {                                          \
        vector<string> _v = split(#args, ','); \
        err(_v.begin(), args);                 \
    }

vector<string> split(const string &s, char c)
{
    vector<string> v;
    stringstream ss(s);
    string x;
    while (getline(ss, x, c))
        v.emplace_back(x);
    return move(v);
}
void err(vector<string>::iterator it) {}
template <typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args)
{
    cerr << it->substr((*it)[0] == ' ', it->length()) << " = " << a << '\n';
    err(++it, args...);
}

class Role
{
public:
    string name;
    int level;

    Role()
    {
    }

    Role(string name, int level)
    {
        name = name;
        level = level;
    }

    void printRole()
    {
        cout << "RoleName : " << name << endl
             << "Level : " << level << endl;
    }

public:
    static Role buildRole()
    {
        Role x = Role();
        cin >> x.name >> x.level;
        return x;
    }
};

class Project
{
public:
    string name;
    int daysToComplete;
    int score;
    int bestBefore;
    int nRoles;
    vector<Role> roles;

    Project()
    {
    }

    Project(string name, int daysToComplete, int score, int bestBefore, int nRoles)
    {
        name = name;
        daysToComplete = daysToComplete;
        score = score;
        bestBefore = bestBefore;
        nRoles = nRoles;
    }

    void printProject()
    {
        cout << "ProjectName : " << name << endl
             << "Days to complete : " << daysToComplete << endl
             << "Score : " << score << endl
             << "Best Before : " << bestBefore << endl
             << "Number of Roles : " << nRoles << endl
             << "Roles Required : " << endl;
        for (auto role : roles)
        {
            role.printRole();
        }
        cout << endl;
    }

public:
    static Project buildProject()
    {
        Project x = Project();
        cin >> x.name;
        cin >> x.daysToComplete;
        cin >> x.score >> x.bestBefore >> x.nRoles;
        REP(i, x.nRoles)
        {
            x.roles.push_back(Role::buildRole());
        }
        return x;
    }
};

int main()
{
    fast_io;
    ll c, p;
    cin >> c >> p;
    map<string, vector<Role>> contributors;
    REP(i, c)
    {
        string name;
        cin >> name;
        int nSkills;
        cin >> nSkills;
        vector<Role> skills = vector<Role>();
        REP(j, nSkills)
        skills.push_back(Role::buildRole());
        cout << name << endl;
        for (auto it : skills)
            it.printRole();
        cout << endl;
    }
    vector<Project> projects = vector<Project>();
    REP(i, p)
    {
        projects.push_back(Project::buildProject());
    }
    for (auto it : projects)
        it.printProject();
    return 0;
}