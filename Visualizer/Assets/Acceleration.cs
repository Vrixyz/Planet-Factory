using UnityEngine;
using System.Collections;
using System.Diagnostics;

public class Acceleration : MonoBehaviour {
	
	public GameObject manager;
	public GameObject boutonPlay;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void OnClick () {
		UniverseTime w = manager.GetComponent<UniverseTime>();
		w.Acc();
		
	}
}
