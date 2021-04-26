#include "snake.h"


//======================findTail
bool findingTail(queue<tuple<int, int>> position, tuple<int, int> target, vector<vector<int>> map, queue<string> operations)
{
	SnakeVirtual snake2(position);

	queue<tuple<int, int>> ori_pos1;
	queue<tuple<int, int>> new_pos1 = position;


	while (new_pos1.back() != target)
	{
		ori_pos1 = new_pos1;
		new_pos1 = snake2.nextPositionForTail(map, target);

		int new_head_x = get<0>(new_pos1.back());
		int new_head_y = get<1>(new_pos1.back());

		//invalid step
		int one_step_limit = 1;
		one_step_limit -= abs(get<0>(ori_pos1.back()) - new_head_x);
		one_step_limit -= abs(get<1>(ori_pos1.back()) - new_head_y);
		if (one_step_limit != 0)
		{
			return false;
		}


		//hit wall
		if (map[new_head_x][new_head_y] == -1)
		{
			return false;
		}

		//hitSelf
		queue<tuple<int, int>> tmp_queue = new_pos1;
		for (int i = 0; i < new_pos1.size() - 1; i++)
		{
			if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y)
			{
				return false;
			}
			tmp_queue.pop();
		}

	}

	return true;
}

//==============================================


//======================findRoad

bool findingRoad(queue<tuple<int, int>> position, tuple<int, int> target, vector<vector<int>> map, queue<string>& operations, tuple<int, int> tail)
{
	SnakeVirtual snake2(position);

	queue<tuple<int, int>> ori_pos1;
	queue<tuple<int, int>> new_pos1 = position;


	while (new_pos1.back() != target)
	{
		ori_pos1 = new_pos1;
		new_pos1 = snake2.nextPositionForRoad(map, target, operations);

		int new_head_x = get<0>(new_pos1.back());
		int new_head_y = get<1>(new_pos1.back());

		//invalid step
		int one_step_limit = 1;
		one_step_limit -= abs(get<0>(ori_pos1.back()) - new_head_x);
		one_step_limit -= abs(get<1>(ori_pos1.back()) - new_head_y);
		if (one_step_limit != 0)
		{
			return false;
		}


		//hit wall
		if (map[new_head_x][new_head_y] == -1)
		{
			return false;
		}

		//hitSelf
		queue<tuple<int, int>> tmp_queue = new_pos1;
		for (int i = 0; i < new_pos1.size() - 1; i++)
		{
			if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y)
			{
				return false;
			}
			tmp_queue.pop();
		}

	}


	if (findingTail(snake2.getPositionNow(), tail, map, operations))
	{
		return true;
	}

	return false;
}

//==============================================



//==============snakeVirtual
SnakeVirtual::SnakeVirtual(queue<tuple<int, int>> start_position)
{
	position = start_position;
}
//constructor

bool SnakeVirtual::collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map)
{
	//Check if the head is crashing into the obstacle
	if (map[std::get<0>(pos_head)][std::get<1>(pos_head)] == -1)
	{
		return true;
	}

	//Check if the head is crashing into itself, a.k.a. tails
	while (pos_body.size() != 0)
	{
		if (std::get<0>(pos_body.front()) == std::get<0>(pos_head) and std::get<1>(pos_body.front()) == std::get<1>(pos_head))
		{
			return true;
		}

		pos_body.pop();
	}
	return false;
}


