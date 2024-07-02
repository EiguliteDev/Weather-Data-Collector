<?php
  $servername = ""; // Server name
  $username = ""; // Username
  $password = ""; // Password
  $dbname = ""; // Database name

  $conn = mysqli_connect($servername, $username, $password, $dbname);

  if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
  }

  $value1 = $_POST["value1"];
  // Add more data here

  $sql = "INSERT INTO tableName (value1) VALUES ('$value1')"; // Change the 'tableName' to your database table name where you want to store the data and add more data

  if (mysqli_query($conn, $sql) && $temp > -15) {
    echo "success";
  } else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
  }
  
  mysqli_close($conn);
?>
