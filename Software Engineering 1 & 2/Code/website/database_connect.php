// references : The Net Ninja : PHP Tutorial PHP Tutorial (& MySQL) #24,25,26

<?php 
	// set connection to database
	$conn = mysqli_connect('localhost', 'alberto', 'silentspaces', 'silent spaces');

	// warns you when error connecting to database occurs
	if(!$conn) {
		echo 'Connection error: ' . mysqli_connect_error();
	}

	// refer to CS 341 Project 1,2 for refresher
	//

	// query to get data
	$sql = 'SELECT * FROM locations';

	$result = mysqli_query($conn, $sql);

	// gets data in an associative array
	$locations = mysqli_fetch_all($result, MYSQLI_ASSOC);

	print_r($locations)


?>
