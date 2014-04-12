using UnityEngine;

[System.Serializable]
public class SGT_StarfieldStarVariant
{
	/*[SerializeField]*/
	private SGT_Starfield parent;
	
	[SerializeField]
	private float spawnProbability = 1.0f;
	
	[SerializeField]
	private bool custom;
	
	[SerializeField]
	private float customRadiusMin = 1.0f;
	
	[SerializeField]
	private float customRadiusMax = 3.0f;
	
	[SerializeField]
	private float customPulseRadiusMax = 1.0f;
	
	[SerializeField]
	private float customPulseRateMax = 1.0f;
	
	[SerializeField]
	private Vector2[] coords = new Vector2[4];
	
	[SerializeField]
	private Rect uv;
	
	public SGT_Starfield Parent
	{
		set
		{
			parent = value;
		}
		
		get
		{
			return parent;
		}
	}
	
	public float SpawnProbability
	{
		set
		{
			value = Mathf.Clamp01(value);
			
			if (value != spawnProbability)
			{
				spawnProbability = value;
				parent.Modified = true;
			}
		}
		
		get
		{
			return spawnProbability;
		}
	}
	
	public bool Custom
	{
		set
		{
			if (value != custom)
			{
				custom = value;
				parent.Modified = true;
			}
		}
		
		get
		{
			return custom;
		}
	}
	
	public float CustomRadiusMin
	{
		set
		{
			if (value != customRadiusMin)
			{
				customRadiusMin = value;
				parent.Modified = true;
			}
		}
		
		get
		{
			return customRadiusMin;
		}
	}
	
	public float CustomRadiusMax
	{
		set
		{
			if (value != customRadiusMax)
			{
				customRadiusMax = value;
				parent.Modified = true;
			}
		}
		
		get
		{
			return customRadiusMax;
		}
	}
	
	public float CustomPulseRadiusMax
	{
		set
		{
			if (value != customPulseRadiusMax)
			{
				customPulseRadiusMax = value;
				parent.Modified = true;
			}
		}
		
		get
		{
			return customPulseRadiusMax;
		}
	}
	
	public float CustomPulseRateMax
	{
		set
		{
			if (value != customPulseRateMax)
			{
				customPulseRateMax = value;
				parent.Modified  = true;
			}
		}
		
		get
		{
			return customPulseRateMax;
		}
	}
	
	public Vector2[] Coords
	{
		get
		{
			return coords;
		}
	}
	
	public Rect Uv
	{
		get
		{
			return uv;
		}
	}
	
	public void RecalculateCoords(int tx, int ty, int i)
	{
		var w = 1.0f / (float)tx;
		var h = 1.0f / (float)ty;
		var x = w * (i % tx);
		var y = h * (i / tx);
		
		coords[0] = new Vector2(x    , y + h);
		coords[1] = new Vector2(x + w, y + h);
		coords[2] = new Vector2(x    , y    );
		coords[3] = new Vector2(x + w, y    );
		
		uv = new Rect(x, y, w, h);
	}
}