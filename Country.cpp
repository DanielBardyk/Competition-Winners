#include "Country.h"

Country::Country(std::string name)
{ this->name = name; };

void Country::addVote(int vote) 
{ votes.push_back(vote); }

void Country::addPoints(int points) 
{ this->points += points; }

std::string Country::getName() const
{ return name; }

int Country::getVoteByIndex(int voteIndex) const
{ return votes[voteIndex]; }

int Country::getPoints() const
{ return points; }