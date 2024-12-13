#include <iostream>
#include <fstream>
#include <string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string;
using namespace std;

bool loadDeck(Game &g)
{
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try
    {
        g.loadDeckFromFile(filename);
    }
    catch (std::runtime_error const &)
    {
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount()
{
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while (true)
    {
        if ((!(std::cin >> numPlayers)) || numPlayers <= 0)
        {
            if (std::cin.fail())
            {
                // Clear the fail flag
                std::cin.clear();
                // Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else
        {
            // break out of the loop once we've read a valid number
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game &g, int numPlayers)
{
    // TODO: Determine whether each player is a human or an AI
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Is player " << i << " an AI? (y/n)" << endl;
        while (true)
        {
            string input;
            cin >> input;
            if (input != "y" && input != "n")
            {
                cout << "Please enter y or n" << endl;
            }
            else
            {
                bool isAi = input == "y";
                g.addPlayer(isAi);
                break;
            }
        }
    }
    // and add them to the game
}

void setupGame(Game &g)
{
    // TODO: Determine how many cards to deal, deal the cards, and
    // print the initial discard
    cout << "How many cards should each player start with?" << endl;
    while (true)
    {
        int input;
        if ((!(std::cin >> input)) || input <= 0)
        {
            if (std::cin.fail())
            {
                // Clear the fail flag
                std::cin.clear();
                // Remove the non-integer data from the stream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else
        {
            Card *c = g.deal(input);
            cout << "The initial discard is " + c->getRank() + " " + c->getSuit() << endl;
            break;
        }
    }
}

void print(Card *c)
{
    cout << c->getRank() << " " << c->getSuit() << endl;
}

int main()
{
    Game g;
    if (!loadDeck(g))
    {
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g, numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if (winner != -1)
    {
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else
    {
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;

    // Testing
    // Card *c1 = new Card("10", "Clubs");
    // Card *c2 = new Card("2", "Clubs");
    // Card *c3 = new Card("7", "Clubs");
    // Card *c4 = new Card("2", "Spades");
    // Card *c5 = new Card("9", "Hearts");
    // Player *p = new Player(true);
    // p->addToHand(c1);
    // p->addToHand(c2);
    // p->addToHand(c3);
    // p->addToHand(c4);
    // p->addToHand(c5);
    // vector<string> suits;
    // suits.push_back("Spades");
    // suits.push_back("Hearts");
    // suits.push_back("Dimonds");
    // suits.push_back("Clubs");
    // string curRank = "3";
    // string curSuit = "Clubs";
    // print(p->playCard(suits, curRank, curSuit));

    // Game *g = new Game();
    // g->loadDeckFromFile("microDeck.txt");
    // g->addPlayer(true);
    // g->addPlayer(true);
    // g->deal(4);
    // int i = g->runGame();
    // cout << i << endl;
}