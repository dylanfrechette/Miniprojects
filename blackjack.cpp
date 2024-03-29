/*********
would like to optimize a bit if possible, 
try to change some 10's to J,Q,K, 11's to A,
cut down on lines, find way to reduce repetition
*********/

#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <array> 
#include <ctime>

using namespace std;

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
        }
        cout << "Your total is: " << pT << endl;
        for (vector<int>::iterator itr = d.begin(); itr != d.end(); itr++)
        {
            //cout << *itr << endl;
            dT += *itr;
        }
        cout << "Dealer's shown card is: \n" << d[1] << endl;
}
void HandWinner(int p, int d)
{
    string winner=((p>d) && (p<=21))?"Player":"Dealer";
    if(d>21){winner="Player";}
    cout << winner + " wins!\n";
    cout << "Player total: " << p << endl;
    cout << "Dealer total: " << d << endl;
}
void HitOrPass(vector<int>& p, int& length, vector<int>& allCards, int& pT)
{
    int hitCard=0;
    char hitOrNah;
    bool ContinueHit = true;
    while(ContinueHit==true)
    {
        if(pT<=21)
        {
        cout << "Would you like to hit? (y or n)\n";
        cin >> hitOrNah;
        if(hitOrNah=='y')
        {
            hitCard = (1 + (rand() % length));
            p.push_back(allCards[hitCard]);
            allCards.erase(allCards.begin() + hitCard);
            length--;
            pT=0;
            cout << "Your hand is:\n";
            for (vector<int>::iterator itr = p.begin(); itr != p.end(); itr++)
            {
                cout << *itr << endl;
                pT += *itr;
            }
            cout << "Your hand total is " << pT << endl;
            continue;
        }
        else if(hitOrNah=='n')
        {
            cout << "You've chosen not to hit, your hand is now final\n";
            ContinueHit=false;
            break;
        }
        else
        {
            cout << "Not a valid input, try again\n";
            continue;
        }
        }
        else
        {
            cout << "You've busted\n";
            break;
        }   
    }
}
void DealHit(vector<int> &p, int &length, vector<int> &allCards, int &pT)
{
    int hitCard = 0;
    char hitOrNah;
    bool ContinueHit = true;
    while (ContinueHit == true)
    {
        if(pT<=21)
        {
        hitOrNah=(pT<=15)?'y':'n';
        if (hitOrNah == 'y')
        {
            cout << "Dealer has chosen to hit\n";
            hitCard = (1 + (rand() % length));
            p.push_back(allCards[hitCard]);
            allCards.erase(allCards.begin() + hitCard);
            length--;
            pT = 0;
            cout << "Dealer's shown cards are: \n";
            for (vector<int>::iterator itr = p.begin()+1; itr != p.end(); itr++)
            {
                cout << *itr << endl;
                pT += *itr;
            }
            cout << pT << endl;
            ContinueHit = true;
            continue;
        }
        else if (hitOrNah == 'n')
        {
            cout << "Dealer has chosen not to hit, his hand is final\n";
            ContinueHit = false;
            break;
        }
        }
        else
        {
            cout << "Dealer busted\n";
            break;
        }
    }
}
        int main()
        {
            //srand(time(NULL)) is used here to create a random seed so that the cards are actually randomized each run
            srand(time(NULL));
            cout << "Welcome to the Blackjack table, special rule is Aces are static at 11 \nand Face Cards are all named as 10, let's deal you in\n";
            bool playing = true;
            //while loop for inserting cards into deck
            while (playing == true)
            {
                //array storing values for cards, face cards are 10, ace is exclusively 11
                int allCards[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
                int arrayLen = (sizeof(allCards) / sizeof(*allCards));
                int i = 0;
                int playHandTotal = 0;
                int dealHandTotal = 0;
                vector<int> cardDeck;
                vector<int> yourHand;
                vector<int> dealerHand;
                //pushes the allCards array 4 times into deck
                for (int j = 0; j < 4; j++)
                {
                    for (i = 0; i < arrayLen; i++)
                    {
                        cardDeck.push_back(allCards[i]);
                    }
                    i = 0;
                }
                cout << "*Dealing Now*\n";
                
                //call function to "deal" hands to yourself and dealer
                DealtHand(cardDeck, yourHand, dealerHand, arrayLen, playHandTotal, dealHandTotal);
                // for (vector<int>::iterator itr = cardDeck.begin(); itr != cardDeck.end(); itr++)
                // {
                //     cout << *itr << endl;
                // }
                HitOrPass(yourHand, arrayLen, cardDeck, playHandTotal);
                if(playHandTotal <=21)
                {
                DealHit(dealerHand, arrayLen, cardDeck, dealHandTotal);
                }
                HandWinner(playHandTotal, dealHandTotal);
                cout << "Would you like to play another hand (y or n)?\n";
                char yesNo = 'y';
                cin >> yesNo;
                playing=(yesNo=='y')?true:false;
            }
            return 0;
        }
