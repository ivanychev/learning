import java.util.*;

public class FibonacciHuge {
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


    private static long getFibonacciHugeNaive(long n, long m) {
        if (n <= 1)
            return n;
        long period = getPeriod(m);
        n = n % period;

        long previous = 0;
        long current  = 1;

        for (long i = 0; i < n; ++i) {
            long tmp_previous = previous;
            previous = current;
            current = (tmp_previous + current) % m;
        }

        return previous;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        long m = scanner.nextLong();
        System.out.println(getFibonacciHugeNaive(n, m));
    }
}



