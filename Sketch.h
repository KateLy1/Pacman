#pragma once
using namespace std;
//перевод карты из строки в массив
array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& _map, array<Coordinates, 3>& ghost_pos, Pacman& _pacman)
{
	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> map;
	for (unsigned char a = 0; a < MAP_HEIGHT; a++)
	{
		for (unsigned char b = 0; b < MAP_WIDTH; b++)
		{
			map[b][a] = Empty;
			if (_map[a][b] == '#')
				map[b][a] = Wall;
			if (_map[a][b] == '.')
				map[b][a] = Pellet;
			if (_map[a][b] == '0')//приведение
			{
				ghost_pos[0].x = CELL_SIZE * b;
				ghost_pos[0].y = CELL_SIZE * a;
			}
			if (_map[a][b] == '1')//приведение
			{
				ghost_pos[1].x = CELL_SIZE * b;
				ghost_pos[1].y = CELL_SIZE * a;
			}
			if (_map[a][b] == '2')//приведение
			{
				ghost_pos[2].x = CELL_SIZE * b;
				ghost_pos[2].y = CELL_SIZE * a;
			}
			if (_map[a][b] == 'P')//пакмэн
				_pacman.set_position(CELL_SIZE * b, CELL_SIZE * a);
		}
	}
	return map;
}
