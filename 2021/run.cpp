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
    cout << "["
         << "Name: " << n << ", "
         << "Start intersection: " << s << ", "
         << "End intersection: " << e << ", "
         << "Length: " << l << "]\n";
  }
};

struct Car {
  vector<string> path;

  Car(vector<string>& p) : path(p) {}

  void print() {
    string output = "START -> ";
    for (auto& s : path) {
      output += s + " -> ";
    }
    output += "END\n";
    cout << output;
  }
};

vector<Car*> cars;
unordered_map<string, Street*> streets;

void input_street() {
  int s, e, l;
  string n;

  cin >> s >> e >> n >> l;
  Street *str = new Street(s, e, n, l);
  streets.insert(make_pair<string, Street*>(std::move(n), std::move(str)));
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
}
