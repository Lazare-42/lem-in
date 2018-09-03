#!/usr/bin/python 
import pygame
import time
import subprocess 
import math
from pygame.locals import *
from classes import *
from map_functions import *

X_SIZE = 1920
Y_SIZE = 1200

def delete_node(array, node, screen, pygame):
    node_nbr = array.index(node)
    array.remove(node);
    for n in array[node_nbr:]:
        tmp = int(n.name)
        tmp -= 1
        n.name = str(tmp)
    for n in array:
        del n.tubes[node_nbr]
    screen.fill(pygame.Color(0, 0, 0))
    show_map(array, screen, pygame)
    put_main_buttons(screen, pygame, 1)
    return (array)

# this function adds a new node upon user click and updates the adjacence matrix connection
def add_del_node(array, node_nbr, mouse, delete_mode, screen, pygame):
	for n in array:
		if abs(n.x - mouse[0]) <= 20 and abs(n.y - mouse[1]) <= 20:
                    if delete_mode:
	        	return delete_node(array, n, screen, pygame), node_nbr
                    else:
                        return array, node_nbr
	for n in array:
		n.tubes.append(n.tubes[-1])
                n.tubes[-2] = 0
	array.append(NewNode(array[-1].name, mouse[0], mouse[1], [0 for i in range(len(array) + 1)]))
	pygame.draw.circle(screen, [44,117,117], (mouse[0], mouse[1]), 20, 0)
	tmp = array[-2]
	array[-2] = array[-1]
	array[-1] = tmp
        array[-1].name = str(node_nbr)
        node_nbr += 1
        return array, node_nbr

#this function displays error in maps which are loaded
def error_func(screen, pygame):
    error_text = []
    wait_user = 1
    error_text.append("Error :")
    with open("./error_trace.txt", 'r') as lem_in_map:
        for line in lem_in_map:
            error_text.append(line)
    put_main_buttons(screen, pygame, 0)
    button_array = put_text_box(error_text, screen, pygame)
    while wait_user:
        for event in pygame.event.get():
            if event.type == MOUSEBUTTONDOWN:
                search_if_restart_launch(event, 0)
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
                    main()

# this function searches for clicks on the restart or the play button
def search_if_restart_launch(event, set_ants_and_launch):
    if (abs(event.pos[0] - X_SIZE) < 70 and event.pos[1] < 70):
        main()
    if (set_ants_and_launch):
        if (event.pos[0] < 70 and abs(event.pos[1] - Y_SIZE) < 70):
            return 1
    return 0

# this function loads all the maps 
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
                search_if_restart_launch(event, 0)
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
                                map_array, max_x, node_nbr = load_map("./output.map")
                            return map_array, max_x, node_nbr

#this function creates a text object for each button
def text_objects(text, font):
        textSurface = font.render(text, 1, (207, 207, 196), (255, 95, 87))
        return textSurface, textSurface.get_rect()

#this function creates buttons
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

#this function displays the re-load and play buttons
def put_main_buttons(screen, pygame, play_button):

    if play_button:
        play = pygame.image.load("./start.png").convert_alpha()
        play = pygame.transform.scale(play, (70, 70))
        play_pos = play.get_rect()
        play_pos.center = (play_pos.width / 2, Y_SIZE - play_pos.height / 2)
        screen.blit(play, play_pos)
        pygame.display.flip()
    restart = pygame.image.load("./restart.png").convert_alpha()
    restart = pygame.transform.scale(restart, (70, 70))
    restart_pos = restart.get_rect()
    restart_pos.center = (X_SIZE - restart_pos.width / 2, restart_pos.height / 2)
    screen.blit(restart, restart_pos)
    pygame.display.flip()


#this function searches for clicks in buttons contained in button_array. If there is a click, it returns the button name
def search_button_click (button_array, x, y, screen, pygame):

    text_array = []
    for n in button_array:
        if abs(x - n.TextRect.center[0]) <= n.TextRect.width / 2  and abs(y - n.TextRect.center[1]) <= n.TextRect.height / 2:
            screen.fill(pygame.Color(0, 0, 0))
	    pygame.display.flip()
            return n.name
    return None


