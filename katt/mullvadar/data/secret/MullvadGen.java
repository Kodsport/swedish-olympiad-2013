package mullvadar;

import java.io.*;
import java.util.*;

public class MullvadGen {
	
	static final String SAMPLES_PATH = "../";
	static final String SECRET_PATH = "";
	
	static final long[] tVals = new long[] {273619947283L, 4827938117823828L, 89352, 99875, 48736284910382L, 5984738290598372L, 49820759837489238L, 12345678912345678L, 47826397482718627L, 1000000000000000000L};
	
	public static void main(String[] args) throws IOException {
		printSamples();
		generateSecret();
	}
	
	static void printSamples() throws IOException {
		String s = "A.AAA";
		long t = 2;
		printTestCase(SAMPLES_PATH+"01", s, t);
		s = ".";
		t = 1337;
		printTestCase(SAMPLES_PATH+"02", s, t);
		s = ".A.A..AAA.AA.A...AAA.A.A.A";
		t = 537;
		printTestCase(SAMPLES_PATH+"03", s, t);
	}
	
	static void generateSecret() throws IOException {
		for (int i = 0; i < tVals.length; i++) {
			String s;
			if (i <= 2) s = "A";
			else s = generatePartyStart();
			String num = (i+1)+"";
			if (num.length() < 2) num = "0"+num;
			printTestCase(SECRET_PATH+num, s, tVals[i]);
		}
	}
	
	static String generatePartyStart() {
		int len = 50 + new Random().nextInt(50);
		char[] res = new char[len];
		for (int i = 0; i < len; i++) {
			res[i] = new Random().nextDouble() <= 0.5 ? 'A' : '.';
		}
		return new String(res);
	}
	
	static void printTestCase(String path, String s, long t) throws IOException {
		String IN_PATH = path+".in";
		String OUT_PATH = path+".ans";
		PrintWriter inFile = new PrintWriter(IN_PATH);
		inFile.print(s+"\n");
		inFile.print(t+"\n");
		inFile.close();
		MullvadCorrect.solve(new BufferedReader(new FileReader(IN_PATH)), new PrintWriter(OUT_PATH));
	}
}
