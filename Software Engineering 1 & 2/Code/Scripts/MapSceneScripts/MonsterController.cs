using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterController : MonoBehaviour
{
    
    float interpolationFramesCount = 1000f;
    float damageInterval = 0.5f;
    int timeSinceLastDamage = 0;

    float elapsedFrames = 0f;
    int currentWaypoint = 1;
    public GameObject waypoints;
    GameObject start;
    GameObject end;
    public GameObject healthBar;

    const int MAX_DISTANCE_FROM_CHARACTER = 5;

    // TODO: should make player script to hold these values / functions to kill player
    public GameObject character;
    int playerHealth = 100;

    void Start(){
        start = waypoints.transform.Find(currentWaypoint.ToString()).gameObject;
        end = GameObject.Find((currentWaypoint+1).ToString()).gameObject;

        gameObject.transform.position = waypoints.transform.Find("1").transform.position;
        character.transform.position = new Vector3(0,10,0);
    }

    void moveOnPath(){
        float percentCompleted = elapsedFrames/interpolationFramesCount;
        Vector3 interpolatedPosition = Vector3.Lerp(start.transform.position, end.transform.position, percentCompleted);       

        if(elapsedFrames >= interpolationFramesCount){
            currentWaypoint++;

            if(waypoints.transform.childCount <= currentWaypoint){
                currentWaypoint = 1;
            }

            start = waypoints.transform.Find(currentWaypoint.ToString()).gameObject;
            end = GameObject.Find((currentWaypoint+1).ToString()).gameObject;

            elapsedFrames = 0;
        }
        else{  
            transform.position = interpolatedPosition;    
        }   
    }

    void attackCharacterIfClose(float distanceFromCharacter){
        if(distanceFromCharacter > MAX_DISTANCE_FROM_CHARACTER){return;}
        // damages player if theyre close enough every damageInterval
        if(timeSinceLastDamage > damageInterval){
            playerHealth -= 10; 
            timeSinceLastDamage = 0; 
            
            print("Player's health: " + playerHealth);

            // 'kills character'
            if(playerHealth <= 0){
                CharacterController cc = character.GetComponent<CharacterController>();
                cc.enabled = false;
                character.transform.position = new Vector3(0,10,0);
                cc.enabled = true;

                // reset players health
                playerHealth = 100;
            }

            healthBar.transform.localScale = new Vector3(playerHealth/100f, healthBar.transform.localScale.y, healthBar.transform.localScale.z);
        }
    }

    void setFocus(float distanceFromCharacter){
        Vector3 posToLookAt;

        if(distanceFromCharacter < MAX_DISTANCE_FROM_CHARACTER){
            posToLookAt = new Vector3( character.transform.position.x, transform.position.y,  character.transform.position.z);
        }
        else{
            posToLookAt = new Vector3(end.transform.position.x, transform.position.y, end.transform.position.z);
        }
        transform.LookAt(posToLookAt);
    }

    void Update(){
        timeSinceLastDamage += 1;
        elapsedFrames += 1;
        float distanceFromCharacter = (transform.position - character.transform.position).magnitude;

        moveOnPath();
        setFocus(distanceFromCharacter);
        attackCharacterIfClose(distanceFromCharacter);
    }
}
