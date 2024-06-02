import java.io.*;

/*
 * Solution that should score 40 points
 */
public class MinirojPartial {
	
	static int N;
	static String s;
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		s = in.readLine();
		N = s.length();
		boolean[] res1 = solve(true);
		boolean[] res2 = solve(false);
		if (res1 == null && res2 == null) {
			System.out.println("fel");
		} else {
			StringBuilder sb = new StringBuilder();
			for (int i = 0; i < N; i++) {
				if (res1 != null) {
					if (res2 != null) {
						sb.append(res1[i] != res2[i] ? "O" : (res1[i] ? "X":"S"));
					} else {
						sb.append(res1[i] ? "X":"S");
					}
				} else {
					sb.append(res2[i] ? "X":"S");
				}
			}
			System.out.println(sb);
		}
	}
	
	static boolean[] solve(boolean first) {
		boolean[] res = new boolean[N];
		res[0] = first;
		int prev = 0;
		int curr = first ? 1 : 0;
		for (int i = 0; i < N - 1; i++) {
			int cnt = s.charAt(i) - '0';
			if (cnt == prev + curr) {
				prev = curr;
				curr = 0;
				res[i+1] = false;
			} else if (cnt == prev + curr + 1) {
				prev = curr;
				curr = 1;
				res[i+1] = true;
			} else {
				return null;
			}
		}
		if (s.charAt(N - 1) - '0' == prev + curr) {
			return res;
		}
		return null;
	}
}
