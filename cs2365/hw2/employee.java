// Ryan Kelley
// Homework 2, Question 2
// February 15th, 2018
// Object Oriented Programming, CS 2365-002
// Michael E. Shin

package ryan.hw2;

public class Employee {

	private String firstName;
	private String lastName;
	private double salary;
	
	Employee(String first, String last, double sal) {
		firstName = first;
		lastName = last;
		salary = sal;
	}
	
	public void setFirst(String first) {
		firstName = first;
	}
	
	public void setLast(String last) {
		lastName = last;
	}
	
	public void setSalary(double sal) {
		if (salary > 0)	
			salary = sal;
	}
	
	public String getFirst() {
		return firstName;
	}
	
	public String getLast() {
		return lastName;
	}
	
	public double getSalary() {
		return salary;
	}
	
}
