#pragma once
//рисунок карты
using namespace std;
using namespace sf;
void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& _map, RenderWindow& _window)
{
	Sprite sprite;
	Texture texture;
	texture.loadFromFile("C:/game/blue1.png");
	sprite.setTexture(texture);

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			sprite.setPosition((CELL_SIZE * a), (CELL_SIZE * b));
			if (_map[a][b] == Pellet)//рисунок еды
			{
				sprite.setTextureRect(IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
				sprite.setColor(Color(0, 182, 255));
				_window.draw(sprite);
			}
			if (_map[a][b] == Wall)//рисунок стены
			{
				sprite.setTextureRect(IntRect(68, 68, CELL_SIZE, CELL_SIZE));
				sprite.setColor(Color(255, 30, 150));
				_window.draw(sprite);
			}
		}
	}
}
