#!/usr/bin/python 
import pygame
import thread
from threading import Thread
import copy
import time
import subprocess 
import math
from pygame.locals import *
from classes import *
from map_functions import *

X_SIZE = 1800
Y_SIZE = 1100

#this function deletes the node clicked upon
def delete_node(array, node, screen, pygame, node_nbr):
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
    node_nbr = len(array)
    return (array, node_nbr)

# this function adds a new node upon user click and updates the adjacence matrix connection
def add_del_node(array, node_nbr, mouse, delete_mode, screen, pygame):
	for n in array:
		if abs(n.x - mouse[0]) <= 40 and abs(n.y - mouse[1]) <= 40:
                    if delete_mode:
	        	return delete_node(array, n, screen, pygame, node_nbr)
                    else:
                        return array, node_nbr
	for n in array:
		n.tubes.append(n.tubes[-1])
                n.tubes[-2] = 0
	array.append(NewNode(array[-1].name, mouse[0], mouse[1], [0 for i in range(len(array) + 1)]))
	pygame.draw.circle(screen, [44,117,117], (mouse[0], mouse[1]), 20, 0)
	tmp = copy.deepcopy(array[-2])
	tmp.name = int(tmp.name) + 1
	tmp.name = str(tmp.name)
	array.remove(array[-2])
	array.append(tmp)
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
def search_if_restart_launch(event, input_buttons):
    if (abs(event.pos[0] - X_SIZE) < 70 and event.pos[1] < 70):
        main()
    if (input_buttons):
        if (event.pos[0] < 70 and abs(event.pos[1] - Y_SIZE) < 70):
            return 1
    return 0

# this function loads all the maps 
def show_all_maps(screen, pygame):

    wait_choice = 1
    o = 0
    max_x = 10
    node_nbr = 10
    button_array = []
    maps_locations = glob.glob("../test_maps//*")
    map_array = []
    for n in maps_locations:
        map_array.append(n.split('/')[2])
    map_array.append("last map")
    button_array = put_text_box(map_array, screen, pygame)
    while wait_choice:
        for event in pygame.event.get():
            if event.type == MOUSEBUTTONDOWN:
                search_if_restart_launch(event, 0)
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
   					screen.fill(pygame.Color(0, 0, 0))
   					pygame.display.flip()
   					if button == "last map":
   					     command = "./lem-in_visualizer" + "<" + "../new_lem-in" + " ./output.map"
   					     o = subprocess.call(command, shell=True)
   					else:
   						 for n in maps_locations:
   						     if button == n.split('/')[2]:
   								command = "./lem-in_visualizer" + "<" + str(n) + " ./output.map"
   								o = subprocess.call(command, shell=True)
   					if o > 0:
   					   error_func(screen, pygame)
   					   return None
   					else:
   					   map_array, max_x, node_nbr = load_map("./output.map")
   					return map_array, max_x, node_nbr

def load_random_map(screen, pygame):

    text_array = input_buttons(screen, pygame, ["Node Number: ", "Connection %: "]);
    node_number = text_array[0][len("Node Number: "):]
    connection_percentage = text_array[1][len("Connection %: "):]
    command = "./lem-in_visualizer"  + " ./output.map" + " " + node_number + " " + connection_percentage
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
        Offset(X_SIZE / (text_box_number + 1), Y_SIZE / (text_box_number + 2))
        y = Offset.y
        Offset.y = 200
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
		if play_button == 1:
			play = pygame.image.load("./start.png").convert_alpha()
		else:
			play = pygame.image.load("./skip.png").convert_alpha()
		play = pygame.transform.scale(play, (70, 70))
		play_pos = play.get_rect()
		play_pos.center = (play_pos.width / 2, Y_SIZE - play_pos.height / 2)
		screen.blit(play, play_pos)
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
            return n.name
    return None


