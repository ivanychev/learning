import java.util.*;

public class FibonacciSumLastDigit {
    private static long getPeriod(long base) {
        long num1 = 0;
        long num2 = 1;
        long temp = 0;
        long period = 0;
        do {
            temp = (num1 + num2) % base;
            num1 = num2;
            num2 = temp;
            period++;
        } while (num1 != 0 || num2 != 1);
        return period;
    }

    private static int getFibonacciLastDigitNaive(long n) {
        if (n <= 1) {
            return (int)n;
        }
        long num1 = 0;
        long num2 = 1;
        long temp = 0;
        for (long i = 1; i < n; i++) {
            temp = (num1 + num2) % 10;
            num1 = num2;
            num2 = temp;
        }
        return (int)num2;
    }

    private static long getFibonacciSumNaive(long n) {
        long period = getPeriod(10);
        int digit = getFibonacciLastDigitNaive((n + 2) % period);
        int ret = (digit - 1) % 10;
        return ret >= 0? ret: ret + 10;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long s = getFibonacciSumNaive(n);
        System.out.println(s);
    }
}

