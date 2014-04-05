﻿using UnityEngine;
using System.Collections;

public class RayCastToPlanets : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetButton("Fire1")) {
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);
			RaycastHit hit;

			// TODO: singletooon !
			GameObject manager = GameObject.Find ("Manager");
			SystemLoader sys = (SystemLoader)manager.GetComponent ("SystemLoader");
			Collider planetCollider = ((GameObject)sys.planets [0]).collider;

			if (planetCollider.Raycast (ray, out hit, 1000.0f)) {
				{
					//Debug.DrawLine (ray.origin, hit.point);
					//print ("hit! ");
					Vector2 textureCoord = hit.textureCoord;
					PlanetUpdater pu = ((GameObject)sys.planets [0]).GetComponent<PlanetUpdater>();
					textureCoord.x *= pu.materials["rock"].width;
					textureCoord.y *= pu.materials["rock"].height;
					//print(hit.textureCoord);
					print (pu.materials["rock"].GetPixel((int)textureCoord.x, (int)textureCoord.y));
				}
			
			}
		}	
	}
}
