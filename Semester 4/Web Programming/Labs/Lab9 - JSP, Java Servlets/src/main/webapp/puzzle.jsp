<%--
  Created by IntelliJ IDEA.
  User: krisz
  Date: 5/21/2023
  Time: 5:46 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%
    String isLogged = (String)session.getAttribute("logged");
    if(isLogged == null || !isLogged.equals("true")){
        response.sendRedirect("loginFailed.jsp");
        return;
    }
%>
<html>
<head>
    <title>Puzzle</title>
    <link rel="stylesheet" type="text/css" href="style.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.min.js" integrity="sha256-VazP97ZCwtekAsvgPBSUwPFKdrwD3unUfSGVYrahUqU=" crossorigin="anonymous"></script>

    <script src="puzzle.js" defer></script>
</head>
<body>
<nav>
    <form action="puzzle" method="GET">
        <input type="submit" value="solve">
    </form>

    <form action="puzzle" method="post">
        <input type="submit" value="reset">
    </form>
    <button type="button" onclick="logout()">Logout</button>

    <script>
        function logout() {
            window.location.href = "logout.jsp";
        }
    </script>

</nav>
</body>
</html>
