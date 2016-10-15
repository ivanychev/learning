package com.ivanychev;

import java.math.BigInteger;
import java.util.Arrays;

import com.ivanychev.Multiplier;

/**
 * Uses com.ivanychev.Multiplier class to calculate multiplication of input integers
 */
public class MultiplyNums {
    /**
     * If there are two arguments, that are castable to integers, then return true, false otherwise.
     * @param args main() arguments
     * @return true if arguments are correct, false otherwise
     */
    static boolean goodArgs(String[] args) {
        if (args.length != 2) {
            return false;
        }
        try {
            new BigInteger(args[0]);
            new BigInteger(args[1]);
        } catch (NumberFormatException e) {
            return false;
        }
        return true;
    }

    /**
     *
     * @param args – two integers
     */
    public static void main(String[] args) {
        if (!goodArgs(args)) {
            System.out.println("There should be two integers as arguments");
            System.out.println(Arrays.toString(args));
            return;
        }
        BigInteger res = Multiplier.multiply(new BigInteger(args[0]), new BigInteger(args[1]));
        System.out.println(res);
    }
}
