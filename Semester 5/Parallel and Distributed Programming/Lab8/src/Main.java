import mpi.MPI;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        MPI.Init(args);

        int me = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        DSM dsm = new DSM();

        System.out.println("Starting <" + me + "> of <" + size + ">");

        // initially
        // a = 1
        // b = 2
        // c = 3
        if (me == 0) {
            Thread thread = new Thread(new Subscriber(dsm));
            thread.start();

            dsm.subscribeToVariable("a");
            Thread.sleep(1000);
            dsm.subscribeToVariable("b");
            Thread.sleep(1000);
            dsm.subscribeToVariable("c");
            Thread.sleep(1000);

            dsm.compareAndExchange("a", 1, 10);
            Thread.sleep(1000);
            dsm.compareAndExchange("c", 3, 30);
            Thread.sleep(1000);
            dsm.compareAndExchange("b", 200, 20);
            Thread.sleep(1000);

            dsm.close();
            Thread.sleep(1000);

            thread.join();
        } else if (me == 1) {
            Thread thread = new Thread(new Subscriber(dsm));
            thread.start();

            dsm.subscribeToVariable("a");
            Thread.sleep(1000);
            dsm.subscribeToVariable("c");
            Thread.sleep(1000);

            dsm.compareAndExchange("b", 2, 222);
            Thread.sleep(1000);

            thread.join();
        } else if (me == 2) {
            Thread thread = new Thread(new Subscriber(dsm));
            thread.start();

            dsm.subscribeToVariable("b");
            Thread.sleep(1000);
            dsm.compareAndExchange("b", 2, 20);
            Thread.sleep(1000);

            thread.join();
        }

        MPI.Finalize();
    }
}