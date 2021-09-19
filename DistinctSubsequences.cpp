#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <map>

using namespace std;

class Solution {
    using iter = std::string::iterator;
    using lettersIndices = vector<vector<int>>;
    vector<map<int, int> > savedCounts;
    string t;
    int getNumberOfWords(int tStart, int indexStart, lettersIndices& letters) {
        if (savedCounts.size() - indexStart < t.size() - tStart) {
            return 0;
        }
        if (indexStart >= 0) {
            auto savedCountIter = savedCounts[indexStart].find(tStart);
            if ( savedCountIter != savedCounts[indexStart].end()) {
                return savedCountIter->second;
            }
        }
        const auto& letterIndices = letters[t[tStart]];
        auto indexIter = upper_bound(letterIndices.begin(), letterIndices.end(), indexStart);
        if (indexIter == letterIndices.end()) {
            if (indexStart >= 0) savedCounts[indexStart][tStart] = 0;
            return 0;
        }

        if (tStart + 1 == t.size()) {
            int d = distance(indexIter, letterIndices.end());
            savedCounts[indexStart][tStart] = d;
            return d;
        }

        
        int sum = 0;    
        for (auto i = indexIter; i !=  letterIndices.end(); ++i) {
            sum += getNumberOfWords(tStart + 1, *i, letters);
        }
        if (indexStart >= 0 ) savedCounts[indexStart][tStart] = sum;
        return sum;
    }
    
public:
    int numDistinct(string s, string t) {
        lettersIndices lettersInS (256);
        for (int i = 0; i < s.size(); ++i) {
            lettersInS[s[i]].push_back(i);
        }
        this->t = std::move(t);
        savedCounts.resize(s.size());
        return getNumberOfWords(0, -1, lettersInS);
    }
};


int main()
{
    Solution s;
    cout << s.numDistinct("rabbbit",
"rabbit");
}