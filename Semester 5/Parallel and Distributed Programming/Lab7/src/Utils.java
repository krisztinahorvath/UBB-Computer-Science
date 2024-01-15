import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Utils {
    public static Polynomial add(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        List<Integer> coefficients = new ArrayList<>(maxDegree + 1);

        // add the two polynomials
        for (int i = 0; i <= minDegree; i++)
            coefficients.add(p1.getCoefficients().get(i) + p2.getCoefficients().get(i));

        // one polynomial has higher degree than the other
        if (minDegree != maxDegree) {
            if (maxDegree == p1.getDegree()) {
                for (int i = minDegree + 1; i <= maxDegree; i++)
                    coefficients.add(p1.getCoefficients().get(i));
            } else
                for (int i = minDegree + 1; i <= maxDegree; i++)
                    coefficients.add(p2.getCoefficients().get(i));
        }
        return new Polynomial(coefficients);
    }

    public static Polynomial subtract(Polynomial p1, Polynomial p2) {
        int minDegree = Math.min(p1.getDegree(), p2.getDegree());
        int maxDegree = Math.max(p1.getDegree(), p2.getDegree());
        List<Integer> coefficients = new ArrayList<>(maxDegree + 1);

        // subtract the two polynomials
        for (int i = 0; i <= minDegree; i++)
            coefficients.add(p1.getCoefficients().get(i) - p2.getCoefficients().get(i));

        // one polynomial has higher degree than the other
        if (minDegree != maxDegree) {
            if (maxDegree == p1.getDegree()) {
                for (int i = minDegree + 1; i <= maxDegree; i++)
                    coefficients.add(p1.getCoefficients().get(i));
            } else
                for (int i = minDegree + 1; i <= maxDegree; i++)
                    coefficients.add(-p2.getCoefficients().get(i));
        }

        // remove the coefficient with the highest degree if it is 0
        int i = coefficients.size() - 1;
        if (i > 0 && coefficients.get(i) == 0)
            coefficients.remove(i);

        return new Polynomial(coefficients);
    }

    public static Polynomial addZeros(Polynomial p, int offset) {
        // add zero coefficients to the front of a polynomial to shift its terms to higher degrees

        List<Integer> coefficients = IntStream.range(0, offset).mapToObj(i -> 0).collect(Collectors.toList());
        coefficients.addAll(p.getCoefficients());

        return new Polynomial(coefficients);
    }

    public static Polynomial multiplySequence(Polynomial p1, Polynomial p2, int start, int end) {
        Polynomial result = new Polynomial(2 * p1.getDegree() + 1);

        for (int i = start; i < end; i++)
            for (int j = 0; j < p2.getCoefficients().size(); j++)
                result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));

        return result;
    }

    public static Polynomial getResult(Object[] polynomials) {
        // adds the coefficients of a polynomial array

        int size = ((Polynomial) polynomials[0]).getDegree();
        Polynomial result = new Polynomial(size + 1);

        for (Object polynomial: polynomials)
            result = add(result, (Polynomial) polynomial);

        return result;
    }
}
