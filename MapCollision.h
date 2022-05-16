#pragma once

using namespace std;
using namespace sf;
//столкновение со стеной
bool map_collision(bool _collect_pellets, bool _use_door, short _x, short _y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& _map)
{
	bool output = 0;
	float cell_x = _x / static_cast<float>(CELL_SIZE);//положение объекта
	float cell_y = _y / static_cast<float>(CELL_SIZE);//положение объекта
	for (unsigned char a = 0; a < 4; a++)
	{
		int x = 0;
		int y = 0;
		//выравнивание по четырем направлениям
		if (a == 0)
		{
			x = (floor(cell_x));//округление в сторону меньшего
			y = (floor(cell_y));
		}
		if (a == 1) 
		{
			x = ceil(cell_x);//округление в сторону большего
			y = floor(cell_y);
		}
		if (a == 2)
		{
			x = floor(cell_x);
			y = ceil(cell_y);
		}
		if (a == 3)
		{
			x = ceil(cell_x);
			y = ceil(cell_y);
		}
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)//если шарик в пределах карты
		{
			if (0 == _collect_pellets)
			{
				if (Wall == _map[x][y])//не может пройти
					output = 1;
			}
			else
			{
				if (_map[x][y] == Pellet)//съесть еду
					_map[x][y] = Empty;
			}
		}
	}

	return output;
}
