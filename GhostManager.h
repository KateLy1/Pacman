#pragma once

using namespace std;
using namespace sf;

class GhostManager
{
private:
	array<Ghost, 3> ghosts;//состоит из трех приведений
public:
	GhostManager();//конструктор пустой, т.к. здесь не позволяет добавить сюда приведений

	void draw(RenderWindow& _window)//рисует приведенией
	{
		for (Ghost& ghost : ghosts)
		{
			ghost.draw(_window);
		}
	}
	void reset(const array<Coordinates, 3>& _ghost_positions)//задает координаты
	{
		for (unsigned char a = 0; a < 3; a++)
		{
			ghosts[a].set_position(_ghost_positions[a].x, _ghost_positions[a].y);
		}
		for (Ghost& ghost : ghosts)
		{
			ghost.reset(ghosts[2].get_coordinates(), ghosts[0].get_coordinates());//по красному определяется дверь, по синему дом
		}
	}
	void update(array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& _map, Pacman& _pacman)//обновляем координаты
	{
		for (Ghost& ghost : ghosts)
		{
			ghost.update(_map, ghosts[0], _pacman);
		}
	}
};
