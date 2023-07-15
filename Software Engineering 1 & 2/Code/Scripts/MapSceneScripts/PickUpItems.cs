using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PickUpItems : MonoBehaviour {
    // upon collider box trigger, refer to playersknapsack instance
    private PlayerKnapSack playerKnapSack;
    // allows you to assign scritptable item object
    public Item item;

    private void OnTriggerEnter(Collider other) {
        var keyboard = Keyboard.current;

        print("aaaa");
        // gets the playerknapsack component of the player when colliding
        playerKnapSack = other.GetComponent<PlayerKnapSack>();
        // gets the item component of the object when colliding
        // Item = other.GetComponent<Item>();
        // PlayerInput playerInput = other.GetComponent<PlayerComponent>();
        
        if (playerKnapSack != null && keyboard.eKey.wasPressedThisFrame) {
            playerKnapSack.add(item);
            gameObject.SetActive(false);
        } 
    }

    void Update(){
         // incorporate keyboard press
        var keyboard = Keyboard.current;

        if (keyboard == null) {
            return; 
        }

        // make contact with collider box of item, obtain item and deactivate from view
        if (playerKnapSack && keyboard.eKey.wasPressedThisFrame){
            // TODO: when to check for knapsack weight limit before adding an item
            // pseduo below
            //          if checkknapsackweight is over not limit
            //          then add item to knapsack inventory
            //          update item was obtained
            playerKnapSack.add(item);
            gameObject.SetActive(false);
        } 
    }
}