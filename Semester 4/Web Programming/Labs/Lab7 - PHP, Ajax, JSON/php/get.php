<?php
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
include('dbConnection.php');

$documentId = $_GET['id'];

$conn = OpenConnection();

$sql = "SELECT * FROM `documents` where `id` = ?;";
$stmt = $conn->prepare($sql);
$stmt->bind_param('i', $documentId);
$stmt->execute();
$result = $stmt->get_result();

if(!$result){
    trigger_error('Invalid query!' . $conn->error);
}

$row = $result->fetch_assoc();

echo json_encode($row);

CloseConnection($conn);
