#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
struct a {
  int b;
};

int main() {
  vector<string> msg{
      "Hello",
      "C++",
      "World",
      "sdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "from",
      "VS Code",
      "and the C++ extension!"};

  for (const string &word : msg) {
    cout << word << " ";
  }
  cout << endl;
}