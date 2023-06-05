/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Pizza.hpp
*/

#pragma once
#include <string>
#include "IResource.hpp"

#include "../MyRayLibHeader/Draw.hpp"
#include "../MyRayLibHeader/Color.hpp"
#include "../MyRayLibHeader/Model.hpp"
#include "../MyRayLibHeader/Texture.hpp"

namespace ZappyGui {
    class Pizza: public IResource {
        private:
            Vector3 _scale;
            float _rotationAngle;
            Vector3 _position;
            const MyRayLib::Model &_model;
            const MyRayLib::Texture2D &_texture;
        public:
            Pizza(const MyRayLib::Model &model, const MyRayLib::Texture2D &texture, const Vector3 &position);
            ~Pizza();
            IResource::resourceType getType();
            void setPosition(float x, float z);
            const Vector3 &getPosition();
            void draw();
    };
}