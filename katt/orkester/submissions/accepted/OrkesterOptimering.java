import java.util.*;
import java.io.*;

public class OrkesterOptimering {
	
	static int M, N;
	static int[] matchedBy;
	static boolean[] visited;
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
		matchedBy = new int[N];
		Arrays.fill(matchedBy, -1);
		double res = 0;
		LinkedList<Integer> q = new LinkedList<Integer>();
		for (int i = 0; i < M; i++) q.add(i);
		int[] timesPlayed = new int[M];
		visited = new boolean[M];
		while (!q.isEmpty()) {
			Arrays.fill(visited, false);
			int v = q.removeFirst();
			visited[v] = true;
			timesPlayed[v]++;
			for (int tact : g[v]) {
				if (match(tact)) {
					res += 1d/timesPlayed[v];
					matchedBy[tact] = v;
					q.add(v);
					break;
				}
			}
		}
		out.println(res);
		
		out.close();
		in.close();
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
