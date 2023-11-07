import time


# recursive function to compute the gcd of 2 numbers using the Euclidean algorithm
def euclidian_gcd(x, y):
    if x == 0:
        return y
    return euclidian_gcd(y % x, x)


# function that computes the gcd of 2 numbers by decomposing them into their prime factors,
# taking the common prime factors with their lowest exponent and multiplying them
def prime_factors_gcd(x, y):
    if x == 0 or x == y:
        return y
    elif y == 0:
        return x

    prime_factor = 2
    gcd = 1
    while x > prime_factor or y > prime_factor:
        while x % prime_factor == 0 and y % prime_factor == 0: # common prime factor of x & y
            gcd *= prime_factor

            x //= prime_factor
            y //= prime_factor

        prime_factor += 1

    return gcd


# Finding gcd(x, y) using Stein’s algorithm(binary gcd algorithm)
# 1. If both x and y are 0, gcd is zero gcd(0, 0) = 0.
# 2. gcd(x, 0) = a and gcd(0, y) = y because everything divides 0.
# 3. If x and y are both even, gcd(x, y) = 2*gcd(x/2, y/2) because 2 is a common divisor.
# Multiplication with 2 can be done with bitwise shift operator.
# 4. If x is even and y is odd, gcd(x, y) = gcd(x/2, y). Similarly, if x is odd and y is even,
# then gcd(x, y) = gcd(x, y/2). It is because 2 is not a common divisor.
# 5. If both x and y are odd, then gcd(x, y) = gcd(|x-y|/2, x). Note that difference of two odd numbers is even
# Repeat steps 3–5 until x = y, or until x = 0. In either case, the GCD is 2^k * y,
# where 2^k is 2 raised to the power of k and k is the number of common factors of 2 found in step 3.
def steins_algorithm_gcd(x, y):
    if x == 0:
        return y

    if y == 0:
        return x

    # finding k, where k is the greatest power of 2 that divides both x and y
    k = 0

    while ((x | y) & 1) == 0: # if x and y are even
        x = x >> 1 # shift 1 bit to the right <=> dividing by 2
        y = y >> 1
        k = k + 1

    # dividing x by 2 until x becomes odd
    while (x & 1) == 0:
        x = x >> 1

    # from here on, x is always odd.
    while y != 0:

        # if y is even, remove all factor of 2 in y
        while (y & 1) == 0:
            y = y >> 1

        # now x and y are both odd, swap if necessary so x <= y, then set y = y - x (which is even)
        if x > y:
            x, y = y, x

        y = (y - x)

    # restore common factors of 2
    return x << k # x * 2^k

if __name__ == '__main__':
   pairs = [
       (60, 48),
       (12, 18),
       (24, 36),
       (9, 27),
       (30, 45),
       (48, 72),
       (7, 11),
       (50, 75),
       (63, 81),
       (33, 99),
       (17, 34),
       (56, 98),
       (255, 400),
       (71, 1005),
       (10007, 11111),
       (123456789, 987654321),
       (1234567890, 9876543210),
       (12345678900, 98765432100),

       # (1_234_567_891_234_567_890, 888_111_123_456_677_688_996),
       # (111_222_333_444_555_666_777_888_999, 111_222_333_444_555_666_777_888_998),
       # (245_567_174_135_442_542_812_517_726, 724_432_532_485_653_253_153_923_498),
       #
       # (234_452_457_758_859_906_695_785_345_231_414_435_687_532_214_638_532_806_856_734,
       #  783_678_532_549_745_481_747_129_035_867_585_376_325_327_432_693_816_354_265_236),
       #
       # (234_452_457_758_859_906_695_785_345_231_414_435_687_532_214_638_532_806_856_734_783_678_532_549_745_481_747_129_035_867_585_376_325_327_432_693_816_354_265_236,
       #  348_601_359_769_021_548_714_785_438_134_678_136_463_464_383_467_348_129_872_373_473_475_347_321_746_374_234_363_123_265_185_215_982_561_752_356_128_536_286_730)
   ]

   for pair in pairs:
       a = pair[0]
       b = pair[1]

       start = time.perf_counter_ns()
       gcd = euclidian_gcd(a, b)
       end = time.perf_counter_ns()
       print("Euclidean GCD: ({}, {}) = {}, and it took {} nanoseconds".format(a, b, gcd, end-start))

       start = time.perf_counter_ns()
       gcd = prime_factors_gcd(a, b)
       end = time.perf_counter_ns()
       print("Prime factors GCD: ({}, {}) = {}, and it took {} nanoseconds".format(a, b, gcd, end-start))

       start = time.perf_counter_ns()
       gcd = steins_algorithm_gcd(a, b)
       end = time.perf_counter_ns()
       print("Stein's GCD: ({}, {}) = {}, and it took {} nanoseconds\n".format(a, b, gcd, end - start))
