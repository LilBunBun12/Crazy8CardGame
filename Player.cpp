#include <iostream>
#include <sstream>
#include "Player.h"
using std::vector, std::string, std::size_t;
using namespace std;

Player::Player(bool isAI) : isAI(isAI), hand() /* TODO: initialize */
{
}

void Player::addToHand(Card *c)
{
    // TODO: Add the card c to the player's hand
    hand.push_back(c);
}

size_t Player::getHandSize()
{
    // TODO: Implement getter
    return hand.size();
}

std::string Player::getHandString()
{
    // TODO: Implement getter
    string out = "";
    for (int i = 0; i < (int)hand.size(); i++)
    {
        out += hand.at(i)->getRank() + " " + hand.at(i)->getSuit() + ", ";
    }
    out = out.substr(0, out.size() - 2);
    return out;
}

Card *Player::playCard(vector<string> const &suits, string &currentRank, string &currentSuit)
{
    // TODO: Choose a card to play and return the chosen card
    Card *c = nullptr;
    if (isAI)
    {
        // cout << "Ran check point 1" << endl;
        for (int i = 0; i < (int)hand.size(); i++)
        {
            // cout << "Ran check point 2" << endl;
            if (hand.at(i)->canBePlayed(currentRank, currentSuit))
            {
                // cout << "Ran check point 3" << endl;
                c = hand.at(i);
                c->play();
                // cout << "Ran check point 4" << endl;
                if (c->getRank() == "8")
                {
                    currentSuit = c->getSuit();
                }
                // cout << "Ran check point 5" << endl;
                // cout << "Ran check point 6" << endl;
                hand.erase(hand.begin() + i);
                // cout << c->getRank() << c->getSuit() << endl;
                currentRank = c->getRank();
                currentSuit = c->getSuit();
                return c;
            }
        }
        return nullptr;
    }
    else
    {
        // cout << "Ran check point 1" << endl;
        // cout << "Ran check point 2" << endl;
        cout << "Your hand contains: " + this->getHandString() << endl;
        cout << "The next card played must be a " + currentRank + " or " + currentSuit << endl;
        cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;
        string rank = "";
        string suit = "";
        // // testing stuff
        // cout << this->getHandString() << endl;
        // cout << "Current rank: " << currentRank << currentSuit << endl;
        // cout << "input: " + rank + " " + suit << endl;
        // // End of testing stuff
        while (true)
        {
        out:
            cin >> rank >> suit;
            if (rank + " " + suit == "draw card")
                return nullptr;
            for (int i = 0; i < (int)hand.size(); i++) // Check every card in hand to see if they match
            {
                // cout << "Check point 1" << endl;
                if (rank == hand.at(i)->getRank() && suit == hand.at(i)->getSuit()) // If the card input is equal to the one in the deck
                {
                    // cout << "Check point 2" << endl;
                    if (hand.at(i)->canBePlayed(currentRank, currentSuit))
                    {
                        // cout << "Check point 3" << endl;
                        c = hand.at(i);
                        c->play();
                        hand.erase(hand.begin() + i);
                        if (c->getRank() == "8")
                        {
                            cout << "What suit would you like to declare?" << endl;
                            while (1 == 1)
                            {
                                string temp;
                                cin >> temp;

                                for (int i = 0; i < (int)suits.size(); i++)
                                {
                                    if (suits.at(i) == temp)
                                    {
                                        currentRank = c->getRank();
                                        currentSuit = temp;
                                        return c;
                                    }
                                }
                                cout << "That's not a suit in this deck. Try again." << endl;
                            }
                        }
                        currentRank = c->getRank();
                        currentSuit = c->getSuit();
                        // // Testing
                        // cout << "Check point 4" << endl;
                        // cout << "Card: " + currentRank + " " + currentSuit;
                        // // End of testing
                        return c;
                    }
                    else
                    {
                        // cout << "Check point 5" << endl;
                        cout << "You can't play that card. Try again." << endl;
                        goto out;
                    }
                }
            }
            // cout << "Check point 6" << endl;
            cout << "That's not a card you have. Try again." << endl;
        }
    }

    return c;
}