import java.util.*;


public class FibonacciPartialSum {
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
    private static int getFibonacciLastDigitNaive(int n) {
        if (n <= 1) {
            return n;
        }
        long num1 = 0;
        long num2 = 1;
        long temp = 0;
        for (int i = 1; i < n; i++) {
            temp = (num1 + num2) % 10;
            num1 = num2;
            num2 = temp;
        }
        return (int)num2;
    }

    private static long getFibonacciPartialSumNaive(long from, long to) {
        if (to <= 1)
            return to;

        long period = getPeriod(10);
        int smaller_from = (int)(from % period);
        int smaller_to = (int)(to % period + period);

        int num1 = getFibonacciLastDigitNaive(smaller_from);
        int num2;
        if (num1 == 0) {
            num2 = 0;
        } else {
            num2 = getFibonacciLastDigitNaive(smaller_from - 1);
        }
        int sum = num1;
        while (smaller_to > smaller_from) {
            int temp = (num1 + num2) % 10;
            num2 = num1;
            num1 = temp;
            sum = (sum + num1) % 10;
            smaller_to--;
        }
        return sum;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long from = scanner.nextLong();
        long to = scanner.nextLong();
        System.out.println(getFibonacciPartialSumNaive(from, to));
    }
}

