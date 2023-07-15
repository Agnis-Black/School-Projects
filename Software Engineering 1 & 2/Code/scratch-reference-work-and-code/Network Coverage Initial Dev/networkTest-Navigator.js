/* FIRST APPROACH ------------------------------------------------------------------
(self-produced code following the guide from the reference below)
Reference: https://usefulangle.com/post/171/javascript-get-network-information

This code snippet utilizes the Mozilla Network Information API to gather the network
speeds of the user. However, it doesn't give the user a download speed, rather a
Downlink speed (description below about the difference). It may be useful to use this
to just categorize the Effective Type of the Network ('slow-2g', '2g', '3g', '4g')
[see https://developer.mozilla.org/en-US/docs/Web/API/NetworkInformation/effectiveType
for more information]. 

*/

if (!navigator.connection) {
    console.log("Network Connection is not supported by this browser.");
}    

var connection = navigator.connection;
var effective_type = connection.effectiveType;
var downlink = navigator.connection.downlink;

/* SECOND APPROACH -----------------------------------------------------------------
(copied example for testing purposes from the reference below)
Reference: https://www.geeksforgeeks.org/how-to-detect-network-speed-using-javascript/

This code snippet downloads the image noted from the link below and as the end of the
download action is assigned to activate when the image downloading is completed. 
The code then calculates the speed of the download process. 

Notes:
    As I ran this code, the Mbps number seems to be extremely high- not sure if it is
    accurate. I am getting download speeds to 10.7 Gbps, while if I run the Ookla Speed
    Test (speedtest.net) I get download speeds of 127.44 Mbps. I think the Ookla test
    and SpeedTest-CLI API is more accuate & reliable.
*/

var userImageLink = "https://media.geeksforgeeks.org/wp-content/cdn-uploads/20200714180638/CIP_Launch-banner.png";
var time_start, end_time;
            
// size in bytes
var downloadSize = 5616998;
var downloadImgSrc = new Image();

downloadImgSrc.onload = function () {
    end_time = new Date().getTime();
    displaySpeed();
};

time_start = new Date().getTime();
downloadImgSrc.src = userImageLink;

function displaySpeed() {
    var timeDuration = (end_time - time_start) / 1000;
    var loadedBits = downloadSize * 8;
    
    /* Converts a number into string using toFixed(2) rounding to 2 */
    var bps = (loadedBits / timeDuration).toFixed(2);
    var speedInKbps = (bps / 1024).toFixed(2);
    var speedInMbps = (speedInKbps / 1024).toFixed(2);

    // Updates the HTML of 'testpage.html' to display the results of both approaches.
    document.body.innerHTML = 
                            // First Approach using the Network Information API
                            "<h1>First Approach: Network Information API</h1>" +
                            "<h2>Speed Type: " + effective_type + 
                            "</h2> <h2>Downlink: " + downlink + 
                                // Note from the first approach (about "downlink")
                            "</h2><p>Note (from website): Downlink speed is different from" + 
                            " download speed. It represents the connection speed between your" + 
                            " device and the network connection device. Example, in case of a WiFi" +
                            " it represents the speed between your device and the WiFi router, which" +
                            " is different from the actual download speed that you get when you download a file.</p>" +
                            // Second Approach using the GeeksForGeeks code
                            "<br><h1>Second Approach</h1>" +
                            "<h2>Your internet connection speed is: " +
                            bps + " bps</p><p>" + speedInKbps + " kbps</p><p>" + speedInMbps + " Mbps</h2>"
}
