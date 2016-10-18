import java.util.*;

public class FibonacciLastDigit {
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
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextInt();
        int c = getFibonacciLastDigitNaive(n);
        System.out.println(c);
    }
}

