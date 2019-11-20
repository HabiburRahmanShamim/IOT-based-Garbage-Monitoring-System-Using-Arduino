<html>
<head></head>
<body align = "center">

<h2>Compputer Network Lab Project</h2>
<h1>IOT Based Garbage Monitoring System</h1>
<?php
	//header("Access-Control-Allow-Origin: *");
	//header("Content-Type: application/json; charset=UTF-8");

	//Creating Array for JSON response
	//$response = array();
	 
	// Include data base connect class
	$filepath = realpath (dirname(__FILE__));
	require_once($filepath."/db_connect.php");

	 // Connecting to database
	$db = new DB_CONNECT();
	 // Fire SQL query to get last data from Sensor_Data
	$result = mysql_query("SELECT Distance_cm FROM Sensor_Data ORDER BY ID DESC LIMIT 1") or die(mysql_error());
	
	if (mysql_num_rows($result) > 0) {
    
		// Storing the returned array in response
		//$response["Sensor_Data"] = array();
	 
		// While loop to store all the returned response in variable
		while ($row = mysql_fetch_array($result)) {
			// temperoary user array
			//$Sensor_Data = array();
			//$Sensor_Data["ID"] = $row["ID"];
			//$Sensor_Data["Distance_cm"] = $row["Distance_cm"];
			//$Sensor_Data["Distance_inch"] = $row["Distance_inch"];
			$distance = $row["Distance_cm"];

			// Push all the items 
			//array_push($response["Sensor_Data"], $Sensor_Data);
		}
		if($distance > 26.5)$distance = 26.5;
		$percent = $distance*100 / 26.5;
		$percent = number_format((float)$percent, 2, '.', '');
		$percent = 100 - $percent;
		echo '<h3>Garbage Lavel : '. (26.5-$distance) .'cm </h3>';
		echo '<br><br>';
		if($percent < 50)echo '<h1 style = "color:green;">'.$percent.'%</h1>';
		else if($percent >= 50 && $percent <= 80)echo '<h1 style = "color:orange;">'.$percent.'%</h1>';
		else echo '<h1 style = "color:red;">'.$percent.'%</h1>';
		// On success
		//$response["success"] = 1;
	 
		// Show JSON response
		//echo json_encode($response);
	}	
	else 
	{
		// If no data is found
		//$response["success"] = 0;
		//$response["message"] = "No data on Sensor_Data found";
		echo '<h3>No Data Found</h3>';
	 
		// Show JSON response
		//echo json_encode($response);
	}
?>


</body>

</html>
