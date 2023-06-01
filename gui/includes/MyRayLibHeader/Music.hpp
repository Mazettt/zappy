/*
** EPITECH PROJECT, 2022
** B-YEP-400-MLH-4-1-zappy-martin.d-herouville
** File description:
** Music.hpp
*/

#include <iostream>
#include "raylib.h"

namespace MyRayLib {
    class Music {
        private:
            ::Music _music;
        public:
            Music(const std::string &path) {
                InitAudioDevice();
                _music = LoadMusicStream(path.c_str());
            }
            ~Music() {
                UnloadMusicStream(_music);
                CloseAudioDevice();
            }
            bool MyIsMusicReady() {
                return IsMusicReady(_music);
            }
            void MyUpdateMusic() {
                UpdateMusicStream(_music);
            }
            void MyPlayMusic() {
                PlayMusicStream(_music);
            }
            void MyStopMusic() {
                StopMusicStream(_music);
            }
            void MyPauseMusic() {
                PauseMusicStream(_music);
            }
            void MyResumeMusic() {
                ResumeMusicStream(_music);
            }
            bool MyIsMusicPlaying() {
                return IsMusicStreamPlaying(_music);
            }
            void MySetMusicVolume(float volume) {
                SetMusicVolume(_music, volume);
            }
        };
}