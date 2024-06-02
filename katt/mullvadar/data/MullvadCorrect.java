package mullvadar;
import java.util.*;
import java.io.*;

public class MullvadCorrect {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
		solve(in, out);
	}
	
	static void solve(BufferedReader in, PrintWriter out) throws IOException {
		String s = in.readLine();
		long t = Long.parseLong(in.readLine());
		
		long res = solveCorrectly(s, t);
		out.print(res+"\n");
		
		out.close();
		in.close();
	}
	
	static HashMap<Long, Long> mem;
	static long solveCorrectly(String s, long t) {
		mem = new HashMap<Long, Long>();
		int[] a = new int[s.length()];
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) != '.') a[i] = 1;
		}
		return solve(a, t);
	}
	
	static long solve(int[] a, long t) {
		if (t == 0) return getCount(a);
		a = reduce(a);
		if (a.length == 0) return 0;
		if (a.length == 1) {
			Long memorized = mem.get(t);
			if (memorized != null) return memorized;
		}
		long res = 0;
		if (t % 2 == 1) {
			res = solve(expand(a), t - 1);
		} else {
			int[] a1 = new int[(a.length + 1)/2];
			int[] a2 = new int[a.length / 2];
			for (int i = 0; i < a1.length; i++) a1[i] = a[i*2];
			for (int i = 0; i < a2.length; i++) a2[i] = a[1 + i*2];
			res = solve(a1, t/2) + solve(a2, t/2);
		}
		if (a.length == 1) {
			mem.put(t, res);
		}
		return res;
	}
	
	static int getCount(int[] a) {
		int res = 0;
		for (int i = 0; i < a.length; i++) res += a[i];
		return res;
	}
	
	static int[] expand(int[] a) {
		int[] res = new int[a.length + 2];
		for (int i = 0; i < a.length; i++) {
			for (int j = i; j < i + 3; j++) {
				res[j] ^= a[i];
			}
		}
		return res;
	}
	
	static int[] reduce(int[] a) {
		int l = a.length;
		int r = -1;
		for (int i = 0; i < a.length; i++) {
			if (a[i] == 1) {
				r = i;
				l = Math.min(l, i);
			}
		}
		if (l > r) return new int[0];
		int[] res = new int[r - l + 1];
		for (int i = 0; i < res.length; i++) {
			res[i] = a[i + l];
		}
		return res;
	}
}
