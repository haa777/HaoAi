
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
			
			$id = $_POST['id'];
			$sql = "SELECT * FROM oldOwner WHERE carId=".$id;
			$result = $conn->query($sql);
			
			if($result->num_rows > 0){ //Tell us how many rows are returned with this query
				$row = $result->fetch_assoc();
				echo "
				<table>
					<tr>
						<td>carID:</td>
						<td>".$row['carId']."</td>
					</tr>
					<tr>
						<td>BasicInfo:</td>
						<td>".$row['carBrand']." ".$row['carYear']." ".$row['carType']." </td>
					</tr>
					<tr>
						<td>Car old owner information</td>
						<td>".$row['oldFName']." ".$row['oldLName']." ".$row['oldCell']."</td>
					</tr>
				</table>";
				
			}
			else
				echo "0 results";
			$result->free();
			 
		 ?> 
