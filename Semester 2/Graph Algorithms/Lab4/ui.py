import math

from graph import Graph, read_file, write_file, random_graph


class UI:
    def __init__(self):
        self._this_graph = None
        self._graph_list = []
        self._file_name = "null"

    @staticmethod
    def print_menu():
        print("Menu:\n"
              "\t1 - Read from file\n"  
              "\t2 - Write to file\n" 
              "\t3 - Switch graph\n"   
              "\t4 - Add empty graph\n" 
              "\t5 - Create copy of current graph\n" 
              "\t6 - Generate random graph with given number of vertices/edges\n"
              "\t7 - Add vertex\n" 
              "\t8 - Remove vertex\n" 
              "\t9 - Get in degree of vertex\n" 
              "\t10 - Get out degree of vertex\n" 
              "\t11 - Add edge\n" 
              "\t12 - Remove edge\n" 
              "\t13 - Modify cost of edge\n" 
              "\t14 - Check if there is edge between two vertices\n"  
              "\t15 - Get the number of vertices\n"  
              "\t16 - Get the number of edges\n"  
              "\t17 - List all vertices\n" 
              "\t18 - List the outbound edges of a given vertex\n" 
              "\t19 - List the inbound edges of a given vertex\n"  
              "\t20 - List all outbound vertices of the graph\n"  
              "\t21 - List all inbound vertices of the graph\n" 
              "\t22 - List edges and costs\n"
              "\t23 - The graph is a DAG and order topologically\n"
              "\t24 - Find the highest cost path between two given vertices\n"
              "\t0 - Exit\n")

    def start(self):
        self.add_empty_graph()
        print("\n\n\t\tTo work on a graph choose a file from which you would like to read it!\n\n")
        cmd_dict = {"1": self.read_file_ui, "2": self.write_file_ui,
                        "3": self.switch_graph_ui, "4": self.add_empty_graph,
                        "5": self.copy_this_graph_ui, "6": self.random_graph_ui,
                        "7": self.add_vertex_ui, "8": self.delete_vertex_ui,
                        "9": self.in_degree_ui, "10": self.out_degree_ui,
                        "11": self.add_edge_ui, "12": self.remove_edge_ui,
                        "13": self.modify_cost_ui, "14": self.check_edge_ui,
                        "15": self.nr_vertices_ui, "16": self.nr_edges_ui,
                        "17": self.iterate_all_vertices, "18": self.list_outbound,
                        "19": self.list_inbound, "20": self.list_all_outbound,
                        "21": self.list_all_inbound, "22": self.list_all_costs,
                        "23": self.topological_sort_ui, "24": self.highest_cost_path_ui}

        while True:
            try:
                self.print_menu()
                option = input("Option: ")
                if option == "0":
                    return
                elif option in cmd_dict:
                    cmd_dict[option]()
                else:
                    print("Invalid input!\n")
            except ValueError as ve:
                print(str(ve))
            except FileNotFoundError as fnfe:
                print(str(fnfe).strip("[Errno 2] "))

    def read_file_ui(self):
        file_name = input("Name of the file: ")

        if self._this_graph is None:
            self._this_graph = 0

        graph = read_file(file_name)

        self._graph_list.append(graph)
        self._this_graph = len(self._graph_list) - 1
        self._file_name = file_name[:-4]

    def write_file_ui(self):
        this_graph = self._graph_list[self._this_graph]
        if self._file_name != "null":
            output_file = str(self._file_name) + "_modif.txt"
        else:
            output_file = "output" + str(self._this_graph) + ".txt"
        write_file(this_graph, output_file)

    def switch_graph_ui(self):
        print("You are on the graph number: {}".format(self._this_graph))
        print("All the graphs: 0 - {}".format(str(len(self._graph_list) - 1)))

        number = int(input("The graph number you want to switch to: "))

        if not 0 <= number < len(self._graph_list):
            raise ValueError("\tTrying to switch to a non existing graph!")

        self._this_graph = number
        print("\tThe switch was made successfully to graph number {}".format(number))

    def add_empty_graph(self):
        """
        Adds an empty graph with which the user can work with, add, then remove vertices etc.
        """
        if self._this_graph is None:
            self._this_graph = 0

        graph = Graph(0, 0)

        self._graph_list.append(graph)
        self._this_graph = len(self._graph_list) - 1
        self._file_name = "null"

    def copy_this_graph_ui(self):
        copy = self._graph_list[self._this_graph].copy_graph()
        self._graph_list.append(copy)

    def random_graph_ui(self):
        vertices = int(input("Number of vertices: "))
        edges = int(input("Number of edges: "))
        graph = random_graph(vertices, edges)

        if self._this_graph is None:
            self._this_graph = 0

        self._graph_list.append(graph)
        self._this_graph = len(self._graph_list) - 1
        self._file_name = "null"

    def add_vertex_ui(self):
        vertex = int(input("New vertex: "))

        if self._graph_list[self._this_graph].add_vertex(vertex):
            print("\tVertex added successfully!")
        else:
            print("\tCannot add vertex, it already exists!")

    def delete_vertex_ui(self):
        vertex = int(input("Vertex to be deleted: "))

        if self._graph_list[self._this_graph].remove_vertex(vertex):
            print("\tVertex deleted successfully!")
        else:
            print("\tCannot delete vertex, it does not exist!")

    def in_degree_ui(self):
        vertex = int(input("Vertex:"))
        d = self._graph_list[self._this_graph].in_degree(vertex)

        if d != -1:
            print("\tThe in degree of the vertex {} is {}".format(vertex, d))
        else:
            print("\tThe vertex does not exist!")

    def out_degree_ui(self):
        vertex = int(input("Vertex:"))
        d = self._graph_list[self._this_graph].out_degree(vertex)

        if d != -1:
            print("\tThe out degree of the vertex {} is {}".format(vertex, d))
        else:
            print("\tThe vertex does not exist!")

    def add_edge_ui(self):
        print("Add an edge (x, y)")
        x = int(input("x = "))
        y = int(input("y = "))
        cost = int(input("Cost: "))

        if self._graph_list[self._this_graph].add_edge(x, y, cost):
            print("\tEdge added successfully!")
        else:
            print("\tCannot add edge, it already exists!")

    def remove_edge_ui(self):
        print("Remove an edge (x, y)")
        x = int(input("x = "))
        y = int(input("y = "))

        if self._graph_list[self._this_graph].remove_edge(x, y):
            print("\tEdge deleted successfully!")
        else:
            print("\tCannot remove edge, it does not exist!")

    def modify_cost_ui(self):
        print("Modify the cost of edge (x, y)")
        x = int(input("x = "))
        y = int(input("y = "))
        cost = int(input("Cost: "))

        if self._graph_list[self._this_graph].change_cost(x, y, cost):
            print("\tCost modified successfully!")
        else:
            print("\tCannot modify cost, the edge does not exist!")

    def check_edge_ui(self):
        x = int(input("x = "))
        y = int(input("y = "))
        e = self._graph_list[self._this_graph].find_edge(x, y)

        if e is False:
            print("\t({}, {}) is not an edge!".format(x, y))
        else:
            print("\t Edge ({}, {}) with cost {}!".format(x, y, e))

    def nr_vertices_ui(self):
        print("The number of vertices is: {}".format(self._graph_list[self._this_graph].nr_vertices))

    def nr_edges_ui(self):
        print("The number of edges is: {}".format(self._graph_list[self._this_graph].nr_edges))

    def iterate_all_vertices(self):
        for v in self._graph_list[self._this_graph].vertice_iterator():
            print("{}".format(v))

    def list_all_outbound(self):
        for x in self._graph_list[self._this_graph].vertice_iterator():
            line = str(x) + " :"
            for y in self._graph_list[self._this_graph].outbound_iterator(x):
                line = line + " " + str(y)
            print(line)

    def list_outbound(self):
        vertex = int(input("Vertex: "))
        line = str(vertex) + " :"
        for y in self._graph_list[self._this_graph].outbound_iterator(vertex):
            line = line + " " + "({}, {})".format(str(vertex), str(y))
        print(line)

    def list_all_inbound(self):
        for x in self._graph_list[self._this_graph].vertice_iterator():
            line = str(x) + " :"
            for y in self._graph_list[self._this_graph].inbound_iterator(x):
                line = line + " " + str(y)
            print(line)

    def list_inbound(self):
        vertex = int(input("Vertex: "))
        line = str(vertex) + " :"
        for y in self._graph_list[self._this_graph].inbound_iterator(vertex):
            line = line + " " + "({}, {})".format(str(y), str(vertex))
        print(line)

    def list_all_costs(self):
        for nr in self._graph_list[self._this_graph].cost_iterator():
            line = "({}, {})".format(nr[0], nr[1]) + " :" + str(
                self._graph_list[self._this_graph].cost[nr])
            print(line)

    def topological_sort_ui(self):
        sorted_graph = self._graph_list[self._this_graph].topological_sort()
        if len(sorted_graph) == 0:
            print("\tGraph has cycles!")
        else:
            print("\tGraph is a DAG!")
            print(sorted_graph)

    def highest_cost_path_ui(self):
        x = int(input("x = "))
        y = int(input("y = "))
        sorted_graph = self._graph_list[self._this_graph].topological_sort()
        if len(sorted_graph) == 0:
            print("\tGraph has cycles! Can't use the information from topological sort!")
        else:
            cost, prev = self._graph_list[self._this_graph].highest_cost_path(sorted_graph, x, y)
            if cost == -math.inf:
                print("No path from {} to {}".format(x, y))
                return
            path = [y]
            while x != y:
                y = prev[y]
                path.append(y)
            path.reverse()
            print("Highest cost walk is: {}, with cost of {}".format(path, cost))


UI().start()