#include <bits/stdc++.h>

using namespace std;

class Lib {
public:
  Lib(uint32_t a, uint32_t b, uint32_t c) {
    num_books = a;
    signup_time = b;
    books_per_day = c;
  }
  uint32_t id;
  uint32_t num_books;
  uint32_t signup_time;
  uint32_t books_per_day;
  std::vector<std::pair<uint32_t, uint32_t>> books;
};

void printLibs(const vector<Lib> &libs) {
  for (auto &lib : libs) {
    cout << lib.id << "--->" << lib.num_books << ", " << lib.signup_time << ", "
         << lib.books_per_day << endl;
    // for (auto &book : lib.books) {
    //  cout << book.first << "->" << book.second << endl;
    //}
    // cout << endl;
  }
  cout << "---------\n";
}

int main() {
  int num_books, num_libs, num_days;
  cin >> num_books >> num_libs >> num_days;
  std::vector<uint32_t> book_scores;

  for (int i = 0; i < num_books; ++i) {
    uint32_t _tmp;
    cin >> _tmp;
    book_scores.push_back(_tmp);
  }

  std::vector<Lib> libs;
  for (int i = 0; i < num_libs; ++i) {
    // BOOKS, SIGNUP, RATE
    uint32_t _a, _b, _c;
    cin >> _a >> _b >> _c;
    Lib _l(_a, _b, _c);
    _l.id = i;

    for (int j = 0; j < _l.num_books; ++j) {
      uint32_t _tmp;
      cin >> _tmp;
      _l.books.push_back(make_pair(_tmp, book_scores[_tmp]));
    }
    libs.push_back(_l);
  }

//  printLibs(libs);
  sort(libs.begin(), libs.end(), [](const Lib &lhs, const Lib &rhs) {
    if (lhs.signup_time == rhs.signup_time) {
      if (lhs.books_per_day == rhs.books_per_day) {
        return lhs.num_books > rhs.num_books;
      }
      return lhs.books_per_day > rhs.books_per_day;
    }
    return lhs.signup_time < rhs.signup_time;
  });
//  printLibs(libs);

  cout << num_libs << endl;
  for (auto &lib : libs) {
    cout << lib.id << " " << lib.num_books << endl;
    sort(lib.books.begin(), lib.books.end(), [](const pair<uint32_t, uint32_t> &lhs, const pair<uint32_t, uint32_t> &rhs){
      return (lhs.first > rhs.second);
    });
    for (auto &book: lib.books) {
      cout << book.first << " ";
    }
    cout << endl;
  }
  // NUM_LIBS
  // LIBx1 NUMBOOKSx1
  // BOOKS IDX
  // LIBx2 NUMBOOKSx2
  // BOOKS IDX
}
