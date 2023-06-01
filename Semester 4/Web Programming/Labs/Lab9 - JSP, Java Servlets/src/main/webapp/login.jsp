<%--
  Created by IntelliJ IDEA.
  User: krisz
  Date: 5/21/2023
  Time: 5:07 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<nav>
    <form name="Login form" action="login" method="POST">
        <input type="text" name="username" autocomplete="off" placeholder="Username">
        <input type="password" name="password" autocomplete="off" placeholder="Password">
        <input type="submit" value="Login">
    </form>
</nav>
</body>
</html>
