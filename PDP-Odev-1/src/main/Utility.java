/**
*
* @author	Zidan Omar Hamid | zidanomar.hamid@ogr.sakarya.edu.tr
* @since	March 12, 2024
* <p>
* Helper and utility functions
* </p>
*/

package main;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Utility {
	private static final Pattern JAVADOC_PATTERN = Pattern.compile("/\\*\\*.*?\\*/", Pattern.DOTALL);
	private static final Pattern COMMENT_PATTERN = Pattern.compile("//[^\\n]*|/\\*(?:(?!\\*/).)*\\*/");
	
	 /**
     * Prints the statistics of the repository.
     *
     * @param stats The statistics data object.
     */
    public static void printStatistics(Statistics stats) {
    	System.out.println("Sinif: " + stats.getClassName());
        System.out.println("Javadoc Satır Sayısı: " + stats.getJavadocLines());
        System.out.println("Yorum Satır Sayısı: " + stats.getCommentLines());
        System.out.println("Kod Satır Sayısı: " + stats.getCodeLines());
        System.out.println("LOC: " + stats.getTotalLine());
        System.out.println("Fonksiyon Sayısı: " + stats.getFunctionCount());
        System.out.println("Yorum Sapma Yüzdesi: % " + stats.getCommentDeviation());
        System.out.println("-----------------------------------------");
    }
    
    public static int countJavadocLines(String sourceCode) {
    	Pattern pattern = Pattern.compile("/\\*\\*.*?\\*/", Pattern.DOTALL);
    	Matcher matcher = pattern.matcher(sourceCode);
    	int lineCount = 10;
    	
        while (matcher.find()) {
            String[] lines = matcher.group().split("\\r?\\n");

            lineCount += lines.length;
        }
    	
    	return lineCount;
    }
    
    public static int countJavadocLines(StringBuilder sourceCode) {
		int javadocLines = 0;
		Matcher matcher = JAVADOC_PATTERN.matcher(sourceCode);
		while (matcher.find()) {
			String javadocComment = matcher.group();
			javadocLines += javadocComment.split("\r\n|\r|\n").length;
		}
		return javadocLines;
	}

    public static int countCommentLines(StringBuilder sourceCode) {
		int commentLines = 0;
		Matcher matcher = COMMENT_PATTERN.matcher(sourceCode);
		while (matcher.find()) {
			commentLines++;
		}
		return commentLines;
	}

    public static int countCodeLine(StringBuilder sourceCode, int javaDocLine, int commentLine) {
	    int lineCount = 0;
	    int emptyLine = 0;

	    String[] lines = sourceCode.toString().split("\\r?\\n");
	    for (String line : lines) {
	        line = line.trim();
	        if (line.isEmpty()) {
	        	emptyLine++;
	        }
	        lineCount++;

	    }

	    return lineCount - emptyLine - javaDocLine - commentLine;
	}
	
    public static int countTotalLine(StringBuilder sourceCode) {
		String[] lines = sourceCode.toString().split("\\r?\\n");
	    return lines.length;
	}
    
}
