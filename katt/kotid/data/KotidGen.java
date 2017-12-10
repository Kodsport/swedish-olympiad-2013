import java.io.*;
import java.util.*;

public class KotidGen {
	
	static Random rand = new Random();
	
	static final int NUM_SECRET = 10;
	static final int[] Nvals = new int[] {             870, 994,     78724, 86792,  85827, 497981,     798124, 899302,    999989, 1000000};
	static final int[] Kvals = new int[] {             813, 990,     7,     85322,  51298732, 480012,  9981023, 9952301,  90000000, 10000000};
	static final boolean[] randomCase = new boolean[] {true, false,  true, true,    false, true,      true, false,     true, false};
	
	public static void main(String[] args) throws IOException {
		// printSamples();
		generateSecret();
	}
	
	static void printSamples() throws IOException {
		int N = 3, K = 3;
		int[] nums = new int[] {2, 2, 1};
		printTestCase("sample/01", N, K, nums);
		N = 5; K = 4;
		nums = new int[] {4, 3, 2, 1, 1};
		printTestCase("sample/02", N, K, nums);
	}
	
	static void generateSecret() throws IOException {
		for (int i = 0; i < NUM_SECRET; i++) {
			String num = ""+(i+1);
			if (num.length() < 2) num = "0" + num;
			int[] nums = randomCase[i] ? generateRandom(Nvals[i], Kvals[i]) : generateWorst(Nvals[i], Kvals[i]);
			printTestCase("secret/"+num, Nvals[i], Kvals[i], nums);
		}
	}
	
	static void printTestCase(String path, int N, int K, int[] nums) throws IOException {
		final String IN_FILE = path+".in";
		final String OUT_FILE = path+".ans";
		PrintWriter inFile = new PrintWriter(new FileWriter(IN_FILE));
		inFile.print(N+" "+K+"\n");
		inFile.print(nums[0]);
		for (int i = 1; i < N; i++) inFile.print(" " + nums[i]);
		inFile.print("\n");
		inFile.close();
		QueueTime2.solve(new BufferedReader(new FileReader(IN_FILE)), new PrintWriter(OUT_FILE));
	}
	
	static int[] generateRandom(int N, int K) {
		int[] res = new int[N];
		for (int i = 0; i < N; i++) {
			res[i] = 1 + rand.nextInt(K);
		}
		return res;
	}
	
	static int[] generateWorst(int N, int K) {
		int curr = K;
		int[] res = new int[N];
		for (int i = 0; i < N; i++) {
			res[i] = curr--;
			if (curr == 0) curr = K;
		}
		return res;
	}
}
