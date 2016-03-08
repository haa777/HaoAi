
<?php
	$servername="localhost";
	$username="root";
	$password="";
	$dbname="cardb";
			
	$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	//importing database
	
	
	$idnum = $_POST['id'];
	$sql = "DELETE FROM car WHERE carId=$idnum;";
	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully <br>";
	} else {
		echo "Error creating database: " . $conn->error;
	}
	

	$sql= "DELETE FROM newOwner WHERE carId=$idnum ;";
	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully <br>";
	} else {
		echo "Error creating database: " . $conn->error;
	}
	 


	$sql= "DELETE FROM oldOwner WHERE carId=$idnum;";
if ($conn->query($sql) === TRUE) {
		echo "New record created successfully <br>";
	} else {
		echo "Error creating database: " . $conn->error;
	}

	$sql= "DELETE FROM carCondition WHERE carId=$idnum;";
	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully <br>";
	} else {
		echo "Error creating database: " . $conn->error;
	}

	$sql= "DELETE FROM accidentHistory WHERE carId=$idnum;";

	if ($conn->query($sql) === TRUE) {
		echo "New record created successfully <br>";
	} else {
		echo "Error creating database: " . $conn->error;
	}


	



	
// Create database

	$conn->close(); 
/*				
	$sql = "ALTER TABLE newOwner ADD CONSTRAINT id1
	FOREIGN KEY(carId)
	REFERENCES car(carId)
	ON DELETE CASCADE
	ON UPDATE CASCADE
	";



	if($conn->query($sql) === TRUE)
		echo "Record delete successfully";
	else
		echo "error deleting record: ".$conn->error;
*/
/*
	$sql = "ALTER TABLE oldOwner ADD CONSTRAINT id2
	FOREIGN KEY(carId)
	REFERENCES car(carId)
	ON DELETE CASCADE
	ON UPDATE CASCADE
	";



	if($conn->query($sql) === TRUE)
		echo "Record delete successfully";
	else
		echo "error deleting record: ".$conn->error;

	$sql = "ALTER TABLE carCondition ADD CONSTRAINT id3
	FOREIGN KEY(carId)
	REFERENCES car(carId)
	ON DELETE CASCADE
	ON UPDATE CASCADE
	";



	if($conn->query($sql) === TRUE)
		echo "Record delete successfully";
	else
		echo "error deleting record: ".$conn->error;

	$sql = "ALTER TABLE accidentHistory ADD CONSTRAINT id4
	FOREIGN KEY(carId)
	REFERENCES car(carId)
	ON DELETE CASCADE
	ON UPDATE CASCADE
	";



	if($conn->query($sql) === TRUE)
		echo "Record delete successfully";
	else
		echo "error deleting record: ".$conn->error;
*/
?> 
