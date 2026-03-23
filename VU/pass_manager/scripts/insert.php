<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="../style.css" />
    <title>Create</title>
</head>
<body>
<?php
require_once "pass_class.php";
require_once "db_class.php";

    // --- Getting input ---
    $user = $_GET["user"];
    $count = $_GET["count"];
    $length = $_GET["length"];
    $complexity = $_GET["complexity"];

    // --- Creating passwords ---
    $generator = new Many_Passwords();
    $generator->set_complexity($complexity);
    $generator->set_number($length);
    $generator->set_password_count($count);

    $pass_arr = $generator->get_passwords();

    // --- Inserting into DB ---
    $db = new DB();
    $db->insert($user, $pass_arr);
    echo "Passwords successfully generated & saved!<br>";
    
    // --- Printing ---
    echo "Here are they: <br>";
    foreach ($pass_arr as $el) {
        echo "$el<br>";
    }
?>
<a href='select.php'>
<font color=green>
<i>See the table</i>
</font>
</a>

</body>
</html> 
