#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct a {
  int b;
};
int main() {
  vector<string> msg{"Hello", "C++",     "World",
                     "from",  "VS Code", "and the C++ extension!"};

  for (const string &word : msg) {
    cout << word << " ";
  }
  cout << endl;
}