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

//add data to the car table
$sql = "INSERT INTO car VALUES ('".$_POST['brand']."','".$_POST['year']."', '".$_POST['type']."','".$_POST['id']."')";
 
if($conn->query($sql) == TRUE)
		echo "New car sample create successfully: ".$sql."<br/>
		with id:".$conn->insert_id;
	else
		echo "Error with query: " .$sql."<br/>".$conn->error;

//add data to the table newOwner
$sql = "INSERT INTO newOwner VALUES ('".$_POST['newfname']."','".$_POST['newlname']."', '".$_POST['newcell']."','".$_POST['brand']."', '".$_POST['year']."', '".$_POST['type']."', '".$_POST['id']."')";

if($conn->query($sql) == TRUE)
		echo "New car sample create successfully: ".$sql."<br/>
		with id:".$conn->insert_id;
	else
		echo "Error with query: " .$sql."<br/>".$conn->error;

//add data to the table oldOwner
$sql = "INSERT INTO oldOwner VALUES ('".$_POST['oldfname']."','".$_POST['oldlname']."', '".$_POST['oldcell']."','".$_POST['brand']."', '".$_POST['year']."', '".$_POST['type']."', '".$_POST['id']."')";

if($conn->query($sql) == TRUE)
		echo "New car sample create successfully: ".$sql."<br/>
		with id:".$conn->insert_id;
	else
		echo "Error with query: " .$sql."<br/>".$conn->error;


//add data to the table carCondition
$sql = "INSERT INTO carCondition VALUES ('".$_POST['brand']."','".$_POST['year']."', '".$_POST['type']."','".$_POST['id']."', '".$_POST['condition']."')";

if($conn->query($sql) == TRUE)
		echo "New car sample create successfully: ".$sql."<br/>
		with id:".$conn->insert_id;
	else
		echo "Error with query: " .$sql."<br/>".$conn->error;

// add to acidentHistory
$sql = "INSERT INTO accidentHistory VALUES ('".$_POST['brand']."','".$_POST['type']."', '".$_POST['year']."','".$_POST['id']."', '".$_POST['condition']."', '".$_POST['accident']."')";


	if($conn->query($sql) == TRUE){
		echo "New car sample create successfully: ".$sql."<br/>
		with id:".$conn->insert_id;

	
		}
	else{
		echo "Error with query: " .$sql."<br/>".$conn->error;
	}

?> 
