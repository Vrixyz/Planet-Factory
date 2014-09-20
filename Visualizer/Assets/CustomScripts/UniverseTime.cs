using UnityEngine;
using System.Diagnostics;
using System.Collections;

public class UniverseTime : MonoBehaviour {
	public float totalTime = 10.0f; // in seconds
	private bool running = false;
	private float elapsed = 0.0f; // in seconds
	private float mult = 1;
	// Use this for initialization
	public void Start () {
		running = true;
	}
	public void Stop () {
		running = false;
	}

	public void Acc () {
		if (mult >= 8)
			return;
		mult += 2;
	}

	public void Desc () {
		if (mult <= -8)
			return;
		mult -= 2;
	}

	public bool IsRunning () {
		return running;
	}
	
	public void Reset() {
		elapsed = 0.0f;
	}
	
	public void setElapsed(float e)
	{
		elapsed = e;
	}
	public float getElapsed()
	{
		return elapsed;
	}
	
	// Update is called once per frame
	void Update () {
		//print ("time.deltatime: " + Time.deltaTime);
		if (running && elapsed <= totalTime)
		{
			if (mult < 0)
				elapsed += Time.deltaTime / (mult*(-1));
			else
				elapsed += Time.deltaTime * mult;
		}
		else
		{
			running = false;
			return;
		}
		if (Input.GetKeyDown(KeyCode.Space))
		{
			if (running)
			{
				print("Stop !");
				running = false;
			}
			else
			{
				print("Start !");
				running = true;
			}
		}
	}
}