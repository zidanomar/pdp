/**
*
* @author	Zidan Omar Hamid | zidanomar.hamid@ogr.sakarya.edu.tr
* @since	March 12, 2024
* <p>
* Encapsulate metrics of data from java file that being read such as line of code, etc.
* </p>
*/

package main;

public class Statistics {
	private String className;
    private int javadocLines; // Javadoc olarak yorum satır sayısı
    private int commentLines; // Diğer yorumlar satır sayısı
    private int codeLines; // Kod satır sayısı
    private int totalLine; // Bir dosyadaki her şey dahil satır sayısı
    private int functionCount; // Fonksiyon Sayısı (Sınıfın içinde bulunan tüm fonksiyonların toplam sayısı)
    private double commentDeviation; // Yorum Sapma Yüzdesi (Yazılması gereken yorum satır sayısı yüzdelik olarak ne kadar sapmış)
    
    public Statistics(String className, int javadocLines, int commentLines, int codeLines,
        int totalLine, int functionCount, double commentDeviation) {
    	this.className = className;
		this.javadocLines = javadocLines;
		this.commentLines = commentLines;
		this.codeLines = codeLines;
		this.totalLine = totalLine;
		this.functionCount = functionCount;
		this.commentDeviation = commentDeviation;
	}
    
    public String getClassName() {
    	return className;
    }
    
    public int getJavadocLines() {
        return javadocLines;
    }

    public int getCommentLines() {
        return commentLines;
    }

    public int getCodeLines() {
        return codeLines;
    }

    public int getTotalLine() {
        return totalLine;
    }

    public int getFunctionCount() {
        return functionCount;
    }

    public double getCommentDeviation() {
        return commentDeviation;
    }

}
