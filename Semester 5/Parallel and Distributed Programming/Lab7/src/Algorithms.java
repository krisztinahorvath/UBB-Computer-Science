public class Algorithms {
    // regular(sequential) O(n^2)
    public static Polynomial multiplySequentialRegular(Polynomial p1, Polynomial p2){
        Polynomial result = new Polynomial(p1.getDegree() + p2.getDegree() + 1);

        for (int i = 0; i <= p1.getDegree(); i++)
            for (int j = 0; j <= p2.getDegree(); j++)
                result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));

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
}
