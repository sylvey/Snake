#include <iostream>
#include <queue>
#include <tuple>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class SnakeVirtual
{
private:
	queue<tuple<int, int>> position;
	tuple<int, int> target;

public:

	SnakeVirtual(queue<tuple<int, int>> start_position);
	queue<tuple<int, int>> nextPositionForRoad(vector<vector<int>> map, tuple<int, int> target, queue<string>& operations);


	queue<tuple<int, int>> nextPositionForTail(vector<vector<int>> map, tuple<int, int> target);
	queue<tuple<int, int>> getPositionNow()
	{
		return position;
	};
	bool collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map);
};




//===================

struct directions
{
	tuple<int, int> point;
	int distanceToApple;
	directions() {
		point = tuple<int, int>(0, 0);
		distanceToApple = 0;
	}
};



//====================

//=====================Snake

class Snake
{
private:
	queue<tuple<int, int>> position;
	tuple<int, int> target;
	queue<string> operations;

public:
	Snake(queue<tuple<int, int>> start_position);
	queue<tuple<int, int>> nextPosition(vector<vector<int>> map);
	tuple<int, int> getTarget(vector<vector<int>> map);
	bool collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map);
};

