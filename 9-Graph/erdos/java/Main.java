import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class MyEntry implements Map.Entry<String, Author> {
	private String key;
	private Author value;

	@Override
	public String getKey() {
		return key;
	}

	@Override
	public Author getValue() {
		return value;
	}

	@Override
	public Author setValue(Author value) {
		this.value = value;
		return this.value;
	}

	public MyEntry(String s, Author a) {
		this.key = s;
		this.value = a;
	}
}

class Author implements Comparable<Author> {
	public static final int MAX_AUTHORS = 10001;
	public static final int MAX_NAME_LEN = 101;
	public static final int MAX_PAPER_AUTHORS = 5001;
	public static final int MAX_INPUT_LEN = 10001;
	public static final int MAX_LINKS = 501;

	static int idCounter = 0;
	int id;
	Set<Author> publ;
	int depht = 0;
	boolean visited = false;

	static Author erdosPtr;

	static Map<String, Author> authors = new HashMap<String, Author>();

	String lname, fname;

	void process(Set<Author> targets) {
		int count = 0;
		Queue<Author> q, n;
		int depht = 0;

		n = new LinkedList<Author>();

		n.add(this);
		targets.remove(this);

		this.depht = depht;
		this.visited = true;

		while (!targets.isEmpty() && !n.isEmpty()) {
			if (Erdos.debug)
				System.out.printf("level %d: %d targest to go whith %d nodes to see\n", depht,
						targets.size(), n.size());
			// swap Queues
			depht++;
			q = n;
			n = new LinkedList<Author>();

			while (!q.isEmpty()) {
				count++;

				Author v = q.poll();

				for (Author i : v.publ) {
					if (!i.visited) {
						n.add(i);
						i.depht = depht;
						targets.remove(i);
						i.visited = true;
					}
				}
			}
		}
		if (Erdos.debug)
			System.out.printf("processed %d nodes\n", count);
	}

	static Author find(String fname, String lname) {
		String fullname = new String(fname + lname);
		if (Erdos.debug) {
			System.out.printf("\tLooking for '%s'\n", fullname);
			for (Entry<String, Author> it : authors.entrySet()) {
				System.out.printf("\t\t'%s'\n", it.getKey());
			}
		}
		Author a = authors.get(fullname);
		return a;
	}

	Author(String fname, String lname) {
		if (Erdos.debug)
			System.out.printf("\t\tAuthor fname'%s' lname'%s'\n", fname, lname);
		publ = new TreeSet<Author>();
		id = idCounter++;

		if (lname.length() == 0 || fname.length() == 0) {
			throw new NullPointerException();
		}
		this.lname = lname;
		this.fname = fname;
		if (lname.compareTo("Erdos") == 0 && fname.compareTo("P.") == 0) {
			erdosPtr = this;
		}

		String fullname = new String(fname + lname);
		authors.put(fullname, this);

		if (Erdos.debug)
			System.out.printf("\tauhor '%s' alocated as %d\n", fullname, this.id);
	}

	void publicouCom(Author other) {
		if (other == null || other == this)
			return;
		if (Erdos.debug)
			System.out.printf("inserting %d on %d\n", other.id, this.id);
		publ.add(other);
	}

	static void freeMemory() {
		if (Erdos.debug)
			System.out.printf("\tfreeMemory\n");
		authors = new HashMap<String, Author>();
		authors.clear();
		erdosPtr = null;
		idCounter = 0;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((fname == null) ? 0 : fname.hashCode());
		result = prime * result + ((lname == null) ? 0 : lname.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Author other = (Author) obj;
		if (fname == null) {
			if (other.fname != null)
				return false;
		} else if (!fname.equals(other.fname))
			return false;
		if (lname == null) {
			if (other.lname != null)
				return false;
		} else if (!lname.equals(other.lname))
			return false;
		return true;
	}

	@Override
	public int compareTo(Author other) {
		return lname.compareTo(other.lname) + fname.compareTo(other.fname);
	}

}

class Erdos {
	public static boolean debug = false;

	Erdos(boolean debug) {
		Erdos.debug = debug;
	}

	void testAuthor() {
		Random rand = new Random();
		String lname, fname;
		lname = new String("Erdos");
		fname = new String("P.");
		Author n = new Author(fname, lname);
		Set<Author> targets = new TreeSet<Author>();
		Author x, k = null;
		for (int i = 0; i < Author.MAX_AUTHORS; i++) {
			x = new Author("a" + rand.nextInt(), "a" + rand.nextInt());
			n.publicouCom(x);

			k = new Author("a" + rand.nextInt(), "a" + rand.nextInt());
			x.publicouCom(k);
			targets.add(k);
		}
		if (k != null) {
			targets.add(k);
		}

		System.out.printf("targets %d\n", targets.size());
		// ~ getchar();
		try {
			System.in.read();
		} catch (IOException e) {
			e.printStackTrace();
		}
		Author.erdosPtr.process(targets);

	}

