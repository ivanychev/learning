import java.awt.geom.Arc2D;
import java.util.*;

public class DifferentSummands {
    private static int findNumber(long n) {
        double N = n*2;
        double sqrtN = java.lang.Math.sqrt((double)N);
        int val = (int)sqrtN;
        while (Double.compare(val*val + val, N) > 0) {
            val--;
        }
        return val;
    }
    private static List<Integer> optimalSummands(int n) {
        int num = findNumber(n);
        List<Integer> summands = new ArrayList<Integer>();
        for (int i = 1; i <= num; ++i) {
            summands.add(i);
        }
        summands.set(num-1, (int)(summands.get(num-1) + (n - (long)num * (num + 1) / 2)));
        return summands;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        List<Integer> summands = optimalSummands(n);
        System.out.println(summands.size());
        for (Integer summand : summands) {
            System.out.print(summand + " ");
        }
    }
}

