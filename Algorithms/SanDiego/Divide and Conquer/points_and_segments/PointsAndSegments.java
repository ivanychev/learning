import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

class Action implements Comparable<Action>{
    int x;
    char type;
    int idx;

    Action(int coord, char type, int idx) {
        this.x = coord;
        this.type = type;
        this.idx = idx;
    }

    @Override
    public int compareTo(Action other) {

        int dif = x - other.x;
        if (dif != 0) {
            return dif;
        }
        if (type == other.type) {
            return 0;
        }
        if (type == 'e') {
            return 1;
        }
        if (other.type == 'e') {
            return -1;
        }
        if (type == 'p') {
            return 1;
        }
        return -1;
    }
}

public class PointsAndSegments {

    private static ArrayList<Action> getActions(int[] starts, int[] ends, int[] points) {
        int len = starts.length + ends.length + points.length;
        ArrayList<Action> ret = new ArrayList<>();
        for (int x: starts) {
            ret.add(new Action(x, 's', 0));
        }
        for (int x: ends) {
            ret.add(new Action(x, 'e', 0));
        }
        for (int i = 0; i < points.length; i++) {
            ret.add(new Action(points[i], 'p', i));
        }
        return ret;
    }

    private static int[] fastCountSegments(int[] starts, int[] ends, int[] points) {
        ArrayList<Action> actions = getActions(starts, ends, points);
        Collections.sort(actions);
        int[] hits = new int[points.length];
        int depth = 0;
        for (Action action: actions) {
            switch (action.type) {
                case 's':
                    depth++;
                    break;
                case 'e':
                    depth--;
                    break;
                case 'p':
                    hits[action.idx] = depth;
                    break;
                default:
                    break;
            }
        }
        return hits;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n, m;
        n = scanner.nextInt();
        m = scanner.nextInt();
        int[] starts = new int[n];
        int[] ends = new int[n];
        int[] points = new int[m];
        for (int i = 0; i < n; i++) {
            starts[i] = scanner.nextInt();
            ends[i] = scanner.nextInt();
        }
        for (int i = 0; i < m; i++) {
            points[i] = scanner.nextInt();
        }
        //use fastCountSegments
        int[] cnt = fastCountSegments(starts, ends, points);
        for (int x : cnt) {
            System.out.print(x + " ");
        }
    }
}

