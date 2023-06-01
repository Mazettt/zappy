/*
** EPITECH PROJECT, 2022
** gui
** File description:
** map.cpp
*/

#include "../../includes/MapHeader/Map.hpp"

using namespace ZappyGui;

Map::Map(int x, int y) {
    float widthCube = 1.0;
    float lengthCube = 1.0;
    float heightCube = 0.1;
    this->_sizeX = x;
    this->_sizeY = y;
    this->_map.resize(x * y);

    Color color = RED;
    for (int y = 0; y < this->_sizeY; ++y) {
        for (int x = 0; x < this->_sizeX; ++x) {
            int key = y * this->_sizeX + x;
            Vector3 cubePosition = { widthCube * x, 0.0f, lengthCube * y };
            Cube cube(cubePosition, widthCube, heightCube, lengthCube, color);
            std::shared_ptr<Tile> tile = std::make_shared<Tile>(cube);
            // tile->addResource(0, 1);
            // tile->addResource(1, 1);
            // tile->addResource(2, 1);
            // tile->addResource(3, 1);
            // tile->addResource(4, 1);
            // tile->addResource(5, 1);
            // tile->addResource(6, 1);
            this->_map[key] = std::move(tile);
        }
    }
}

std::vector<std::shared_ptr<Tile>> Map::getMap() {
    return this->_map;
}

std::shared_ptr<Tile> &Map::getTile(int key) {
    return this->_map.at(key);
}

void Map::addResourceForTile(int posX, int posY, int keyResource, int quantity) {
    this->_map[posY * this->_sizeX + posX]->addResource(keyResource, quantity);
}

Map::~Map() {}