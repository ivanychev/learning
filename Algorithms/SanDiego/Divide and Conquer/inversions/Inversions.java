import java.util.*;

public class Inversions {

    private static long getNumberOfInversions(int[] a, int[] b, int left, int right) {
        long numberOfInversions = 0;
        if (right <= left + 1) {
            b[left] = a[left];
            return numberOfInversions;
        }
        int ave = (left + right) / 2;
        numberOfInversions += getNumberOfInversions(a, b, left, ave);
        numberOfInversions += getNumberOfInversions(a, b, ave, right);
        int i = left;
        int j = ave;
        int k = 0;
        int[] buffer = new int[right - left];
        while (i < ave || j < right) {
//            System.out.printf("%d:%d %d:%d = %d\n", i, b[i], j, b[j], numberOfInversions);

            if (i == ave) {
                buffer[k] = b[j];
                k++;
                j++;
                continue;
            }
            if (j == right) {
                buffer[k] = b[i];
                k++;
                i++;
                continue;
            }
            if (b[i] <= b[j]) {
                buffer[k] = b[i];
                k++;
                i++;
                continue;
            }
            else {
                buffer[k] = b[j];
                k++;
                j++;
                numberOfInversions += ave - i;
            }
        }
        System.arraycopy(buffer, 0, b, left, buffer.length);
//        System.out.println(Arrays.toString(buffer));
        return numberOfInversions;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = scanner.nextInt();
        }
        int[] b = new int[n];
        System.out.println(getNumberOfInversions(a, b, 0, a.length));
    }
}

