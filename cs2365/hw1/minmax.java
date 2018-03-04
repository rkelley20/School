// Ryan Kelley
// Homework 1, Question 1
// February 6th, 2018
// Object Oriented Programming, CS 2365-002
// Michael E. Shin

import java.util.Scanner;

public class HW1_Q1 {

	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		int[] input = new int[5];
		
		System.out.print("Enter 5 integers: ");
		
		// Read 5 integers from the user
		for (int i = 0; i < 5; i++) input[i] = scanner.nextInt();
		
		// Output max and min to the screen
		System.out.println("The max is: " + getMax(input));
		System.out.println("The min is: " + getMin(input));
		
		scanner.close();
		
	}
	
	// Returns the integer with maximum value in array a.
	private static int getMax(int[] a) {
		int max = a[0];
		for (int i = 1; i < a.length; i++) {
			if (a[i] > max) max = a[i];
		}
		return max;
	}
	
	// Returns the integer with minimum value in array a.
	private static int getMin(int[] a) {
		int min = a[0];
		for (int i = 1; i < a.length; i++) {
			if (a[i] < min) min = a[i];
		}
		return min;
	}
	
}
