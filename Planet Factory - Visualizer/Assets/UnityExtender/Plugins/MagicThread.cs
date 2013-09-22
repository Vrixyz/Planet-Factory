using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Threading;


public class BackgroundTask : YieldInstruction
{
};

public class ForegroundTask : YieldInstruction
{
};
	
public class MagicThread : MonoBehaviour
{
	
	static MagicThread _instance;

	static MagicThread instance {
		get {
			if (_instance == null) {
				_instance = new GameObject ("MagicThreads", typeof(MagicThread)).GetComponent<MagicThread> ();
				_instance.gameObject.hideFlags = HideFlags.HideAndDontSave;
			}
			return _instance;
		}
	}
	
	public static void Start (IEnumerator task)
	{
		instance.backgroundTasks.Add (task);
	}
	
	List<IEnumerator> foregroundTasks = new List<IEnumerator> ();
	List<IEnumerator> backgroundTasks = new List<IEnumerator> ();

	IEnumerator Start ()
	{
		while (true) {
			yield return null;
			if (foregroundTasks.Count > 0) {
				lock (foregroundTasks) {
					foreach (var i in foregroundTasks) {
						StartCoroutine (HandleCoroutine (i));	
					}
					foregroundTasks.Clear ();
				}
			}
			if (backgroundTasks.Count > 0) {
				foreach (var i in backgroundTasks) {
					ThreadPool.QueueUserWorkItem ((state) => {
						HandleThread (i); 
					});
				}
				backgroundTasks.Clear ();
			}
		}
	}
	
	IEnumerator HandleCoroutine (IEnumerator task)
	{
		while (task.MoveNext()) {
			var t = task.Current;
			if ((t as BackgroundTask) == null)
				yield return t;
			else {
				backgroundTasks.Add (task);
				yield break;
			}
		}
	}
	
	void HandleThread (IEnumerator task)
	{
		while (task.MoveNext()) {
			var t = task.Current;
			if ((t as ForegroundTask) != null) {
				lock (foregroundTasks) {
					foregroundTasks.Add (task);
				}
				break;
			}
		}
	}
	
	
}
