import java.io.*;
import java.util.*;

public class MinirojSolver {
	
	static final int MINE = -1;
	static final int NOT_VISITED = -2;
	static final int POSSIBLE = 1;
	static final int IMPOSSIBLE = 0;
	
	static final char MINE_CHAR = 'X';
	static final char UNKNOWN_CHAR = 'O';
	static final char SAFE_CHAR = 'S';
	
	static int N;
	static int[] cells;
	static int[][][] dp;
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String s = in.readLine();
		System.out.println(solve(s));
	}
	
	static String solve(String s) {
		N = s.length();
		cells = new int[N];
		for (int i = 0; i < N; i++) {
			cells[i] = s.charAt(i) == 'X' ? MINE : s.charAt(i) - '0';
		}
		dp = new int[N][2][2];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 2; j++) {
				Arrays.fill(dp[i][j], NOT_VISITED);
			}
		}
		solve(0, 0, 0);
		solve(0, 0, 1);
		StringBuilder res = new StringBuilder();
		for (int i = 0; i < N; i++) {
			boolean mine = dp[i][0][1] == POSSIBLE || dp[i][1][1] == POSSIBLE;
			boolean safe = dp[i][0][0] == POSSIBLE || dp[i][1][0] == POSSIBLE;
			if (mine && safe) {
				res.append(UNKNOWN_CHAR);
			} else if (mine) {
				res.append(MINE_CHAR);
			} else if (safe) {
				res.append(SAFE_CHAR);
			} else {
				return "fel";
			}
		}
		return res.toString();
	}
	
	static int solve(int pos, int topLeft, int topMid) {
		if (dp[pos][topLeft][topMid] != NOT_VISITED) return dp[pos][topLeft][topMid];
		int cnt = topLeft + topMid;
		if (pos > 0 && cells[pos - 1] == MINE) cnt++;
		if (pos < N - 1 && cells[pos + 1] == MINE) cnt++;
		int res = IMPOSSIBLE;
		if (pos == N - 1) {
			res = cells[pos] == MINE || cells[pos] == cnt ? POSSIBLE : IMPOSSIBLE;
		} else {
			for (int topRight = 0; topRight < 2; topRight++) {
				if (cells[pos] == MINE || cells[pos] == cnt + topRight) {
					if (solve(pos + 1, topMid, topRight) == POSSIBLE) res = POSSIBLE;
				}
			}
		}
		return dp[pos][topLeft][topMid] = res;
	}
}
