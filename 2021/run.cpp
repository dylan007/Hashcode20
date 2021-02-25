#include <bits/stdc++.h>

using namespace std;

int sim_time;
int n_intersections;
int n_streets;
int n_cars;
int kScore;

struct Street {
  int s, e, l;
  string n;

  Street(int start, int end, string name, int length) {
    s = start;
    e = end;
    n = name;
    l = length;
  }

  void print() {
    cout << "Road " << n << ":["
         << "Start intersection: " << s << ", "
         << "End intersection: " << e << ", "
         << "Length: " << l << "]\n";
  }
};

struct Car {
  vector<string> path;

  Car(vector<string>& p) : path(p) {}

  void print() {
    string output = "Car:[START -> ";
    for (auto& s : path) {
      output += s + " -> ";
    }
    output += "END]\n";
    cout << output;
  }
};

struct Intersection {
  int num, n_inter;
  unordered_map<string, float> streets;

  Intersection(int n) {
    num = n;
  }

  void insert(string street) {
    streets.insert(make_pair(street, 0));
  }

  void print() {
    std::cout << "Intersection " << num << ":[";
    string output = "";
    for (auto& s: streets) {
      output += s.first + " = " + to_string(s.second) + ", ";
    }
    cout << output << "]\n";
  }

  void update_score(string street, float score) {
    streets[street] += score;
  }

  void normalize() {
    if (streets.size() <= 1) {
      for (auto &s: streets) {
        s.second = 1.0;
      }
    }

    float total = 0;
    for (auto &s: streets) {
      total += s.second;
    }

    if (total < sim_time * 1.0) {
      return;
    }

    for (auto &s: streets) {
      s.second = (s.second / total) * sim_time;
    }
  }
};

vector<Car*> cars;
unordered_map<string, Street*> streets;
unordered_map<int, Intersection*> intersections;


template <typename T1, typename T2>
struct comp {
  typedef pair<T1, T2> type;
  bool operator()(type const& a, type const& b) const {
    return a.second > b.second;
  }
};

void final_solution() {
  std::cout << intersections.size() << endl;
  for (auto &in : intersections) {
    std::cout << in.first << endl;
    auto I = in.second;
    std::cout << I->streets.size() << endl;

    vector<pair<string, float> > mapcopy(I->streets.begin(), I->streets.end());
    sort(mapcopy.begin(), mapcopy.end(), comp<string, float>());

    for (auto &s: mapcopy) {
      int ans = floor(s.second) == 0? 1 : floor(s.second);
      std::cout << s.first << " " << ans << endl;
    }
  }
}

void input_street() {
  int s, e, l;
  string n;

  cin >> s >> e >> n >> l;
  Street *str = new Street(s, e, n, l);

  auto inter = intersections.find(e);

  Intersection *I;
  if (inter == intersections.end()) {
    I = new Intersection(e);
    I->insert(n);
    intersections.insert(make_pair(e, I));
  } else {
    inter->second->insert(n);
  }

  streets.insert(make_pair(n, str));
}

void input_car() {
  int npath;
  cin >> npath;
  vector<string> paths;
  while (npath--) {
    string street_name;
    cin >> street_name;
    paths.push_back(street_name);
  }
  cars.push_back(new Car(paths));
}

void solve() {
  unordered_map<string, int> traffics; // [intersection, street] -> (num cars * time to next)

  for (auto c : cars) {
    for (int i = 0; i < c->path.size() - 1; ++i) {
      string str = c->path[i];
      Street* street = streets[str];
      // intersections[street->e]->update_score(street->n, street->l);
      // intersections[street->e]->update_score(street->n, 1);
      // intersections[street->e]->update_score(street->n, streets[c->path[i]]->l);
      // intersections[street->e]->update_score(street->n, streets[c->path[i]]->l * 1.0 / (i+1));
      // intersections[street->e]->update_score(street->n, 1.0 / (i+1));
      // intersections[street->e]->update_score(street->n, 1.0 / sqrt(i+1));
      // intersections[street->e]->update_score(street->n, streets[c->path[i+1]]->l * 1.0 / (i+1));
      intersections[street->e]->update_score(street->n, streets[c->path[i+1]]->l * 1.0 / sqrt(i+1));
    }
    string lastStr = c->path[c->path.size() - 1];
    Street* lastStreet = streets[lastStr];
    intersections[lastStreet->e]->update_score(
      lastStreet->n, 1);
  }

  for (auto in: intersections) {
    in.second->normalize();
  }
}

void input() {
  cin >> sim_time
      >> n_intersections
      >> n_streets
      >> n_cars
      >> kScore;

  for (int i = 0; i < n_streets; ++i) {
    input_street();
  }

  for (int i = 0; i < n_cars; ++i) {
    input_car();
  }
}

int main() {
  input();

//  for (auto s: streets) {
//    s.second->print();
//  }
//
//  for (auto c: cars) {
//    c->print();
//  }
//
//  for (auto i : intersections) {
//    i.second->print();
//  }

  solve();

//  for (auto i : intersections) {
//    i.second->print();
//  }

  final_solution();
}
