using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class KnapSackUI : MonoBehaviour
{
    private TextMeshProUGUI itemText;
    // Start is called before the first frame update
    void Start(){
        itemText = GetComponent<TextMeshProUGUI>();
    }

    public void updateItemText(PlayerKnapSack playerKnapSack){
        itemText.text = "Items: " + playerKnapSack.items.Count.ToString();
    }
}
