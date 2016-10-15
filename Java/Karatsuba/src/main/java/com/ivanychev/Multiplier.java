package com.ivanychev;

import java.math.BigInteger;
import java.util.Arrays;

import static java.lang.Math.max;

/**
 *  Implements multiplication of BigIntegers using Karatsuba's algorithm
 *
 *  @author Sergey Ivanychev
 *
 *  @version 0.1
 */
public class Multiplier {

    /**
     * Returns 2^pw
     * @param pw – exponent
     * @return 2^pw as BigInteger
     */
    private static BigInteger pow2(int pw) {
        return (BigInteger.valueOf(2)).pow(pw);
    }

    /**
     * For given length, this method returns a mask that covers first len/2 bits
     *
     * For example for len = 4 it will return 3 which is 11 in binary system.
     * For len = 7 it will return 7=111b as 7/2 equals 3
     *
     * @param len – length of integer, for whom we are creating a mask
     * @return BigInteger mask
     */
    private static BigInteger getMask(int len) {
        int half = len/2;
        BigInteger mask = pow2(half).add(BigInteger.valueOf(-1));
        return mask;
    }

    /**
     * If binary representation of integer is shorter that lenLowerBound, then we just
     * multiply integers in any way.
     */
    final private static int lenLowerBound = 2;

    /**
     * Method multiplies BigIntegers x and y using Karatsuba's algorithm
     *
     * @see <a href="https://en.wikipedia.org/wiki/Karatsuba_algorithm">en.wikipedia.org/wiki/Karatsuba_algorithm</a>
     *
     * @param x
     * @param y
     * @return x*y
     */
    public static BigInteger multiply(BigInteger x, BigInteger y) {
        int len = max(x.bitLength(), y.bitLength());
        if (len <= lenLowerBound) {
            return x.multiply(y);
        }
        int xSign = x.signum();
        int ySign = y.signum();
        int sign = xSign * ySign;
        x = x.abs();
        y = y.abs();
        BigInteger mask = getMask(len);
        BigInteger b = x.and(mask);
        BigInteger a = x.subtract(b).divide(pow2(len/2));
        BigInteger d = y.and(mask);
        BigInteger c = y.subtract(d).divide(pow2(len/2));
        BigInteger summand1 = pow2(len/2 * 2).multiply(multiply(a, c));
        BigInteger summand2 = pow2(len/2).multiply(multiply(a, d).add(multiply(b, c)));
        BigInteger summand3 = multiply(b, d);
        return summand1.add(summand2).add(summand3).multiply(BigInteger.valueOf(sign));
    }
}
