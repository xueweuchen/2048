#ifndef _LEADER_DATA_H_
#define _LEADER_DATA_H_

#include "cocos2d.h"
#include <string>
#include <vector>
#include <algorithm>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

class recordItem
{
public:
	std::string time;
	int score;
};

bool recordCompare(const recordItem &r1, const recordItem &r2);

class LeaderData : public cocos2d::Ref
{
public:
	LeaderData(void);
	~LeaderData(void);
	
	void updateLederData(int newScore);
	int getBestScore();
	std::vector<recordItem> & getLederBoardTen();
	static LeaderData* create();
	virtual bool init();

private:
	std::string getCurrentTime();
	void getLeaderData();
	std::vector<recordItem> leaderBoardTen;
};

#endif


