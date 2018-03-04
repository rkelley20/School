// Ryan Kelley
// Homework 3
// February 28th, 2018
// Object Oriented Programming, CS 2365-002
// Michael E. Shin

import java.util.Scanner;

public class Customer {
	
	private double charge = 2.00;	// The customer's amount charged from yesterday

	public static void main(String[] args) {
		
		Scanner scanner = new Scanner(System.in);
		
		double total = 0;
		
		System.out.print("Current customer hours parked: ");
		
		while (scanner.hasNextInt()) {
			int customerHours = scanner.nextInt();
			Customer cur = new Customer(customerHours);	// Creates new customer with inputted hours
			total += cur.getCharge();					// Add charge to running total
			cur.printCharge();
			System.out.println("Running total: $" + String.format( "%.2f", total ));
			System.out.print("Current customer hours parked: ");
		}
		
			
		scanner.close();
	}
	
	// Calculate charge when the customer is made
	Customer(int hours) {
		calculateCharge(hours);
	}
	
	// Calculates charge based on hours parked
	private void calculateCharge(int hours) {
		if (hours > 3) {
			charge += (hours - 3) * 0.50;
			if (charge > 10.00) charge = 10.00;
		}
	}
	
	// Print their current charge with proper format
	public void printCharge() {
		System.out.println("Yesterday's Charge: $" + String.format("%.2f", charge));
	}
	
	public double getCharge() {
		return charge;
	}
	
}
