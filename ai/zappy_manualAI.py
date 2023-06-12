##
## EPITECH PROJECT, 2023
## B-YEP-400-MLH-4-1-zappy-martin.d-herouville
## File description:
## zappy_manualAI
##

import ai.zappy_commands as zc
import ai.zappy_dataStruct as zds
import ai.zappy_inventory as zi
import ai.zappy_elevation as ze
import ai.zappy_POV as zp
import select

def move(p: zds.Player):
    zc.forward(p.client.sock)
    if (p.remindToTurn == "R"):
        zc.right(p.client.sock)
        p.remindToTurn = "No"
    if (p.remindToTurn == "L"):
        zc.left(p.client.sock)
        p.remindToTurn = "No"

def gameLoop(p: zds.Player):
    while True:
        #select ?
        zp.POVmanager(p)
        zi.pickupFood(p)
        p.inventory = zc.inventory(p.client.sock)
        if (ze.canElevate(p)):
            while (p.stats.elevating == True):
                ze.elevationTry(p)
        zi.pickupItems(p)
        try:
            zp.lookForFood(p)
        except:
            # print("Pfiew ! I was about to crash!\n")
            continue
        move(p)
