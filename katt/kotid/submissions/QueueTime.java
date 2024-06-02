import java.io.*;
import java.util.*;

public class QueueTime {
	
	public static final int INF = 100000000;

	public static void main(String[] args) throws IOException {
		Kattio io = new Kattio(System.in);
		int n = io.getInt();
		int k = io.getInt();
		SegmentTree queue = new SegmentTree(n);
		int[] g = new int[n];
		for (int i = 0; i < n; i++) {
			g[i] = io.getInt();
			queue.update(i, g[i]);
		}
		int[] res = new int[n];
		Arrays.fill(res, -1);
		int t = 0;
		for (int i = 0; i < n; i++) {
			if (res[i] == -1) {
				res[i] = t;
				int left = k - g[i];
				g[i] = INF;
				queue.update(i, INF);
				while (left > 0) {
					int lo = i + 1;
					int hi = n;
					while (lo < hi) {
						int mid = lo + (hi - lo)/2;
						if (queue.getMin(0, mid) <= left) {
							hi = mid;
						} else {
							lo = mid + 1;
						}
					}
					if (lo < n && g[lo] <= left) {
						left -= g[lo];
						res[lo] = t;
						queue.update(lo, INF);
						g[lo] = INF;
					} else {
						break;
					}
				}
				t++;
			}
		}
		StringBuilder sb = new StringBuilder(res[0]+"");
		for (int i = 1; i < n; i++) {
			sb.append(" " + res[i]);
		}
		System.out.println(sb);
		io.close();
	}
	
	static class SegmentTree {
		int[] s;
		int n;
		public SegmentTree(int size) {
			n = 1;
			while (n < size) n *= 2;
			s = new int[2*n];
			Arrays.fill(s, INF);
		}
		public void update(int pos, int val) {
			pos += n;
			s[pos] = val;
			pos /= 2;
			while (pos > 0) {
				s[pos] = Math.min(s[pos*2], s[pos*2 + 1]);
				pos /= 2;
			}
		}
		public int getMin(int l, int r) {
			return query(1, l, r + 1, 0, n);
		}
		private int query(int pos, int a, int b, int x, int y) {
			if (a >= b) return INF;
			if (a == x && b == y) return s[pos];
			int m = (x + y)/2;
			return Math.min(query(pos*2, a, Math.min(b, m), x, m), query(pos*2 + 1, Math.max(a, m), b, m, y));
		}
	}

	static class Kattio extends PrintWriter {
		public Kattio(InputStream i) {
			super(new BufferedOutputStream(System.out));
			r = new BufferedReader(new InputStreamReader(i));
		}
		public Kattio(InputStream i, OutputStream o) {
			super(new BufferedOutputStream(o));
			r = new BufferedReader(new InputStreamReader(i));
		}

		public boolean hasMoreTokens() {
			return peekToken() != null;
		}

		public int getInt() {
			return Integer.parseInt(nextToken());
		}

		public double getDouble() { 
			return Double.parseDouble(nextToken());
		}

		public long getLong() {
			return Long.parseLong(nextToken());
		}

		public String getWord() {
			return nextToken();
		}



		private BufferedReader r;
		private String line;
		private StringTokenizer st;
		private String token;

		private String peekToken() {
			if (token == null) 
				try {
					while (st == null || !st.hasMoreTokens()) {
						line = r.readLine();
						if (line == null) return null;
						st = new StringTokenizer(line);
					}
					token = st.nextToken();
				} catch (IOException e) { }
				return token;
		}

		private String nextToken() {
			String ans = peekToken();
			token = null;
			return ans;
		}
	}
}
