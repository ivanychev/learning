/*
*
 */

import java.util.ArrayList;
import java.util.List;

public class HelloWorld {
    public static void main(String[] args) {
        List<String> testCollection = new ArrayList<String>();
        for (String testS: testCollection) {
            System.out.println(testS);
        }
        System.out.println("Hello, World!");
        try {
            System.out.println("Checking...");
        } catch (RuntimeException e) {
            System.out.println("Error");
        }
    }
}

