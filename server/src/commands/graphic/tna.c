/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tna.c
*/

#include "../../../include/server.h"

void cmd_tna(zappy_t *zappy, char *command, int ci)
{
    (void)command;
    for (int i = 0; i < zappy->game.nbrTeams; ++i)
        sdprintf(zappy, client_socket(ci), "tna %s\n", zappy->game.teams[i].name);
}
