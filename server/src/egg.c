/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** egg.c
*/

#include "../include/server.h"

egg_t *add_egg(zappy_t *zappy, team_t *team)
{
    egg_t *new = malloc(sizeof(egg_t));
    if (!new)
        return NULL;
    new->id = ++zappy->game.eggIdIt;
    new->x = rand() % zappy->game.width;
    new->y = rand() % zappy->game.height;
    new->team = team;
    new->next = NULL;

    egg_t *tmp = team->eggs;
    while (tmp && tmp->next)
        tmp = tmp->next;
    new->prev = tmp;
    if (tmp)
        tmp->next = new;
    else
        team->eggs = new;
    return new;
}

static void remove_egg(egg_t *egg)
{
    if (egg->prev)
        egg->prev->next = egg->next;
    else
        egg->team->eggs = egg->next;
    if (egg->next)
        egg->next->prev = egg->prev;
    free(egg);
}

void kill_egg(zappy_t *zappy, egg_t *egg)
{
    notif_guis(send_edi(zappy, notif_it, egg));
    remove_egg(egg);
}

player_t *hatch_egg(zappy_t *zappy, egg_t *egg, client_t *client)
{
    notif_guis(send_ebo(zappy, notif_it, egg));
    player_t *new = add_player(zappy, egg, client);
    remove_egg(egg);
    return new;
}

int nbr_eggs_in_team(team_t *team)
{
    int res = 0;
    egg_t *eggBuff = team->eggs;
    while (eggBuff) {
        ++res;
        eggBuff = eggBuff->next;
    }
    return res;
}
