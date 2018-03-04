// Ryan Kelley
// Homework 1, Question 2
// February 8th, 2018
// Object Oriented Programming, CS 2365-002
// Michael E. Shin

import java.util.Scanner;

public class HW1_Q2 {

	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		double[] price = {2.98, 4.50, 9.98, 4.49, 6.87};
		
		// Display all products and prices to user.
		System.out.println("Products Available \n ______________________");
		for (int i = 0; i < price.length; i++) {
			System.out.println("Product " + (i + 1) + ": " + price[i]);
		}
		
		double total = 0.0;
		
		// Get amount of each product from user.
		for (int i = 0; i < price.length; i++) {
			System.out.print("How many of product " + (i+1) + "? ");
			int q = scanner.nextInt();
			// Add total price for current product to the total.
			total += q * price[i];
		}
		
		System.out.println("Total: $" + total);

		scanner.close();
	}
}
