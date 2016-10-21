import java.lang.reflect.Array;
import java.util.*;

public class CoveringSegments {

    private static ArrayList<Integer> optimalPoints(Segment[] segments) {
        //write your code here
        ArrayList<Integer> points = new ArrayList<>();
        Arrays.sort(segments);
        int end = segments[0].end;
        for (int i = 0; i < segments.length; i++) {
            if (segments[i].start > end) {
                points.add(end);
                end = segments[i].end;
            }
            end = (segments[i].end < end)? segments[i].end: end;
        }
        points.add(end);
        return points;
    }

    private static class Segment implements Comparable<Segment>{
        int start, end;

        Segment(int start, int end) {
            this.start = start;
            this.end = end;
        }

        @Override
        public int compareTo(Segment other) {
            return start - other.start;
        }
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Segment[] segments = new Segment[n];
        for (int i = 0; i < n; i++) {
            int start, end;
            start = scanner.nextInt();
            end = scanner.nextInt();
            segments[i] = new Segment(start, end);
        }
        ArrayList<Integer> points = optimalPoints(segments);
        System.out.println(points.size());
        for (int point : points) {
            System.out.print(point + " ");
        }
    }
}
 
