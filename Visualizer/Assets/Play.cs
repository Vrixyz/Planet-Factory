using UnityEngine;
using System.Collections;
using System.Diagnostics;

public class Play : MonoBehaviour {

    public GameObject manager;

    // Use this for initialization
	void Start () {
      
	}
	
	// Update is called once per frame
	void OnClick () {
		UniverseTime w = manager.GetComponent<UniverseTime>();
        w.Start();
	}
}
