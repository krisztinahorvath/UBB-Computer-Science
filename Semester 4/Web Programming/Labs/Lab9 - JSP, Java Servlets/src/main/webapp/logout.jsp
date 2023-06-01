<%--
  Created by IntelliJ IDEA.
  User: krisz
  Date: 5/21/2023
  Time: 7:03 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Logout</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
    <h1>Are you sure you want to log out?</h1>
    <form action="logout" method="GET">
        <input type="submit" value="Yes">
    </form>
<%--    <form action="puzzle" method="GET">--%>
<%--        <input type="submit" value="No">--%>
<%--    </form>--%>

    <button type="button" onclick="noLogout()">No</button>

    <script>
        function noLogout() {
            window.location.href = "puzzle.jsp";
        }
    </script>
</body>
</html>
