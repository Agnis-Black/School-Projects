using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// refer to https://docs.unity3d.com/Manual/class-ScriptableObject.html

[CreateAssetMenu(fileName = "Item", menuName = "Knapsack Item", order = 1)]
public class Item : ScriptableObject
{
   public int weight;
   public string itemName;

   // You can use this to have image for each item in UI
   public Sprite img;
   // Assign gameobject
   public GameObject prefab;
}