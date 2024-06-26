package main;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @author Zidan Omar Hamid | zidan.hamid@ogr.sakarya.edu.tr
 * @since March 17, 2024
 *        <p>
 *        Code Analyzer Class
 *        </p>
 */
public class CodeAnalyzer {
	private String fileName;
	private int totalJavadocLine; // Javadoc olarak yorum satır sayısı
	private int totalCommentLine; // Diğer yorumlar satır sayısı
	private int totalCodeLine; // Kod satır sayısı (tüm yorum ve boşluk satırları hariç)
	private int totalLine; // LOC (Line of Code) (Bir dosyadaki her şey dahil satır sayısı)
	private int totalFunction; // Fonksiyon Sayısı (Sınıfın içinde bulunan tüm fonksiyonların toplam sayısı)
	private double commentDeviation; // Yorum Sapma Yüzdesi (Yazılması gereken yorum satır sayısı yüzdelik olarak)

	public CodeAnalyzer(File file) {
		this.fileName = file.getName();
		analyzeFile(file);
	}

	/**
	 * <p>
	 * Analyze file
	 * </p>
	 * 
	 * @param file
	 */
	private void analyzeFile(File file) {
		Object[] javadocCounterArr = new Object[2];
		javadocCounterArr[0] = 0;
		javadocCounterArr[1] = false;

		Object[] commentLineCounterArr = new Object[3];
		commentLineCounterArr[0] = 0;
		commentLineCounterArr[1] = false;
		commentLineCounterArr[2] = false;

		Object[] codeLineCounterArr = new Object[2];
		codeLineCounterArr[0] = 0;
		codeLineCounterArr[1] = false;

		int lineCounter = 0;

		Object[] functionCounterArr = new Object[1];
		functionCounterArr[0] = 0;

		try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
			String line;
			while ((line = reader.readLine()) != null) {
				line = line.trim();
				lineCounter++;
				countJavadocLine(javadocCounterArr, line);
				countCommentLine(commentLineCounterArr, line);
				countCodeLine(codeLineCounterArr, line);
				countFunction(functionCounterArr, line);
			}

			this.totalJavadocLine = (int) javadocCounterArr[0];
			this.totalCommentLine = (int) commentLineCounterArr[0];
			this.totalCodeLine = (int) codeLineCounterArr[0];
			this.totalLine = lineCounter;
			this.totalFunction = (int) functionCounterArr[0];
			this.commentDeviation = calculateCommentDeviation();
		} catch (IOException e) {
			System.err.println("Error reading file: " + e.getMessage());
		}
	}

	/**
	 * <p>
	 * Count javadoc line
	 * </p>
	 * 
	 * @param javadoc counter array
	 * @param line    of string
	 */
	private void countJavadocLine(Object[] javadocCounterArr, String line) {
		int counter = (int) javadocCounterArr[0];
		boolean inJavaDoc = (boolean) javadocCounterArr[1];

		line = line.trim();
		if (line.startsWith("/**")) {
			inJavaDoc = true;
		} else if (line.startsWith("*/") && inJavaDoc) {
			inJavaDoc = false;
		} else if (line.startsWith("*") && inJavaDoc) {
			counter++;
		}

		javadocCounterArr[0] = counter;
		javadocCounterArr[1] = inJavaDoc;
	}

	/**
	 * <p>
	 * Count comment line
	 * </p>
	 * 
	 * @param comment counter array
	 * @param line    of string
	 */
	private void countCommentLine(Object[] commentLineCounterArr, String line) {
		Pattern inlineCommentPattern = Pattern.compile("//.*|/\\\\*(?:.|[\\\\n\\\\r])*?\\\\*/");
		Matcher inlineCommentMatcher = inlineCommentPattern.matcher(line);

		Pattern endCommentPattern = Pattern.compile("\\*/");
		Matcher endCommentMatcher = endCommentPattern.matcher(line);

		int commentLineCounter = (int) commentLineCounterArr[0];
		boolean inMultilineComment = (boolean) commentLineCounterArr[1];
		boolean inJavadoc = (boolean) commentLineCounterArr[2];

		if (inlineCommentMatcher.find() && !inJavadoc) {
			commentLineCounter++;
			commentLineCounterArr[0] = commentLineCounter;
			commentLineCounterArr[1] = inMultilineComment;
			commentLineCounterArr[2] = inJavadoc;
			return;
		}

		if (line.startsWith("/*") && !inMultilineComment && !line.startsWith("/**")) {
			inMultilineComment = true;

			if (endCommentMatcher.find()) {
				inMultilineComment = false;
			}

		} else if (line.endsWith("*/") && inMultilineComment) {
			inMultilineComment = false;

		} else if (inMultilineComment) {
			commentLineCounter++;
		}

		if (line.startsWith("/**") && !inJavadoc) {
			inJavadoc = true;
		} else if (line.endsWith("*/") && inJavadoc) {
			inJavadoc = false;
		}

		commentLineCounterArr[0] = commentLineCounter;
		commentLineCounterArr[1] = inMultilineComment;
		commentLineCounterArr[2] = inJavadoc;

	}

	/**
	 * <p>
	 * Count code line
	 * </p>
	 * 
	 * @param code line counter array
	 * @param line of string
	 */
	private void countCodeLine(Object[] codeLineCounterArr, String line) {
		int codeLineCounter = (int) codeLineCounterArr[0];
		boolean inComment = (boolean) codeLineCounterArr[1];

		if (line.startsWith("//")) {
			codeLineCounterArr[0] = codeLineCounter;
			codeLineCounterArr[1] = inComment;
			return;
		}

		if (line.startsWith("/*") && !inComment) {
			inComment = true;

			Pattern endCommentPattern = Pattern.compile("\\*/");
			Matcher matcher = endCommentPattern.matcher(line);

			if (matcher.find()) {
				inComment = false;
			}
		} else if (line.endsWith("*/") && inComment) {
			inComment = false;
		} else if (!inComment && !line.trim().isEmpty()) {
			codeLineCounter++;
		}

		codeLineCounterArr[0] = codeLineCounter;
		codeLineCounterArr[1] = inComment;
	}

	/**
	 * <p>
	 * Count function
	 * </p>
	 * 
	 * @param function counter array
	 * @param line     of string
	 */
	private void countFunction(Object[] functionCounterArr, String line) {
		Pattern methodPattern = Pattern.compile(
				"^\\s*(?:(?:public|protected|private)\\s+)?(?:static\\s+)?(?:final\\s+)?(?:synchronized\\s+)?(?:abstract\\s+)?(?:native\\s+)?(?:strictfp\\s+)?\\w+\\s+\\w+\\s*\\([^)]*\\)\\s*\\{?\\s*$");
		int functionCounter = (int) functionCounterArr[0];
		Matcher matcher = methodPattern.matcher(line.trim());

		if (matcher.matches())
			functionCounter++;

		functionCounterArr[0] = functionCounter;
	}

	/**
	 * <p>
	 * Calculate comment deviation
	 * </p>
	 */
	private double calculateCommentDeviation() {
		if (this.totalFunction == 0)
			return Double.POSITIVE_INFINITY;

		// YG=[(Javadoc + Diğer yorumlar)*0.8]/Fonksiyon sayisi
		double YG = ((this.totalJavadocLine + this.totalCommentLine) * 0.8) / this.totalFunction;
		// YH= (Kod satir/Fonksiyon sayisi)*0.3
		double YH = (((double) this.totalCodeLine / (double) this.totalFunction) * 0.3);
		// Yorum Sapma Yüzdesinin Hesabı: [(100*YG)/YH]-100
		double YS = ((100 * YG) / YH) - 100;

		DecimalFormat df = new DecimalFormat("#.##");
		return Double.parseDouble(df.format(YS));

	}

	/**
	 * <p>
	 * Helper funtion to print file statistic
	 * </p>
	 */
	public void printStatistics() {
		System.out.println("Sinif: " + this.fileName);
		System.out.println("Javadoc Satır Sayısı: " + this.totalJavadocLine);
		System.out.println("Yorum Satır Sayısı: " + this.totalCommentLine);
		System.out.println("Kod Satır Sayısı: " + this.totalCodeLine);
		System.out.println("LOC: " + this.totalLine);
		System.out.println("Fonksiyon Sayısı: " + this.totalFunction);
		System.out.println("Yorum Sapma Yüzdesi: % " + this.commentDeviation);
		System.out.println("-----------------------------------------");
	}
}
