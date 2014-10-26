using UnityEngine;
using System.Collections;
using System.Diagnostics;

public class Stop : MonoBehaviour {

	public GameObject manager;
    public GameObject slider;
    private float totalTime ;
    // Use this for initialization
	void Start () {
      
	}
	
	// Update is called once per frame
	void OnClick () {
		UniverseTime w = manager.GetComponent<UniverseTime>();
       	w.Reset();
       	w.Start();
		w.Stop();
		w.mult = 1;
	}
}
