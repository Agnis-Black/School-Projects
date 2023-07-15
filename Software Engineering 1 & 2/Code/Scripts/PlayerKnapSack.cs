using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class PlayerKnapSack : MonoBehaviour{
    // value to keep track of items
    public int ItemsInSack {get; private set;}
    public int KnapSackWeight {get; private set;}
    public UnityEvent<PlayerKnapSack> OnItemCollected;

    // increase inventory count when picking up item
    public void itemsObtained() {
        ItemsInSack++;
        Debug.Log("item obtained");
        //KnapSackWeight += ItemOneWeight;
        Debug.Log("Knapsack weight:" + KnapSackWeight);
        OnItemCollected.Invoke(this);
    }
    
}
