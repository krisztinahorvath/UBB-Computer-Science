import mpi.MPI;

import java.util.Arrays;
import java.util.Map;

public class GraphColoring {
    public static Map<Integer,String> master(Graph graph, Colors colors, int size) throws Exception {

        // start the recursive calls with the master process
        int[] colorCodes = graphColoringRecursive(0, graph, colors.getNoOfColors(), new int[graph.getNoOfNodes()], 0, size, 0);

        if (colorCodes.length == 0)
            throw new Exception("No solution was found :(");

        return colors.getColorNamesForCodes(colorCodes);
    }

    public static void worker(Graph graph, int noOfColors, int rank, int size) {
        // receive data from parent graph node (process)
        int[] receivedData = new int[3];
        MPI.COMM_WORLD.Recv(receivedData, 0, receivedData.length, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        // extract the received data
        int parentNode = receivedData[0];
        int nodeCurrent = receivedData[1];
        int power = receivedData[2];

        int noOfNodes = graph.getNoOfNodes();

        // receive the current coloring from the parent process
        int[] colorCodes = new int[noOfNodes];
        MPI.COMM_WORLD.Recv(colorCodes, 0, noOfNodes, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        // perform the recursive graph coloring computation
        int[] result = graphColoringRecursive(nodeCurrent, graph, noOfColors, colorCodes, rank, size, power);

        // send the resulting coloring back to the parent process
        MPI.COMM_WORLD.Send(result, 0, noOfNodes, MPI.INT, parentNode, 0);
    }

    private static int[] graphColoringRecursive(int node, Graph graph, int noOfColors, int[] colorCodes, int rank, int size, int power){
        int noOfNodes = graph.getNoOfNodes();

        // no correct solution found
        if(!isColorValid(graph, colorCodes, node)) {
            return new int[0];
        }

        // found solution
        if(graph.getNoOfNodes() == node + 1)
            return colorCodes;

        // compute destinationRankFactor and initial color code for distributing colors among processes
        int destinationRankFactor = (int) Math.pow(noOfColors, power);

        // start with first color
        int colorCode = 0;

        // compute the rank of the destination process
        int destinationProcess = rank + destinationRankFactor * (colorCode + 1);

        // find the first available color code for the current process
        while (colorCode + 1 < noOfColors && destinationProcess < size ) {
            colorCode++ ;
            destinationProcess = rank + destinationRankFactor * (colorCode + 1);
        }

        // send data to destination process
        int nextNode = node + 1;
        int nextPower = power + 1;

        // so that it doesn't get too expensive computationally
        if(nextPower > 10)
            nextPower = 2;

        sendDataToDestinationProcess(colorCode, rank, destinationRankFactor, nextNode, nextPower, colorCodes, noOfNodes);

        // go to first color and try if it can be used here
        int[] nextColorCodes = Arrays.copyOf(colorCodes, colorCodes.length);
        nextColorCodes[nextNode] = 0;

        // recursively call the function for the next node and see if the color can be used there
        int[] result = graphColoringRecursive(nextNode, graph, noOfColors, nextColorCodes, rank, size, nextPower);
        if(result.length > 0) // solution found
            return result;

        // receive data from destination processes
        result = receiveDataFromDestinationProcess(colorCode, rank, destinationRankFactor, noOfNodes);
        if(result.length > 0) // solution found
            return result;

        // try remaining colors for next node (on this process)
        result = tryRemainingColors(colorCode, noOfColors, colorCodes, nextNode, graph, rank, size, nextPower);
        return result;
    }

    private static void sendDataToDestinationProcess(int colorCode, int rank, int destinationRankFactor, int nextNode, int nextPower, int[] colorCodes, int noOfNodes){
        for (int currColorCode = 1; currColorCode < colorCode; currColorCode++) {

            // destination process that computes the color for the next node
            int destinationProcess = rank + destinationRankFactor * currColorCode;

            // send data to destination process
            int[] data = new int[] { rank, nextNode, nextPower};
            MPI.COMM_WORLD.Send(data, 0, data.length, MPI.INT, destinationProcess, 0);

            // copy the current coloring and set the color for the next node
            int[] nextColorCodes = Arrays.copyOf(colorCodes, colorCodes.length);
            nextColorCodes[nextNode] = currColorCode;

            // send the modified coloring to the destination process
            MPI.COMM_WORLD.Send(nextColorCodes, 0, noOfNodes, MPI.INT, destinationProcess, 0);
        }
    }

    public static int[] receiveDataFromDestinationProcess(int colorCode, int rank, int destinationRankFactor, int noOfNodes){
        for (int currColorCode = 1; currColorCode < colorCode; currColorCode++) {

            // compute from which process the data must be received
            int destinationProcess = rank + destinationRankFactor * currColorCode;
            int[] result = new int[noOfNodes];

            // receive the coloring result from the destination process
            MPI.COMM_WORLD.Recv(result, 0, noOfNodes, MPI.INT, destinationProcess, MPI.ANY_TAG);

            // if a valid solution is found, return it
            if(result.length > 0)
                return result;
        }

        return new int[0];
    }

    private static int[] tryRemainingColors(int colorCode, int noOfColors, int[] colorCodes, int nextNode, Graph graph, int rank, int size, int nextPower){
        for (int currColorCode = colorCode; currColorCode < noOfColors; currColorCode++ ) {
            int[] nextColorCodes = Arrays.copyOf(colorCodes, colorCodes.length);
            nextColorCodes[nextNode] = currColorCode;

            // recursively call the function for the next node with the current color code
            int[] result = graphColoringRecursive(nextNode, graph, noOfColors, nextColorCodes, rank, size, nextPower);

            // if a valid solution is found, return it
            if(result.length > 0)
                return result;
        }

        return new int[0];
    }

    private static boolean isColorValid( Graph graph, int[] colorCodes, int node ){
        for(int currNode = 0; currNode < node; currNode++)
            // check if there is an edge between the current node and the other node and if they have the same color
            if((graph.isEdge(node, currNode) || graph.isEdge(currNode, node)) && colorCodes[node] == colorCodes[currNode])
                return false;

        return true;
    }
}