import java.util.*;
import java.lang.Math;
import java.math.BigInteger;

public class LCM {
    private static long gcd(long a, long b) {
      return b == 0 ? a : gcd(b, a % b);
    }

  public static void main(String args[]) {
    Scanner scanner = new Scanner(System.in);
    long a = scanner.nextInt();
    long b = scanner.nextInt();
    BigInteger biga = BigInteger.valueOf(a);
    BigInteger bigb = BigInteger.valueOf(b);
    System.out.println((biga.multiply(bigb)).divide(BigInteger.valueOf(gcd(a, b))));
  }
}
