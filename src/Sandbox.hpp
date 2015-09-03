#pragma once
#include <glm/glm.hpp>

struct Player;
struct Position;
struct World;

struct TileMap
{
  enum { TILE_NONE = -1, TILE_GRASS, TILE_WALL };
  static const int TILE_SIZE;
  static const int WIDTH;
  static const int HEIGHT;
  static const int TileColors[];

  int tilemapX;
  int tilemapY;
  int* tiles;

  bool contains(int x, int y)
  {
    return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
  }

  int getTileValue(int x, int y)
  {
    return contains(x, y) ? tiles[y * WIDTH + x] : TILE_NONE;
  }

  int getTileColor(int x, int y)
  {
    return contains(x, y) ? TileColors[tiles[y * WIDTH + x]] : 0;
  }
};

struct Position
{
  // tile relative coords
  int tilemapX;
  int tilemapY;
  int tileX;
  int tileY;
  int X;
  int Y;

  // screen relative coords
  float x;
  float y;
};

struct Player
{
  static const int color;
  static const int width;
  static const int height;

  Position pos;

  float dx;
  float dy;
  float speed;
};

struct World
{
  static const int WIDTH = 3;
  static const int HEIGHT = 2;

  TileMap tilemaps[WIDTH * HEIGHT];

  void init(Player& player);

  Position getMapPosition(int mx, int my, float px, float py);

  bool contains(int mapx, int mapy)
  {
    return (mapx >= 0 && mapx < WIDTH && mapy >= 0 && mapy < HEIGHT);
  }

  TileMap* getTileMap(int mapx, int mapy)
  {
    return contains(mapx, mapy) ? &tilemaps[mapy * WIDTH + mapx] : 0;
  }

  bool canWalk(Position pos)
  {
    auto map = getTileMap(pos.tilemapX, pos.tilemapY);
    return (map && map->getTileValue(pos.tileX, pos.tileY) == TileMap::TILE_GRASS);
  }
};
