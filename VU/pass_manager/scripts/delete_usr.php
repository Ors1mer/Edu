<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="../style.css" />
    <title>Delete</title>
</head>
<body>
<?php
require_once "db_class.php";
    // --- Getting input ---
    if (isset($_GET["user_id"])) {
        $user_id = $_GET["user_id"];
    }

    // --- Deleteing from DB ---
    $db = new DB();
    $db->delete_usr($user_id);
?>
    <b>The user is deleted.</b><br>
    <br><a href="select.php"><font color=green><i>Return to the table</i></font></a>
</body>
</html> 
