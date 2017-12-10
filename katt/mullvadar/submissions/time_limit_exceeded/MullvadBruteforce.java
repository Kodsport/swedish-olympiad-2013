import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class MullvadBruteforce {
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
		
		String s = in.readLine();
		long t = Long.parseLong(in.readLine());
		out.println(solveBruteForce(s, t));
		
		in.close();
		out.close();
	}
	
	static long solveBruteForce(String s, long t) {
		int[] a = new int[s.length()];
		for (int i = 0; i < s.length(); i++) {
			if (s.charAt(i) != '.') a[i] = 1;
		}
		for (int i = 0; i < t; i++) {
			a = expand(a);
		}
		return getCount(a);
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
}
