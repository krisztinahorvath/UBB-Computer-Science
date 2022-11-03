import copy
from random import randint


def read_file(file_name):
    """
    Reads from a file a graph
    :param file_name: file name
    :return: the read graph
    """
    f = open(file_name, "r")
    line = f.readline()
    line = line.strip()

    vertices, edges = line.split(' ')

    g = UndirectedGraph(int(vertices), 0)

    line = f.readline().strip()
    while len(line) > 0:
        line = line.split(" ")

        if len(line) != 1 and int(line[0]) != int(line[1]):
            if int(line[0]) not in g.edges[int(line[1])]:
                g._nr_edges += 1
                g.edges[int(line[1])].append(int(line[0]))

        if int(line[1]) not in g.edges[int(line[0])]:
            g.edges[int(line[0])].append(int(line[1]))

        line = f.readline().strip()
    f.close()
    return g


def write_file(graph, file):
    f = open(file, "w")

    line = str(graph.nr_vertices) + " " + str(graph.nr_edges) + '\n'
    f.write(line)

    if len(graph.vertices) == 0 and len(graph.edges) == 0:
        raise ValueError("There is nothing that can be written!")

    var_edges = []
    for x in graph.vertices:
        if len(graph.edges[x]) != 0:
            for y in graph.edges[x]:
                one_edge = (x, y)
                if (x, y) not in var_edges and (y, x) not in var_edges:
                    var_edges.append(one_edge)
        else:
            new_line = "{}\n".format(x)
            f.write(new_line)
        for one_edge in var_edges:  # write the edges to the file
            new_line = "{} {}\n".format(one_edge[0], one_edge[1])
            f.write(new_line)
    f.close()


def random_graph(vertices, edges):
    """
    Generates randomly a graph with a given numbers of vertices and edges
    :param vertices: the number of vertices
    :param edges: the number of edges
    :return: generated graph
    """
    if edges > vertices * vertices:
        raise ValueError("Too many edges!")
    g = UndirectedGraph(vertices, 0)
    i = 0
    while i < edges:
        x = randint(0, vertices - 1)
        y = randint(0, vertices - 1)
        cost = randint(0, 1000)
        if g.add_edge(x, y, cost):
            i += 1
    return g


class UndirectedGraph:
    def __init__(self, nr_vertices, nr_edges):
        self._nr_vertices = nr_vertices
        self._nr_edges = nr_edges
        self._edges = dict()
        self._vertices = []
        self._visited = []
        self._cost = dict()

        for i in range(nr_vertices):
            self._edges[i] = []
            self._vertices.append(i)

    @property
    def vertices(self):
        return self._vertices

    @property
    def edges(self):
        return self._edges

    @property
    def visited(self):
        return self._visited

    @property
    def cost(self):
        return self._cost

    @property
    def nr_vertices(self):
        return self._nr_vertices

    @property
    def nr_edges(self):
        return self._nr_edges

    def copy_graph(self):
        return copy.deepcopy(self)

    def vertices_iterator(self):
        for v in self._vertices:
            yield v

    def bound_iterator(self, x):  # iterator for the bound vertices
        for y in self._edges[x]:
            yield y

    def add_vertex(self, v):
        """
        Adds a vertex to the graph
        :param v: a vertex
        :return: True - if the vertex was added successfully
                 False - if it already exists
        """
        # if the vertex already exists
        if v in self._vertices:
            return False

        else:
            self._edges[v] = []
            self._vertices.append(v)
            self._nr_vertices += 1
            return True

    def remove_vertex(self, v):
        """
        Removes a vertex from the graph
        :param v: a vertex
        :return: True - if was removed successfully
                 False - if it doesn't exist
        """
        # if the vertex doesn't exist
        if v not in self._vertices or v not in self._edges.keys():
            return False

        self._vertices.remove(v)
        self._edges.pop(v)
        self._nr_vertices -= 1

        # remove all the apparitions of the vertex from the dictionaries
        for key in self._edges.keys():
            if v in self._edges[key]:
                self._edges[key].remove(v)
                self._nr_edges -= 1
        return True

    def degree(self, v):
        if v not in self._edges.keys():
            return -1
        return len(self._edges[v])

    def add_edge(self, x, y, cost):
        """
        Adds and edge to the graph
        :param x: inbound vertice
        :param y: outbound vertice
        :param cost: cost of edge
        :return: True - if edge was added successfully
                 False - if it already exists
        """
        if x not in self._vertices or y not in self._vertices:
            return False

        if x == y:
            return False

        if x in self._edges[y] and y in self._edges[x]:
            return False

        self._edges[y].append(x)
        self._edges[x].append(y)
        self._nr_edges += 1
        return True

    def remove_edge(self, x, y):
        """
        Removes and edge from the graph
        :param x: inbound vertice
        :param y: outbound vertice
        :return: True - if edge was removed successfully
                 False - if it doesn't exist
        """
        # if the edge doesn't exist we can't delete it
        if x not in self._vertices or y not in self._vertices:
            return False

        # if there is no edge with the vertices we can't remove it
        if x not in self._edges[y] or y not in self._edges[x]:
            return False

        self._edges[y].remove(x)
        self._edges[x].remove(y)
        self._cost.pop((x, y))
        self._nr_edges -= 1
        return True

    def find_edge(self, x, y):
        if x not in self._vertices or y not in self._vertices:
            return False
        if x in self._edges[y] and y in self._edges[x]:
            return True

        return False

    def change_cost(self, x, y, cost):
        if (x, y) not in self._cost.keys():
            return False
        else:
            self._cost[(x, y)] = cost
            return True

    def depth_first_traversal(self, v, nr):
        """
        Depth first traversal of an undirected graph
        :param v: vertex
        :param nr: the number of the current component
        :return:
        """
        for node in self._edges[v]:
            if self._visited[node] == 0:  # check to see if the vertex had not been visited
                self._visited[node] = 1  # mark it as visited
                self._dfsRes[nr].append(node)  # add vertex to nr comp
                self.depth_first_traversal(node, nr)  # explore neighbours

    def find_connected_components(self):
        self._dfsRes = dict()

        n = len(self.edges)  # length of vertices

        # clearing the visited list
        while len(self._visited) > 0:
            self._visited.pop()

        # initializing the visited list
        for i in range(n):
            self._visited.append(0)

        nr = 0  # number of connected components

        for i in range(n):
            if self._visited[i] == 0:  # we check if the vertex is visited
                nr += 1  # if not we check its component
                self._dfsRes[nr] = [i]  # add vertex to the first component result
                self._visited[i] = 1  # mark every vertex in this component as visited
                self.depth_first_traversal(i, nr)

        for i in range(1, nr + 1):
            print("Component number " + str(i) + ":", end=' ')
            for j in self._dfsRes[i]:
                print(str(j) + " ", end=' ')
            print("")