#this function waits for the user input to define ants and then launches lem-in
def input_buttons(screen, pygame, text_array):
    
    wait_for_ants = 1
    text_array.append("Go !")
    text_array_copy = copy.deepcopy(text_array)
    put_text_box(text_array, screen, pygame)
    screen.fill((0, 0, 0))
    screen.blit(screen, (0,0))   
    pygame.display.flip()
    button_array = put_text_box(text_array, screen, pygame)
    i = 0
    while wait_for_ants:
    	for event in pygame.event.get():   
    	    if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                wait_for_ants = 0
            if event.type == MOUSEBUTTONDOWN:
                    button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                    if button:
                        for n in text_array:
                            if n == button:
                                i = text_array.index(n)
                                if i == len(text_array) - 1:
                                    i = 0
            if (event.type == KEYDOWN):
                if event.key == K_0 or event.key == K_KP0:
                    text_array[i] += "0"
                elif event.key == K_1 or event.key == K_KP1:
                    text_array[i] += "1"
                elif event.key == K_2 or event.key == K_KP2:
                    text_array[i] += "2"
                elif event.key == K_3 or event.key == K_KP3:
                    text_array[i] += "3"
                elif event.key == K_4 or event.key == K_KP4:
                    text_array[i] += "4"
                elif event.key == K_5 or event.key == K_KP5:
                    text_array[i] += "5"
                elif event.key == K_6 or event.key == K_KP6:
                    text_array[i] += "6"
                elif event.key == K_7 or event.key == K_KP7:
                    text_array[i] += "7"
                elif event.key == K_8 or event.key == K_KP8:
                    text_array[i] += "8"
                elif event.key == K_9 or event.key == K_KP9:
                    text_array[i] += "9"
                elif event.key == K_BACKSPACE and len(text_array[i]) > len(text_array_copy[i]):
                    text_array[i] = text_array[i][:-1]
                if event.key == K_0 or event.key == K_1 or event.key == K_2 or event.key == K_3 or event.key == K_4 or event.key == K_5 or event.key == K_6 or event.key == K_7 or event.key == K_8 or event.key == K_9 or event.key == K_KP0 or event.key == K_KP1 or event.key == K_KP2 or event.key == K_KP3 or event.key == K_KP4 or event.key == K_KP5 or event.key == K_KP6 or event.key == K_KP7 or event.key == K_KP8 or event.key == K_KP9:
                        put_text_box(text_array, screen, pygame)
                elif event.key == K_BACKSPACE:
                    screen.fill((0, 0, 0))
                    screen.blit(screen, (0,0))   
                    pygame.display.flip()
                    put_text_box(text_array, screen, pygame)
            can_return = 1
            if event.type == MOUSEBUTTONDOWN or event.type == KEYDOWN:
                for n in text_array[0:-1]:
                    if len(n) <= len(text_array_copy[text_array.index(n)]):
                        can_return = 0
            if event.type == MOUSEBUTTONDOWN and can_return:
                button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
                if button:
                    if button == "Go !":
                        screen.fill(pygame.Color(0, 0, 0))
                        return text_array
            elif event.type == KEYDOWN and event.key == K_RETURN and can_return:
                screen.fill(pygame.Color(0, 0, 0))
                return text_array

NB_STEP = 50


def show_movements_1_turn(screen, pygame, ants, i, map_array, circle_red, circle_red_pos, screen_copy):

	screen.blit(screen_copy, (0, 0))
	for n in ants:
		if i != 1:
			circle_red_pos.center =  ((n.arrive_x - n.depart_x) * i / NB_STEP + n.depart_x, (n.arrive_y - n.depart_y[0]) * i / NB_STEP + n.depart_y[0]) 
			screen.blit(circle_red, circle_red_pos)
	pygame.display.flip()
	pygame.time.delay(3 / (len(ants) + 1))

def show_lem_in_output(map_array, ant_array, output, screen, pygame, circle_red, circle_red_pos):

	ant_moves_line = []
	total_moves = output.split((' '))
	screen_copy = screen.copy()
	for n in total_moves[0:-1]:
		ant_nbr = int(n.split('-')[0][1:])
		ant_nbr -= 1
		room_nbr = int(n.split('-')[1])
		depart_x = ant_array[ant_nbr].x
		depart_y = ant_array[ant_nbr].y
		ant_array[ant_nbr].x = map_array[room_nbr].x
		ant_array[ant_nbr].y = map_array[room_nbr].y
		arrive_x = ant_array[ant_nbr].x
		arrive_y = ant_array[ant_nbr].y 
		vec_x = (arrive_x - depart_x) / NB_STEP
		vec_y = (arrive_y - depart_y) / NB_STEP
		ant_moves_line.append(Ant_move(depart_x, vec_x, depart_y, vec_y, arrive_x, arrive_y))
	for i in range (1, NB_STEP):
		thread = Thread(target = show_movements_1_turn, args = (screen, pygame, ant_moves_line, i, map_array, circle_red, circle_red_pos, screen_copy))
		thread.start()
		thread.join()
	screen.blit(screen_copy, (0, 0))

def manage_ant_movement(map_array, ant_array, all_movements, screen, pygame, ant_number):

	i = 0
	loop_display = 1
	total_moves_nbr = len(all_movements)
	circle_red = pygame.image.load("./red_circle.png").convert_alpha()
	circle_red = pygame.transform.scale(circle_red, (10, 10))
	circle_red_pos = circle_red.get_rect()
	while loop_display and i < total_moves_nbr:
	    for event in pygame.event.get():   
			if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
			    loop_display = 0
			if event.type == KEYDOWN and event.key == K_RETURN:		
				show_score(map_array[-1].weight, len(all_movements), pygame, screen, ant_number)
			if event.type == MOUSEBUTTONDOWN:
				if search_if_restart_launch(event, 1):
					show_score(map_array[-1].weight, len(all_movements), pygame, screen, ant_number)
	    if (i < total_moves_nbr):
			show_lem_in_output(map_array, ant_array, all_movements[i], screen, pygame, circle_red, circle_red_pos)
			i += 1
	if loop_display:
		show_score(map_array[-1].weight, len(all_movements), pygame, screen, ant_number)

