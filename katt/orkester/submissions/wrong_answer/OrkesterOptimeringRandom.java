import java.util.*;
import java.io.*;

public class OrkesterOptimeringRandom {
	
	static int N, M;
	static int[] matchedBy;
	static boolean[] visited;
	static LinkedList<Integer>[] g;
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		StringTokenizer st = new StringTokenizer(in.readLine());
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		g = new LinkedList[N];
		for (int i = 0; i < N; i++) {
			g[i] = new LinkedList<Integer>();
			st = new StringTokenizer(in.readLine());
			int T = Integer.parseInt(st.nextToken());
			for (int j = 0; j < T; j++) {
				g[i].add(Integer.parseInt(st.nextToken()) - 1);
			}
		}
		double res = 0;
		for (int i = 0; i < 1000; i++) {
			res = Math.max(res, getEstimate());
		}
		out.println(res);
		
		out.close();
		in.close();
	}
	
	static double getEstimate() {
		matchedBy = new int[M];
		Arrays.fill(matchedBy, -1);
		double res = 0;
		int[] timesPlayed = new int[N];
		visited = new boolean[N];
		int cntBad = 0;
		while (true) {
			boolean matchFound = false;
			int i = new Random().nextInt(N);
			Arrays.fill(visited, false);
			visited[i] = true;
			for (int tact : g[i]) {
				if (match(tact)) {
					timesPlayed[i]++;
					res += 1d/timesPlayed[i];
					matchedBy[tact] = i;
					matchFound = true;
					break;
				}
			}
			if (!matchFound) {
				cntBad++;
				if (cntBad == 2*N) break;
			} else {
				cntBad = 0;
			}
		}
		return res;
	}
	
	static boolean match(int tact) {
		if (matchedBy[tact] == -1) return true;
		int m = matchedBy[tact];
		if (visited[m]) return false;
		visited[m] = true;
		for (int newTact : g[m]) {
			if (match(newTact)) {
				matchedBy[newTact] = m;
				return true;
			}
		}
		return false;
	}
}
