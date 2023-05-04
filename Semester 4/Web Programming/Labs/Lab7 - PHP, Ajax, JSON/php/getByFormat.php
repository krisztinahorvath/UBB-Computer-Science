<?php
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
include('dbConnection.php');

$format = strtolower($_GET['format']);

$conn = OpenConnection();

if($format != ""){
    $sql = "SELECT * FROM `documents` WHERE `format` = ?;";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param('s', $format);
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
    $sql = "SELECT distinct `format` FROM `documents`;";
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
