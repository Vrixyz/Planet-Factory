﻿using UnityEngine;
using UnityEngine;
using System.Collections;

public class RayCastToPlanets : MonoBehaviour {
	public GameObject controler;
	private UILabel[] labels;
	private UIPopupList[] pops;
	// Use this for initialization
	void Start () {
		
	}
	
	
	void ShowInformations(float x, float y, PlanetUpdater pu) {
		labels = controler.GetComponentsInChildren<UILabel>();
		UILabel b = labels.Get(2);
		b.text = x.ToString() + "," + y.ToString();
		
		pops = controler.GetComponentsInChildren<UIPopupList>();
		UIPopupList p = pops.Get(0);
		
		
		//creation de la fenetre dynamic
		b = labels.Get(1);
		p.items.Clear();
		foreach (var t in pu.materials)
			p.items.Add(t.Key);
		p.selection = "Rock";
		foreach (var t in pu.materials)
		{
			b = labels.Get(3);
			Color c = ((Texture2D)t.Value).GetPixel ((int)x, (int)y);
			b.text = t.Key + " : " + ((int)((c.r + c.g + c.b) / 3 * 100)).ToString() + 'p';
			return;
		}
		
	}
	

	// Update is called once per frame
	void Update () {
		if (Input.GetButton("Fire1")) {
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);
			RaycastHit hit;
			
			// TODO: singletooon !
			GameObject manager = GameObject.Find ("Manager");
			SystemLoader sys = (SystemLoader)manager.GetComponent ("SystemLoader");
			if (controler.activeInHierarchy){
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
						if (controler.activeInHierarchy)
							ShowInformations(Input.mousePosition.x, Input.mousePosition.y, pu);
					}
				}
			}
		}	
	}
}

