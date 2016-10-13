package com.app;

import static org.apache.commons.lang3.ArrayUtils.*;

class HelloWorld {
  public static void main(String[] args) {
    String[] phrase = {"Hello"};
        phrase = add(phrase, " ");
        phrase = add(phrase, "world");
        for (String word : phrase) {
            System.out.print(word);
        }
        System.out.println();
  }
}
