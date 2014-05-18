using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class TextureGenerator : MonoBehaviour {
	//PlanetUpdater pU;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public static Texture2D generate(Dictionary<string, Texture2D> mat_textures, Dictionary<string, object> mat_def)
	{
		print ("generating a texture...");
		Texture2D newText = null;
        print("number of textures : " + mat_textures.Count);
		foreach (var v in mat_textures)
		{
            print("blending one material: " + v.Key);
			if (v.Value == null)
			{
				print ("one map hadn't loaded properly");
				continue;
			}
            if (newText == null)
            {
                newText = new Texture2D(v.Value.width, v.Value.height, TextureFormat.ARGB32, false);
                for (int x = 0; x < newText.width; x++)
                    for (int y = 0; y < newText.height; y++)
                        newText.SetPixel(x, y, new Color(0, 0, 0));
                newText.Apply();
                //return newText;
            }
            Texture2D toMix = v.Value;
            print("painting : " + v.Key);
			Dictionary<string, object> current_mat_def = mat_def[v.Key] as Dictionary<string, object>;
			print (current_mat_def["minColor"]);
			print (current_mat_def["maxColor"]);
			print("width : " + newText.width);
			print("height : " + newText.height);

            Dictionary<string, object> colorToMix = current_mat_def["maxColor"] as Dictionary<string, object>;
            int red = (int)((long)(colorToMix["r"]));
            int green = (int)((long)(colorToMix["g"]));
            int blue = (int)((long)(colorToMix["b"]));
            print("color: " + red + " " + green + " " + blue);
            //newText.Apply();
            //return newText;
			for (int x = 0; x < newText.width; x++) {
				for (int y = 0; y < newText.height; y++)
				{

                    Color pixel = newText.GetPixel(x,y);

                    pixel.r += (v.Value.GetPixel(x,y).r / 255) * red;

                    pixel.g += (v.Value.GetPixel(x, y).g / 255) * green;
                    
                    pixel.b += (v.Value.GetPixel(x, y).b / 255) * blue;

                    newText.SetPixel(x,y, pixel);
					//print("pixel white");
				}
			}
            //newText.Apply();
            //return newText;
		}
        newText.Apply();
		return newText;
	}
}