<?php

function OpenConnection(): mysqli
{
    $server = "localhost";
    $user = "root";
    $password = "";
    $database = "documentsdb";

    $con = mysqli_connect($server, $user, $password, $database);

    if(!$con){
        die('Could not connect to database!');
    }
    
    return $con;
}

function CloseConnection(mysqli $con): void
{
    $con->close();
}