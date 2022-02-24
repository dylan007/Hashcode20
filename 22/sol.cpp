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
    int maxLevel;

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
             << "Max Level : " << maxLevel << endl
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
        x.maxLevel = 0;
        REP(i, x.nRoles)
        {
            x.roles.push_back(Role::buildRole());
            x.maxLevel = max(x.maxLevel, x.roles.back().level);
        }
        return x;
    }
};

class Person
{
public:
    string name;
    unordered_map<string, Role> skills;

    Person()
    {
    }

    Person(string name, unordered_map<string, Role> skills)
    {
        name = name;
        skills = skills;
    }

    void update(string skillName, int skillLevel)
    {
        skills[skillName].level += (skills[skillName].level == skillLevel);
    }

public:
    static Person createPerson()
    {
        Person x = Person();
        cin >> x.name;
        int nSkills;
        cin >> nSkills;
        REP(i, nSkills)
        {
            Role xRole = Role::buildRole();
            x.skills[xRole.name] = xRole;
        }
        return x;
    }
};

class Project_Compare
{
public:
    bool operator()(const Project &a, const Project &b)
    {
        if (a.maxLevel != b.maxLevel)
            return (a.maxLevel < b.maxLevel);
        if (a.score != b.score)
            return (a.score > b.score);
        if (a.daysToComplete != b.daysToComplete)
            return (a.daysToComplete < b.daysToComplete);
        if (a.bestBefore != b.bestBefore)
            return (a.bestBefore < b.bestBefore);
        return false;
    }
};

map<string, Person> contributors;

int main()
{
    fast_io;
    ll c, p;
    cin >> c >> p;
    contributors = map<string, Person>();
    REP(i, c)
    {
        Person x = Person::createPerson();
        contributors[x.name] = x;
    }
    list<Project> projects = list<Project>();
    REP(i, p)
    {
        projects.push_back(Project::buildProject());
    }
    Project_Compare cmp;

    projects.sort(cmp);
    // for (auto it : projects)
    //     it.printProject();

    vector<pair<string, vector<string>>> output = vector<pair<string, vector<string>>>();
    for (auto project : projects)
    {
        int check = 1;
        vector<string> persons = vector<string>();
        unordered_set<string> taken;
        for (auto skill : project.roles)
        {
            int f = 0;
            for (auto person : contributors)
            {
                if (taken.find(person.second.name) != taken.end())
                    continue;
                string skillName = skill.name;
                if (person.second.skills.find(skillName) != person.second.skills.end())
                {
                    f |= (person.second.skills[skillName].level >= skill.level);
                    if (f)
                    {
                        persons.push_back(person.second.name);
                        taken.insert(person.second.name);
                        person.second.update(skillName, skill.level);
                        break;
                    }
                }
            }
            check &= f;
        }
        if (check)
            output.push_back(MK(project.name, persons));
    }

    cout << output.size() << endl;
    for (auto project : output)
    {
        cout << project.first << endl;
        for (auto name : project.second)
            cout << name << " ";
        cout << endl;
    }
    return 0;
}