<?php
header('Access-Control-Allow-Origin: *');
header('Content-type: application/json');
include('dbConnection.php');

if ($_SERVER['REQUEST_METHOD'] == 'DELETE') {
    $documentId = $_GET['id'];

    $conn = OpenConnection();

    $sql = "DELETE FROM `documents` WHERE `id` = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param('i', $documentId);

    if ($stmt->execute()) {
        http_response_code(204);
    } else {
        http_response_code(500);
        echo json_encode(array('message' => 'Error deleting document.'));
    }
    CloseConnection($conn);
} else {
    http_response_code(405);
    echo json_encode(array('message' => 'Method not allowed.'));
}
