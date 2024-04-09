// * Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //Big brain moment, we are just doing math, exactly how the silicon does it.
        //Reverse order is just x1^(n) + y1^(n), x2^(n) + y2^(n) (...)
        //Therefore we just traverse the list and do math as we go.
        ListNode* rootNode = l1;    //My solution will focus on the l1 number, doesn't really matter which one.
        int carryValue = 0;
        int currNodeValue = 0;
        ListNode* currL1Pointer = l1;
        ListNode* currL2Pointer = l2;


        while (true) {
            //First, calculate current node values.
            currNodeValue = currL1Pointer->val + currL2Pointer->val + carryValue;
            carryValue = 0;

            //mmm, carry the one.
            if (currNodeValue > 9) {
                currNodeValue = currNodeValue - 10;
                carryValue = 1;
            }

            //Case 1: There are still nodes available in l1 and l2:
            //This case means we keep going.
            if (currL1Pointer->next != nullptr && currL2Pointer->next != nullptr) {
                currL1Pointer->val = currNodeValue;
                currL1Pointer = currL1Pointer->next;
                currL2Pointer = currL2Pointer->next;
                continue;   //Iterate and continue.
            }

            //Case 2: the l1 list will become exhausted, but the l2 list will not.
            //This case will cause a solution endpoint.
            if (currL1Pointer->next == nullptr && currL2Pointer->next != nullptr) {
                currL1Pointer->val = currNodeValue;
                //Here we cross-stitch l1 to l2, so our linked list will be complete.
                currL1Pointer->next = currL2Pointer->next;
                //Visual reference, l1 =  3 -> 6 -> (9) -> ~~~
                //                                    -> stich to 7
                //                  l2 =  7 -> 4 -> (0) -> 7 -> 3 -> (...)
                // Effective l1 list is now:
                //                  l1 =  3 -> 6 -> (9) -> 7 -> 3 -> (...)


                //Now, an edge case. If our carryValue is 1, and the next node value is 9, we have to cover the carry ripple/cascade
                //New sub-loop. Note that the loop only runs once if the edge case isn't true.
                while (true) {
                    currL1Pointer = currL1Pointer->next;
                    if (carryValue && currL1Pointer->val == 9) { //we love our guard statements.
                        currL1Pointer->val = 0;

                        //Edge-edge case: overflow causes new index. Solution end-case.
                        if (currL1Pointer->next == nullptr) {
                            //Create a new node with the carry-1, then we are finished.
                            ListNode* carryCascadeNode = new ListNode(carryValue);
                            currL1Pointer->next = carryCascadeNode;
                            return rootNode;
                        }
                    }
                    else {
                        //If there won't be a cascade, but we need to carry, do that.
                        if (carryValue) {
                            currL1Pointer->val += carryValue;
                            //Now we are done!
                            return rootNode;
                        }

                        //If there is no carry, we are done.
                        return rootNode;
                    }

                }


            }

            //Case 3: l2 will become exhausted.
            //This case will cause a solution endpoint.
            if (currL2Pointer->next == nullptr) {
                currL1Pointer->val = currNodeValue;

                //Carry edge cases from above;
                while (true) {
                    if (carryValue && currL1Pointer->next == nullptr) {
                        currL1Pointer->next = new ListNode(carryValue);
                        return rootNode;
                    }
                    else if (carryValue && currL1Pointer->next->val == 9) {
                        currL1Pointer->next->val = 0;
                        currL1Pointer = currL1Pointer->next;
                        continue;
                    }
                    else if (carryValue && currL1Pointer->next->val != 9) {
                        currL1Pointer->next->val += carryValue;
                        return rootNode;
                    }
                    else {
                        return rootNode;
                    }
                }

            }



        }


    }
};