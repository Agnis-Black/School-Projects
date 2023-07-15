using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickUpItems : MonoBehaviour {
    // upon collider box trigger, refer to playersknapsack instance
    private void OnTriggerEnter(Collider other) {
        PlayerKnapSack playerKnapSack = other.GetComponent<PlayerKnapSack>();
        PlayerInput playerInput = other.GetComponent<PlayerComponent>();
        
        // makde contact with collider box of item, obtain item and deactivate from view
        if (playerKnapSack != null) {
            playerKnapSack.itemsObtained();
            gameObject.SetActive(false);
        }
    }
}