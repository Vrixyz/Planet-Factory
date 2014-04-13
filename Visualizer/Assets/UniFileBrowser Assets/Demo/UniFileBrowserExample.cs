// Example of open/save usage with UniFileBrowser
// This script is free to use in any manner

using UnityEngine;
using System.Collections;

public class UniFileBrowserExample : MonoBehaviour {
	
	string message = "";
	float alpha = 1.0f;
	char pathChar = '/';
	
	void Start () {
		if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer) {
			pathChar = '\\';
		}
	}
	
	void OnMouseDown () {
		UniFileBrowser.use.OpenFileWindow (OpenFile);
	}
	
	void OpenFile (string pathToFile) {
		var fileIndex = pathToFile.LastIndexOf (pathChar);
		message = "You selected file: " + pathToFile.Substring (fileIndex+1, pathToFile.Length-fileIndex-1);
		Fade();
	}
	
	void OpenFiles (string[] pathsToFiles) {
		message = "You selected these files:\n";
		for (var i = 0; i < pathsToFiles.Length; i++) {
			var fileIndex = pathsToFiles[i].LastIndexOf (pathChar);
			message += pathsToFiles[i].Substring (fileIndex+1, pathsToFiles[i].Length-fileIndex-1) + "\n";
		}
		Fade();
	}
	
	void SaveFile (string pathToFile) {
		var fileIndex = pathToFile.LastIndexOf (pathChar);
		message = "You're saving file: " + pathToFile.Substring (fileIndex+1, pathToFile.Length-fileIndex-1);
		Fade();
	}
	
	void OpenFolder (string pathToFolder) {
		message = "You selected folder: " + pathToFolder;
		Fade();
	}
	
	void Fade () {
		StopCoroutine ("FadeAlpha");	// Interrupt FadeAlpha if it's already running, so only one instance at a time can run
		StartCoroutine ("FadeAlpha");
	}
	
	IEnumerator FadeAlpha () {
		alpha = 1.0f;
		yield return new WaitForSeconds (5.0f);
		for (alpha = 1.0f; alpha > 0.0f; alpha -= Time.deltaTime/4) {
			 yield return null;
		}
		message = "";
	}
}