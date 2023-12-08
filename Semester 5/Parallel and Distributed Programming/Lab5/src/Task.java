import java.util.List;

public final class Task implements Runnable{
    private final int start;
    private final int end;
    private final Polynomial p1;
    private final Polynomial p2;
    private final Polynomial result;

    public Task(int _start, int _end, Polynomial _p1, Polynomial _p2, Polynomial _result) {
        start = _start;
        end = _end;
        p1 = _p1;
        p2 = _p2;
        result = _result;
    }

    @Override
    public void run() {
        List<Integer> resultCoefficients = result.getCoefficients();  // get mutable list

        // iterate over the indices of the resulting coefficients
        for (int i = start; i < end; i++) {
            if (i >= resultCoefficients.size()) {
                return;
            }

            for (int j = 0; j <= i; j++) {
                // don't go out of bounds
                if (j < p1.getCoefficients().size() && (i - j) < p2.getCoefficients().size()) {
                    int val = p1.getCoefficients().get(j) * p2.getCoefficients().get(i - j);
                    resultCoefficients.set(i, resultCoefficients.get(i) + val); // coeff + p1[i] * p2[i]
                }
            }
        }
    }
}