#this function waits for the user input to define ants and then launches lem-in
def set_ants_and_launch(map_array, screen, pygame):
    
    wait_for_ants = 1
    text_array = []
    button_array = []
    text_array.append("Ant number: ")
    text_array.append("Go !")
    put_text_box(text_array, screen, pygame)
    screen.fill((0, 0, 0))
    screen.blit(screen, (0,0))   
    pygame.display.flip()
    button_array = put_text_box(text_array, screen, pygame)

    while wait_for_ants:
    	for event in pygame.event.get():   
    	    if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                wait_for_ants = 0
            if (event.type == KEYDOWN):
                if event.key == K_0 or event.key == K_KP0:
                    text_array[0] += "0"
                elif event.key == K_1 or event.key == K_KP1:
                    text_array[0] += "1"
                elif event.key == K_2 or event.key == K_KP2:
                    text_array[0] += "2"
                elif event.key == K_3 or event.key == K_KP3:
                    text_array[0] += "3"
                elif event.key == K_4 or event.key == K_KP4:
                    text_array[0] += "4"
                elif event.key == K_5 or event.key == K_KP5:
                    text_array[0] += "5"
                elif event.key == K_6 or event.key == K_KP6:
                    text_array[0] += "6"
                elif event.key == K_7 or event.key == K_KP7:
                    text_array[0] += "7"
                elif event.key == K_8 or event.key == K_KP8:
                    text_array[0] += "8"
                elif event.key == K_9 or event.key == K_KP9:
                    text_array[0] += "9"
                elif event.key == K_BACKSPACE and len(text_array[0]) > len("Ant number: "):
                    text_array[0] = text_array[0][:-1]
                if event.key == K_0 or event.key == K_1 or event.key == K_2 or event.key == K_3 or event.key == K_4 or event.key == K_5 or event.key == K_6 or event.key == K_7 or event.key == K_8 or event.key == K_9 or event.key == K_KP0 or event.key == K_KP1 or event.key == K_KP2 or event.key == K_KP3 or event.key == K_KP4 or event.key == K_KP5 or event.key == K_KP6 or event.key == K_KP7 or event.key == K_KP8 or event.key == K_KP9:
                        put_text_box(text_array, screen, pygame)
                elif event.key == K_BACKSPACE:
                    screen.fill((0, 0, 0))
                    screen.blit(screen, (0,0))   
                    pygame.display.flip()
                    put_text_box(text_array, screen, pygame)
            if event.type == MOUSEBUTTONDOWN and ((text_array[0][len("Ant number: "):])):
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
                    if button == "Go !":
                            ant_number = int(text_array[0][len("Ant number: "):])
                            launch_lem_in(map_array, ant_number, screen, pygame)
            if event.type == KEYDOWN and ((text_array[0][len("Ant number: "):])) and event.key == K_RETURN:
                        screen.fill(pygame.Color(0, 0, 0))
                        ant_number = int(text_array[0][len("Ant number: "):])
                        launch_lem_in(map_array, ant_number, screen, pygame)

import time
def show_lem_in_output(map_array, ant_array, output, screen, pygame):

    total_moves = output.split((' '))
    for n in total_moves[0:-1]:
        ant_nbr = int(n.split('-')[0][1:])
        ant_nbr -= 1
        room_nbr = int(n.split('-')[1])
        if (ant_array[ant_nbr].x != map_array[0].x and ant_array[ant_nbr].y != map_array[0].y):
            pygame.draw.circle(screen, [192,192,192], (ant_array[ant_nbr].x, ant_array[ant_nbr].y), 20, 0)
	pygame.draw.line(screen, [192,192,192], (ant_array[ant_nbr].x, ant_array[ant_nbr].y), (map_array[room_nbr].x, map_array[room_nbr].y), 5)
        ant_array[ant_nbr].x = map_array[room_nbr].x
        ant_array[ant_nbr].y = map_array[room_nbr].y
        if (ant_array[ant_nbr].x != map_array[-1].x and ant_array[ant_nbr].y != map_array[-1].y):
            pygame.draw.circle(screen, [147,112,219], (ant_array[ant_nbr].x, ant_array[ant_nbr].y), 20, 0)
        draw_first_last_nodes(map_array[0], map_array, screen, pygame)
        draw_first_last_nodes(map_array[-1], map_array, screen, pygame)
    	screen.blit(screen, (0,0))   
    	pygame.display.flip()


