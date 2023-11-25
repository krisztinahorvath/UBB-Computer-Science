import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main {
    public static Matrix matrix1;
    public static Matrix matrix2;
    public static int productNrLines;
    public static int productNrColumns;
    public static int nrTasks;

    Main(Matrix _matrix1, Matrix _matrix2, int _nrTasks){
        matrix1 = _matrix1;
        matrix2 = _matrix2;

        productNrLines = matrix1.getNrLines();
        productNrColumns = matrix2.getNrColumns();

        nrTasks = _nrTasks;
    }

    public static Matrix computeProductByTask() throws InterruptedException {
        int[][] product = new int[productNrLines][productNrColumns];
        List<Thread> threadList = new ArrayList<>();

        for(int i = 0; i < nrTasks; i++)
            threadList.add(new Thread(new KthThread(product, i, nrTasks)));

        for(Thread thread: threadList)
            thread.start();

        for(Thread thread: threadList)
            thread.join();

        return new Matrix(product);
    }

    public static Matrix computeProductByThreadPool() throws InterruptedException {
        int[][] product = new int[productNrLines][productNrColumns];
        ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(nrTasks);
        List<Runnable> tasks = new ArrayList<>();

        for(int i = 0; i < nrTasks; i++)
            tasks.add(new KthThread(product, i, nrTasks));

        for (Runnable task : tasks)
            executor.execute(task);
        executor.shutdown();

        while (!executor.awaitTermination(1, TimeUnit.DAYS)){
            System.out.println("Executor hasn't finished yet!");
        }

        return new Matrix(product);
    }

    public static void printResults(double startTime, double endTime, Matrix computedProduct, Matrix correctProduct){
        System.out.println("Time taken: " + (endTime - startTime) /  1_000_000_000.0 + " seconds");
        if(computedProduct.equals(correctProduct))
            System.out.println("Correct result!");
        else System.out.println("Incorrect result!");
    }

    public static void main(String[] args) throws InterruptedException {
        Matrix matrix1 = new Matrix(2000, 2000);
        Matrix matrix2 = new Matrix(2000, 2000);
        int nrTasks = 8;
        Main tasks = new Main(matrix1, matrix2, nrTasks);

        // the result of the simple computation of the product of the matrices
        System.out.println("Computing product sequentially...");
        Matrix correctProduct = Matrix.computeSequentialProduct(matrix1, matrix2);
        System.out.println("Done computing product sequentially!\n");

        double startTime, endTime;

        // simple threads
        System.out.println("Simple threads:");
        startTime = System.nanoTime();

        Matrix productSimpleThreads = computeProductByTask();

        endTime = System.nanoTime();
        printResults(startTime, endTime, productSimpleThreads, correctProduct);

        // thread pool
        System.out.println("\nThread pool:");
        startTime = System.nanoTime();

        Matrix productThreadPool = computeProductByThreadPool();

        endTime = System.nanoTime();
        printResults(startTime, endTime, productThreadPool, correctProduct);
    }
}
