using UnityEngine;
using System.Collections.Generic;

public abstract class SGT_MonoBehaviourUnique<T> : SGT_MonoBehaviour
    where T : SGT_MonoBehaviourUnique<T>
{
    public enum AwakeState
    {
        AwakeOriginal,
        AwakeDuplicate,
        AwakeAgain
    }
    
    /*[SerializeField]*/
    private static HashSet<T> instances = new HashSet<T>();
    
    /*[SerializeField]*/
    private static int highestUid;
    
    [SerializeField]
    private bool awoken;
    
    [SerializeField]
    private int uid;
    
    protected virtual void Start()
    {
        Check();
    }
    
    protected virtual void OnDestroy()
    {
        instances.Remove((T)this);
    }
    
    protected AwakeState FindAwakeState()
    {
        Check();
        
        if (awoken == false)
        {
            awoken = true;
            
            return AwakeState.AwakeOriginal;
        }
        
        return ThisHasBeenDuplicated() == true ? AwakeState.AwakeDuplicate : AwakeState.AwakeAgain;
    }
    
    protected bool ThisHasBeenDuplicated()
    {
        Check();
        
        foreach (var instance in instances)
        {
            if (instance != this && instance.uid == uid)
            {
                uid = ++highestUid;
                
                return true;
            }
        }
        
        return false;
    }
    
    private void Check()
    {
        if (instances.Count == 0)
        {
            var allT = Object.FindObjectsOfType(typeof(T));
            
            foreach (var t in allT)
            {
                var instance = (T)t;
                
                if (instance.uid > highestUid)
                {
                    highestUid = uid;
                }
                
                instances.Add(instance);
            }
        }
        else
        {
            instances.Add((T)this);
        }
        
        if (uid == 0) uid = ++highestUid;
    }
}