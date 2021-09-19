#include <string>
#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

class Solution {
    using iter = std::string::iterator;
    using lettersIndices = vector<vector<int>>;
    int getNumberOfWords(iter wordStart, iter wordEnd, int indexStart, lettersIndices& letters) {
        const auto& letterIndices = letters[*wordStart];
        auto indexIter = upper_bound(letterIndices.begin(), letterIndices.end(), indexStart);
        if (indexIter == letterIndices.end()) {
            return 0;
        }

        if (wordStart + 1 == wordEnd) {
            return distance(indexIter, letterIndices.end());
        }
        int sum = 0;    
        for (auto i = indexIter; i !=  letterIndices.end(); ++i) {
            sum += getNumberOfWords(wordStart + 1, wordEnd, *i, letters);
        }
        return sum;
    }
    
public:
    int numDistinct(string s, string t) {
        lettersIndices lettersInS (256);
        for (int i = 0; i < s.size(); ++i) {
            lettersInS[s[i]].push_back(i);
        }
        return getNumberOfWords(t.begin(), t.end(), -1, lettersInS);
    }
};


int main()
{
    Solution s;
    cout << s.numDistinct("adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc", "bcddceeeebecbc");
}