queue<tuple<int,int>> SnakeVirtual::nextPositionForRoad(vector<vector<int>> map, tuple<int,int> target, queue<string>& operations)
{
	this->target = target;
	int head_x = std::get<0>(position.back());
	int head_y = std::get<1>(position.back());
	

	//Check if going y-1 is toward target and viable
	if (std::get<1>(target) < head_y)
	{
		if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
		{
			position.push(tuple<int, int>(head_x, head_y - 1));
			if (map[head_x][head_y - 1] == 0)
			{
				position.pop();
				operations.push("D");
			}
			else
			{
				operations.push("DE");
			}
			return position;
		}
	}

	//Check if going x-1 is toward target and viable
	if (std::get<0>(target) < head_x)
	{
		if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
		{
			position.push(tuple<int, int>(head_x - 1, head_y));
			if (map[head_x - 1][head_y] == 0)
			{
				position.pop();
				operations.push("L");
			}
			else
			{
				operations.push("LE");
			}
			return position;
		}
	}

	//Check if going x+1 is toward target and viable
	if (std::get<0>(target) > head_x)
	{
		if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
		{
			position.push(tuple<int, int>(head_x + 1, head_y));
			if (map[head_x + 1][head_y] == 0)
			{
				position.pop();
				operations.push("R");
			}
			else
			{
				operations.push("RE");
			}
			return position;
		}
	}

	//Check if going y+1 is toward target and viable
	if (std::get<1>(target) > head_y)
	{
		if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
		{
			position.push(tuple<int, int>(head_x, head_y + 1));
			if (map[head_x][head_y + 1] == 0)
			{
				position.pop();
				operations.push("U");
			}
			else
			{
				operations.push("UE");
			}
			return position;
		}
	}		
	
	
	//If none of those is viable, then repeat it without having to go toward the target
	
	//if y-1 is viable
	if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
	{
		position.push(tuple<int, int>(head_x, head_y - 1));
		if (map[head_x][head_y - 1] == 0)
		{
			position.pop();
			operations.push("D");
		}
		else
		{
			operations.push("DE");
		}
		return position;
	}

	//if x-1 is viable
	if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
	{
		position.push(tuple<int, int>(head_x - 1, head_y));
		if (map[head_x - 1][head_y] == 0)
		{
			position.pop();
			operations.push("L");
		}
		else
		{
			operations.push("LE");
		}
		return position;
	}

	//if x+1 is viable
	if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
	{
		position.push(tuple<int, int>(head_x + 1, head_y));
		if (map[head_x + 1][head_y] == 0)
		{
			position.pop();
			operations.push("R");
		}
		else
		{
			operations.push("RE");
		}
		return position;
	}

	//if y+1 is viable
	if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
	{
		position.push(tuple<int, int>(head_x, head_y + 1));
		if (map[head_x][head_y + 1] == 0)
		{
			position.pop();
			operations.push("U");
		}
		else
		{
			operations.push("UE");
		}
		return position;
	}

	//If all of those if unreachable, then GG!
	
	return position;
}


queue<tuple<int, int>> SnakeVirtual::nextPositionForTail(vector<vector<int>> map, tuple<int, int> target)
{
	this->target = target;
	int head_x = std::get<0>(position.back());
	int head_y = std::get<1>(position.back());


	//Check if going y-1 is toward target and viable
	if (std::get<1>(target) < head_y)
	{
		if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
		{
			position.push(tuple<int, int>(head_x, head_y - 1));
			if (map[head_x][head_y - 1] == 0)
			{
				position.pop();
			}
			return position;
		}
	}

	//Check if going x-1 is toward target and viable
	if (std::get<0>(target) < head_x)
	{
		if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
		{
			position.push(tuple<int, int>(head_x - 1, head_y));
			if (map[head_x - 1][head_y] == 0)
			{
				position.pop();
			}			
			return position;
		}
	}

	//Check if going x+1 is toward target and viable
	if (std::get<0>(target) > head_x)
	{
		if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
		{
			position.push(tuple<int, int>(head_x + 1, head_y));
			if (map[head_x + 1][head_y] == 0)
			{
				position.pop();
			}
			return position;
		}
	}

	//Check if going y+1 is toward target and viable
	if (std::get<1>(target) > head_y)
	{
		if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
		{
			position.push(tuple<int, int>(head_x, head_y + 1));
			if (map[head_x][head_y + 1] == 0)
			{
				position.pop();
			}
			return position;
		}
	}


	//If none of those is viable, then repeat it without having to go toward the target

	//if y-1 is viable
	if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
	{
		position.push(tuple<int, int>(head_x, head_y - 1));
		if (map[head_x][head_y - 1] == 0)
		{
			position.pop();
		}
		return position;
	}

	//if x-1 is viable
	if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
	{
		position.push(tuple<int, int>(head_x - 1, head_y));
		if (map[head_x - 1][head_y] == 0)
		{
			position.pop();
		}
		return position;
	}

	//if x+1 is viable
	if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
	{
		position.push(tuple<int, int>(head_x + 1, head_y));
		if (map[head_x + 1][head_y] == 0)
		{
			position.pop();
		}
		return position;
	}

	//if y+1 is viable
	if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
	{
		position.push(tuple<int, int>(head_x, head_y + 1));
		if (map[head_x][head_y + 1] == 0)
		{
			position.pop();
		}
		return position;
	}

	//If all of those if unreachable, then GG!

	return position;
}
//=============================================


