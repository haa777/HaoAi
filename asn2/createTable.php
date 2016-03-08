<?php
	$servername="localhost";
	$username="root";
	$password="";
//create table for the car
	$sql = "CREATE TABLE car(
			carBrand VARCHAR(30) NOT NULL,
			carYear INT(4) NOT NULL,
			carType VARCHAR(30),
			carId INT(5) NOT NULL
		)";
	$conn = new mysqli($servername,$username,$password,"cardb");
//check connection 
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

//Create Table
	if ($conn->query($sql) ===TRUE) {
		echo "car table created successfully";
	}else{
		echo "car table created failed" . $conn->error;
	}
//========================================================================

	// table about the new owner
	$sql = "CREATE TABLE newOwner(
			newFName VARCHAR(30) NOT NULL,
			newLName VARCHAR(30) NOT NULL,
			newCell INT(10),
			carBrand VARCHAR(30) NOT NULL,
			carYear INT(4) NOT NULL,
			carType VARCHAR(30),
			carId INT(5) REFERENCES car ON DELETE CASCADE 
		)";

	$conn = new mysqli($servername,$username,$password,"cardb");
//check connection 
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

//Create Table
	if ($conn->query($sql) ===TRUE) {
		echo "New owner table created successfully";
	}else{
		echo "New owner table created failed" . $conn->error;
	}

//========================================================================


	// table about the old owner 
	$sql = "CREATE TABLE oldOwner(
			oldFName VARCHAR(30) NOT NULL,
			oldLName VARCHAR(30) NOT NULL,
			oldCell INT(10),
			carBrand VARCHAR(30) NOT NULL,
			carYear INT(4) NOT NULL,
			carType VARCHAR(30),
			carId INT(5) REFERENCES car ON DELETE CASCADE
		)";

	$conn = new mysqli($servername,$username,$password,"cardb");
//check connection 
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

//Create Table 
	if ($conn->query($sql) ===TRUE ){
		echo "old owner table created successfully";
	}else{
		echo "old owner table created failed" . $conn->error;
	}

//========================================================================


// table about the car condition 
	$sql = "CREATE TABLE carCondition(
			carBrand VARCHAR(40) NOT NULL,
			carYear INT(4) NOT NULL,
			carType VARCHAR(30),
			carId INT(5) REFERENCES car ON DELETE CASCADE,
			carCond VARCHAR(30) NOT NULL
		)";

	$conn = new mysqli($servername,$username,$password,"cardb");
//check connection 
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

//Create Table
	if ($conn->query($sql)===TRUE) {
		echo "car condition table created successfully";
	}else{
		echo "car condition table created failed" . $conn->error;
	}

//========================================================================



// table about the car accident number
	$sql = "CREATE TABLE accidentHistory(
			carName VARCHAR(30) NOT NULL,
			carGender VARCHAR(10) NOT NULL,
			carType VARCHAR(30),
			carId INT(5) REFERENCES car ON DELETE CASCADE,
			carCond VARCHAR(30) NOT NULL,
			accidentNumber INT(3)
		)";

	$conn = new mysqli($servername,$username,$password,"cardb");
//check connection 
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}

//Create Table
	if ($conn->query($sql)===TRUE) {
		echo "car history table created successfully";
	}else{
		echo "car history table created failed" . $conn->error;
	}

//========================================================================

	$conn->close();

?>




