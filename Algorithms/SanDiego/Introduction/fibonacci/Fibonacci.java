import java.util.Scanner;

public class Fibonacci {
    private static long calc_fib(int n) {
        if (n <= 1) {
            return n;
        }
        long num1 = 0;
        long num2 = 1;
        long temp = 0;
        for (int i = 1; i < n; i++) {
            temp = num1 + num2;
            num1 = num2;
            num2 = temp;
        }
        return num2;
    }

  public static void main(String args[]) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();

    System.out.println(calc_fib(n));
  }
}
