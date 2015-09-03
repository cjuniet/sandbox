#include "Sandbox.hpp"

const int TileMap::TILE_SIZE = 80;
const int TileMap::WIDTH = 17;
const int TileMap::HEIGHT = 9;
const int TileMap::TileColors[] = { 0x339933, 0x424266, 0xffff00 };

const int Player::color = 0xff3333cc;
const int Player::width = 50;
const int Player::height = 70;

int Tiles00[TileMap::WIDTH * TileMap::HEIGHT] = {
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 1,  1, 0, 0, 1,  1,  1, 0, 0, 1,  1, 0, 0, 1,
  1, 0, 0, 0,  1, 1, 0, 1,  0,  1, 0, 1, 1,  0, 0, 0, 0,
  1, 0, 0, 1,  1, 0, 0, 1,  1,  1, 0, 0, 1,  1, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 1, 1, 1,  1, 1, 1, 1,  0,  1, 1, 1, 1,  1, 1, 1, 1,
};

int Tiles01[TileMap::WIDTH * TileMap::HEIGHT] = {
  1, 1, 1, 1,  1, 1, 1, 1,  0,  1, 1, 1, 1,  1, 1, 1, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 1, 0,  0, 0, 0, 1,  0,  1, 0, 0, 0,  0, 1, 0, 1,
  1, 0, 1, 0,  0, 1, 1, 1,  0,  1, 1, 1, 0,  0, 1, 0, 0,
  1, 0, 1, 0,  0, 0, 0, 1,  0,  1, 0, 0, 0,  0, 1, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
};

int Tiles10[TileMap::WIDTH * TileMap::HEIGHT] = {
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 1,  1, 0, 0, 0,  0,  0, 0, 0, 1,  1, 0, 0, 1,
  0, 0, 0, 0,  0, 0, 0, 1,  1,  1, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 1,  1, 0, 0, 0,  0,  0, 0, 0, 1,  1, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 1, 1, 1,  1, 1, 1, 1,  0,  1, 1, 1, 1,  1, 1, 1, 1,
};

int Tiles11[TileMap::WIDTH * TileMap::HEIGHT] = {
  1, 1, 1, 1,  1, 1, 1, 1,  0,  1, 1, 1, 1,  1, 1, 1, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 1, 0,  0, 0, 1, 1,  0,  1, 1, 0, 0,  0, 1, 0, 1,
  0, 0, 0, 0,  0, 1, 1, 0,  0,  0, 1, 1, 0,  0, 0, 0, 0,
  1, 0, 1, 0,  0, 0, 1, 1,  0,  1, 1, 0, 0,  0, 1, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
};

int Tiles21[TileMap::WIDTH * TileMap::HEIGHT] = {
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  0, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 0, 0, 0,  0, 0, 0, 0,  0,  0, 0, 0, 0,  0, 0, 0, 1,
  1, 1, 1, 1,  1, 1, 1, 1,  1,  1, 1, 1, 1,  1, 1, 1, 1,
};

void World::init(Player& player)
{
  tilemaps[0] = { 0, 0, Tiles00 };
  tilemaps[1] = { 1, 0, Tiles10 };
  tilemaps[2] = { 2, 0, 0 };
  tilemaps[3] = { 0, 1, Tiles01 };
  tilemaps[4] = { 1, 1, Tiles11 };
  tilemaps[5] = { 2, 1, Tiles21 };

  const float px = 2 * TileMap::TILE_SIZE + player.width / 2;
  const float py = 3 * TileMap::TILE_SIZE - 1;
  player.pos = getMapPosition(0, 0, px, py);
  player.dx = player.dy = 0;
  player.speed = 160; // pixel/sec
}

Position World::getMapPosition(int mx, int my, float px, float py)
{
  Position pos;
  pos.tilemapX = mx;
  pos.tilemapY = my;
  pos.tileX = (int)glm::floor(px / TileMap::TILE_SIZE);
  pos.tileY = (int)glm::floor(py / TileMap::TILE_SIZE);
  pos.X = (int)glm::floor(px - pos.tileX * TileMap::TILE_SIZE);
  pos.Y = (int)glm::floor(py - pos.tileY * TileMap::TILE_SIZE);
  pos.x = px;
  pos.y = py;

  if (pos.tileX < 0) {
    --pos.tilemapX;
    pos.tileX += TileMap::WIDTH;
    pos.x = pos.tileX * TileMap::TILE_SIZE + pos.X;
  }
  if (pos.tileX >= TileMap::WIDTH) {
    ++pos.tilemapX;
    pos.tileX -= TileMap::WIDTH;
    pos.x = pos.tileX * TileMap::TILE_SIZE + pos.X;
  }
  if (pos.tileY < 0) {
    --pos.tilemapY;
    pos.tileY += TileMap::HEIGHT;
    pos.y = pos.tileY * TileMap::TILE_SIZE + pos.Y;
  }
  if (pos.tileY >= TileMap::HEIGHT) {
    ++pos.tilemapY;
    pos.tileY -= TileMap::HEIGHT;
    pos.y = pos.tileY * TileMap::TILE_SIZE + pos.Y;
  }

  return pos;
}
