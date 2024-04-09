#include <string>
using namespace std;

class Solution {
public:
    string makeGood(string s) {
        bool notSafe;
        string retString;   //I am so good at naming things lmao.
        //Really simple algorithm: since we are looking for upper/lower ASCII, we just +- 32, and skip two if same.
        //God I love ASCII.
        for(int i = 0; i < s.length(); i++){
            if(s[i+1] + 32 == s[i] || s[i+1] - 32 == s[i]){
                i++;
                //BEFORE we do anything, check to make sure we aren't past bounds for nextchar now.
                if(!(i < s.length()-1)){
                    break;  //cant do anything, nope out.
                }
                //teeny tiny subcase owo: if the next character coming up is a +-32, TECHNICALLY
                //it's illegal for both it AND our last character to exist, therefore, we must deny both.
                else if(!(retString.empty())&&(retString.back() + 32 == s[i+1] || retString.back() - 32 == s[i+1])){
                    i++;
                    retString.pop_back();
                }
                continue; //Implicit i++

                }
            else{
                if(!(retString.empty())&&(s[i] + 32 == retString.back() || s[i] - 32 == retString.back())){
                    retString.pop_back();
                    continue;
                }
                else{
                    retString += s[i];

                }
                
            }

        }
        return retString; //AecGem at it again B^)
    }
};