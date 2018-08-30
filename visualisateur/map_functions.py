from classes import *
import glob
import sys
X_SIZE = 2000
Y_SIZE = 1000

# this puts the map on the screen
def show_map(array, screen, pygame):
        array_len = len(array)
        for a in array:
                i = 0
        	if a == array[0]:
        		pygame.draw.circle(screen, [0,245,0], (a.x, a.y), 20, 0)
        	elif a == array[-1]:
        		pygame.draw.circle(screen, [245, 0, 0], (a.x, a.y), 20, 0)
        	else:
        		pygame.draw.circle(screen, [245,245,220], (a.x - a.x % array_len, a.y - a.y % array_len), 20, 0)
        	for n in a.tubes:
        		if n:
        		    pygame.draw.line(screen, [245, 245, 245], (a.x, a.y), (array[i].x, array[i].y), 5)
                        i += 1
    	pygame.display.flip()

# this puts the map to scale
def put_map_to_scale (array, max_x, max_y):

        for n in array:
        	n.x *= X_SIZE / max_x
        	if n.x <= 50:
        		n.x += 50
        	elif n.x >= X_SIZE - 50:
        		n.x -= 50
        	n.y *= Y_SIZE / max_y
        	if n.y >= Y_SIZE - 50:
        		n.y -= 50
        	elif n.y <= 50:
        		n.y += 50
        return array, max_x

# this loads the map generated by lthe lem-in executable
def load_map(a):

        array = []
        max_x = 0
        max_y = 0
	with open(a, 'r') as lem_in_map:
		for line in lem_in_map:
			tab = line.split()
			name = tab[0]
			x = int(tab[1])
			if x > max_x:
				max_x = x
			y = int(tab[2])
			if y > max_y:
				max_y = y
			matrix_array = []
			for n in tab[3:]:
				matrix_array.append(int(n))
			array.append(NewNode(name, x, y, matrix_array))
        if max_x == 0:
        	max_x = 1
        if max_y == 0:
        	max_y = 1
        return put_map_to_scale(array, max_x, max_y)

# this creates a new link between two maps
def create_link(array, down, up, screen, pygame):
	draw_line = 0
	for n in array:
		if abs(n.x - down[0]) <= 20 and abs(n.y - down[1]) <= 20:
			draw_line += 1
			first = n
		if abs(n.x - up[0]) <= 20 and abs(n.y - up[1]) <= 20:
			draw_line += 1
			second = n
	if draw_line == 2:
		pygame.draw.line(screen, [245,245,220], (first.x, first.y), (second.x, second.y), 5)
		first.tubes[array.index(second)] = 1
		second.tubes[array.index(first)] = 1
        return array

def print_matrix(array):
    print ("This is the node Matrix")
    size = len(array)
    for n in array:
        sys.stdout.write(str(n.name + " "))
        for i in range (0, size):
            sys.stdout.write(str(n.tubes[i]))
        sys.stdout.write('\n')

# this function prints the map in a file called new_lem-in
def print_map(array):
	i = 0;
	file = open('../new_lem-in', 'w+')
        # Attention I am setting ant number to 10 but you should be able to change
        file.write(str(10) + "\n")
	for n in array:
		if n == array[0]:
			file.write("##start\n")
		if n == array[-1]:
			file.write("##end\n")
		file.write(n.name +  " " + str(n.x) + " " + str(n.y) + '\n')
	i = 0
	for n in array:
		i += 1
		for j in range (0, i):
			if n.tubes[j]:
				file.write(n.name + "-" + array[j].name + '\n')
