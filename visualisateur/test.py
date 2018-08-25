#!/usr/bin/python 
import pygame
from pygame.locals import *

pygame.init()

#Ouverture de la screen Pygame
screen = pygame.display.set_mode((2560, 1440), RESIZABLE)

#Chargement et collage du fond
fond = pygame.image.load("background.png").convert()
fond = pygame.transform.scale(fond, (2560, 1440), screen)
#red = [244, 164, 96]
#screen.fill(red)

screen.blit(fond, (0,0))


#Chargement et collage du personnage
#perso = pygame.image.load("perso.png").convert_alpha()
#position_perso = perso.get_rect()
#screen.blit(perso, position_perso)

# on utilise en parametre de la methode append l'objet que l'on don souhaite ajouter a la fin
# de la liste   
# pour concatener on utilise append
# i = 0 ; while i < len (maliste)jj

class Tubes:
    """this is the tube structure contained by each node"""
    def __init__(self):
        self.next = None
        return

class NewNode:
    """This is the node structure. It contain the name, number, orthogonal position
    and a list of tubes to other nodes"""

    def __init__(self, name, x, y, tubes):
        self.name = name
        self.x = x
        self.y = y
        self.tubes = tubes
        self.next = None
        return

class LinkedList:

    def __init__(self):
        self.head = None
        self.tail = None
        return

    def add_list_item(self, item):
        if self.head == None:
            self.head = item
        else:
            self.tail.next = item
        self.tail = item
        return 

#Rafraichissement cd l'ecran
pygame.display.flip()


#BOUCLE INFINIE
continuer = 1

lem_in_map = open("../output.map", 'r')
room_numbers = lem_in_map.readline()
int(room_numbers)

pygame.key.set_repeat(400, 30)
while continuer:
    for event in pygame.event.get():    #Attente des events
        if event.type == QUIT:
            continuer = 0
#        if event.type == KEYDOWN:
#            if event.key == K_DOWN:
#                position_perso = position_perso.move(0,3)
        if event.type == MOUSEBUTTONUP:
            pygame.draw.circle(screen, [0, 0, 255], (10, 10), 0)
    pygame.draw.circle(screen, [0, 0, 255], (10, 10), 0)
    #Re-collage
    screen.blit(fond, (0,0))   
#    screen.blit(perso, position_perso)
    #refresh
    pygame.display.flip()
