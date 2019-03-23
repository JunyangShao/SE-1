package com.gui;

public class tester {
	public static void main(String[] args) {
		flag x = new flag();
		System.out.println(x.value);
		change(x);
		System.out.println(x.value);
		String tests = "s";
		System.out.println(tests);
		change2(tests);
		System.out.println(tests);
		int x1[]= {1,2,3,4,5};
		System.out.println(x1[2]);
		change3(x1);
		System.out.println(x1[2]);
	}
	public static void change(flag i) {
		i.value=1;
	}
	public static void change2(String s) {
		s = "t";
	}
	public static void change3(int x[]) {
		x[2]=5;
	}
}
