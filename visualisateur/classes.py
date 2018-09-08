class NewNode:
	"""This is the node structure. It contain the name, number, orthogonal position
	and a list of tubes to other nodes"""

	def __init__(self, name, x, y, tubes = []):
		self.name = name
		self.x = x
		self.y = y
		self.tubes = tubes
		return
	def __str__(self):
		return  self.name +  " " + str(self.x) + " " + str (self.y)

class Ant_move:

	def __init__(self, depart_x, vec_x, depart_y, vec_y, arrive_x, arrive_y):
		self.depart_x = depart_x
		self.vec_x = vec_x
		self.depart_y = depart_y,
		self.vec_y = vec_y
		self.arrive_x = arrive_x
		self.arrive_y = arrive_y

class Ant:
    """This is the ant class"""

    def __init__(self, current_x, current_y):
        self.x = current_x
        self.y = current_y

class Offset:
    """This is the offset object used to put offset between buttons"""

    def __init__(self, x, y):
        Offset.x = x
        Offset.y = y

class Button:
    """This is the button class containing all the necessaray information to manipulate it"""

    def __init__(self, name, font, TextSurf, TextRect):
        self.name = name
        self.font = font
        self.TextSurf = TextSurf
        self.TextRect = TextRect
