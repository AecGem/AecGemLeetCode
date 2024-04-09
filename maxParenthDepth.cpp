#include <string>
using namespace std;
class Solution {
public:
    int maxDepth(string s) {
        short d = 0;
        short md = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i]==40){
                d++;
                md = d>md ? d : md;
            }
            else if(s[i]==41){
                d--;
            }
        }
        return md;
    }
};