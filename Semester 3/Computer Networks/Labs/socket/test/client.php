<?php
$s=socket_create(AF_INET,SOCK_STREAM,0);
socket_connect($s,"192.168.1.6",1234);

$end = 0;
if(pcntl_fork() == 0) {
            while($end != 1) {
                socket_recv($s,$response,4096,0);
                echo "\nServer message: ";
                echo $response;
                echo "\nClient: ";
            }
}
while($end != 1) {
            $msg = readline("\nClient: ");
            socket_send($s,$msg, strlen($msg), 0);
}

socket_close($s);
?>
