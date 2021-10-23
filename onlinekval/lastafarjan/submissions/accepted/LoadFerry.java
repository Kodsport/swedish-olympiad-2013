import java.io.*;
import java.util.*;

public class LoadFerry {
    
    /*
10
5
2 1 2 5 1 1 2 1 1 2
     */
    
    static int[][][][] dp;
    static int[] numCarsTaken;
    static int[] cars;
    static int n, L;

    public static void main(String[] args) throws IOException {
        Kattio io = new Kattio(System.in);
        n = io.getInt();
        L = io.getInt() + 1;
        dp = new int[L + 1][L + 1][L + 1][L + 1];
        for (int i = 0; i <= L; i++) {
            for (int j = 0; j <= L; j++) {
                for (int k = 0; k <= L; k++) {
                    Arrays.fill(dp[i][j][k], -1);
                }
            }
        }
        numCarsTaken = new int[n*10 + 1];
        cars = new int[n];
        int tot = 0;
        for (int i = 0; i < n; i++) {
            cars[i] = io.getInt() + 1;
            tot += cars[i];
            numCarsTaken[tot] = i + 1;
        }
        io.println(solve(new int[]{0, 0, 0, 0}));
        io.close();
    }
    
    static int solve(int[] files) {
        int numCars = numCarsTaken[files[0] + files[1] + files[2] + files[3]];
        if (numCars == n) return 0;
        if (dp[files[0]][files[1]][files[2]][files[3]] != -1) return dp[files[0]][files[1]][files[2]][files[3]];
        int res = 0;
        for (int i = 0; i < 4; i++) {
            if (files[i] + cars[numCars] <= L) {
                files[i] += cars[numCars];
                res = Math.max(res, solve(files) + 1);
                files[i] -= cars[numCars];
            }
        }
        return dp[files[0]][files[1]][files[2]][files[3]] = res;
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

