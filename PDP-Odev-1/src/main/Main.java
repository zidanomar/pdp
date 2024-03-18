/**
* @author	Zidan Omar Hamid | zidanomar.hamid@ogr.sakarya.edu.tr
* @since	March 12, 2024
* <p>
* Main Class
* </p>
*/

package main;

import java.io.File;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		long timestamp = System.currentTimeMillis();
		String cwd = System.getProperty("user.dir");
		String path = Paths.get(cwd, "public", String.valueOf(timestamp)).toString();
		File workingDir = new File(path);

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

		FileUtility.deleteFolder(workingDir);

	}

	public static void exitProgram() {
		for (int i = 3; i > 0; i--) {
			System.err.println("Exiting program in " + i + "s...");
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// Ignore interruption
			}

		}
		System.exit(1);
	}

}
