##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_commands
##

import socket
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import ai.zappy_network_utils as znu

class Commands:
    FORWARD = {"Forward\n", 7}
    RIGHT = {"Right\n", 7}
    LEFT = {"Left\n", 7}
    LOOK = {"Look\n", 7}
    INVENTORY = {"Inventory\n", 1}
    BROADCAST = {"Broadcast\n", 7}
    CONNECT_NBR = {"Connect_nbr\n", 0}
    FORK = {"Fork\n", 42}
    EJECT = {"Eject\n", 7}
    TAKE = {"Take\n", 7}
    SET = {"Set\n", 7}
    INCANTATION = {"Incantation\n", 300}

def forward(sock: socket.socket):
    znu.send_to_server(sock, "Forward\n")
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def right(sock: socket.socket):
    znu.send_to_server(sock, "Right\n")
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def left(sock: socket.socket):
    znu.send_to_server(sock, "Left\n")
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def look(sock: socket.socket):
    znu.send_to_server(sock, "Look\n")
    resp = znu.multiple_recv_from_server(sock, 200)
    res_resp = [[]]
    resp = resp[1:]
    resp = resp.split(',')
    for i in range(0, len(resp)):
        if resp[i] == "]":
            break
        if i % 2 == 0:
            res_resp.append([])
        res_resp[-1].append(resp[i])
    for i in range(0, len(res_resp)):
        for j in range(0, len(res_resp[i])):
            res_resp[i][j] = res_resp[i][j].replace("\n", "")
            res_resp[i][j] = res_resp[i][j].replace("]", "")
    full_resp = []
    for i in range(0, len(res_resp)):
        for j in range(0, len(res_resp[i])):
            full_resp.append(res_resp[i][j])
    return full_resp


def inventory(sock: socket.socket):
    znu.send_to_server(sock, "Inventory\n")
    resp = znu.multiple_recv_from_server(sock, 20)
    inventory = {}
    resp = resp.split(',')
    for item in resp:
        item = item.split(' ')
        inventory[item[1]] = int(item[2])
    return inventory

def broadcast_text(sock: socket.socket, text: str):
    znu.send_to_server(sock, "{} {}".format(7, text))
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def unused_connect_nbr(sock: socket.socket):
    znu.send_to_server(sock, "Connect_nbr\n")
    resp = znu.multiple_recv_from_server(sock,0)
    return resp

def fork(sock: socket.socket):
    znu.send_to_server(sock, "Fork\n")
    resp = znu.multiple_recv_from_server(sock, 42)
    return resp

def eject(sock: socket.socket):
    znu.send_to_server(sock, "Eject\n")
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def take(sock: socket.socket, resource: str):
    znu.send_to_server(sock, "{} {}".format("Take\n", resource))
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def set(sock: socket.socket, resource: str):
    znu.send_to_server(sock, "{} {}".format("set\n", resource))
    resp = znu.multiple_recv_from_server(sock, 7)
    return resp

def incantation(sock: socket.socket):
    znu.send_to_server(sock, "Incantation\n")
    resp = znu.multiple_recv_from_server(sock, 300)
    return resp

def view_map(map: list, map_x: int, map_y: int):
    for line in map:
        for cell in line:
            print(cell, end=' ')
        print()