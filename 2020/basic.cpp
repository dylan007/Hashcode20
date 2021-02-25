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

  sort(libs.begin(), libs.end(), [](const Lib &lhs, const Lib &rhs) {
    if (lhs.signup_time == rhs.signup_time) {
      if (lhs.books_per_day == rhs.books_per_day) {
        return lhs.num_books > rhs.num_books;
      }
      return lhs.books_per_day > rhs.books_per_day;
    }
    return lhs.signup_time < rhs.signup_time;
  });

  // SORT BOOKS
  for (auto &lib : libs) {
    sort(lib.books.begin(), lib.books.end(),
         [](const pair<uint32_t, uint32_t> &lhs,
            const pair<uint32_t, uint32_t> &rhs) {
           return (lhs.second > rhs.second);
         });
  }

  // DUPLICATE REMOVAL
  unordered_set<uint32_t> book_set;
  std::vector<Lib> new_libs;
  for (auto &lib : libs) {
    vector<pair<uint32_t, uint32_t>> new_books;
    for (auto b : lib.books) {
      if (book_set.find(b.first) == book_set.end()) {
        new_books.push_back(b);
        book_set.insert(b.first);
      }
    }
    lib.books = new_books;
    if (lib.books.size() != 0) {
      new_libs.push_back(lib);
    }
  }
  libs = new_libs;

  // FINAL OUTPUT
  cout << libs.size() << endl;
  for (auto &lib : libs) {
    cout << lib.id << " " << lib.books.size() << endl;
    for (auto &book : lib.books) {
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