	void UvaErdo() {
		int scenarios, papers = 0, names = 0;
		int scenario;

		Scanner scanIn = new Scanner(System.in);
		String s = scanIn.nextLine();
		scenarios = Integer.parseInt(s.trim());
		for (scenario = 1; scenario <= scenarios; scenario++) {
			System.out.printf("Scenario %d\n", scenario);

			String nextLine = scanIn.nextLine();
			String s2[] = nextLine.split(" ");
			int i = 0;
			for (; i < s2.length; i++) {
				try {
					papers = Integer.parseInt(s2[i].trim());
					if (Erdos.debug)
						System.out.printf("\tConverted '%s' to %d\n", s2[i].trim(), papers);
					break;
				} catch (NumberFormatException e) {
				}
			}
			i++;
			for (; i < s2.length; i++) {
				try {
					names = Integer.parseInt(s2[i].trim());
					if (Erdos.debug)
						System.out.printf("\tConverted '%s' to %d\n", s2[i].trim(), names);
					break;
				} catch (NumberFormatException e) {
				}
			}
			if (Erdos.debug)
				System.out.printf("\tConverted '%s' to %d papers and %d names\n", nextLine, papers,
						names);

			readPapers(papers, scanIn);

			if (Erdos.debug) {
				System.out.printf("Scenario %d\n", scenario);
			}

			List<Entry<String, Author>> theMap = new ArrayList<Map.Entry<String, Author>>(names);
			Set<Author> targets = new TreeSet<Author>();

			readCases(names, scanIn, theMap, targets);

			if (Author.erdosPtr != null) {
				Author.erdosPtr.process(targets);
				if (Erdos.debug)
					System.out.printf("Author::erdosPtr not null\n");
			}

			for (Entry<String, Author> it : theMap) {
				Author a = it.getValue();
				String bigname = it.getKey();
				if (a == null) {
					System.out.printf("%s infinity\n", bigname);
				} else {
					int d = a.depht;
					if (d <= 0 && Author.erdosPtr != a) {
						System.out.printf("%s, %s infinity\n", a.lname, a.fname);
					} else {
						System.out.printf("%s, %s %d\n", a.lname, a.fname, d);
					}
				}
			}

			theMap.clear();
			Author.freeMemory();
		}
	}

	private void readPapers(int papers, Scanner scanIn) {
		int paper;
		for (paper = 1; paper <= papers; paper++) {
			String paperAuthors;

			paperAuthors = scanIn.nextLine();
			if (Erdos.debug)
				System.out.printf("paper #%d %s\n", paper, paperAuthors);

			Author authors[] = new Author[Author.MAX_PAPER_AUTHORS];
			int authorsIndex = 0;

			Pattern p = Pattern.compile("\\s*(\\S*)[,]\\s*(\\S*)[,:]");
			Matcher m = p.matcher(paperAuthors);
			while (m.find()) {
				String lname = m.group(1);
				String fname = m.group(2);

				if (debug) {
					System.out.printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname, fname);
				}

				authors[authorsIndex] = Author.find(fname, lname);
				if (authors[authorsIndex] == null) {
					if (lname.length() == 0 || fname.length() == 0) {
						continue;
					}
					authors[authorsIndex] = new Author(fname, lname);
				}
				authorsIndex++;
			}

			for (int i = 0; i < authorsIndex; i++) {
				for (int j = 0; j < authorsIndex; j++) {
					authors[i].publicouCom(authors[j]);
				}
			}
		}
	}

	private int readCases(int names, Scanner scanIn, List<Entry<String, Author>> theMap,
			Set<Author> targets) {
		int nameInd;
		for (nameInd = 1; nameInd <= names; nameInd++) {
			String bigname;

			bigname = scanIn.nextLine();
			if (Erdos.debug)
				System.out.printf("\tname #%d %s\n", nameInd, bigname);

			Pattern p = Pattern.compile("\\s*(\\S*)[,]\\s*(\\S*)");
			Matcher m = p.matcher(bigname);
			if (m.find()) {
				String lname = m.group(1);
				String fname = m.group(2);

				if (Erdos.debug)
					System.out.printf("\tmatcher2'%s' => '%s', '%s'\n", bigname, lname, fname);

				Author a = Author.find(fname, lname);

				theMap.add(new MyEntry(bigname, a));
				if (a != null) {
					targets.add(a);
					if (Erdos.debug)
						System.out.printf("\tauthor case '%s' is #%d\n", a.lname, targets.size());
				}
			} else {
				theMap.add(new MyEntry(bigname, null));
			}
		}
		return nameInd;
	}

	public static void main(String[] args) {
		Erdos erdos = new Erdos(false);

		// erdos.testAuthor();
		erdos.UvaErdo();

		if (Erdos.debug)
			System.out.printf("\nEND PROG\n");
	}

}


public class Main{
	public static void main(String[] args) {
		Erdos.main(args);
	}
}
