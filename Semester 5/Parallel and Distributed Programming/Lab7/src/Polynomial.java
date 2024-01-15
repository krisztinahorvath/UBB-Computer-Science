import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.StringJoiner;

public class Polynomial implements Serializable {
    private List<Integer> coefficients;

    public Polynomial(List<Integer> _coefficients) {
        coefficients = _coefficients;
    }

    public Polynomial(int size){
        coefficients = new ArrayList<>();
        for(int i = 0; i < size; i++)
            coefficients.add(0);
    }

    public void generateCoefficients() {
        Random random = new Random();

        for (int i = 0; i <= getDegree(); i++) {
            int coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);

            // ensure non-zero coefficient for the highest degree term
            while (coefficient == 0 && i == getDegree()) {
                coefficient = random.nextInt(10) * (random.nextBoolean() ? 1 : -1);
            }

            coefficients.set(i, coefficient);
        }
    }

    public List<Integer> getCoefficients() {
        return coefficients;
    }

    public int getDegree() {
        return coefficients.size() - 1;
    }

    public int getSize(){
        return coefficients.size();
    }

    @Override
    public String toString() {
        var terms = new StringJoiner(" ");

        for (int i = getDegree(); i >= 0; i--) {
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