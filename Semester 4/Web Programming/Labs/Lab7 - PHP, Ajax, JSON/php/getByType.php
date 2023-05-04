<?php
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
include('dbConnection.php');

$type = strtolower($_GET['type']);

$conn = OpenConnection();

if($type != ""){
    $sql = "SELECT * FROM `documents` WHERE `type` = ?;";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param('s', $type);
    $stmt->execute();
    $result = $stmt->get_result();

    if(!$result){
        trigger_error('Invalid query!' . $conn->error);
    }

    $rows = array();
    while ($row = $result->fetch_assoc()) {
        $rows[] = $row;
    }
}
else{
    $sql = "SELECT distinct `type` FROM `documents`;";
    $result = $conn->query($sql);

    if(!$result){
        trigger_error('Invalid query!' . $conn->error);
    }

    $rows = array();
    while ($row = $result->fetch_assoc()) {
        $rows[] = $row;
    }
}


echo json_encode($rows);

CloseConnection($conn);