#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        //This one is a neat lil question!
        //Analyzing the behaviour of the numbers in the deck led me to realize a few properties:
        //1. The even indices of the final deck are never "moved", and on that note:
        //2. The even indices of the final deck are populated by the corresponding indices < ceiling(len/2) of the sorted array.
        //3. Then, that leads us to discover that the remaining indices can be reverse-formed using a procedure on their own, described later.
        
        //Let's go!
        std::sort(deck.begin(),deck.end()); //First, sort the array :3
        //Small exception!
        //If the deck is literally just two items, nothing fancy is needed. Just return sorted deck.
        if(deck.size()==2){
            return deck;
        }
        //Another lil tidbit - logic changes if deck size is odd or even!
        int oddness = deck.size()%2;

        vector<int> returnDeck(deck); //Now, we make another array that will be our final deck.

        //Now for each item in the first sorted array, below index ceiling(deck.len/2)
        //we are going to add these to the even indexes in the return deck.

        for(int i = 0; i<ceil(deck.size()/2)+oddness;i++){
            returnDeck[i*2] = deck[i];
        }

        //Next step, we are going to take the remaining elements and put them into another temporary vector.
        vector<int> parkingVec;
        for(int i = ceil(deck.size()/2)+oddness; i < deck.size();i++){
            parkingVec.push_back(deck[i]);
        }

        //Now we need a queue to facilitate our items being put to the bottom (or in our case, the top) of the deck.
        deque<int> swapperQueue;

        //Now, we are going to replicate the movements the proper deck has to go through for it's odd items,
        //however, we will do this in reverse, thereby creating the correct order. We will have to do n-1 iterations.
        for(int i=0;i<deck.size()-;i++){
            //This iteration has two parts. First part: if the parkingVec still has stuff in it, we will inject one
            //onto the front of our queue.
            if(parkingVec.empty()==false){
                swapperQueue.push_front(parkingVec.back());
                parkingVec.pop_back();
            }
            //Next part, we will take the item currently at the "back" of the deck and put it to the front.
            swapperQueue.push_front(swapperQueue.back());
            swapperQueue.pop_back();
        }
        //After that is done, we are going to take all the items in the swapperQueue and allocate them
        //to the i*2+1 'th index in the return deck.
        for(int i = 0; i<swapperQueue.size();i++){
            returnDeck[i*2+1] = swapperQueue[i];
        }
        //And... Thats it!
        return returnDeck;
    }
};