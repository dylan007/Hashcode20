#include <bits/stdc++.h>

using namespace std;

int sim_time;
int n_intersections;
int n_streets;
int n_cars;
int score;

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
  vector<string> streets;

  Intersection(int n) {
    num = n;
  }

  void insert(string street) {
    streets.push_back(street);
  }

  void print() {
    std::cout << "Intersection " << num << ":[";
    string output = "";
    for (auto& s: streets) {
      output += s + ", ";
    }
    cout << output << "]\n";
  }
};

vector<Car*> cars;
unordered_map<string, Street*> streets;
unordered_map<int, Intersection*> intersections;

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

void input() {
  cin >> sim_time
      >> n_intersections
      >> n_streets
      >> n_cars
      >> score;

  for (int i = 0; i < n_streets; ++i) {
    input_street();
  }

  for (int i = 0; i < n_cars; ++i) {
    input_car();
  }
}

int main() {
  input();

  for (auto s: streets) {
    s.second->print();
  }

  for (auto c: cars) {
    c->print();
  }

  for (auto i : intersections) {
    i.second->print();
  }
}