def  show_score(fastest_path, lem_in, pygame, screen, ant_number):
	result = float(lem_in) / float(fastest_path + ant_number - 1)
	result = "%.2f" % result
	screen.fill(pygame.Color(0, 0, 0))
	screen.blit(screen, (0,0))   
	pygame.display.flip()
	wait = 1
	button_array = []
	button_array.append("Ants traveled at ")
	button_array.append(str(result) + " times")
	button_array.append("the speed of Dijsktra")
	button_array = put_text_box(button_array, screen, pygame)
	while wait:
		for event in pygame.event.get():   
			if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
				wait = 0
			if event.type == KEYDOWN and event.key == K_RETURN:
					main()
			if event.type == MOUSEBUTTONDOWN:
			        button = search_button_click(button_array, event.pos[0], event.pos[1], screen, pygame)
			        if button:
						main()


def find_shortest_path(map_array, speed, node):
	pos = 0
	if (node == map_array[-1]):
		map_array[-1].weight = speed
	for n in node.tubes:
		if n:
			if map_array[pos].weight > speed:
				map_array[pos].weight = speed
				find_shortest_path(map_array, speed + 1, map_array[pos])
		pos += 1

def launch_lem_in(map_array, ant_number, screen, pygame):

	print_map(map_array, ant_number)
	show_map(map_array, screen, pygame)
	put_main_buttons(screen, pygame, 2)
	pygame.display.flip()
        show_output = 0
	find_shortest_path(map_array, 0, map_array[0])
	command = "../lem-in" + "<" + "../new_lem-in" + " for visualiser"
        ant_array = [Ant(map_array[0].x, map_array[0].y) for i in range (0, ant_number)]
        all_movements = []
        output = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
        while(True):
            retcode = output.poll() #returns None while subprocess is running
            line = output.stdout.readline()
            print line
            if line == "":
                break
            if line.find("Error", 0) != -1 or line.find("ERROR", 0) != -1:
                put_text_box([line], screen, pygame)
            if show_output == 0:
                if 'L' in line:
                    show_output = 1
            if show_output == 1:
                all_movements.append(line)
        manage_ant_movement(map_array, ant_array, all_movements, screen, pygame, ant_number)

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
                        text_array = input_buttons(screen, pygame, ["Ant number: "])
                        ant_number = int(text_array[0][len("Ant number: "):])
                        launch_lem_in(map_array, ant_number, screen, pygame)
                if event.type == KEYDOWN and event.key == K_RETURN and loop_init_map == 0:
                        screen.fill(pygame.Color(0, 0, 0))
                        put_main_buttons(screen, pygame, 1)
                        map_array, max_x, new_node_nbr = load_map("./new_map")
                        new_node_nbr += 1
                        show_map(map_array, screen, pygame)
                elif event.type == MOUSEBUTTONDOWN and loop_init_map:
                        if search_if_restart_launch(event, 1):
                            text_array = input_buttons(screen, pygame, ["Ant number: "])
                            ant_number = int(text_array[0][len("Ant number: "):])
                            launch_lem_in(map_array, ant_number, screen, pygame)
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
                            screen.fill(pygame.Color(0, 0, 0))
	                    pygame.display.flip()
                            button_array = []
                            if button == "Load map":
                                put_main_buttons(screen, pygame, 0)
                                map_array, max_x, new_node_nbr = show_all_maps(screen, pygame)
                                show_map(map_array, screen, pygame)
                                loop_init_map = 2
                                put_main_buttons(screen, pygame, 1)
                            elif button == "Create map":
                                put_main_buttons(screen, pygame, 1)
                                map_array, max_x, new_node_nbr = load_map("./new_map")
                                new_node_nbr += 1
                                show_map(map_array, screen, pygame)
                                loop_init_map = 2
                            elif button == "Create random map":
                                put_main_buttons(screen, pygame, 0)
                                map_array, max_x, new_node_nbr = load_random_map(screen, pygame)
                                map_array, max_x, new_node_nbr = load_map("./output.map")
                                show_map(map_array, screen, pygame)
                                loop_init_map = 2
                                put_main_buttons(screen, pygame, 1)
    
        if welcome_screen:
                text_array.append("Load map")
                text_array.append("Create random map")
                text_array.append("Create map")
                button_array = put_text_box(text_array, screen, pygame)
                welcome_screen = 0
    	#Re-collage
    	screen.blit(screen, (0,0))   
    	#refresh
    	pygame.display.flip()

main()
