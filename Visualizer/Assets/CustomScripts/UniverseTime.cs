﻿using UnityEngine;
using System.Diagnostics;
using System.Collections;

public class UniverseTime : MonoBehaviour {
	public Stopwatch timer = Stopwatch.StartNew ();

	// Use this for initialization
	void Start () {
		reset ();
		timer.Start ();
	}

	void reset() {
		timer.Stop ();
		timer.Reset ();
	}
	// Update is called once per frame
	void Update () {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (timer.IsRunning)
            {
                print("Stop !");
                timer.Stop();
            }
            else
            {
                print("Start !");
                timer.Start();
            }
        }
	}
}