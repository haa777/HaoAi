<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	$dbname="cardb";


	$carBrand = "toyota";
	$carYear = "2010";
	$carType = "truck";
	$carId = "12345";
	$newFName = "John";
	$newLName = "Smith";
	$newCell = "1234567890";
	$oldFName = "Harry";
	$oldLName = "Edward";
	$oldCell = "0987653421";
	$carCond = "fine";
	$accidentNumber = "2";

	$sql = "INSERT INTO posts(carBrand, carYear, carType, carId, newFName,newLName, newCell, oldFName, oldLName, oldCell, carCond, accidentNumber) VALUES ('$carBrand', '$carYear', '$carType', '$carId', '$newFName','$newLName', '$newCell', '$oldFName', '$oldLName', '$oldCell', '$carCond', '$accidentNumber')";




	// Create connection
	$conn = new mysqli($servername, $username, $password,"cardb");
// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
// Create database
	if ($conn->query($sql) === TRUE) {
		$last_id=$conn->insert_id;
		echo "New record created successfully <br>";
		echo "Last ID is: ".$last_id;
	} else {
		echo "Error creating database: " . $conn->error;
		}
	$conn->close();
?>