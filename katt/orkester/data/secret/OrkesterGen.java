package orkester;

import java.util.*;
import java.io.*;

public class OrkesterGen {
	
	static final Random rand = new Random();
	
	static final int NUM_TEST_CASES = 15;
	
	static final int[] NVals = {17, 9, 20,
								371, 200, 571,
								346, 571, 813,
								942, 470, 987,
								993, 499, 1000};
	static final int[] MVals = {17, 18, 20,
								457, 607, 571,
								728, 770, 813,
								998, 940, 987,
								999, 1000, 1000};
	static final boolean[] evil = {  false, false, true,
									 false, true, true,
									 false, false, true,
									 false, false, true,
									 false, true, true};
	
	public static void main(String[] args) throws IOException {
		generateSecret();
	}
	
	static void generateSecret() throws IOException {
		for (int i = 0; i < NUM_TEST_CASES; i++) {
			String num = ""+(i+1);
			if (num.length() < 2) num = "0"+num;
			String IN_FILE = num+".in";
			String OUT_FILE = num+".ans";
			int N = NVals[i];
			int M = MVals[i];
			TreeSet<Integer>[] musicians;
			if (evil[i]) {
				musicians = generateEvil(N, M);
			} else {
				musicians = generateRandom(N, M);
			}
			int edges = 0;
			for (int j = 0; j < N; j++) {
				edges += musicians[j].size();
			}
			System.out.println("Generated case with " + edges + " edges");
			printData(new PrintWriter(IN_FILE), N, M, musicians);
			OrkesterOptimering.solve(new BufferedReader(new FileReader(IN_FILE)), new PrintWriter(OUT_FILE));
		}
	}
	
	static void printData(PrintWriter out, int N, int M, TreeSet<Integer>[] musicians) {
		out.print(N+" "+M+"\n");
		for (int i = 0; i < N; i++) {
			out.print(musicians[i].size());
			for (int num : musicians[i]) {
				out.write(' ');
				out.print(num);
			}
			out.write('\n');
		}
		out.close();
	}
	
	static TreeSet<Integer>[] generateRandom(int N, int M) {
		TreeSet<Integer>[] res = new TreeSet[N];
		for (int i = 0; i < N; i++) {
			res[i] = new TreeSet<Integer>();
			int nums = 2 + rand.nextInt(Math.min(10, M/3));
			if (i == 9) nums = 2*M;
			for (int j = 0; j < nums; j++) {
				res[i].add(1+rand.nextInt(M));
			}
		}
		return res;
	}
	
	// M should be a multiple of N
	static TreeSet<Integer>[] generateEvil(int N, int M) {
		TreeSet<Integer>[] res = new TreeSet[N];
		for (int i = 0; i < N; i++) res[i] = new TreeSet<Integer>();
		int k = M/N;
		ArrayList<Integer> left = new ArrayList<Integer>();
		for (int i = 1; i <= M; i++) left.add(i);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < k; j++) {
				res[i].add(getRandomElement(left));
			}
		}
		ArrayList<Integer> notVisited = new ArrayList<Integer>();
		for (int i = 0; i < N; i++) notVisited.add(i);
		LinkedList<Integer> q = new LinkedList<Integer>();
		q.add(getRandomElement(notVisited));
		while (!q.isEmpty()) {
			int curr = q.removeFirst();
			int subs = Math.min(notVisited.size(), 1 + rand.nextInt(3));
			for (int i = 0; i < subs; i++) {
				int next = getRandomElement(notVisited);
				for (int num : res[next]) {
					res[curr].add(num);
				}
				for (int num : res[curr]) {
					res[next].add(num);
				}
				q.add(next);
			}
		}
		return res;
	}
	
	static int getRandomElement(List<Integer> list) {
		return list.remove(rand.nextInt(list.size()));
	}
}
