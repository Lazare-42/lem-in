#!/usr/bin/python 
import pygame
from pygame.locals import *

pygame.init()

#Ouverture de la fenetre Pygame
fenetre = pygame.display.set_mode((640, 480))

#Chargement et collage du fond
fond = pygame.image.load("background.png").convert()

fenetre.blit(fond, (0,0))


#Chargement et collage du personnage
perso = pygame.image.load("perso.png").convert_alpha()
position_perso = perso.get_rect()
fenetre.blit(perso, position_perso)


#Rafraichissement cd l'ecran
pygame.display.flip()


#BOUCLE INFINIE
continuer = 1

pygame.key.set_repeat(400, 30)
while continuer:
    for event in pygame.event.get():    #Attente des events
        if event.type == QUIT:
            continuer = 0
        if event.type == KEYDOWN:
            if event.key == K_DOWN: #If down arrow
                #On descend le perso
                    position_perso = position_perso.move(0,3)
    #Re-collage
    fenetre.blit(fond, (0,0))   
    fenetre.blit(perso, position_perso)
    #refresh
    pygame.display.flip()
