import mpi.MPI;

public class Main {
    public static void main(String[] args) {
        Graph graph = Graph.generateRandomGraph(1000);
        Colors colors = new Colors(8);
        colors.addColor(0, "blue");
        colors.addColor(1, "green");
        colors.addColor(2, "black");
        colors.addColor(3, "purple");
        colors.addColor(4, "red");
        colors.addColor(5, "magenta");
        colors.addColor(6, "turquoise");
        colors.addColor(7, "white");

        // make sure that all processes have the same graph
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        if (rank == 0){
            System.out.println("Master");

            try{
                long start = System.nanoTime();
                System.out.println(GraphColoring.master(graph, colors, size));
                long stop = System.nanoTime();

                System.out.println("Time elapsed: " + (stop - start) / 1_000_000 + "ms");

                MPI.COMM_WORLD.Abort(0);
                System.exit(0);

            } catch (Exception e) {
                System.out.println(e.getMessage());
                System.exit(0);
            }
        }
        else {
            System.out.println("Worker: "+ rank);
            GraphColoring.worker(graph, colors.getNoOfColors(), rank, size);
        }

        MPI.Finalize();
    }
}