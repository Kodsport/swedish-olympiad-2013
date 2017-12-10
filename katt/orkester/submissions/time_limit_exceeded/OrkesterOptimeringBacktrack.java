import java.util.*;
import java.io.*;

public class OrkesterOptimeringBacktrack {
	
	static int M, N;
	static LinkedList<Integer>[] g;
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		StringTokenizer st = new StringTokenizer(in.readLine());
		
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		g = new LinkedList[M];
		for (int i = 0; i < M; i++) {
			g[i] = new LinkedList<Integer>();
			st = new StringTokenizer(in.readLine());
			int T = Integer.parseInt(st.nextToken());
			for (int j = 0; j < T; j++) {
				g[i].add(Integer.parseInt(st.nextToken()) - 1);
			}
		}
		out.println(solveBacktracking());
		
		out.close();
		in.close();
	}
	
	static LinkedList<Integer>[] rg;
	static int[] used;
	static double solveBacktracking() {
		rg = new LinkedList[N];
		for (int i = 0; i < N; i++) rg[i] = new LinkedList<Integer>();
		for (int i = 0; i < M; i++) {
			for (int tact : g[i]) {
				rg[tact].add(i);
			}
		}
		used = new int[M];
		return backtrack(0, 0);
	}
	
	static double backtrack(int tact, double d) {
		if (tact == N) return d;
		double res = backtrack(tact+1, d);
		for (int musician : rg[tact]) {
			used[musician]++;
			res = Math.max(res, backtrack(tact+1, d + 1d/used[musician]));
			used[musician]--;
		}
		return res;
	}
}
