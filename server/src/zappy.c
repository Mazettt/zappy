/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.c
*/

#include "../include/server.h"

static void reset_fd(zappy_t *zappy)
{
    FD_ZERO(&zappy->readfds);FD_ZERO(&zappy->writefds);
    FD_SET(STDOUT_FILENO, &zappy->writefds);
    if (STDOUT_FILENO > zappy->max_fd) zappy->max_fd = STDOUT_FILENO;
    FD_SET(STDERR_FILENO, &zappy->writefds);
    if (STDERR_FILENO > zappy->max_fd) zappy->max_fd = STDERR_FILENO;
    FD_SET(zappy->main.s, &zappy->readfds);
    FD_SET(zappy->main.s, &zappy->writefds);
    if (zappy->main.s > zappy->max_fd) zappy->max_fd = zappy->main.s;

    for (size_t i = 0; i < MAX_CONNECTIONS; ++i) {
        if (client_socket(i) > 0) {
            FD_SET(client_socket(i), &zappy->readfds);
            FD_SET(client_socket(i), &zappy->writefds);
        }
        if (client_socket(i) > zappy->max_fd)
            zappy->max_fd = client_socket(i);
    }
    FD_SET(zappy->fd_sigint, &zappy->readfds);
    if (zappy->fd_sigint > zappy->max_fd) zappy->max_fd = zappy->fd_sigint;
}

static void first_select(zappy_t *zappy)
{
    int maxSd = 0;
    FD_ZERO(&zappy->writefds);
    FD_SET(STDOUT_FILENO, &zappy->writefds);
    if (STDOUT_FILENO > maxSd)
        maxSd = STDOUT_FILENO;
    FD_SET(STDERR_FILENO, &zappy->writefds);
    if (STDERR_FILENO > maxSd)
        maxSd = STDERR_FILENO;
    select(maxSd + 1, NULL, &zappy->writefds, NULL, NULL);
}

static void free_all(zappy_t *zappy)
{
    for (int i = 0; i < zappy->game.nbrTeams; ++i) {
        free(zappy->game.teams[i].name);
        while (zappy->game.teams[i].players)
            kill_player(zappy, zappy->game.teams[i].players);
    }
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j)
            free(zappy->game.map[i][j]);
        free(zappy->game.map[i]);
    }
    free(zappy->game.map);
    free(zappy->game.teams);
    free(zappy);
}

static game_t init_game(args_t args)
{
    int nbrTeams = word_array_len(args.teamNames);
    game_t game = {
        .width = args.width,
        .height = args.height,
        .freq = args.freq,
        .teams = malloc(sizeof(team_t) * nbrTeams),
        .nbrTeams = nbrTeams
    };

    game.playerIdIt = 0;
    for (int i = 0; i < nbrTeams; ++i) {
        game.teams[i].name = strdup(args.teamNames[i]);
        game.teams[i].nbrClients = args.clientsNb;
        game.teams[i].players = NULL;
    }
    init_resources(args, &game);
    return game;
}

void zappy(args_t args)
{
    zappy_t *zappy = malloc(sizeof(zappy_t));
    struct timeval tv = {0, 0};
    zappy->game = init_game(args);
    first_select(zappy);
    init_main_socket(zappy, args.port);
    while (zappy->main.s) {
        zappy->max_fd = 0;
        reset_fd(zappy);
        select(zappy->max_fd + 1, &zappy->readfds,
            &zappy->writefds, NULL, &tv);
        if (FD_ISSET(zappy->fd_sigint, &zappy->readfds))
            break;
        else {
            accept_new_connections(zappy);
            read_connections(zappy);
        }
    }
    debug_print("\n%s\n", "Quitting...");
    close_all(zappy);
    free_all(zappy);
}
