#include <cctype>
#include <stdexcept>
#include <cctype>
#include "Card.h"
using std::string;
using namespace std;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) /* TODO: initialize */
{
    // TODO: implement constructor checks
    if (rank == "" || suit == "")
        throw invalid_argument("Rank or Suit is empty");
    for (int i = 0; i < (int)rank.length(); i++)
    {

        if (!isalnum(rank[i]))
        {
            throw invalid_argument("Rank is not valid");
        }
    }
    for (int i = 0; i < (int)suit.length(); i++)
    {
        if (!isalnum(suit[i]))
        {
            throw invalid_argument("Suit is not valid");
        }
    }
}

string Card::getRank()
{
    // TODO: implement getter
    return rank;
}

string Card::getSuit()
{
    // TODO: implement getter
    return suit;
}

int Card::getTimesPlayed()
{
    // TODO: implement getter
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit)
{
    // TODO: return whether or not the card can legally be played
    if (currentRank == rank || currentSuit == suit || rank == "8")
        return true;
    return false;
}

void Card::play()
{
    timesPlayed++;
}