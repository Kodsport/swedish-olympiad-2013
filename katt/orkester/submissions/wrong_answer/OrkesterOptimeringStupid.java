import java.io.*;
import java.util.*;

public class OrkesterOptimeringStupid {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);
		StringTokenizer st = new StringTokenizer(in.readLine());
		
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		double res = 0;
		int m = 0;
		int X = 1;
		for (int i = 0; i < M; i++) {
			res += 1d/X;
			m++;
			if (m == N) {
				m = 0;
				X++;
			}
		}
		out.println(res);
		in.close();
		out.close();
	}
}
