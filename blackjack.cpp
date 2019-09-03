#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <array> 
#include <ctime>

using namespace std;
//Next, work on a hit/pass function, this should be damn easy after the ordeal with the heap

void DealtHand(vector<int>& i, vector<int>& h, vector<int>& d, int& length, int& pT, int& dT)
{
        int firstCard=0;
        int secondCard=0;
        int dealFCard=0;
        int dealSCard=0;
        //From here through line 40 is generating player and dealer opening hands, very rudimentary, try to optimize later
        firstCard=(1+(rand()%length));
        h.push_back(i[firstCard]);
        i.erase(i.begin() + firstCard);
        length--;
        secondCard = (1 + (rand() % length));
        h.push_back(i[secondCard]);
        i.erase(i.begin() + secondCard);
        length--;

        dealFCard = (1 + (rand() % length));
        d.push_back(i[dealFCard]);
        i.erase(i.begin() + dealFCard);
        length--;
        dealSCard = (1 + (rand() % length));
        d.push_back(i[dealSCard]);
        i.erase(i.begin() + dealSCard);
        length--;
        //From here until function end, iterating through respective vectors for player and dealer hands and printing them to check for rand()
        cout << "Your opening hand is: \n";
        for (vector<int>::iterator itr = h.begin(); itr != h.end(); itr++)
        {
            cout << *itr << endl;
            pT+=*itr;
            // cout << yourHandSum << endl;
        }
        cout << "Dealer's opening hand is: \n";
        for (vector<int>::iterator itr = d.begin(); itr != d.end(); itr++)
        {
            cout << *itr << endl;
            dT += *itr;

        }
     cout << endl;
}
void HandWinner(int p, int d)
{
    string winner=((p>d))?"Player":"Dealer";
    cout << winner + " wins!\n";
    cout << p << endl;
    cout << d << endl;
}
int main()
{
    //srand(time(NULL)) is used here to create a random seed so that the cards are actually randomized each run
    srand(time(NULL));
    // int jack, queen, king = 10;
    // int ace = 11;
    int allCards[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 11};
    int arrayLen=(sizeof(allCards)/sizeof(*allCards));
    int i=0;
    int playHandTotal=0;
    int dealHandTotal=0;
    vector<int> cardDeck;
    vector<int> yourHand;
    vector<int> dealerHand;
    cout << "Welcome to the Blackjack table, special rule is Aces are static at 11 \nand Face Cards are all named as 10, let's deal you in\n";
    bool playing = true;
    while (playing==true)
    {
        for(int j=0;j<4;j++)
        {
            for (i=0; i < arrayLen; i++)
            {
                cardDeck.push_back(allCards[i]);
            }
        i=0;
        }
        cout << "*Dealing Now*\n";
        
        DealtHand(cardDeck, yourHand, dealerHand, arrayLen, playHandTotal, dealHandTotal);
        
        //****Ha, fuck you pointers, I did it****
        // for (vector<int>::iterator itr = cardDeck.begin(); itr != cardDeck.end(); itr++)
        // {
        //     cout << *itr << endl;
        // }
        HandWinner(playHandTotal,dealHandTotal);

        playing=false;
    }





    return 0;
}