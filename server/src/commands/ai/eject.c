/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** eject.c
*/

#include "../../../include/server.h"

static void destroy_eggs(zappy_t *zappy, player_t *player)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        egg_t *egg = zappy->game.teams[i].eggs;
        egg_t *eggBuff = NULL;
        while (egg) {
            eggBuff = egg->next;
            (egg->x == player->x && egg->y == player->y) ?
                kill_egg(zappy, egg) : 0;
            egg = eggBuff;
        }
    }
}

static pos_t get_move(zappy_t *zappy, player_t *player)
{
    pos_t move = {player->x, player->y};
    switch (player->direction) {
        case NORTH:
            move.y = cast_pos(move.y - 1, HEIGHT);
            break;
        case EAST:
            move.x = cast_pos(move.x + 1, WIDTH);
            break;
        case SOUTH:
            move.y = cast_pos(move.y + 1, HEIGHT);
            break;
        case WEST:
            move.x = cast_pos(move.x - 1, WIDTH);
            break;
        default:
            break;
    }
    return move;
}

static void eject(zappy_t *zappy, unused char *command, int ci)
{
    player_t *player = zappy->client[ci].player;
    pos_t move = get_move(zappy, player);

    bool check = false;
    player_t *p = NULL;
    for (int i = -1; (p = parse_players(zappy, &i, p)); p = p->next) {
        if (p->client && p != player &&
        p->x == player->x && p->y == player->y) {
            p->x = move.x;
            p->y = move.y;
            sdprintf(zappy, p->client->command.s, "eject: %d\n", get_direction(
            (pos_t){p->x, p->y}, (pos_t){player->x, player->y}, p->direction));
            int it = 0;
            notif_guis(it, send_pex(zappy, it, p));
            check = true;
        }
    }
    destroy_eggs(zappy, player);
    sdprintf(zappy, client_socket(ci), (check ? "ok\n" : "ko\n"));
}

void cmd_eject(zappy_t *zappy, char *command, int ci)
{
    add_action(&zappy->client[ci], time_limit(7), command, eject);
}
