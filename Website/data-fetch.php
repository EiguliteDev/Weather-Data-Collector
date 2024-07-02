<?php
  $servername = ""; // Server name
  $username = ""; // Username
  $password = ""; // Password
  $dbname = ""; // Database name

  $conn = mysqli_connect($servername, $username, $password, $dbname);

  if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
  }

  $sql = "SELECT * FROM tableName ORDER BY dateTime DESC"; // Change 'tableName' to your database table name where you want to store the data
  $result = mysqli_query($conn, $sql);

  $data = array();
  if (mysqli_num_rows($result) > 0) {
    while ($row = mysqli_fetch_assoc($result)) {
      $data[] = array(
        'value1' => $row['value1']
	// Add more data
      );
    }
  }

  echo json_encode($data);

  mysqli_close($conn);
?>
