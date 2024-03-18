/**
*
* @author	Zidan Omar Hamid | zidanomar.hamid@ogr.sakarya.edu.tr
* @since	March 12, 2024
* <p>
* Main Class
* </p>
*/

package main;

import java.io.File;
import java.util.Iterator;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		String cwd = System.getProperty("user.dir");
		String destinationPath = cwd + File.separator + "public";
		File workingDir = new File(destinationPath);

		try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("Enter Git repository URL: ");
			String repoURL = scanner.nextLine().trim();

			try {
				FileUtility.cloneRepository(repoURL, workingDir);
				FileUtility.processFiles(workingDir);
			} catch (Exception e) {
				System.err.println("Error cloning repository: " + e.getMessage());

				exitProgram();
			}
		}

	}

	public static void exitProgram() throws InterruptedException {
		for (int i = 3; i < 0; i--) {
			System.err.println("Exiting program in " + i + "s...");
			Thread.sleep(1000);
		}
		
		System.exit(1);
	}

}
