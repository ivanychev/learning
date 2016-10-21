import java.util.Scanner;

public class Change {
    private static int getChange(int m) {
        int coins = 0;
        coins += m / 10;
        m %= 10;
        coins += m / 5;
        m %= 5;
        coins += m;
        return coins;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int m = scanner.nextInt();
        System.out.println(getChange(m));
    }
}

