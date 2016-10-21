import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

class Item implements Comparable<Item> {
    int idx;
    int value;
    int weight;
    Double density;

    @Override
    public int compareTo(Item it) {
        double dif = -(density - it.density);
        return (dif > 0) ? 1 : -1;
    }

}

public class FractionalKnapsack {
    private static double getOptimalValue(int capacity, int[] values, int[] weights) {
        double value = 0;
        Item[] items = new Item[values.length];
        for (int i = 0; i < values.length; i++) {
            Double density = ((double) values[i]) / weights[i];
            items[i] = new Item();
            items[i].value = values[i];
            items[i].weight = weights[i];
            items[i].density = density;
            items[i].idx = i;
        }
        Arrays.sort(items);
        for (Item x: items) {
            if (x.weight > capacity) {
                value += ((double) x.value) * (capacity / (double)x.weight);
                return value;
            }
            value += x.value;
            capacity -= x.weight;
        }

        return value;
    }

    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int capacity = scanner.nextInt();
        int[] values = new int[n];
        int[] weights = new int[n];
        for (int i = 0; i < n; i++) {
            values[i] = scanner.nextInt();
            weights[i] = scanner.nextInt();
        }
        System.out.printf("%.4f\n", getOptimalValue(capacity, values, weights));
    }
} 
