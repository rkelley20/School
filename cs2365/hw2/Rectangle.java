// Ryan Kelley
// Homework 2, Question 1
// February 15th, 2018
// Object Oriented Programming, CS 2365-002
// Michael E. Shin

package ryan.hw2;

public class Rectangle {
	
	private float length = 1;
	private float width = 1;
	
	public float perimeter() {
		return (2 * length + 2 * width);
	}
	
	public float area() {
		return length * width;
	}
	
	public void setLength(float l) {
		if (l > 0 && l < 20) length = l;
	}
	
	public void setWidth(float w) {
		if (w > 0 && w < 20) width = w;
	}
	
	public float getWidth() {
		return width;
	}
	
	public float getLength() {
		return length;
	}
	
}
