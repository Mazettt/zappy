/*
** EPITECH PROJECT, 2021
** project
** File description:
** main.c
*/

#include "../include/server.h"

static void args_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit for execution of actions\n");
}

void signal_handler(int signum)
{
    if (signum == SIGSEGV) {
        printf("Segmentation fault\n");
        exit(84);
    }
}

args_t get_args(int ac, char **av)
{
    args_t args = {.port = 4242, .width = 20, .height = 20, .teamNames = NULL,
        .clientsNb = 10, .freq = 100};

    for (int i = 1; i < ac; ++i) {
        if (!strcmp(av[i], "-p") && i + 1 < ac)
            args.port = atoi(av[i + 1]);
        if (!strcmp(av[i], "-x") && i + 1 < ac)
            args.width = atoi(av[i + 1]);
        if (!strcmp(av[i], "-y") && i + 1 < ac)
            args.height = atoi(av[i + 1]);
        if (!strcmp(av[i], "-n")) {
            ++i;
            for (int count = 0; i < ac && av[i][0] != '-'; ++i) {
                args.teamNames = realloc(args.teamNames, sizeof(char *) * (count + 2));
                args.teamNames[count] = av[i];
                args.teamNames[++count] = NULL;
            }
            --i;
        }
        if (!strcmp(av[i], "-c") && i + 1 < ac)
            args.clientsNb = atoi(av[i + 1]);
        if (!strcmp(av[i], "-f") && i + 1 < ac)
            args.freq = atoi(av[i + 1]);
    }
    return args;
}

void print_args(args_t args)
{
    printf("port: %d\n", args.port);
    printf("width: %d\n", args.width);
    printf("height: %d\n", args.height);
    printf("names: ");
    for (int i = 0; args.teamNames && args.teamNames[i]; ++i)
        printf("%s ", args.teamNames[i]);
    printf("\nclientsNb: %d\n", args.clientsNb);
    printf("freq: %d\n", args.freq);
}

int main(int ac, char **av)
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGSEGV, signal_handler);
    if (ac == 2 && (!strcmp(av[1], "-help") || !strcmp(av[1], "-h") ||
    !strcmp(av[1], "--help"))) {
        args_help();
        return 0;
    }
    args_t args = get_args(ac, av);
    print_args(args);
    zappy(args);
    free(args.teamNames);
    return 0;
}
