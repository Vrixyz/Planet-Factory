//----------------------------------------------
//            NGUI: Next-Gen UI kit
// Copyright © 2011-2013 Tasharen Entertainment
//----------------------------------------------

using UnityEngine;

/// <summary>
/// Very basic script that will activate or deactivate an object (and all of its children) when clicked.
/// </summary>

[AddComponentMenu("NGUI/Interaction/Button Activate")]
public class FileBroswer : MonoBehaviour
{
	public string message = "";
	public float alpha = 1.0f;
	public char pathChar = '/';
	public GameObject controler;
	
	private SystemLoader sysLoader;

	void Start () {
		if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer) {
			pathChar = '\\';
		}
	}
	
	void OnClick () {
		UniFileBrowser.use.OpenFileWindow (OpenFile);
	}
	
	void OpenFile (string pathToFile) {
		var fileIndex = pathToFile.LastIndexOf (pathChar);
		message = "You selected file: " + pathToFile.Substring (fileIndex+1, pathToFile.Length-fileIndex-1);
		controler.SetActive(true);
		controler.animation.Play();
	
		GameObject g = GameObject.Find ("Manager");
        sysLoader = SystemLoader.getInstance();
		sysLoader.rootFolder = pathToFile.Substring (0, fileIndex + 1);
		var index = sysLoader.rootFolder.LastIndexOf ("Resources") + 10;
		string folder = sysLoader.rootFolder.Substring(index, sysLoader.rootFolder.Length - index);
		folder = folder.Replace ('\\', '/');
		sysLoader.resourceFolder = folder;
		sysLoader.initialize ();
	}
	
}