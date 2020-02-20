import java.util.*;
import java.io.*;
import java.math.*;

class Solutions {
	final static int MOD = 998244353;
	static ArrayList<Integer> score;
	public static void main(String args[]) throws Exception {
		score = new ArrayList<>();
		int b = nextInt();
		int l = nextInt();
		int d = nextInt();
		int finalScore = 0;
		for(int i=0;i<b;i++)
			score.add(nextInt());
		HashSet<Library> libraries = new HashSet<>();
		for(int i=0;i<l;i++) {
			int n = nextInt();
			Library library = new Library(i, nextInt(), nextInt());
			while(n-->0) {
				library.books.add(nextInt());
			}
			library.sort();
			libraries.add(library);
		}
		Set<Integer> done = new HashSet<>();
		HashMap<Integer, List<Integer>> ans = new HashMap<>();
		while(d>0 && libraries.size()>0) {
			// System.out.println(libraries.toString());
			final int left = d;
			Library min = libraries.parallelStream().map(z -> z.compute(done, left)).min(new Comparator<Library>(){
				public int compare(Library a, Library b) {
					return Long.compare(b.score, a.score);
				}
			}).get();
			finalScore += min.score;
			libraries.remove(min);
			List<Integer> books = min.getScans(done, d);
			done.addAll(books);
			ans.put(min.idx, books);
			d-=min.sd;
		}
		System.out.println(ans.size());
		for(int lib:ans.keySet()) {
			List<Integer> vals = ans.get(lib);
			System.out.println(lib + " " + vals.size());
			for(int i:vals) {
				System.out.print(i+" ");
			}
			System.out.println();
		}
		// System.out.println(finalScore);
	}

	static class Library implements Comparable<Library> {
		int idx;
		int sd;
		int m;
		List<Integer> books;
		long score;
		Library(int idx, int sd, int m) {
			this.idx = idx;
			this.sd = sd;
			this.m = m;
			books = new ArrayList<>();
			score = 0;
		}

		void sort() {
			Collections.sort(books, new Comparator<Integer>(){
				public int compare(Integer a, Integer b) {
					return Solutions.score.get(b) - Solutions.score.get(a);
				}
			});
		}

		public int compareTo(Library l) {
			return Long.compare(l.score,score);
		}

		Library compute(Set<Integer> done, int d) {
			int max = m * (d - sd);
			this.score = 0;
			for(int book:books) {
				if(max < 1)
					break;
				if(done.contains(book))
					continue;
				this.score += Solutions.score.get(book);
				max--;
			}
			return this;
		}

		List<Integer> getScans(Set<Integer> done, int d) {
			int max = m * (d - sd);
			this.score = 0;
			List<Integer> scans = new ArrayList<>();
			for(int book:books) {
				if(max < 1)
					break;
				if(done.contains(book))
					continue;
				this.score += Solutions.score.get(book);
				scans.add(book);
				max--;
			}
			return scans;
		}

		public String toString() {
			return idx + " " + score;
		}
	}

	static boolean isPrime(int n) {
		if(n<2) return false;
		for(int i=2;i<n;i++) {
			if(n%i==0) return false;
		}
		return true;
	}

	static long modpow(long a, long b) {
		if(b==0)
			return 1;
		if(b==1)
			return a;
		long x = modpow(a,b/2);
		x = (x * x) % MOD;
		if(b%2==1)
			x = (x * a) % MOD;
		return x;
	}

	static long modinv(long a) {
		return modpow(a,MOD-2);
	}

	static double nextDouble() throws IOException {
		InputStream in = System.in;
		double ans=0;
		boolean flag = true;
		byte b = 0;
		boolean neg = false;
		double pow = 0.1;
		boolean dec = false;
		while((b>=45 && b<58) || flag) {
			if(b==45)
				neg = true;
			else if(b==46) {
				dec = true;
				pow = 0.1;
			}
			else if(b>=48 && b<58) {
				if(dec) {
					ans += (b-48)*pow;
					pow /= 10.0;
				}
				else
					ans = ans*10+(b-48);
				flag = false;
			}
			b=(byte)in.read();
		}
		if(neg)
			return -ans;
		return ans;
	}
	static int nextInt()throws IOException{
		InputStream in=System.in;
		int ans=0;
		boolean flag=true;
		byte b=0;
		boolean neg=false;
		while ((b>47 && b<58) || flag){
			if(b==45)
				neg=true;
			if(b>=48 && b<58){
				ans=ans*10+(b-48);
				flag=false;
			}
			b=(byte)in.read();
		}
		if(neg)
			return -ans;
		return ans;
	}

	static long nextLong()throws IOException{
		InputStream in=System.in;
		long ans=0;
		boolean flag=true;
		byte b=0;
		while ((b>47 && b<58) || flag){
			if(b>=48 && b<58){
				ans=ans*10+(b-48);
				flag=false;
			}
			b=(byte)in.read();
		}
		return ans;
	}

	static String next() throws IOException {
		StringBuilder sb = new StringBuilder(1 << 16);
		InputStream in=System.in;
		int b = in.read();
		while (sb.length() == 0 || !Character.isWhitespace(b)) {
			if (!Character.isWhitespace(b)) {
				sb.append((char) b);
			}
			b = in.read();
		}
		return sb.toString();
	}
	static boolean isWhiteSpace(byte b){
		char ch=(char)b;
		return ch=='\0' || ch==' ' || ch=='\n';
	}
}