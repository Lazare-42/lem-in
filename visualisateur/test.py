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


#Rafraichissement cd l'ecran
pygame.display.flip()


#BOUCLE INFINIE
continuer = 1

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
