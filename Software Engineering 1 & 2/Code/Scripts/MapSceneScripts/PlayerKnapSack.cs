using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class PlayerKnapSack : MonoBehaviour{
    public delegate void PickUp();
    public static event PickUp OnItemPickedUp;

     // singleton design pattern
    public static PlayerKnapSack Instance;

    // keep a list of all items in knapsack
    public List<Item> items = new List<Item>();

    //public int ItemWeight {get; private set;}
    public int KnapSackWeight {get; private set;}
    public UnityEvent<PlayerKnapSack> OnItemCollected;
    
    // loads the class instance
    public void Awake() {
        Instance = this;
    }

    // TODO : When interacting with item, check if item can be picked up
    public void checkKnapSackLimit() {

    }
  
    // increase inventory count when picking up item
    public void add(Item item) {
        items.Add(item);
        // Debug.Log("item obtained");
        // take item weight from an item that is of the item scriptable script
        KnapSackWeight += item.weight;
        Debug.Log("Knapsack weight:" + KnapSackWeight);
        
        // callback to PlayerKnapSnack when event triggered
        OnItemCollected.Invoke(this);
        OnItemPickedUp();
    }

}