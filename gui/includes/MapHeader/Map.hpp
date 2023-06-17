/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Map.hpp
*/

#pragma once
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "../resources/FactoryResource.hpp"
#include "../MyRayLibHeader/Music.hpp"
#include "../MyRayLibHeader/Mouse.hpp"
#include "../MyRayLibHeader/Vector2D.hpp"
#include "../MyRayLibHeader/FreeCamera.hpp"
#include "../Server/ServerLink.hpp"

namespace ZappyGui {
    class Map {
        private:
            MyRayLib::Vector2D _size;
            std::vector<std::shared_ptr<Tile>> _map;
            ResourceManager &_manager;
            MyRayLib::FreeCamera &_camera;
            int _selectedTileKey;
            ServerLink &_link;

        public:
            std::shared_ptr<Player> findPlayerByID(int id);
            std::vector<std::shared_ptr<Player>> _players;
            Map(ResourceManager &manager, MyRayLib::FreeCamera &camera, ServerLink &link);
            ~Map();
            void createMap(int x, int y);
            void updateResourceForTile(const MyRayLib::Vector2D &pos, IResource::resourceType type, int number);
            void addEggForTile(const MyRayLib::Vector2D &pos, int id);
            void removeEgg(int id);
            void addPlayerForTile(const PlayerArguments &playerArgs);
            void draw();
            bool movePlayer(int playerID, float x, float z, Player::orientationAxis orientation);
            void deadPlayer(int playerID);
            void setPlayerLevel(int playerID, int level);
            bool lvlupPlayer(std::vector<int> playersID, int level);
            void StartPlayersLeveling(std::vector<int> playersID, int level, float x, float z);
            void EndPlayersLeveling(float x, float z, bool result);
            void dropResource(int playerID, IResource::resourceType type);
            void collectResource(int playerID, IResource::resourceType type);
            void updateMusic();
            void resetGame();
            void updatePlayer(float deltaTime);
            MyRayLib::Vector2D getSize() const { return _size; };
            void updatePlayerInventory(int id, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
    };
}
