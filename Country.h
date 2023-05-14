#pragma once
#include <iostream>
#include <string>
#include <vector>

class Country
{
	std::string name;
	std::vector<int> votes;
	int points = 0;
public:
	Country(std::string name);
	void addVote(int vote);
	void addPoints(int points);
	std::string getName();
	int getVoteByIndex(int voteIndex);
	int getPoints();
};