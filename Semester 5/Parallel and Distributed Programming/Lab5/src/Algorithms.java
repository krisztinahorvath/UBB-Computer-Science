import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.*;

public class Algorithms {
    private static final int NO_THREADS = 8;
    private static final int MAX_DEPTH = 4;

    // regular(sequential) O(n^2)
    public static Polynomial multiplySequentialRegular(Polynomial p1, Polynomial p2){
        int maxDegree = p1.getDegree() + p2.getDegree() + 1;
        List<Integer> coefficients = new ArrayList<>(Collections.nCopies(maxDegree, 0));

        for (int i = 0; i <= p1.getDegree(); i++) {
            for (int j = 0; j <= p2.getDegree(); j++) {
                coefficients.set(i + j, coefficients.get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
            }
        }
        return new Polynomial(coefficients);
    }

    // parallel regular O(n^2)
    public static Polynomial multiplyParallelRegular(Polynomial p1, Polynomial p2) throws InterruptedException {
        int maxDegree = p1.getDegree() + p2.getDegree() + 1;

        List<Integer> coefficients = new ArrayList<>(Collections.nCopies(maxDegree, 0));
        Polynomial result = new Polynomial(coefficients);

        ThreadPoolExecutor threadPoolExecutor = (ThreadPoolExecutor) Executors.newFixedThreadPool(NO_THREADS);

        // no tasks each thread should handle
        int noTasks = (maxDegree / NO_THREADS == 0) ? 1 : maxDegree / NO_THREADS;

        // index of the last degree the task should compute
        int end;
        for (int i = 0; i < maxDegree; i += noTasks) {
            end = i + noTasks;
            Task task = new Task(i, end, p1, p2, result);
            threadPoolExecutor.execute(task);
        }

        threadPoolExecutor.shutdown();
        threadPoolExecutor.awaitTermination(1, TimeUnit.MINUTES);

        return result;
    }

    // sequential Karatsuba
    public static Polynomial multiplySequentialKaratsuba(Polynomial p1, Polynomial p2){
        if(p1.getDegree() < 2 || p2.getDegree() < 2)
            return multiplySequentialRegular(p1, p2);

        int len = Math.max(p1.getDegree(), p2.getDegree()) / 2;

        // high & low order halves of p1
        Polynomial lowP1 = new Polynomial(p1.getCoefficients().subList(0, len));
        Polynomial highP1 = new Polynomial(p1.getCoefficients().subList(len, p1.getCoefficients().size()));

        // high & low order halves of p2
        Polynomial lowP2 = new Polynomial(p2.getCoefficients().subList(0, len));
        Polynomial highP2 = new Polynomial(p2.getCoefficients().subList(len, p2.getCoefficients().size()));

        // product of low halves
        Polynomial productLow = multiplySequentialKaratsuba(lowP1, lowP2);

        // product of the high halves
        Polynomial productHigh = multiplySequentialKaratsuba(highP1, highP2);

        // product of the sums of the two pairs
        Polynomial productOfSums = multiplySequentialKaratsuba(Utils.add(lowP1, highP1), Utils.add(lowP2, highP2));

        // compute final result P(x) = P1(x) * x^(2*half) + Pmid(x) * x^half + P2(x), Pmid(x) = P3(x) - P1(x) - P2(x)
        Polynomial result1 = Utils.addZeros(productHigh, 2 * len);
        Polynomial result2 = Utils.addZeros(Utils.subtract(Utils.subtract(productOfSums, productHigh), productLow), len);
        return Utils.add(Utils.add(result1, result2), productLow);
    }

    // parallel Karatsuba
    public static Polynomial multiplyParallelKaratsuba(Polynomial p1, Polynomial p2, int currentDepth) throws ExecutionException, InterruptedException {
        if (currentDepth > MAX_DEPTH) {
            return multiplySequentialKaratsuba(p1, p2);
        }

        if (p1.getDegree() < 2 || p2.getDegree() < 2) {
            return multiplySequentialKaratsuba(p1, p2);
        }

        int len = Math.max(p1.getDegree(), p2.getDegree()) / 2;

        // high & low order halves of p1
        Polynomial lowP1 = new Polynomial(p1.getCoefficients().subList(0, len));
        Polynomial highP1 = new Polynomial(p1.getCoefficients().subList(len, p1.getCoefficients().size()));

        // high & low order halves of p2
        Polynomial lowP2 = new Polynomial(p2.getCoefficients().subList(0, len));
        Polynomial highP2 = new Polynomial(p2.getCoefficients().subList(len, p2.getCoefficients().size()));

        ExecutorService executor = Executors.newFixedThreadPool(NO_THREADS);

        // product of low halves
        Future<Polynomial> productLow = executor.submit(() -> multiplyParallelKaratsuba(lowP1, lowP2, currentDepth + 1));

        // product of high halves
        Future<Polynomial> productHigh = executor.submit(() -> multiplyParallelKaratsuba(highP1, highP2, currentDepth + 1));

        // product of the sums of the two pairs
        Future<Polynomial> productOfSums = executor.submit(() -> multiplyParallelKaratsuba(Utils.add(lowP1, highP1), Utils.add(lowP2, highP2), currentDepth + 1));

        executor.shutdown();

        Polynomial resultProductLow = productLow.get();
        Polynomial resultProductHigh = productHigh.get();
        Polynomial resultProductOfSums = productOfSums.get();

        executor.awaitTermination(6, TimeUnit.SECONDS);

        // compute final result P(x) = P1(x) * x^(2*half) + Pmid(x) * x^half + P2(x), Pmid(x) = P3(x) - P1(x) - P2(x)
        Polynomial result1 = Utils.addZeros(resultProductHigh, 2 * len);
        Polynomial result2 = Utils.addZeros(Utils.subtract(Utils.subtract(resultProductOfSums, resultProductHigh), resultProductLow), len);
        return Utils.add(Utils.add(result1, result2), resultProductLow);
    }
}
