#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Game.h"
using std::string, std::vector;
using namespace std;

Game::Game() : players({}), suits({}), ranks({}),
               deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename)
{
    ifstream f;
    f.open(filename);
    if (!f.is_open())
    {
        throw runtime_error("Cannot open file");
    }
    string line;
    // Read Suits
    getline(f, line);
    istringstream lineReader(line);
    string temp;
    while (lineReader >> temp)
    {
        suits.push_back(temp);
    }
    // Read Ranks
    getline(f, line);
    lineReader.clear();
    lineReader.str(line);
    bool check = false;
    while (lineReader >> temp)
    {
        if (temp == "8")
        {
            check = true;
        }
        ranks.push_back(temp);
    }
    if (!check)
    {
        throw runtime_error("Ranks did not contain an 8");
    }
    // Read Cards
    while (getline(f, line))
    {
        vector<string> lineAr;
        lineReader.clear();
        lineReader.str(line);
        while (lineReader >> temp)
        {
            lineAr.push_back(temp);
        }
        if (lineAr.size() != 2)
        { // Check arguments
            throw runtime_error("Missing or to many card arguments");
        }
        string curRank = lineAr.at(0);
        string curSuit = lineAr.at(1);
        // check if in suits and rank are in the list
        check = false;
        for (int i = 0; i < (int)suits.size(); i++)
        {
            if (suits.at(i) == curSuit)
            {
                check = true;
            }
        }
        if (!check)
        {
            throw runtime_error(curSuit + "not a valid suit");
        }
        check = false;
        for (int i = 0; i < (int)ranks.size(); i++)
        {
            if (ranks.at(i) == curRank)
            {
                check = true;
            }
        }
        if (!check)
        {
            throw runtime_error(curRank + "not a valid Rank");
        }
        // Check card constructor
        Card *CurCard;
        try
        {
            CurCard = new Card(curRank, curSuit);
        }
        catch (...)
        {
            throw runtime_error("failed card constructor");
        }
        // Add card to deck
        deck.push_back(CurCard);
        drawPile.insert(drawPile.begin(), CurCard);
    }
    for (int i = 0; i < (int)deck.size(); i++)
    {
        // Card *tempCard = deck.at(i);
        // cout << tempCard->getRank() + " " + tempCard->getSuit() << endl;
    }

    // TODO: initialize suits, ranks, deck, and drawPile from the given file
}

void Game::addPlayer(bool isAI)
{
    // TODO: add a new player to the game
    players.push_back(new Player(isAI));
}

void Game::drawCard(Player *p)
{
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    if (drawPile.empty() && discardPile.size() < 2)
    {
        throw runtime_error("Not enough cards in draw and discard pile");
    }
    else if (drawPile.empty()) // If drawPile is empty create new draw pile
    {
        cout << "Draw pile, empty, flipping the discard pile." << endl;
        int len = discardPile.size();
        for (int i = 0; i < len - 1; i++)
        {
            drawPile.insert(drawPile.begin(), discardPile.at(0));
            discardPile.erase(discardPile.begin());
        }
    }
    p->addToHand(drawPile.back());
    drawPile.pop_back();
}

// deals numCards cards to each player
Card *Game::deal(int numCards)
{

    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    // Create Discard pile
    discardPile.push_back(drawPile.back());
    drawPile.pop_back();
    for (int i = 0; i < numCards; i++) // Give cards out to each player numCards amount of times
    {
        for (int j = 0; j < (int)players.size(); j++) // Give each player a card
        {
            this->drawCard(players.at(j));
        }
    }
    return discardPile.back();
}
string Game::mostPlayedSuit()
{
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits

    string biggest_suit = suits.at(0);
    int biggest_num = 0;
    string temp_suit;
    // int temp_num = 0;

    // Run through all the suits
    for (int i = 0; i < (int)suits.size(); i++)
    {
        temp_suit = suits.at(i);
        int temp_num = 0;
        for (int j = 0; j < (int)deck.size(); j++) // Run through all the cards
        {
            if (deck.at(j)->getSuit() == temp_suit)
            {
                temp_num += deck.at(j)->getTimesPlayed();
            }
        }
        if (temp_num > biggest_num)
        {
            biggest_num = temp_num;
            biggest_suit = temp_suit;
        }
    }
    return biggest_suit;
}

int Game::runGame()
{
    // int cnt = 1;
    // TODO: Run the game and return the number of the winning
    string curRank;
    string curSuit;
    curRank = discardPile.back()->getRank();
    curSuit = discardPile.back()->getSuit();
    while (true)
    {
        Card *curCard = discardPile.back();
        for (int i = 0; i < (int)players.size(); i++) // Run through all the players
        {
            cout << "Player " << i << "'s turn!" << endl;
            Player *curPlayer = players.at(i);

            // Testing
            // cout << "Turn: " << cnt++ << endl;
            // cout << "TESTING hand before playing turn: " << curPlayer->getHandString() << endl;
            // cout << "What's ontop of the discard pile: " << discardPile.back()->getRank() + " " + discardPile.back()->getSuit() << endl;

            // cout << endl;
            // cout << "DrawPile Size: " << drawPile.size() << endl;
            // for (int i = 0; i < drawPile.size(); i++)
            // {
            //     cout << drawPile.at(i)->getRank() + " " + drawPile.at(i)->getSuit() << " ";
            // }
            // cout << endl;

            // cout << "Discard Size: " << discardPile.size() << endl;
            // for (int i = 0; i < discardPile.size(); i++)
            // {
            //     cout << discardPile.at(i)->getRank() + " " + discardPile.at(i)->getSuit() << " ";
            // }
            // cout << endl;
            // cout << endl;

            // End of testing
            curCard = curPlayer->playCard(suits, curRank, curSuit);
            if (curCard == nullptr) // Draw card
            {
                try
                {
                    this->drawCard(curPlayer);
                    cout << "Player " << i << " draws a card." << endl;
                }
                catch (...)
                {
                    cout << "Player " << i << " cannot draw a card." << endl;
                    return -1;
                }
            }
            else // Play card
            {
                cout << "Player " << i << " plays " + curCard->getRank() + " " + curCard->getSuit();
                if (curRank == "8")
                {
                    cout << " and changes the suit to " + curSuit + ".";
                }
                else
                {
                    cout << ".";
                }
                cout << endl;
                discardPile.push_back(curCard);
            }
            // cout << "TESTING hand before playing turn: " << curPlayer->getHandString() << endl << endl;
            if (curPlayer->getHandSize() == 0)
                return i;
        }
    }
}

// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game()
{
    for (unsigned int i = 0; i < deck.size(); i++)
    {
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++)
    {
        delete players.at(i);
    }
}