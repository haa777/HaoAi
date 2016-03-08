<?php 
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname="cardb";


	$conn= new mysqli($servername,$username,$password);
	if($conn->connect_error)
	{
		die("Connectin Failed:".$conn->connect_error);
	}
	echo "Connected succesfully";
 ?>

