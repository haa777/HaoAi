<?php
	$servername="localhost";
	$username="root";
	$password="";
	$dbname="cardb";
			
	$conn = new mysqli($servername, $username, $password, $dbname);
			
	if($conn->connect_error)
		die("connection failed: ".$conn->connect_error);
	else
		echo "Connected successfully";
				
	$id=$_POST['id'];
	$newacc=$_POST['newacc'];
	$sql = "UPDATE accidentHistory SET accidentNumber=$newacc WHERE carId=$id";
		
	if(mysqli_query($conn, $sql)){
		echo "Record updated successfully.";
	}
	else{
		echo "Error updating record: $sql " . mysqli_error($conn);
	}



	mysqli_close($conn);
?> 