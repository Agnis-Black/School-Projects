using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Objectives : MonoBehaviour
{
    //public int itemLimit;
    public GameOver gameOverCondition;
    public PlayerKnapSack playerKnapSack;
    // Start is called before the first frame update
    void Start()
    {
        playerKnapSack = GetComponent<PlayerKnapSack>();
    }

    // Update is called once per frame
    void Update()
    {
        // check knapsackweight from playerknapsack against value
        if (playerKnapSack.KnapSackWeight >= 13) {
            gameOverCondition.Win();
        }
    }

}
