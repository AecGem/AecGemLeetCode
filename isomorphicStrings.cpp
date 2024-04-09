#include <string>
#include <map>
using namespace std;
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        //Now, we need to map. Surely, such a convenient standard library item does not exist?
        std::map<char, short> map1;
        std::map<char, short> map2;
        bool inMap1;
        bool inMap2;
        short iter = 0;

        //Iterate through length of strings.
        for(int i = 0; i<s.length(); i++){
            //Now, some fun lil logic :3
            //Two strings are isomorphic if their unique character mapings are equivalent.
            //So, title = 12134, and paper = 12134, thus title and paper are isomorphic.
            //Therefore, we are going to have two running maps, and if no contradictions are found, its isomorphic!
            
            //Check and cache char in map for s and t.
            inMap1 = map1.contains(s[i]);
            inMap2 = map2.contains(t[i]);

            //If there is a unique char difference here, the result is not isomorphic!
            if(inMap1!=inMap2){
                return false;
                //Now, we check if they both don't have it. Add if so, add the map.
            } else if(inMap1==false){   //inMap1==inMap2 at this point due to first guard.
                map1[s[i]] = iter;
                map2[t[i]] = iter;
                iter++;
            }
            else{
                if(map1[s[i]]==map2[t[i]]){
                    continue;
                }
                else{
                    return false;
                }
            }

        }
        return true;
    }
};