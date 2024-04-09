#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool checkValidString(string s) {
        //This is a neat lil problem. Trying to create a linear solution was kind of difficult, but I think I got it.
        //The way we are going to handle this is creating a wildcard "budget" for each depth. 
        //Budgets are spent whenever we need to create a bracket out of a wildcard.
        //A depth level is created whenever we open a parenth, and removed whenever we close.
        //We will do two passes, an allocation, and a solve.

        int depth = 0;
        vector<int> depthBudget;
        depthBudget.push_back(0);   //Inital depth is zero. Zero has it's own budget - for preventing
                                    //Negative depth
        
        for(int i = 0; i<s.length();i++){   //First pass: Allocate.
            if(s[i]=='('){
                depthBudget.push_back(0);  //This is simple for now. Just make a new budget layer.
                depth++;
            }
            if(s[i]==')'){
                if(depth==0){
                    //Possible negative depth, check to see if we can prevent.
                    if(depthBudget[0]>0){
                        depthBudget[0]--;
                    }
                    else{
                        return false;   //Can't spend a token to prevent. We are kill.
                    }
                }
                else{
                    //Pop a layer off.
                    depthBudget.pop_back();
                    depth--;
                }
            }
            else if(s[i]=='*'){
                //If we get a wildcard, we get one additional token for every active layer.
                for(int x = 0; x<=depth;x++){
                    depthBudget[x]++;
                }
            }
        }

        while(true){                    //Second pass: Solve.
            if(depth>0){
                if(depthBudget[depth]>0){       //Use 1 budget from each level to reduce depth.
                    for(int x = 0; x<=depth;x++){
                        depthBudget[x]--;
                    }
                    depth--;
                    depthBudget.pop_back();
                }
                else{
                    return false;   //Cannot spend tokens to reduce depth. We lose :<
                }
            }
            else if(depth==0){
                return true;    //We are back to zero! We win! :3
            }
            
        }
        return false;       //Backup to prevent unintended behaviour.
    }
};