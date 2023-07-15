using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.Events;

public class InventoryUI : MonoBehaviour
{
    public Button  unequipAllButton;
    public GameObject equipedText;
    public GameObject inventoryTemplate;
    GameObject player;
    List<Item> knapsackItems;

    // <equip button, item>
    Dictionary<GameObject, Item> itemsBeingHeld = new Dictionary<GameObject, Item>();

    // <item frame, item>
    Dictionary<GameObject, Item> itemsInInventorySlots = new Dictionary<GameObject, Item>();

    const int NUM_ITEMS = 9;

    void createInventoryItem(float x, float y, string name){
        GameObject newInventoryItem = GameObject.Instantiate(
            inventoryTemplate, 
            new Vector3(0,0,0),
            new Quaternion(0f, 0f, 0f, 0f), 
            inventoryTemplate.transform.parent.transform.Find("Frames")
        );
        newInventoryItem.name = name;
        newInventoryItem.SetActive(false);
        newInventoryItem.GetComponent<RectTransform>().anchoredPosition = new Vector3(x,y,0);

        Button equipButton = newInventoryItem.transform.Find("equipButton").gameObject.GetComponent<Button>();
        Button dropButton = newInventoryItem.transform.Find("dropButton").gameObject.GetComponent<Button>();

        equipButton.onClick.AddListener(() => onEquipButtonPressed(newInventoryItem, equipButton));
        dropButton.onClick.AddListener(() => onRemoveButtonPressed(newInventoryItem, equipButton, dropButton));
        unequipAllButton.onClick.AddListener(() => onUnEquipAllButtonPressed());
    }


    void onUnEquipAllButtonPressed(){
        foreach(var entry in new Dictionary<GameObject, Item>(itemsBeingHeld)){            
            Button equipBtn = entry.Key.transform.parent.transform.Find("equipButton").gameObject.GetComponent<Button>();
            onEquipButtonPressed(entry.Key, equipBtn);
        }
    }

    void onEquipButtonPressed(GameObject inventoryItem, Button equipButton){
        if(equipButton.GetComponentInChildren<TMP_Text>().text == "Equip"){
            equipButton.GetComponentInChildren<TMP_Text>().text = "Unequip";
        }
        else{
            equipButton.GetComponentInChildren<TMP_Text>().text = "Equip";
        }

        GameObject itemFrame = equipButton.transform.parent.gameObject;

        Item knapsackItem = itemsInInventorySlots[itemFrame];
        Item outItem; 

        bool gotItem = itemsBeingHeld.TryGetValue(equipButton.gameObject, out outItem);

        if (!gotItem) {
            itemsBeingHeld.Add(equipButton.gameObject, knapsackItem);
        } 
        else{
            itemsBeingHeld.Remove(equipButton.gameObject);
        }

        TextMeshProUGUI equipTMP = equipedText.GetComponent<TextMeshProUGUI>(); 
        string builtStr = "Items Equiped:\n";
        
        foreach(KeyValuePair<GameObject, Item> entry in itemsBeingHeld){
            builtStr += ("- " + entry.Value.itemName + "\n");
        }

        equipTMP.text = itemsBeingHeld.Count > 0 ? builtStr : "Equiped Items: None";
    }

    void onRemoveButtonPressed(GameObject inventoryItem, Button equipButton, Button dropButton){
        inventoryItem.transform.Find("itemNameText").gameObject.GetComponent<TMP_Text>().text = "No item";
        equipButton.GetComponentInChildren<TMP_Text>().text = "Equip";
        equipButton.gameObject.SetActive(false);
        dropButton.gameObject.SetActive(false);
    }

    void initInventoryItems(int MAX_NUM_ITEMS){
        var rectTransform = inventoryTemplate.GetComponent<RectTransform>();

        float windowWidth = rectTransform.sizeDelta.x;
        float windowHeight = rectTransform.sizeDelta.y;

        float templateXSize = inventoryTemplate.transform.localScale.x * windowWidth;
        float templateYSize = inventoryTemplate.transform.localScale.y * windowHeight;
        float padding = (float)(.15*templateXSize);

        int rowNum = 0;
        int ITEMS_PER_ROW = 3; 
        int numRows = (MAX_NUM_ITEMS/ITEMS_PER_ROW);

        float leftSpace =  windowWidth - ((ITEMS_PER_ROW*templateXSize) + (ITEMS_PER_ROW*padding));
        float bottomSpace =  windowHeight - ((numRows*templateYSize) + ((numRows-1)*padding));

        for(int i = 0; i < MAX_NUM_ITEMS; i++){
            int posInRow = i%ITEMS_PER_ROW;

            if(i%ITEMS_PER_ROW ==0  && i != 0){
                rowNum++;
            }

            float xPos = ((templateXSize*posInRow) + ((posInRow)*padding)) + (leftSpace / 2);
            float yPos =  (rowNum * -templateYSize) - (rowNum*padding) - (bottomSpace / 2);

            createInventoryItem(xPos,yPos, i+"");  
        }
    }

    void refreshInventoryUI(){
        for(int i = 0; i < NUM_ITEMS; i++){
            GameObject inventoryFrame = inventoryTemplate.transform.parent.transform.Find("Frames").gameObject;
            GameObject itemFrame = inventoryFrame.transform.Find(i+"").gameObject;

            if(i < knapsackItems.Count){
                TextMeshProUGUI knapItemText = itemFrame.transform.Find("itemNameText").GetComponent<TextMeshProUGUI>(); 
                itemFrame.SetActive(true);
                
                Item currItem = knapsackItems[i];
                knapItemText.text = currItem.itemName;

                itemFrame.transform.Find("ItemImage").gameObject.GetComponent<Image>().sprite = currItem.img;
                itemFrame.transform.Find("weightText").gameObject.GetComponent<TextMeshProUGUI>().text = "weight: " + currItem.weight;

                Item item;
                bool gotItem = itemsInInventorySlots.TryGetValue(itemFrame, out item);

                if(!gotItem){
                    itemsInInventorySlots.Add(itemFrame, currItem);
                }
            } else {
               itemFrame.SetActive(false);
            }
        }
    }

    void Start(){
        
        itemsBeingHeld = new Dictionary<GameObject, Item>();
        itemsInInventorySlots = new Dictionary<GameObject, Item>();
        
        player = GameObject.FindGameObjectsWithTag("Player")[0];
        knapsackItems = player.GetComponent<PlayerKnapSack>().items;
        
        PlayerKnapSack.OnItemPickedUp += refreshInventoryUI;
        
        inventoryTemplate.SetActive(false);

        initInventoryItems(NUM_ITEMS);
        refreshInventoryUI();
    }

    void Update(){
        
    }
}
