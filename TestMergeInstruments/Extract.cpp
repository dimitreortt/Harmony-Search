#include <iostream>
#include <list>

using namespace std;

void showStringList(list<string> strings) {
  for (auto str : strings) {
    cout << str << " ";
  }
}

list<string> split(string s, string delimiter) {
  list<string> strings;

  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    strings.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  if (s.length() > 0) {
    strings.push_back(s);
  }

  return strings;
}

string lastPathToken(string path) {
  list<string> sl = split(path, "\\");

  if (sl.size() == 1) {
    sl = split(path, "/");
  }
  
  return sl.back();
}

string extractGenomeNameFromFullPath(string fullpath) {
  list<string> strings{ split(fullpath, ".f") };

  size_t size = strings.size();
  if (size == 2 || size == 1) {
    return lastPathToken(*strings.begin());
  }

  showStringList(strings);
  cout << "Erro em extractGenomeName";
  exit(1);
} 