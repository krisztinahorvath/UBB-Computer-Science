<?php
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
header('Access-Control-Allow-Methods: GET');
include('dbConnection.php');
    $conn = OpenConnection();
    $sql = "SELECT * FROM `documents`;";
    $result = $conn->query($sql);

    if(!$result){
        trigger_error('Invalid query!' . $conn->error);
    }

    $rows = array();
    while($row = $result->fetch_assoc()){
        $rows[] = $row;
    }

    echo json_encode($rows);

    CloseConnection($conn);

