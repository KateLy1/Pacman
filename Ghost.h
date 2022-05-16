#pragma once
#include "MapCollision.h"

using namespace std;
using namespace sf;

class Ghost
{
private:
	bool door; //возможность использовать дверь
	unsigned char direction;// направление
	unsigned char num;//номер приведения
	Coordinates home;//координаты дома
	Coordinates home_exit;//координаты выхода из дома
	Coordinates coordinates;//координаты приведения
	Coordinates target;//координаты цели
public:
	Ghost(unsigned char _num)//конструктор
	{
		num = _num;
		door = 0;
		direction = 0;
		home = { 0, 0 };
		home_exit = { 0,0 };
		coordinates = { 0,0 };
		target = { 0,0 };
	};

	bool pacman_collision(const Coordinates& _pacman_coordinates)//столкновение с пакмэном
	{
		if (coordinates.x > _pacman_coordinates.x - CELL_SIZE && coordinates.x < CELL_SIZE + _pacman_coordinates.x)//если пересекаются картинки по х
		{
			if (coordinates.y > _pacman_coordinates.y - CELL_SIZE && coordinates.y < CELL_SIZE + _pacman_coordinates.y)//если пересекаются картинки по у
			{
				return 1;//есть столкновение
			}
		}
		return 0;//нет столкновения
	}

	float get_target_distance(unsigned char _direction)// расчет пути до цели
	{
		int x = coordinates.x;
		int y = coordinates.y;
		if (_direction == 0)  //по направлинию определяем расстояние до цели по х и у
			x += GHOST_SPEED;
		if (_direction == 1)
			y -= GHOST_SPEED;
		if (_direction == 2)
			x -= GHOST_SPEED;
		if (_direction == 3)
			y += GHOST_SPEED;
		return (sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));//теорема Пифагора
	}

	void draw(RenderWindow& _window) //рисуем приведение
	{
		Sprite body;
		Texture texture;
		texture.loadFromFile("C:/game/Ghost16.png");
		body.setTexture(texture);
		body.setPosition(coordinates.x, coordinates.y);//ставим приведение на карту
		body.setTextureRect(IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));//выделяем спрайт из нужного места
		//задаем цвета приведений
		if (num == 0)
			body.setColor(Color(255, 0, 0));
		if (num == 1)
			body.setColor(Color(255, 182, 255));
		if (num == 2)
			body.setColor(Color(0, 255, 255));
		_window.draw(body);
	}

	void reset(const Coordinates& _home, const Coordinates& _home_exit) //задание данных приведению
	{
		door = 0 <= num;
		direction = 0;
		home = _home;
		home_exit = _home_exit;
		target = _home_exit;
	}

	void set_position(short i_x, short i_y)//задание координат приведению
	{
		coordinates = { i_x, i_y };
	}

	void update(array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& _ghost, Pacman& _pacman)//движение приведения
	{
		unsigned char available_ways = 0;//сколько возможных путей
		unsigned char speed = GHOST_SPEED;//скорость приведения
		vector<bool> walls(4);//содержит возможность движения в четыре стороны
		update_target(_pacman.get_direction(), _ghost.get_coordinates(), _pacman.get_coordinates());//обновление цели
		walls[0] = map_collision(0, door, speed + coordinates.x, coordinates.y, i_map);//заполняем массив, проверяя есть ли столкновение
		walls[1] = map_collision(0, door, coordinates.x, coordinates.y - speed, i_map);
		walls[2] = map_collision(0, door, coordinates.x - speed, coordinates.y, i_map);
		walls[3] = map_collision(0, door, coordinates.x, speed + coordinates.y, i_map);
		unsigned char optimal_direction = 4;//оптимальное направление
		for (unsigned char a = 0; a < 4; a++)
		{
			if (a == (2 + direction) % 4)//направление и а не должны совпадать
				continue;//прервать
			else if (0 == walls[a])//если нет столкновения
			{
				if (4 == optimal_direction)
					optimal_direction = a;
				available_ways++;//+1 возможный путь
				if (get_target_distance(a) < get_target_distance(optimal_direction))//выбираем наименьшее расстояние до цели
					optimal_direction = a;
			}
		}
		if (1 < available_ways)//если есть несколько путей
			direction = optimal_direction;//выбираем оптимальный
		else
		{
			if (4 == optimal_direction)//если не выбрали
				direction = (2 + direction) % 4;//выбираем рандом
			else
				direction = optimal_direction;//если один путь
		}
		if (direction == 0)//передвигаем в выбранном направлении
			coordinates.x += speed;
		if (direction == 1)
			coordinates.y -= speed;
		if (direction == 2)
			coordinates.x -= speed;
		if (direction == 3)
			coordinates.y += speed;
		if (-CELL_SIZE >= coordinates.x)//если координата за полем
			coordinates.x = CELL_SIZE * MAP_WIDTH - speed;
		else if (coordinates.x >= CELL_SIZE * MAP_WIDTH)//если координата за полем
			coordinates.x = speed - CELL_SIZE;
		if (1 == pacman_collision(_pacman.get_coordinates()))//если столкновение с пакмэном
			_pacman.set_dead(1);//пакмэн мертв
	}
	void update_target(unsigned char _pacman_direction, const Coordinates& _ghost_coordinates, const Coordinates& _pacman_coordinates)//обновление цели
	{
		if (1 == door)//если может выйти из двери
		{
			if (coordinates == target)
			{
				if (home_exit == target)
					door = 0;//если вышел, не войдет
			}
		}
		else
		{//задаем цели приведениям
			if (num == 0)
				target = _pacman_coordinates;//цель красного пакмэн
			if (num == 1)//цель розового -- на одну клетки дальше пакмэна
			{
				target = _pacman_coordinates;
				if (_pacman_direction == 0)
					target.x -= CELL_SIZE * GHOST_1_CHASE;
				if (_pacman_direction == 1)
					target.y += CELL_SIZE * GHOST_1_CHASE;
				if (_pacman_direction == 2)
					target.x += CELL_SIZE * GHOST_1_CHASE;
				if (_pacman_direction == 3)
					target.y -= CELL_SIZE * GHOST_1_CHASE;
			}
			if (num == 2)//цель голубого на 4 клетки вперед от пакмэна
			{
				target = _pacman_coordinates;
				if (_pacman_direction == 0)
					target.x += CELL_SIZE * GHOST_2_CHASE;
				if (_pacman_direction == 1)
					target.y -= CELL_SIZE * GHOST_2_CHASE;
				if (_pacman_direction == 2)
					target.x -= CELL_SIZE * GHOST_2_CHASE;
				if (_pacman_direction == 3)
					target.y += CELL_SIZE * GHOST_2_CHASE;
			}
		}
	}

	Coordinates get_coordinates()//отдает координаты приведения
	{
		return coordinates;
	}
};