//================snake
Snake::Snake(queue<tuple<int, int>> start_position)
{
	position = start_position;
}

bool Snake::collide(queue<tuple<int, int>> pos_body, tuple<int, int> pos_head, vector<vector<int>> map)
{
	//Check if the head is crashing into the obstacle
	if (map[std::get<0>(pos_head)][std::get<1>(pos_head)] == -1)
	{
		return true;
	}

	//Check if the head is crashing into itself, a.k.a. tails
	while (pos_body.size() != 0)
	{
		if (std::get<0>(pos_body.front()) == std::get<0>(pos_head) and std::get<1>(pos_body.front()) == std::get<1>(pos_head))
		{
			return true;
		}

		pos_body.pop();
	}
	return false;
}

tuple<int, int> Snake::getTarget(vector<vector<int>> map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			// This sample code will only try 1-point target
			if (map[i][j] == 2)
			{
				return tuple<int, int>(i, j);
			}
		}
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			// This sample code will only try 1-point target
			if (map[i][j] == 1)
			{
				return tuple<int, int>(i, j);
			}
		}
	}

	
	cout << "No 1-Point Target!! Call the TA!!";
	exit(0);
}


queue<tuple<int, int>> Snake::nextPosition(vector<vector<int>> map)
{
	target = getTarget(map);

	int head_x = std::get<0>(position.back());
	int head_y = std::get<1>(position.back());


	if (!operations.empty())
	{
		string nextToDo = operations.front();
		operations.pop();

		if (nextToDo == "R")
		{
			position.push(tuple<int, int>(head_x + 1, head_y));
			position.pop();
			
			return position;
		}
		else if (nextToDo == "RE")
		{
			position.push(tuple<int, int>(head_x + 1, head_y));

			while (!operations.empty())
			{
				operations.pop();
			}
			return position;
		}
		else if (nextToDo == "L")
		{
			position.push(tuple<int, int>(head_x - 1, head_y));
			position.pop();

			return position;
		}
		else if (nextToDo == "LE")
		{
			position.push(tuple<int, int>(head_x - 1, head_y));

			while (!operations.empty())
			{
				operations.pop();
			}
			return position;
		}
		else if (nextToDo == "U")
		{
			position.push(tuple<int, int>(head_x, head_y + 1));
			position.pop();

			return position;
		}
		else if (nextToDo == "UE")
		{
			position.push(tuple<int, int>(head_x, head_y + 1));
			while (!operations.empty())
			{
				operations.pop();
			}

			return position;
		}
		else if (nextToDo == "D")
		{
			position.push(tuple<int, int>(head_x, head_y - 1));
			position.pop();

			return position;
		}
		else if (nextToDo == "DE")
		{
			position.push(tuple<int, int>(head_x, head_y - 1));
			while (!operations.empty())
			{
				operations.pop();
			}

			return position;
		}

	}
	else
	{
		bool FindRoad = true;
		FindRoad = findingRoad(position, target, map, operations, position.front());
		

		if (FindRoad)
		{
			string nextToDo = operations.front();
			operations.pop();

			if (nextToDo == "R")
			{
				position.push(tuple<int, int>(head_x + 1, head_y));
				position.pop();

				return position;
			}
			else if (nextToDo == "RE")
			{
				position.push(tuple<int, int>(head_x + 1, head_y));
				while (!operations.empty())
				{
					operations.pop();
				}

				return position;
			}
			else if (nextToDo == "L")
			{
				position.push(tuple<int, int>(head_x - 1, head_y));
				position.pop();

				return position;
			}
			else if (nextToDo == "LE")
			{
				position.push(tuple<int, int>(head_x - 1, head_y));
				while (!operations.empty())
				{
					operations.pop();
				}

				return position;
			}
			else if (nextToDo == "U")
			{
				position.push(tuple<int, int>(head_x, head_y + 1));
				position.pop();

				return position;
			}
			else if (nextToDo == "UE")
			{
				position.push(tuple<int, int>(head_x, head_y + 1));
				while (!operations.empty())
				{
					operations.pop();
				}

				return position;
			}
			else if (nextToDo == "D")
			{
				position.push(tuple<int, int>(head_x, head_y - 1));
				position.pop();

				return position;
			}
			else if (nextToDo == "DE")
			{
				position.push(tuple<int, int>(head_x, head_y - 1));
				while (!operations.empty())
				{
					operations.pop();
				}

				return position;
			}
		}
		else
		{
			while (!operations.empty())
			{
				operations.pop();
			}

			directions fourDirection[4];
			//set up directions
			fourDirection[0].point = tuple<int, int>(head_x - 1, head_y);
			fourDirection[1].point = tuple<int, int>(head_x + 1, head_y);
			fourDirection[2].point = tuple<int, int>(head_x, head_y - 1);
			fourDirection[3].point = tuple<int, int>(head_x, head_y + 1);

			for (int i = 0; i < 4; i++)
			{
				int dx = abs(get<0>(target) - get<0>(fourDirection[i].point));
				int dy = abs(get<1>(target) - get<1>(fourDirection[i].point));

				fourDirection[i].distanceToApple = dx + dy;
			}

			//sorted
			for (int i = 0; i < 4; i++)
			{
				for (int j = i; j > 0; j--)
				{
					if (fourDirection[j].distanceToApple > fourDirection[j - 1].distanceToApple)
					{
						directions temp = fourDirection[j];
						fourDirection[j] = fourDirection[j - 1];
						fourDirection[j - 1] = temp;
					}
					else
						break;
				}
			}

			for (int i = 0; i < 4; i++)
			{
				queue<tuple<int, int>> position_copy = position;
				position_copy.push(fourDirection[i].point);
				queue<string> op;

				if (!collide(position, fourDirection[i].point, map))
				{
					if (findingTail(position_copy, position.front(), map, op))
					{
						position.push(fourDirection[i].point);
						if (map[get<0>(fourDirection[i].point)][get<1>(fourDirection[i].point)] == 0)
						{
							position.pop();
						}

						return position;
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				queue<tuple<int, int>> position_copy = position;
				position_copy.push(fourDirection[i].point);
				queue<string> op;

				if (!collide(position, fourDirection[i].point, map))
				{
					position.push(fourDirection[i].point);
					if (map[get<0>(fourDirection[i].point)][get<1>(fourDirection[i].point)] == 0)
					{
						position.pop();
					}

					return position;
					
				}
			}



			//Check if going y-1 is toward target and viable
			if (std::get<1>(target) < head_y)
			{
				if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
				{
					position.push(tuple<int, int>(head_x, head_y - 1));
					if (map[head_x][head_y - 1] == 0)
					{
						position.pop();
					}
					return position;
				}
			}

			//Check if going x-1 is toward target and viable
			if (std::get<0>(target) < head_x)
			{
				if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
				{
					position.push(tuple<int, int>(head_x - 1, head_y));
					if (map[head_x - 1][head_y] == 0)
					{
						position.pop();
					}
					return position;
				}
			}

			//Check if going x+1 is toward target and viable
			if (std::get<0>(target) > head_x)
			{
				if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
				{
					position.push(tuple<int, int>(head_x + 1, head_y));
					if (map[head_x + 1][head_y] == 0)
					{
						position.pop();
					}
					return position;
				}
			}

			//Check if going y+1 is toward target and viable
			if (std::get<1>(target) > head_y)
			{
				if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
				{
					position.push(tuple<int, int>(head_x, head_y + 1));
					if (map[head_x][head_y + 1] == 0)
					{
						position.pop();
					}
					return position;
				}
			}


			//If none of those is viable, then repeat it without having to go toward the target

			//if y-1 is viable
			if (!collide(position, tuple<int, int>(head_x, head_y - 1), map))
			{
				position.push(tuple<int, int>(head_x, head_y - 1));
				if (map[head_x][head_y - 1] == 0)
				{
					position.pop();
				}
				return position;
			}

			//if x-1 is viable
			if (!collide(position, tuple<int, int>(head_x - 1, head_y), map))
			{
				position.push(tuple<int, int>(head_x - 1, head_y));
				if (map[head_x - 1][head_y] == 0)
				{
					position.pop();
				}
				return position;
			}

			//if x+1 is viable
			if (!collide(position, tuple<int, int>(head_x + 1, head_y), map))
			{
				position.push(tuple<int, int>(head_x + 1, head_y));
				if (map[head_x + 1][head_y] == 0)
				{
					position.pop();
				}
				return position;
			}

			//if y+1 is viable
			if (!collide(position, tuple<int, int>(head_x, head_y + 1), map))
			{
				position.push(tuple<int, int>(head_x, head_y + 1));
				if (map[head_x][head_y + 1] == 0)
				{
					position.pop();
				}
				return position;
			}
		}
	}
	return position;
}