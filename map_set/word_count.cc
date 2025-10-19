#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
  string line;
  getline(cin,line);

  map<string,int> wordCount;
  string word="";

  for(char c:line)
  {
    if(isalpha(c))
    {
      word+=tolower(c);
    }
    else
    {
      if(!word.empty())
      {
        wordCount[word]++;
        word="";
      }
    }
  }

  vector<pair<string, int>> sortedWords(wordCount.begin(), wordCount.end());
  sort(sortedWords.begin(), sortedWords.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             if (a.second != b.second) {
                 return a.second > b.second;  // 次数降序
             }
             return a.first < b.first;        // 字典序升序
         });

  for (const auto& p : sortedWords) {
        cout << p.first << ":" << p.second << endl;
    }

    return 0;
}