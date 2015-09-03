#include "Sandbox.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cassert>
#include <cstdio>

bool DEBUG = false;

const float SQRT1_2 = 0.70710678118f;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TEXTURE_WIDTH = SCREEN_WIDTH;
const int TEXTURE_HEIGHT = SCREEN_HEIGHT;
const int TEXTURE_SIZE = 4 * TEXTURE_WIDTH * TEXTURE_HEIGHT;
const int SCREEN_OFFSET_X = -TileMap::TILE_SIZE / 2;
const int SCREEN_OFFSET_Y = 0;
const float epsilon = 0.001f;

GLuint textureID;
GLuint myBuffer;

World world;
Player player;

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
  int mods)
{
  switch (key) {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  case GLFW_KEY_D:
    if (action == GLFW_PRESS) DEBUG = !DEBUG;
    break;
  }
}

void updatePlayer(GLFWwindow* window)
{
  float dx = 0, dy = 0;
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    dx -= player.speed;
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    dx += player.speed;
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    dy -= player.speed;
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    dy += player.speed;
  }

  player.dx = (dx != 0 ? dx : 0.7f * player.dx);
  if (player.dx > -epsilon && player.dx < epsilon) player.dx = 0;
  player.dy = (dy != 0 ? dy : 0.7f * player.dy);
  if (player.dy > -epsilon && player.dy < epsilon) player.dy = 0;
}

bool updateFPS(GLFWwindow* window, int nbframes, double nbsec)
{
  if (nbsec > 1) {
    char buf[128];
    snprintf(buf, sizeof(buf), "Sandbox - FPS = %d - dx=%d dy=%d",
             (int)(nbframes / nbsec), (int)player.dx, (int)player.dy);
    glfwSetWindowTitle(window, buf);
    return true;
  }
  return false;
}

void initOpenGL(int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glfwSwapInterval(1);

  glEnable(GL_TEXTURE_RECTANGLE);
  glGenTextures(1, &textureID);
  glGenBuffers(1, &myBuffer);
  glBindTexture(GL_TEXTURE_RECTANGLE, textureID);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT,
               0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_RECTANGLE, 0);
}

void drawPoint(GLubyte* pbo, int x, int y, int c)
{
  x = glm::clamp(x + SCREEN_OFFSET_X, 0, TEXTURE_WIDTH);
  y = glm::clamp(y + SCREEN_OFFSET_Y, 0, TEXTURE_HEIGHT);
  ((int*)pbo)[y * TEXTURE_WIDTH + x] = c;
}

void drawRectangle(GLubyte* pbo, int x, int y, int w, int h, int c, bool filled = true)
{
  if (w < 0) {
    w = -w;
    x -= (w - 1);
  }
  if (h < 0) {
    h = -h;
    y -= (h - 1);
  }

  x += SCREEN_OFFSET_X;
  y += SCREEN_OFFSET_Y;
  int minX = glm::clamp(x, 0, TEXTURE_WIDTH);
  int minY = glm::clamp(y, 0, TEXTURE_HEIGHT);
  int maxX = glm::clamp(x + w, minX, TEXTURE_WIDTH);
  int maxY = glm::clamp(y + h, minY, TEXTURE_HEIGHT);

  int* buffer = (int*)pbo;
  if (filled) {
    for (int j = minY; j < maxY; ++j) {
      for (int i = minX; i < maxX; ++i) {
        buffer[j * TEXTURE_WIDTH + i] = c;
      }
    }
  } else {
    for (int i = minX; i < maxX; ++i) {
      buffer[minY * TEXTURE_WIDTH + i] = c;
      buffer[(maxY - 1) * TEXTURE_WIDTH + i] = c;
    }
    for (int j = minY; j < maxY; ++j) {
      buffer[j * TEXTURE_WIDTH + minX] = c;
      buffer[j * TEXTURE_WIDTH + (maxX - 1)] = c;
    }
  }
}

void render(int width, int height)
{
  // Render texture
  glBindTexture(GL_TEXTURE_RECTANGLE, textureID);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, myBuffer);
  glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT,
                  GL_BGRA, GL_UNSIGNED_BYTE, NULL);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, TEXTURE_SIZE, NULL, GL_STREAM_DRAW);
  GLubyte* pbo = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

  auto map = world.getTileMap(player.pos.tilemapX, player.pos.tilemapY);
  for (int j = 0; j < TileMap::HEIGHT; ++j) {
    for (int i = 0; i < TileMap::WIDTH; ++i) {
      drawRectangle(pbo, i * TileMap::TILE_SIZE, j * TileMap::TILE_SIZE,
                    TileMap::TILE_SIZE, TileMap::TILE_SIZE,
                    map->getTileColor(i, j));
    }
  }
  if (DEBUG) {
    for (int j = 0; j < TileMap::HEIGHT; ++j) {
      for (int i = 0; i < TileMap::WIDTH; ++i) {
        drawRectangle(pbo, i * TileMap::TILE_SIZE, j * TileMap::TILE_SIZE,
                      TileMap::TILE_SIZE, TileMap::TILE_SIZE, 0xf7f7f7, false);
      }
    }
  }

  const int px = player.pos.tileX * TileMap::TILE_SIZE + player.pos.X;
  const int py = player.pos.tileY * TileMap::TILE_SIZE + player.pos.Y;
  drawRectangle(pbo, px - player.width / 2, py, player.width, -player.height, player.color);
  drawPoint(pbo, px, py, 0xffffff);

  glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  glBindTexture(GL_TEXTURE_RECTANGLE, 0);

  // Draw texture
  glBindTexture(GL_TEXTURE_RECTANGLE, textureID);
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d(0.0, 0.0);
  glTexCoord2d(width, 0.0);
  glVertex2d(width, 0.0);
  glTexCoord2d(width, height);
  glVertex2d(width, height);
  glTexCoord2d(0.0, height);
  glVertex2d(0.0, height);
  glEnd();
  glBindTexture(GL_TEXTURE_RECTANGLE, 0);
}

void update(float dt)
{
  if (player.dx == 0 && player.dy == 0) return;
  float newX = player.pos.x + dt * player.dx;
  float newY = player.pos.y + dt * player.dy;

  auto newPos = world.getMapPosition(player.pos.tilemapX, player.pos.tilemapY, newX, newY);
  auto leftPos = world.getMapPosition(player.pos.tilemapX, player.pos.tilemapY, newX - player.width / 2, newY);
  auto rightPos = world.getMapPosition(player.pos.tilemapX, player.pos.tilemapY, newX + player.width / 2 - 1, newY);
  if (world.canWalk(leftPos) && world.canWalk(rightPos)) {
    player.pos = newPos;
  }
}

int main(int argc, char* argv[])
{
  if (!glfwInit()) {
    return 0;
  }

  glfwWindowHint(GLFW_RESIZABLE, 0);
  GLFWwindow* window =
      glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sandbox", NULL, NULL);
  if (window == nullptr) {
    glfwTerminate();
    return 0;
  }
  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return -1;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  initOpenGL(width, height);

  world.init(player);

  int nbframes = 0;
  double lastUpdate = 0;
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    const double now = glfwGetTime();
    const float dt = (float)(now - lastTime);
    lastTime = now;

    updatePlayer(window);
    update(dt);

    render(width, height);

    glfwSwapBuffers(window);

    glfwPollEvents();

    if (updateFPS(window, ++nbframes, now - lastUpdate)) {
      lastUpdate = now;
      nbframes = 0;
    }
  }

  glfwTerminate();
  return 0;
}
