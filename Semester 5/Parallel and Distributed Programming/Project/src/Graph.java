import java.util.*;

public class Graph {
    private int noOfNodes;
    private Map<Integer, Set<Integer>> nodes;

    public Graph( int n) {
        noOfNodes = n;

        nodes = new HashMap<>();
        for(int node = 0; node < n; node++)
            nodes.put(node, new HashSet<>());
    }

    public boolean addEdge(int start, int end){
        return nodes.get(start).add(end);
    }

    public boolean isEdge(int start, int end){
        return nodes.get(start).contains(end);
    }

    public int getNoOfNodes() { return noOfNodes; }

    // generate a random graph of a given number of nodes
    public static Graph generateRandomGraph(int size) {
        Graph graph = new Graph(size);
        for (int i = 0; i < size - 1; i++) {
            graph.addEdge(i, i + 1);
        }

        Random random = new Random();
        int n = 0;
        while (n < size) {
            n++;

            int edgeA = random.nextInt(size);
            int edgeB;

            do {
                edgeB = random.nextInt(size);
            } while (edgeA == edgeB);

            if(!graph.isEdge(edgeA,edgeB) || !graph.isEdge(edgeB,edgeA))
                graph.addEdge(edgeA,edgeB);
        }
        return graph;
    }
}