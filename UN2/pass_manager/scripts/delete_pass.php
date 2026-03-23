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
    if (isset($_GET["pass_id"])) {
        $pass_id = $_GET["pass_id"];
    }

    // --- Deleteing from DB ---
    $db = new DB();
    $db->delete_pass($pass_id);
?>
    <b>The password is deleted.</b><br>
    <br><a href="select.php"><font color=green><i>Return to the table</i></font></a>
</body>
</html> 
