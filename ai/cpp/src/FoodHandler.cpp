/*
** EPITECH PROJECT, 2022
** cpp
** File description:
** FoodHandler.cpp
*/

#include <cmath>
#include <iostream>
#include "FoodHandler.hpp"

using namespace my;

FoodHandler::FoodHandler(int x, int y):
    _incantationScore(0),
    _mapSize(x * y),
    _factorLevel(6.4),
    _factorMapSize(0.7),
    _factorIncantationScore(7.2)
    {}

FoodHandler::~FoodHandler() {}

int FoodHandler::getMinimumFood() {
    return this->_minimumFood;
}

int FoodHandler::getMaximumFood() {
    return this->_maximumFood;
}

void FoodHandler::calculate(int playerLevel) {
    // MINIMUM PART
    double levelResult = this->_factorLevel * std::log10(1.0 + playerLevel);
    double mapResult = this->_factorMapSize * std::log10(1.0 + this->_mapSize);
    double IncantationResult = this->_factorIncantationScore * std::log10(1.0 + (-0));
    int finalResult = std::round(levelResult + mapResult + IncantationResult);
    this->_minimumFood = ((finalResult >= 4) ? finalResult : 4);

    // MAXIMUM PART
    int maximumFood = std::round(this->_minimumFood * (1 + 30 / (levelResult + 8)));
    this->_maximumFood = maximumFood;
}

void FoodHandler::incantationFail() {
    this->_incantationScore -= 1;
}

void FoodHandler::incantationSuccess() {
    this->_incantationScore = 0;
}

int FoodHandler::getIncantationScore() {
    return this->_incantationScore;
}
