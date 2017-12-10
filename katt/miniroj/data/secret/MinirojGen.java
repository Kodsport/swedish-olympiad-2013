package Miniroj;

import java.io.*;
import java.util.*;

public class MinirojGen {
	
	static final int NUM_SAMPLES = 2;
	static final int NUM_TEST_CASES = 10;
	static final int[] len = new int[] {5,17,547,9875,46,153,1295,23848,47893,50000};
	static final boolean[] minesPossible = new boolean[] {false, false, false, false, true, true, true, true, true, true};
	static final boolean[] impossibleCase = new boolean[] {false, true, false, false, false, true, false, true, false, false};
	
	static Random rand = new Random();
	
	public static void main(String[] args) throws IOException {
		generateTestCases();
	}
	
	static void generateTestCases() throws IOException {
		printSample1(new PrintWriter(new FileWriter("1.in")), new PrintWriter(new FileWriter("1.out")));
		printSample2(new PrintWriter(new FileWriter("2.in")), new PrintWriter(new FileWriter("2.out")));
		for (int i = 0; i < NUM_TEST_CASES; i++) {
			PrintWriter inFile = new PrintWriter(new FileWriter((NUM_SAMPLES+i+1)+".in"));
			PrintWriter outFile = new PrintWriter(new FileWriter((NUM_SAMPLES+i+1)+".out"));
			String s;
			if (impossibleCase[i]) {
				s = generateMaybeImpossible(len[i], minesPossible[i]);
			} else {
				s = generatePossible(len[i], minesPossible[i]);
			}
			inFile.println(s);
			outFile.println(MinirojSolver.solve(s));
			inFile.close();
			outFile.close();
		}
	}
	
	static void printSample1(PrintWriter in, PrintWriter out) {
		String s = "11111";
		in.println(s);
		out.println(MinirojSolver.solve(s));
		in.close();
		out.close();
	}
	
	static void printSample2(PrintWriter in, PrintWriter out) {
		String s = "121";
		in.println(s);
		out.println(MinirojSolver.solve(s));
		in.close();
		out.close();
	}
	
	static String generatePossible(int N, boolean mines) {
		return generatePossible(N, mines, rand.nextDouble(), rand.nextDouble());
	}
	
	static String generatePossible(int N, boolean mines, double p1, double p2) {
		boolean[] solution = new boolean[N];
		for (int i = 0; i < N; i++) {
			if (rand.nextDouble() <= p1) {
				solution[i] = true;
			}
		}
		int[] res = new int[N];
		for (int i = 0; i < N; i++) {
			if (mines && rand.nextDouble() <= p2) {
				res[i] = -1;
				for (int j = i-1; j <= i+1; j++) {
					if (j != i && j >= 0 && j < N && res[j] >= 0) {
						res[j]++;
					}
				}
			} else {
				for (int j = i-1; j <= i+1; j++) {
					if (j >= 0 && j < N && solution[j]) {
						res[i]++;
					}
				}
			}
		}
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < N; i++) {
			if (res[i] == -1) {
				sb.append(MinirojSolver.MINE_CHAR);
			} else {
				sb.append(res[i]);
			}
		}
		return sb.toString();
	}
	
	static String generateMaybeImpossible(int N, boolean mines) {
		char[] c = generatePossible(N, mines).toCharArray();
		int change = rand.nextInt(N);
		if (c[change] == MinirojSolver.MINE_CHAR) {
			c[change] = '0';
			for (int i = change - 1; i <= change + 1; i++) {
				if (i >= 0 && i < N && c[i] == MinirojSolver.MINE_CHAR) c[change]++;
			}
		} else {
			if (c[change] == '0') {
				c[change]++;
			} else {
				c[change]--;
			}
		}
		return new String(c);
	}
}
