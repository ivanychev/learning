import java.io.*;
import java.util.*;

import static java.lang.Math.*;

public class Closest {

    static class Point implements Comparable<Point> {
        long x, y;
        int idx;

        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Point o) {
            return o.y == y ? Long.signum(x - o.x) : Long.signum(y - o.y);
        }

        static double distance(Point p1, Point p2) {
            return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
        }
    }

    static class CompareX implements Comparator<Point> {
        @Override
        public int compare(Point a, Point b) {
            return Long.signum(a.x - b.x);
        }
    }

    static class CompareY implements Comparator<Point> {
        @Override
        public int compare(Point a, Point b) {
            return Long.signum(a.y - b.y);
        }
    }

    static ArrayList<Point> getPoints(int[] x, int[] y) {
        ArrayList<Point> points = new ArrayList<>();
        for (int i = 0; i < x.length; i++) {
            points.add(new Point(x[i], y[i]));
        }
        return points;
    }

    static ArrayList<ArrayList<Point>> formYSortedSublists(ArrayList<Point> Rx, ArrayList<Point> Qx, ArrayList<Point> Py) {
        HashSet<Point> Pxset = new HashSet<Point>(Rx);
        HashSet<Point> Pyset = new HashSet<Point>(Qx);

        ArrayList<Point> Ry = new ArrayList<>();
        ArrayList<Point> Qy = new ArrayList<>();

        for (Point point: Py) {
            if (Pxset.contains(point)) {
                Ry.add(point);
            } else {
                Qy.add(point);
            }
        }
        ArrayList<ArrayList<Point>> ret = new ArrayList<>();
        ret.add(Ry);
        ret.add(Qy);
        return ret;
    }

    static Point[] getClosest(Point[] pair1, Point[] pair2) {
        if (pair1 == null) {
            return pair2;
        }
        if (pair2 == null) {
            return pair1;
        }
        double dist1 = Point.distance(pair1[0], pair1[1]);
        double dist2 = Point.distance(pair2[0], pair2[1]);
        return (dist1 < dist2)? pair1: pair2;
    }

    static Point[] closestSplitPair(ArrayList<Point> Px, ArrayList<Point> Py, double delta) {
        Point withBiggestXFromLeft = Px.get(Px.size()/2 - 1);
        ArrayList<Point> inBand = new ArrayList<>();
        for (Point p: Py) {
            if (Math.abs(p.x - withBiggestXFromLeft.x) < delta) {
                inBand.add(p);
            }
        }
        double best = delta;
        Point[] bestPair = null;
        if (inBand.size() > 8) {
            for (int i = 0; i < inBand.size() - 8; i++) {
                for (int j = 1; j < 8; j++) {
                    if (Point.distance(inBand.get(i), inBand.get(j)) < delta) {
                        delta = Point.distance(inBand.get(i), inBand.get(j));
                        bestPair = new Point[]{inBand.get(i), inBand.get(j)};
                    }
                }
            }
        } else {
            for (int i = 0; i < inBand.size() - 1; i++) {
                for (int j = i + 1; j < inBand.size(); j++) {
                    if (Point.distance(inBand.get(i), inBand.get(j)) < delta) {
                        delta = Point.distance(inBand.get(i), inBand.get(j));
                        bestPair = new Point[]{inBand.get(i), inBand.get(j)};
                    }
                }
            }
        }
        return bestPair;
    }

    static Point[] closestPair(ArrayList<Point> Px, ArrayList<Point> Py) {
        if (Px.size() == 1) {
            return null;
        }
        if (Px.size() == 2) {
            return new Point[]{Px.get(0), Px.get(1)};
        }
        ArrayList<Point> Rx = new ArrayList<Point>(Px.subList(0, Px.size()/2));
        ArrayList<Point> Qx = new ArrayList<Point>(Px.subList(Px.size()/2, Px.size()));
        ArrayList<ArrayList<Point>> Ysplit = formYSortedSublists(Rx, Qx, Py);
        ArrayList<Point> Ry = Ysplit.get(0);
        ArrayList<Point> Qy = Ysplit.get(1);
        Point[] pair1 = closestPair(Qx, Qy);
        Point[] pair2 = closestPair(Rx, Ry);
        Point[] closest = getClosest(pair1, pair2);
        double delta = Point.distance(closest[0], closest[1]);
        Point[] splitClosest = closestSplitPair(Px, Py, delta);

        return (splitClosest != null)? splitClosest: closest;
    }

    static double minimalDistance(int[] x, int y[]) {
        double ans = Double.POSITIVE_INFINITY;
        ArrayList<Point> pointsX = getPoints(x, y);
        ArrayList<Point> pointsY = new ArrayList<>(pointsX);
        Collections.sort(pointsX, new CompareX());
        Collections.sort(pointsY, new CompareY());
        Point[] pair = closestPair(pointsX, pointsY);
        return Point.distance(pair[0], pair[1]);
    }

    public static void main(String[] args) throws Exception {
        reader = new BufferedReader(new InputStreamReader(System.in));
        writer = new PrintWriter(System.out);
        int n = nextInt();
        int[] x = new int[n];
        int[] y = new int[n];
        for (int i = 0; i < n; i++) {
            x[i] = nextInt();
            y[i] = nextInt();
        }
        System.out.println(minimalDistance(x, y));
        writer.close();
    }

    static BufferedReader reader;
    static PrintWriter writer;
    static StringTokenizer tok = new StringTokenizer("");


    static String next() {
        while (!tok.hasMoreTokens()) {
            String w = null;
            try {
                w = reader.readLine();
            } catch (Exception e) {
                e.printStackTrace();
            }
            if (w == null)
                return null;
            tok = new StringTokenizer(w);
        }
        return tok.nextToken();
    }

    static int nextInt() {
        return Integer.parseInt(next());
    }
}
