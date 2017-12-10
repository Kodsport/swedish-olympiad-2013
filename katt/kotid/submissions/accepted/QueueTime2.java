import java.util.*;
import java.io.*;

public class QueueTime2 {
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		
		solve(in, out);
	}
	
	static void solve(BufferedReader in, PrintWriter out) throws IOException {
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		
		SegmentTree tree = new SegmentTree(n);
		for (int i = 0; i < n; i++) {
			tree.update(i, k);
		}
		
		StringBuilder res = new StringBuilder();
		st = new StringTokenizer(in.readLine());
		for (int i = 0; i < n; i++) {
			int g = Integer.parseInt(st.nextToken());
			res.append(tree.placeGroup(g) + " ");
		}
		res.delete(res.length() - 1, res.length());
		out.println(res);
		out.close();
		in.close();
	}
	
	static class SegmentTree {
		int[] s;
		int size;
		
		public SegmentTree(int n) {
			size = 1;
			while (size < n) size *= 2;
			s = new int[size * 2];
		}
		
		public void update(int pos, int val) {
			pos += size;
			s[pos] = val;
			pos /= 2;
			while (pos > 0) {
				s[pos] = Math.max(s[pos*2], s[pos*2 + 1]);
				pos /= 2;
			}
		}
		
		public int placeGroup(int g) {
			int pos = 1;
			while (pos*2 + 1 < s.length) {
				if (s[pos*2] >= g) {
					pos = pos*2;
				} else {
					pos = pos*2 + 1;
				}
			}
			update(pos - size, s[pos] - g);
			return pos - size;
		}
	}
}