def launch_lem_in(map_array, ant_number, screen, pygame):

        loop_display = 1
	print_map(map_array, ant_number)
	show_map(map_array, screen, pygame)
	put_main_buttons(screen, pygame, 0)
        show_output = 0
	command = "../lem-in" + "<" + "../new_lem-in"
        ant_array = [Ant(map_array[0].x, map_array[0].y) for i in range (0, ant_number)]
        all_movements = []
        output = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
        while(True):
            retcode = output.poll() #returns None while subprocess is running
            line = output.stdout.readline()
            if line == "":
                break
            if line.find("Error", 0) != -1 or line.find("ERROR", 0) != -1:
                put_text_box([line], screen, pygame)
            if show_output == 0:
                if 'L' in line:
                    show_output = 1
            if show_output == 1:
                all_movements.append(line)
        i = 0
        total_moves_nbr = len(all_movements)
        while loop_display:
            for event in pygame.event.get():   
    	        if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                    loop_display = 0
                if event.type == MOUSEBUTTONDOWN:
                    search_if_restart_launch(event, 0)
                if (event.type == KEYDOWN and i < total_moves_nbr):
                    show_lem_in_output(map_array, ant_array, all_movements[i], screen, pygame)
                    i += 1

def main():
    pygame.init()
    screen = pygame.display.set_mode((X_SIZE, Y_SIZE), RESIZABLE)
    pygame.key.set_repeat(400, 30)
    pygame.display.flip()
    
    new_node_nbr = 1
    loop_display = 1
    loop_init_map = 0
    welcome_screen = 1
    delete_mode = 0
    text_array = []
    button_array = []
    map_array = []
    
    while loop_display: #Boucle principale : attente des events
    
    	for event in pygame.event.get():   
    		if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                        loop_display = 0
                if event.type == KEYDOWN and event.key == K_d:
                    delete_mode = 1
                if event.type == KEYDOWN and event.key == K_RETURN and loop_init_map:
                        set_ants_and_launch(map_array, screen, pygame)
                if event.type == KEYDOWN and event.key == K_RETURN and loop_init_map == 0:
                        screen.fill(pygame.Color(0, 0, 0))
                        put_main_buttons(screen, pygame, 1)
                        map_array, max_x, new_node_nbr = load_map("./new_map")
                        new_node_nbr += 1
                        show_map(map_array, screen, pygame)
                elif event.type == MOUSEBUTTONDOWN and loop_init_map:
                        if search_if_restart_launch(event, 1):
                            set_ants_and_launch(map_array, screen, pygame)
                        else:
    			    map_array, new_node_nbr = add_del_node(map_array, new_node_nbr, event.pos, delete_mode, screen, pygame)
                            delete_mode = 0
    			down = event.pos
                        loop_init_map = 1
                elif event.type == MOUSEBUTTONUP and loop_init_map and loop_init_map != 2:
    			up = event.pos
    			map_array = create_link(map_array, down, up, screen, pygame)
                if event.type == MOUSEBUTTONDOWN and welcome_screen == 0:
                        button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                        if button:
                            button_array = []
                            if button == "Load map":
                                put_main_buttons(screen, pygame, 0)
                                map_array, max_x, new_node_nbr = show_all_maps(screen, pygame)
                                show_map(map_array, screen, pygame)
                                put_main_buttons(screen, pygame, 1)
                                loop_init_map = 2
                            elif button == "Create map":
                                put_main_buttons(screen, pygame, 1)
                                map_array, max_x, new_node_nbr = load_map("./new_map")
                                new_node_nbr += 1
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
