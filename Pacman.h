#pragma once
#include "MapCollision.h"
using namespace std;
using namespace sf;

class Pacman
{
private:
	bool dead; //мертв?
	unsigned char direction; //направление
	Coordinates coordinates; //координаты
public:
	Pacman() //конструктор
	{
		dead = 0;
		direction = 0;
		coordinates = {0, 0};
	}

	bool get_dead()
	{
		return dead;
	}

	unsigned char get_direction()
	{
		return direction;
	}

	void draw(bool _victory, RenderWindow& i_window) //рисунок
	{
		Sprite sprite;
		Texture texture;
		sprite.setPosition(coordinates.x, coordinates.y);
		texture.loadFromFile("C:/game/Pacman16.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
		i_window.draw(sprite);
	}

	void set_dead(bool _dead)
	{
		dead = _dead;
	}

	void set_position(short _x, short _y)
	{
		coordinates = { _x, _y };
	}

	void update(array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& _map) //обновление кординат
	{
		vector<bool> walls (4); //может ли двигаться в 4 направлениях
		walls[0] = map_collision(0, 0, PACMAN_SPEED + coordinates.x, coordinates.y, _map);
		walls[1] = map_collision(0, 0, coordinates.x, coordinates.y - PACMAN_SPEED, _map);
		walls[2] = map_collision(0, 0, coordinates.x - PACMAN_SPEED, coordinates.y, _map);
		walls[3] = map_collision(0, 0, coordinates.x, PACMAN_SPEED + coordinates.y, _map);
		if (1 == Keyboard::isKeyPressed(Keyboard::Right)) //меняем направление клавиатурой
		{
			if (0 == walls[0])
			{
				direction = 0;
			}
		}
		if (1 == Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (0 == walls[1])
			{
				direction = 1;
			}
		}
		if (1 == Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (0 == walls[2])
			{
				direction = 2;
			}
		}
		if (1 == Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (0 == walls[3])
			{
				direction = 3;
			}
		}
		if (0 == walls[direction]) //задание движения, если оно возможно
		{
			if (direction == 0)
				coordinates.x += PACMAN_SPEED;
			if (direction == 1)
				coordinates.y -= PACMAN_SPEED;
			if (direction == 2)
				coordinates.x -= PACMAN_SPEED;
			if (direction == 3)
				coordinates.y += PACMAN_SPEED;
		}
		if (-CELL_SIZE >= coordinates.x)//если находится за картой
		{
			coordinates.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
		}
		else if (CELL_SIZE * MAP_WIDTH <= coordinates.x) //если находится за картой
		{
			coordinates.x = PACMAN_SPEED - CELL_SIZE;
		}
		map_collision(1, 0, coordinates.x, coordinates.y, _map);
	}

	Coordinates get_coordinates()
	{
		return coordinates;
	}
};
