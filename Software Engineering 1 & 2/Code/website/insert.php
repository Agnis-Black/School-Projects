<?php
$username = $_POST['username'];
$email = $_POST['email'];
$password = $_POST['password'];

if(!empty($username) || !empty($email) || !empty($password) ) {
   $host = "localhost";
   $dbUsername = "root";
   $dbPassword = "";
   $dbname = "accountinfo"

   $conn = new mysqli($host,$dbUsername,$dbPassword,$dbname);

   if(mysqli_connect_error()) {
		  die('Connect Error('. mysqli_connect_errno().')'.mysqli_connect_error());
   } else {
		  $SELECT = "SELECT email From account Where email = ? Limit 1";
		  $INSERT = "INSERT Into account (username, email, password) values(?,?,?)";

		  $stmt = $conn->prepare($SELECT);
		  $stmt -> bind_param("s",$email);
		  $stmt -> execute();
		  $stmt -> bind_result($email);
		  $stmt ->store_result();
		  $rnum = $stmt->num_rows;

		  if($rnum==0){
				$stmt->close();
				$stmt = $conn->prepare($INSERT);
				$stmt->bind_param($username,$email,$password);
				$stmt->execute();
				echo "New record inserted sucessfully";
		  } else {
				echo "Someone already registered using this email";
		  }
		  $stmt->close();
		  $conn->close();

   }

} else {
	echo "All fields are required";
	die();
}
?>