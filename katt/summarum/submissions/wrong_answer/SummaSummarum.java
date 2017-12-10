import java.io.*;
import java.util.*;
 
public class SummaSummarum {
 
        public static void main(String[] args) throws IOException {
                Kattio io = new Kattio(System.in);
                int N = io.getInt();
                int[] a = new int[N];
                int[] b = new int[N];
                int A = 0;
                int B = 0;
                for (int i = 0; i < N; i++) {
                        a[i] = io.getInt();
                        A += a[i];
                }
                for (int i = 0; i < N; i++) {
                        b[i] = io.getInt();
                        B += b[i];
                }
                for (int i = 0; i < N; i++) {
                        a[i] = A - 2*a[i];
                        b[i] = B - 2*b[i];
                }
                Arrays.sort(a);
                Arrays.sort(b);
                int bi = 0;
                int res = Integer.MAX_VALUE;
                for (int ai = 0; ai < N; ai++) {
                        if (bi > 0) bi--;
                        int best = Integer.MAX_VALUE;
                        while (bi < N) {
                                int diff = Math.abs(a[ai] - b[bi]);
                                if (diff <= best) {
                                        best = diff;
                                        bi++;
                                } else {
                                        break;
                                }
                        }
                        res = Math.min(res, best);
                }
                System.out.println(res);
                io.close();
        }
 
        // ---------I/O----------
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
