#include "LeaderData.h"

bool recordCompare(const recordItem &r1, const recordItem &r2)
{
	return r1.score > r2.score;
}

LeaderData::LeaderData(void)
{
}


LeaderData::~LeaderData(void)
{
}

LeaderData* LeaderData::create()
{
	LeaderData* leader = new LeaderData();
	if (leader)
	{
		leader->autorelease();
		leader->init();
		return leader;
	}
	CC_SAFE_DELETE(leader);
	return NULL;
}

bool LeaderData::init()
{
	getLeaderData();
	return true;
}

int LeaderData::getBestScore()
{
	if (leaderBoardTen.size() > 0)
	{
		return leaderBoardTen[0].score;
	}
	// return 0 means there is no record now;
	return 0;
}

std::string LeaderData::getCurrentTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	std::string str(buffer);
	return str;
}

void LeaderData::getLeaderData()
{
	char buffer[1024] = {0};
	auto path = cocos2d::FileUtils::getInstance()->getWritablePath();
	path.append("leaderboard.json");
	FILE *file = fopen(path.c_str(), "r");
	if (file)
	{
		fgets(buffer, 1024, file);
	
		std::string data = buffer;
		cocos2d::log(data.c_str());

		rapidjson::Document doc;
		if (data.length() > 0)
		{
			doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
			rapidjson::Value & array = doc["leaderBoard"];
			for (int i = 0; i < array.Size(); i++)
			{
				recordItem tempItem;
				rapidjson::Value & object = array[i];
				tempItem.time = object["time"].GetString();
				tempItem.score = object["score"].GetInt();
				leaderBoardTen.push_back(tempItem);
			}
			std::sort(leaderBoardTen.begin(), leaderBoardTen.end(), recordCompare);
		}

		fclose(file);
	}
}

std::vector<recordItem> & LeaderData::getLederBoardTen()
{
	return leaderBoardTen;
}

void LeaderData::updateLederData(int newScore)
{
	// update the top ten leaders in leaderBoardTen array
	recordItem newItem;
	newItem.score = newScore;
	newItem.time = getCurrentTime();

	if (leaderBoardTen.size() < 10)
	{
		leaderBoardTen.push_back(newItem);
		std::sort(leaderBoardTen.begin(), leaderBoardTen.end(), recordCompare);
	}
	else
	{
		leaderBoardTen.pop_back();
		leaderBoardTen.push_back(newItem);
		std::sort(leaderBoardTen.begin(), leaderBoardTen.end(), recordCompare);
	}

	// write the new result to json file
	auto  path =cocos2d::FileUtils::getInstance()->getWritablePath();
	path.append("leaderboard.json");
	CCLOG(path.c_str());

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	std::vector<recordItem>::iterator it = leaderBoardTen.begin();
	while (it != leaderBoardTen.end())
	{
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("time", it->time.c_str(), allocator);
		object.AddMember("score", it->score, allocator);
		array.PushBack(object, allocator);
		it ++;
	}
	
	document.AddMember("leaderBoard", array, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}
