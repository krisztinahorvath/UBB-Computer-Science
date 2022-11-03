import copy
from random import randint

import sys, numpy as np

inf = sys.maxsize


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
    g = Graph(int(vertices), int(edges))
    line = f.readline().strip()
    while len(line) > 0:
        line = line.split(" ")

        if len(line) == 1:
            g._in_vertices[int(line[0])] = []
            g._out_vertices[int(line[0])] = []
        else:
            v1 = int(line[0])
            v2 = int(line[1])
            cost = int(line[2])
            g._in_vertices[v2].append(v1)
            g._out_vertices[v1].append(v2)
            g._cost[(v1, v2)] = cost

        line = f.readline().strip()
    f.close()
    return g


def write_file(graph, file):
    f = open(file, "w")

    line = str(graph.nr_vertices) + " " + str(graph.nr_edges) + '\n'
    f.write(line)

    if len(graph.cost) == 0 and len(graph.in_vertices) == 0:
        raise ValueError("There is nothing that can be written!")

    for edge in graph.cost.keys():
        line = "{} {} {}\n".format(edge[0], edge[1], graph.cost[edge])
        f.write(line)

    for vertex in graph.in_vertices.keys():
        if len(graph.in_vertices[vertex]) == 0 and len(graph.out_vertices[vertex]) == 0:
            line = "{}\n".format(vertex)
            f.write(line)
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
    g = Graph(vertices, 0)
    i = 0
    while i < edges:
        x = randint(0, vertices - 1)
        y = randint(0, vertices - 1)
        cost = randint(0, 1000)
        if g.add_edge(x, y, cost):
            i += 1
    return g


class Graph:
    def __init__(self, nr_vertices, nr_edges):
        self._nr_vertices = nr_vertices
        self._nr_edges = nr_edges
        self._in_vertices = dict()
        self._out_vertices = dict()
        self._cost = dict()

        for i in range(nr_vertices):
            self._in_vertices[i] = []
            self._out_vertices[i] = []

    @property
    def in_vertices(self):
        return self._in_vertices

    @property
    def out_vertices(self):
        return self._out_vertices

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

    def vertice_iterator(self):
        vertices = list(self._in_vertices.keys())
        for v in vertices:
            yield v

    def inbound_iterator(self, x):
        for y in self._in_vertices[x]:
            yield y

    def outbound_iterator(self, x):
        for y in self._out_vertices[x]:
            yield y

    def cost_iterator(self):
        keys = list(self._cost.keys())
        for key in keys:
            yield key

    def add_vertex(self, v):
        """
        Adds a vertex to the graph
        :param v: a vertex
        :return: True - if the vertex was added successfully
                 False - if it already exists
        """
        # if the vertex already exists
        if v in self._in_vertices.keys() and v in self._out_vertices.keys():
            return False

        else:
            self._in_vertices[v] = []
            self._out_vertices[v] = []
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
        if v not in self._in_vertices.keys() and v not in self._out_vertices.keys():
            return False

        self._in_vertices.pop(v)
        self._out_vertices.pop(v)

        # remove all the apparitions of the vertex from the dictionaries
        for key in self._in_vertices.keys():
            if v in self._in_vertices[key]:
                self._in_vertices[key].remove(v)
            elif v in self._out_vertices[key]:
                self._out_vertices[key].remove(v)

        # remove the costs of the vertex
        keys = list(self._cost.keys())
        for key in keys:
            if key[0] == v or key[1] == v:
                self._cost.pop(key)
                self._nr_edges -= 1

        self._nr_vertices -= 1
        return True

    def in_degree(self, v):
        if v not in self._in_vertices.keys():
            return -1
        return len(self._in_vertices[v])

    def out_degree(self, v):
        if v not in self._out_vertices.keys():
            return -1
        return len(self._out_vertices[v])

    def add_edge(self, x, y, cost):
        """
        Adds and edge to the graph
        :param x: inbound vertice
        :param y: outbound vertice
        :param cost: cost of edge
        :return: True - if edge was added successfully
                 False - if it already exists
        """
        # if we can find the edge anywhere in the dictionaries then we can't add it again
        if x in self._in_vertices[y] or y in self._out_vertices[x] or (x, y) in self._cost.keys():
            return False

        self._in_vertices[y].append(x)
        self._out_vertices[x].append(y)
        self._cost[(x, y)] = cost
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
        if x not in self._in_vertices.keys() or y not in self._in_vertices.keys() or \
                x not in self._out_vertices.keys() or y not in self._out_vertices.keys():
            return False

        # if there is no edge with the vertices we can't remove it
        if x not in self._in_vertices[y] or y not in self._out_vertices[x] or (x, y) not in self._cost.keys():
            return False

        self._in_vertices[y].remove(x)
        self._out_vertices[x].remove(y)
        self._cost.pop((x, y))
        self._nr_edges -= 1
        return True

    def find_edge(self, x, y):
        if x in self._in_vertices[y]:
            return self._cost[(x, y)]
        elif y in self._out_vertices[x]:
            return self._cost[(x, y)]

        return False

    def change_cost(self, x, y, cost):
        if (x, y) not in self._cost.keys():
            return False
        else:
            self._cost[(x, y)] = cost
            return True

    def min_path_matrix(self, s):
        """
        # Function to find the shortest path between S and D with exactly K edges
        :param s: destination vertex
        :return:
        """
        n = self.nr_edges
        # To store the dp states
        dp = np.zeros((n + 1, 2 * n))

        path = dict()  # dictionary with all the paths

        # Initialising the dp[][] matrix
        for i in range(n + 1):
            dp[i][0] = inf

        dp[s][0] = 0

        for i in range(1, 2 * n):
            # initializing current state
            for j in range(n + 1):
                dp[j][i] = inf

            current_path = []

            # updating current state
            d = -1
            for (x, y) in self.cost:
                if d == -1:
                    d = y
                dp[y][i] = min(dp[y][i], dp[x][i - 1] + self._cost[(x, y)])
                current_path.append(y)

            path[i] = current_path

        return dp, path

    # 4.The program will use a matrix defined as d[x,k]=the
    # cost of the lowest cost walk from s to x
    # and of length equal to k, where s is the starting vertex.
    def lowest_cost_walk(self, s, d):
        dp, path = self.min_path_matrix(s)

        cost = inf

        # If distance of any vertex from itself becomes negative,
        # then there is a negative weight cycle.
        for k in range(2 * self.nr_edges):  # d = the starting vertex(given)
            if dp[d][k] < 0:
                raise Exception("Negative cost cycles accessible from the starting vertex")

        # finding the minimum cost

        this_path = []
        for k in range(2 * self.nr_edges):
            if dp[d][k] < cost:
                cost = dp[d][k]
                if s in self._in_vertices[d] or d in self._out_vertices[s] or (s, d) in self._cost.keys():
                    this_path.append(s)
                    this_path.append(d)
                else:
                    this_path = path[k]

        return cost, this_path
