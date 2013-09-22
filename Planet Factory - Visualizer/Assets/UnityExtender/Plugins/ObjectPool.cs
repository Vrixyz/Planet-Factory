using System;

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

/// <summary>
/// Object pool. Used for recyling tather than Instantiate/Destroy.
/// </summary>
public class ObjectPool<T> where T : RecycledBehaviour
{
    List<T> freeObjects;
    HashSet<T> knownObjects;
    T prefab;

    /// <summary>
    /// Initializes a new object pool of prefabs.
    /// </summary>
    /// <param name='prefab'>
    /// Prefab.
    /// </param>
    /// <param name='count'>
    /// Count.
    /// </param>
    public ObjectPool (T prefab, int count)
    {
        this.prefab = prefab;
        freeObjects = new List<T> (count);
        knownObjects = new HashSet<T>();
        for (var i=0; i<count; i++) {
            var g = UnityEngine.Object.Instantiate (prefab) as T;
            g.SaveInitialState ();
            g.gameObject.SetActiveRecursively (false);
            freeObjects.Add (g);
            knownObjects.Add(g);
        }
    }

    /// <summary>
    /// Take an object from the pool and set the position and rotation.
    /// </summary>
    /// <param name='position'>
    /// Position.
    /// </param>
    /// <param name='rotation'>
    /// Rotation.
    /// </param>
    public T Take (Vector3 position, Quaternion rotation)
    {
        var g = Take ();
        g.transform.position = position;
        g.transform.rotation = rotation;
        return g;
    }

    /// <summary>
    /// Take an object from the pool.
    /// </summary>
    public T Take ()
    {
        T g;
        if (freeObjects.Count > 0) {
            g = freeObjects.Pop (0);
            g.gameObject.SetActiveRecursively (true);
        } else {
            g = UnityEngine.Object.Instantiate (prefab) as T;
            g.SaveInitialState ();
        }
        knownObjects.Remove(g);
        return g;
    }

    /// <summary>
    /// Place an object back into the pool.
    /// </summary>
    /// <param name='g'>
    /// G.
    /// </param>
    public void Recycle (T g)
    {
        if(knownObjects.Contains(g))
            throw new System.InvalidOperationException("Already Recycled");
        g.gameObject.SetActiveRecursively (false);
        g.RestoreInitialState ();
        freeObjects.Add (g);
        knownObjects.Add(g);
    }

    /// <summary>
    /// Place an object back into the pool after d seconds.
    /// </summary>
    /// <param name='g'>
    /// G.
    /// </param>
    /// <param name='d'>
    /// D.
    /// </param>
    public void Recycle (T g, float d)
    {
        g.StartCoroutine (_Free (g, d, null));
    }

    /// <summary>
    /// Place an object back into the pool after d seconds, then run an action.
    /// </summary>
    /// <param name='g'>
    /// G.
    /// </param>
    /// <param name='d'>
    /// D.
    /// </param>
    /// <param name='OnFree'>
    /// On free.
    /// </param>
    public void Recycle (T g, float d, System.Action OnFree)
    {
        g.StartCoroutine (_Free (g, d, OnFree));
    }

    IEnumerator _Free (T g, float d, System.Action OnFree)
    {
        yield return new WaitForSeconds(d);
        if(knownObjects.Contains(g))
            throw new System.InvalidOperationException("Already Recycled");
        g.gameObject.SetActiveRecursively (false);
        g.RestoreInitialState ();
        freeObjects.Add (g);
        knownObjects.Add(g);
        if (OnFree != null)
            OnFree ();
    }
    
}




