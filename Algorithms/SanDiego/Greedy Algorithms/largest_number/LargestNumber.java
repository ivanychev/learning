import java.lang.reflect.Array;
import java.util.*;

class NumsComparator implements Comparator<String> {
    @Override
    public int compare(String a, String b) {
//        System.out.println("fdafsd");
//        int len = java.lang.Math.min(a.length(), b.length());
//        for (int i = 0; i < len; ++i) {
//            if (a.charAt(i) != b.charAt(i)) {
//                return a.charAt(i) - b.charAt(i);
//            }
//        }
        String A = a + b;
        String B = b + a;
        return A.compareTo(B);
//        String left = (a.length() == len)? b: a;
//        int lenDiff = left.length() - len;
//        if (lenDiff == 0) {
//            return 0;
//        }
//        int cmp = left.substring(0, len).compareTo(
//                left.substring(left.length() - len, left.length()));
//        System.out.println(cmp);
//        if (cmp == 0) {
//            return 0;
//        }
//        if (cmp > 0) {
//            return (a.length() < b.length())? 1: -1;
//        }
//        return (a.length() < b.length())? -1: 1;
    }
}

class ReverseNumComparator implements Comparator<String> {
    private static NumsComparator cmp = new NumsComparator();
    @Override
    public int compare(String a, String b) {
        return -1 * cmp.compare(a, b);
    }
}
public class LargestNumber {
    private static String largestNumber(String[] a) {
        ArrayList<String> nums = new ArrayList<String>(Arrays.asList(a));
        nums.sort(new ReverseNumComparator());
        String result = "";
        for (int i = 0; i < a.length; i++) {
            result += nums.get(i);
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        String[] a = new String[n];
        for (int i = 0; i < n; i++) {
            a[i] = scanner.next();
        }
        System.out.println(largestNumber(a));
    }
}

