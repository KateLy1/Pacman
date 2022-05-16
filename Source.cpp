#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "Sketch.h"
#include "Map.h"
#include "MapCollision.h"
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

GhostManager::GhostManager() : //конструктор гостменеджера
	ghosts({ Ghost(0), Ghost(1), Ghost(2)})
{}

int main()
{
	Music music; //музыка
	music.openFromFile("inf_project_Rammstein_-_Mann_Gegen_Mann.ogg");
	music.play();
	bool game_won = 0; 
	unsigned lag = 0;
	chrono::time_point<chrono::steady_clock> previous_time; //для скорости игры
	array<string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#.......#.#    ",
		"#####.#.##0##.#.#####",
		"........#12 #........",
		"#####.#.#####.#.#####",
		"#.....#.......#.....#",
		"#####.# ##### #.#####",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #..#.....P.....#..# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};
	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> map;
	array<Coordinates, 3> ghost_positions;
	Event event;
	RenderWindow window(VideoMode(CELL_SIZE * MAP_WIDTH * 2, (CELL_SIZE * MAP_HEIGHT) * 2), "Pac-Man", Style::Close); //создание окна
	window.setView(View(FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT)));//создание окна
	GhostManager ghost_manager;
	Pacman pacman;
	map = convert_sketch(map_sketch, ghost_positions, pacman);//создание карты через массив
	ghost_manager.reset(ghost_positions);//установка позиций приведений
	previous_time = chrono::steady_clock::now();
	while (1 == window.isOpen())
	{
		unsigned delta_time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - previous_time).count();
		lag += delta_time;
		previous_time += chrono::microseconds(delta_time);
		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;
			while (1 == window.pollEvent(event))//надо лт закрывать окно?
			{
				if (event.type == Event::Closed)
					window.close();
			}
			if (0 == game_won && 0 == pacman.get_dead())//кончилась ли игра?
			{
				game_won = 1;
				pacman.update(map);//обновляем позиции
				ghost_manager.update(map, pacman);//обновляем позиции
				for (const array<Cell, MAP_HEIGHT>& column : map)
				{
					for (const Cell& cell : column)
					{
						if (Pellet == cell)//осталась ли еда?
						{
							game_won = 0;
							break;
						}
					}
					if (0 == game_won)
						break;//выходим, если игра не выиграна
				}
			}
			if (FRAME_DURATION > lag)
			{
				window.clear();
				if (0 == game_won && 0 == pacman.get_dead())
				{
					draw_map(map, window);//рисуем карту
					ghost_manager.draw(window);//рисуем приведения
				}
				pacman.draw(game_won, window);//рисуем пакмэна
				window.display();
			}
		}
	}
	return 0;
}
