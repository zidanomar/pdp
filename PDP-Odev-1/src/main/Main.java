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
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

	public static void main(String[] args) {
		long timestamp = System.currentTimeMillis();
		String cwd = System.getProperty("user.dir");
		String path = Paths.get(cwd, "public", String.valueOf(timestamp)).toString();
		File workingDir = new File(path);

		boolean isValidURL = false;
		String repoURL = null;

		try (Scanner scanner = new Scanner(System.in)) {
            while (!isValidURL) {
                System.out.print("Enter Git repository URL: ");
                repoURL = scanner.nextLine().trim();
                isValidURL = validateRepoUrl(repoURL);
                if (!isValidURL) {
                    System.out.println("Invalid URL. Please try again.");
                }
            }
        }

		try {
			FileUtility.cloneRepository(repoURL, workingDir);
			FileUtility.processFiles(workingDir);
		} catch (Exception e) {
			System.err.println("Error cloning repository: " + e.getMessage());
			exitProgram();
		}

		FileUtility.deleteFolder(workingDir);

	}
	
	public static boolean validateRepoUrl(String url)  {
		String repoUrlPattern = "^(?:https?://|git@)?(?:[\\w.]+[:/])*(?:[\\w.-]+/[\\w.-]+|[\\w.-]+)\\.git$";

		if (url == null || url.isBlank()) {
			return false;
		}
		Pattern pattern = Pattern.compile(repoUrlPattern);
		Matcher matcher = pattern.matcher(url);

		if (!matcher.matches())
			return false;
		
		return true;
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
