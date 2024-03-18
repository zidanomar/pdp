/**
* @author	Zidan Omar Hamid | zidanomar.hamid@ogr.sakarya.edu.tr
* @since	March 17, 2024
* <p>
* File Utility Class
* </p>
*/
package main;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.eclipse.jgit.api.CloneCommand;
import org.eclipse.jgit.api.Git;

public class FileUtility {
	public static void processFiles(File directory) {
		File[] files = directory.listFiles();
		if (files != null) {
			for (File file : files) {
				if (file.isDirectory()) {
					processFiles(file);
				} else {
					if (file.getName().endsWith(".java") && containsClassDefinition(file)) {
						CodeAnalyzer codeAnalyzer = new CodeAnalyzer(file);
						codeAnalyzer.printStatistics();
					}
				}
			}
		}
	}

	private static boolean containsClassDefinition(File file) {
		try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
			Pattern classPattern = Pattern.compile("\\bclass\\s+\\w+\\b");
			String line;
			while ((line = reader.readLine()) != null) {
				Matcher matcher = classPattern.matcher(line);
				if (matcher.find()) {
					return true;
				}
			}
		} catch (IOException e) {
			System.err.println("Error reading file: " + e.getMessage());
		}
		return false;
	}

	public static void cloneRepository(String repoURL, File destinationPath) throws Exception {
		System.out.println("Validating url...");
		validateRepoUrl(repoURL);
		
		System.out.println("Cleaning up working destination directory...");
		if (destinationPath.exists()) {
			if (!deleteFolder(destinationPath)) {
				throw new Exception("Failed to delete existing destination folder, administrator required");
			}
		}

		System.out.println("Clonning repository...");

		CloneCommand cloneCommand = Git.cloneRepository().setURI(repoURL).setDirectory(destinationPath);
		try (Git git = cloneCommand.call()) {
			System.out.println("Repository cloned successfully!");
		}
	}

	public static boolean deleteFolder(File folder) {
		File[] files = folder.listFiles();
		if (files != null) {
			for (File file : files) {
				if (file.isDirectory()) {
					deleteFolder(file);
				} else {
					if (!file.delete()) {
						return false; // Unable to delete file
					}
				}
			}
		}
		return folder.delete(); // Delete the empty directory
	}

	public static void validateRepoUrl(String url) throws Exception {
		String repoUrlPattern = "^(?:https?://|git@)?(?:[\\w.]+[:/])*(?:[\\w.-]+/[\\w.-]+|[\\w.-]+)\\.git$";

		if (url == null || url.isBlank()) {
			throw new Exception("Invalid Git repository URL");
		}
		Pattern pattern = Pattern.compile(repoUrlPattern);
		Matcher matcher = pattern.matcher(url);

		if (!matcher.matches())
			throw new Exception("Invalid Git repository URL");
	}

}
