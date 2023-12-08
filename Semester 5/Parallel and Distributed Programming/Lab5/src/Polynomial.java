import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.StringJoiner;

public class Polynomial {
    private List<Integer> coefficients;
    private int degree;

    public Polynomial(List<Integer> _coefficients) {
        coefficients = _coefficients;
        degree = coefficients.size() - 1;
    }

    public Polynomial(int _degree) {
        degree = _degree;
        generateCoefficients(degree);
    }

    private void generateCoefficients(int degree) {
        coefficients = new ArrayList<>();
        Random random = new Random();

        for (int i = 0; i <= degree; i++) {
            int coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);

            // ensure non-zero coefficient for the highest degree term
            while (coefficient == 0 && i == degree) {
                coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);
            }

            coefficients.add(coefficient);
        }
    }


    public List<Integer> getCoefficients() {
        return coefficients;
    }

    public int getDegree() {
        return degree;
    }

    @Override
    public String toString() {
        var terms = new StringJoiner(" ");

        for (int i = degree; i >= 0; i--) {
            int coefficient = coefficients.get(i);

            if (coefficient != 0) {
                String term = (coefficient > 0 ? "+" : "") +
                        (coefficient != 1 || i == 0 ? coefficient : "") +
                        (i > 0 ? "x" : "") +
                        (i > 1 ? "^" + i : "");
                terms.add(term);
            }
        }

        return terms.toString();
    }

}