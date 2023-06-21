/*
** EPITECH PROJECT, 2022
** ai_leo
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Player {
    public:
        int playerNumber;
        int level;
        int mapSizeX;
        int mapSizeY;
        std::vector<std::string> View;
        std::map<std::string, int> Inventory;

        ~Player() {};
        Player() {};
    private:
};

#endif /* !PLAYER_HPP_ */