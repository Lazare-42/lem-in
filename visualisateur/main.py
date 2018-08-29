#!/usr/bin/python 
import pygame
import time
import subprocess 
import math
from pygame.locals import *
from classes import *
from map_functions import *

X_SIZE = 2560
Y_SIZE = 1440

# this function adds a new node upon user click and updates the adjacence matrix connection
def add_new_node(array, max_x, mouse, screen, pygame):
	create = 1
	for n in array:
		if abs(n.x - mouse[0]) <= 20 and abs(n.y - mouse[1]) <= 20:
			create = 0
	if create == 0:
		return array
	for n in array:
		n.tubes.append(n.tubes[-1])
                n.tubes[-2] = 0
	array.append(NewNode(str(max_x), mouse[0], mouse[1], [0 for i in range(len(array) + 1)]))
	pygame.draw.circle(screen, [245,245,220], (mouse[0], mouse[1]), 20, 0)
	tmp = array[-2]
	array[-2] = array[-1]
	array[-1] = tmp
        return array

def text_objects(text, font):
        textSurface = font.render(text, 1, (207, 207, 196), (255, 95, 87))
        return textSurface, textSurface.get_rect()

def put_text_box (text_array, screen, pygame):
	"""This is the text function, used when display all buttons whose names are found in put text box. It contains its text, it width, height, and x, y position"""
        text_box_number = int(math.sqrt(len(text_array)))
        i = 0;
        x = 0;
        Offset(X_SIZE / (text_box_number + 1), Y_SIZE / (text_box_number + 1))
        y = Offset.y
        Offset.y = 300
        button_array = []
        for n in text_array:
            font = pygame.font.SysFont("comicsansms", 200 / text_box_number, 1, 1)
            TextSurf, TextRect = text_objects(n, font)
            TextRect.center = (Offset.x + x * Offset.x, Offset.y)
            button_array.append(Button(n, font, TextSurf, TextRect))
            screen.blit(TextSurf, TextRect)
	    pygame.display.flip()
            i += 1
            x += 1
            if (x % text_box_number == 0):
                x = 0
                Offset.y += y
        return button_array

def put_main_buttons(screen, pygame):

    restart = pygame.image.load("./restart.png").convert_alpha()
    restart = pygame.transform.scale(restart, (100, 100))
    restart_pos = restart.get_rect()
    restart_pos.center = (X_SIZE - restart_pos.width / 2, restart_pos.height / 2)
    screen.blit(restart, restart_pos)
    pygame.display.flip()


def search_button_click (button_array, x, y, screen, pygame):

    text_array = []
    for n in button_array:
        if abs(x - n.TextRect.center[0]) <= n.TextRect.width / 2  and abs(y - n.TextRect.center[1]) <= n.TextRect.height / 2:
            screen.fill(pygame.Color(0, 0, 0))
	    pygame.display.flip()
            return n.name
    return None

def error_func(screen, pygame):
    error_text = []
    wait_user = 1
    error_text.append("Error :")
    with open("./error_trace.txt", 'r') as lem_in_map:
        for line in lem_in_map:
            error_text.append(line)
    error_text.append("OK")
    button_array = put_text_box(error_text, screen, pygame)
    while wait_user:
        for event in pygame.event.get():
            if event.type == MOUSEBUTTONDOWN:
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
                    main()

def search_if_restart(event):
    if (abs(event.pos[0] - X_SIZE) < 100 and event.pos[1] < 100):
        main()

def show_all_maps(screen, pygame):

    wait_choice = 1
    button_array = []
    maps_locations = glob.glob("../test_maps//*")
    map_array = []
    for n in maps_locations:
        map_array.append(n.split('/')[2])
    button_array = put_text_box(map_array, screen, pygame)
    while wait_choice:
        for event in pygame.event.get():
            if event.type == MOUSEBUTTONDOWN:
                search_if_restart(event)
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
                    for n in maps_locations:
                        if button == n.split('/')[2]:
                            command = "./lem-in_visualizer" + "<" + n
                            o = subprocess.call(command, shell=True)
                            if o > 0:
                                error_func(screen, pygame)
                                return None
                            else:
                                map_array, max_x = load_map("./output.map")
                            return map_array, max_x

def main():
    pygame.init()
    screen = pygame.display.set_mode((X_SIZE, Y_SIZE), RESIZABLE)
    pygame.key.set_repeat(400, 30)
    pygame.display.flip()
    
    loop_display = 1
    loop_init_map = 0
    welcome_screen = 1
    text_array = []
    button_array = []
    map_array = []
    
    while loop_display:
    
    	for event in pygame.event.get():    #Attente des events
    		if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
    			print_map(map_array)
                        loop_display = 0
                if event.type == MOUSEBUTTONDOWN and loop_init_map:
                        search_if_restart(event)
    			max_x += 1
    			map_array = add_new_node(map_array, max_x, event.pos, screen, pygame)
    			down = event.pos
                        loop_init_map = 1
                if event.type == MOUSEBUTTONUP and loop_init_map and loop_init_map != 2:
    			up = event.pos
    			map_array = create_link(map_array, down, up, screen, pygame)
                if event.type == MOUSEBUTTONDOWN and welcome_screen == 0:
                        button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                        if button:
                            button_array = []
                            if button == "Load map":
                                put_main_buttons(screen, pygame)
                                map_array, max_x = show_all_maps(screen, pygame)
                                show_map(map_array, screen, pygame)
                                put_main_buttons(screen, pygame)
                                loop_init_map = 2
                            elif button == "Create map":
                                put_main_buttons(screen, pygame)
                                map_array, max_x = load_map("./new_map")
                                show_map(map_array, screen, pygame)
                                loop_init_map = 2
    
        if welcome_screen:
                text_array.append("Load map")
                text_array.append("Create map")
                button_array = put_text_box(text_array, screen, pygame)
                welcome_screen = 0
    	#Re-collage
    	screen.blit(screen, (0,0))   
    	#refresh
    	pygame.display.flip()

main()
