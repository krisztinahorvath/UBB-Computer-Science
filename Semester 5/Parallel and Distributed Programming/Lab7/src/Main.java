import mpi.*;

public class Main {
    public static int POLYNOMIAL_SIZE = 5;
    public static String IMPLEMENTATION = "regular"; // 4 instances
    public static void master(Polynomial p1, Polynomial p2, int processes){
        long startTime = System.nanoTime();

        // length of segments for data distribution
        int length = p1.getSize() / (processes - 1);
        int start;
        int end = 0;

        // distribute to workers
        for (int i = 1; i < processes; i++) {
            start = end;
            end = start + length;

            // ensure that no data is left out
            if (i == processes - 1)
                end = p1.getSize();

            // send p1 to the i-th worker
            MPI.COMM_WORLD.Send(new Object[]{p1}, 0, 1, MPI.OBJECT, i, 0);

            // send p2 to the i-th worker
            MPI.COMM_WORLD.Send(new Object[]{p2}, 0, 1, MPI.OBJECT, i, 0);

            // send start & end indices to the i-th worker to know how much to process from the polynomials
            MPI.COMM_WORLD.Send(new int[]{start}, 0, 1, MPI.INT, i, 0);
            MPI.COMM_WORLD.Send(new int[]{end}, 0, 1, MPI.INT, i, 0);
        }

        // receive results from workers
        Object[] results = new Object[processes - 1];
        for (int i = 1; i < processes; i++)
            MPI.COMM_WORLD.Recv(results, i - 1, 1, MPI.OBJECT, i, 0);

        // combine results
        Polynomial result = Utils.getResult(results);

        long endTime = System.nanoTime();

        System.out.println("\nResult for " + IMPLEMENTATION + " implementation: " + result + "\n");
        System.out.println("Duration: " + ((double) endTime - (double) startTime) / 1_000_000_000.0 + " seconds");
    }

    public static void regularWorker(int me) {
        Object[] p1 = new Object[2];
        Object[] p2 = new Object[2];

        int[] start = new int[1];
        int[] end = new int[1];

        MPI.COMM_WORLD.Recv(p1, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(p2, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(start, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(end, 0, 1, MPI.INT, 0, 0);

        Polynomial polynomial1 = (Polynomial) p1[0];
        Polynomial polynomial2 = (Polynomial) p2[0];

        // perform regular multiplication
        Polynomial result = Utils.multiplySequence(polynomial1, polynomial2, start[0], end[0]);

        System.out.println("--- me = "  + me + " --- " + "p1 * p2 = " + result);

        // send the result back to the master
        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void karatsubaWorker(int me) {
        Object[] p1 = new Object[2];
        Object[] p2 = new Object[2];
        int[] start = new int[1];
        int[] end = new int[1];

        MPI.COMM_WORLD.Recv(p1, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(p2, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(start, 0, 1, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(end, 0, 1, MPI.INT, 0, 0);

        Polynomial polynomial1 = (Polynomial) p1[0];
        Polynomial polynomial2 = (Polynomial) p2[0];

        // p1 = 3x^3 + 2x^2 + 5x + 1 => 3x^4 + 2x^3 + 5x^2 + 1x + 0
        // p2 = 4x^2 + 6x + 2        => 4x^4 + 6x^3 + 2x^2 + 0x + 0
        for (int i = 0; i < start[0]; i++)
            polynomial1.getCoefficients().set(i, 0);

        for (int j = end[0]; j < polynomial1.getCoefficients().size(); j++)
            polynomial1.getCoefficients().set(j, 0);

        Polynomial result = Algorithms.multiplySequentialKaratsuba(polynomial1, polynomial2);

        System.out.println("--- me = "  + me + " --- " + "p1 * p2 = " + result);

        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }


    public static void main(String[] args) throws MPIException {
        MPI.Init(args);

        int me = MPI.COMM_WORLD.Rank(); // id
        int size = MPI.COMM_WORLD.Size(); // number of launched instances

        if(me == 0){
            Polynomial p1 = new Polynomial(POLYNOMIAL_SIZE);
            p1.generateCoefficients();

            Polynomial p2 = new Polynomial(POLYNOMIAL_SIZE);
            p2.generateCoefficients();

            System.out.println("p1 = " + p1);
            System.out.println("p2 = " + p2);

            System.out.println("Master process started...\n");
            master(p1, p2, size);
        }
        else{
            if(IMPLEMENTATION.equals("regular"))
                regularWorker(me);
            else if(IMPLEMENTATION.equals("karatsuba"))
                karatsubaWorker(me);
            else System.out.println("Incorrect choice for implementation!");
        }

        MPI.Finalize();
    }

    public static void testCPUImplementations(){
        // todo: make sure there is only one running process!

        Polynomial p1 = new Polynomial(10_000);
        p1.generateCoefficients();
        Polynomial p2 = new Polynomial(10_000);
        p2.generateCoefficients();

        long startTime, endTime;
        double duration;

        System.out.println("Sequential regular algorithm: ");
        startTime = System.nanoTime();
        Algorithms.multiplySequentialRegular(p1, p2);
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        System.out.println("Duration: " + duration + " seconds\n");

        // sequential Karatsuba
        System.out.println("Sequential Karatsuba algorithm: ");
        startTime = System.nanoTime();
         Algorithms.multiplySequentialKaratsuba(p1, p2);
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        System.out.println("Duration: " + duration + " seconds\n");

    }
}