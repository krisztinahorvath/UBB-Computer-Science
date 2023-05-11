<?php

header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
header('Access-Control-Allow-Methods: PUT, OPTIONS');
header('Access-Control-Allow-Headers: Content-Type');

if ($_SERVER['REQUEST_METHOD'] == 'OPTIONS') {
    http_response_code(200);
    exit();
}

include('dbConnection.php');

$documentId = $_GET['id'];

$data = json_decode(file_get_contents('php://input'), true);

$conn = OpenConnection();
$sql = "UPDATE `documents` SET `title` = ?, `author` = ?, `numberOfPages` = ?, `type` = ?, `format` = ? WHERE `id` = ?";
$stmt = $conn->prepare($sql);

if(!$data['title']){
    http_response_code(500);
    echo json_encode(array('message' => 'Please enter a title.'));
    exit();
}

if(!is_numeric($data['numberOfPages'])){
    http_response_code(500);
    echo json_encode(array('message' => 'Please enter a valid number for the number of pages.'));
    exit();
} else if((int)$data['numberOfPages'] <= 0){
    http_response_code(500);
    echo json_encode(array('message' => 'Please enter a non-null positive number for the number of pages.'));
}

if(!$data['format']){
    http_response_code(500);
    echo json_encode(array('message' => 'Please enter a format.'));
    exit();
}

$stmt->bind_param('ssissi', $data['title'], $data['author'], $data['numberOfPages'], $data['type'], $data['format'], $documentId);

if ($stmt->execute()) {
    http_response_code(200);
    echo json_encode(array('message' => 'Document updated successfully.'));
} else {
    http_response_code(500);
    echo json_encode(array('message' => 'Error updating document.'));
}

CloseConnection($conn);