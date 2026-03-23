<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="../style.css" />
    <title>Read</title>
</head>
<body>
<?php
require_once "db_class.php";
    $db = new DB();
    $db->select();
?>

<h3>
You may edit them by clicking or
<a href='../index.html'><i>add a new one</i></a>.
</h3>
</body>
</html> 
