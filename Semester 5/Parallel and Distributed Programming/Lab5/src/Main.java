import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) throws InterruptedException, ExecutionException, IOException {
        List<Integer> x = new ArrayList<>(Arrays.asList(1, 4, 5, 6));

        List<Integer> y = new ArrayList<>(Arrays.asList(6, 5, 3, 3));
        Polynomial p1 = new Polynomial(x);
        Polynomial p2 = new Polynomial(y);

        System.out.println("p1 = " + p1);
        System.out.println("p2 = " + p2);

        long startTime, endTime;
        double duration;

        // sequential regular
        System.out.println("Sequential regular algorithm: ");
        startTime = System.nanoTime();
        System.out.println("\t p1 * p2 = " + Algorithms.multiplySequentialRegular(p1, p2));
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        writeResults(p1, p2, "sequential", "regular", duration);
        System.out.println("Duration: " + duration + " seconds\n");

        // parallel regular
        System.out.println("Parallel regular algorithm: ");
        startTime = System.nanoTime();
        System.out.println("\t p1 * p2 = " + Algorithms.multiplyParallelRegular(p1, p2));
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        writeResults(p1, p2, "parallel", "regular", duration);
        System.out.println("Duration: " + duration + " seconds\n");

        // sequential Karatsuba
        System.out.println("Sequential Karatsuba algorithm: ");
        startTime = System.nanoTime();
        System.out.println("\t p1 * p2 = " + Algorithms.multiplySequentialKaratsuba(p1, p2));
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        writeResults(p1, p2, "sequential", "Karatsuba", duration);
        System.out.println("Duration: " + duration + " seconds\n");

        // parallel Karatsuba
        System.out.println("Parallel Karatsuba algorithm: ");
        startTime = System.nanoTime();
        System.out.println("\t p1 * p2 = " + Algorithms.multiplyParallelKaratsuba(p1, p2, 1));
        endTime = System.nanoTime();
        duration = ((double) endTime - (double) startTime) / 1_000_000_000.0;
        writeResults(p1, p2, "parallel", "Karatsuba", duration);
        System.out.println("Duration: " + duration + " seconds\n");
    }

    public static void writeResults(Polynomial p1, Polynomial p2, String method, String algorithm, double duration) throws IOException {
        BufferedWriter out = new BufferedWriter(
                new FileWriter("src\\tests.txt", true));
        out.write(String.format("%s - degrees: %s & %s, duration: %s seconds", method + " " + algorithm, p1.getDegree(), p2.getDegree(), duration));
        out.newLine();
        out.close();
    }
}