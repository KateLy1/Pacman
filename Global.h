#pragma once
//все константы
using namespace std;
using namespace sf;
constexpr unsigned char CELL_SIZE = 16;//размер клетки
constexpr unsigned char GHOST_1_CHASE = 1;//для преследования нужной клетки
constexpr unsigned char GHOST_2_CHASE = 4;//для преследования нужной клетки
constexpr unsigned char GHOST_SPEED = 1;//скорость приведений
constexpr unsigned char MAP_HEIGHT = 21;//высота поля
constexpr unsigned char MAP_WIDTH = 21;//ширина поля
constexpr unsigned char PACMAN_SPEED = 2;//скороксть пакмэна
constexpr unsigned int FRAME_DURATION = 16000; //отвечает за скорость всей игры

enum Cell //перечисление
{
	Empty,//пустая
	Pellet,//еда
	Wall//стена
};

struct Coordinates //структура координаты
{
	int x;
	int y;
	bool operator==(const Coordinates& _coordinates) //переопределение == для координат
	{
		return this->x == _coordinates.x && this->y == _coordinates.y;
	}
};
