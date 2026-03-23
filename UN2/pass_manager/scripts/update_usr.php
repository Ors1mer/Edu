<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="../style.css" />
    <title>Update</title>
</head>
<body>
<?php
require_once "pass_class.php";
require_once "db_class.php";
    // --- Getting input ---
    $user_id = $_GET["user_id"];
    $user = $_GET["user"];
?>
    <h2>Change <?=$user?>'s passwords</h2>
    <form method=post>
        <label for="count">How many?</label><br>
        <input name="count" type="number" id="count" placeholder="amount"><br>
        <label for="length">Length:</label><br>
        <input name="length" type="number" id="length" placeholder="8-256"><br>
        <label for="complexity">Complexity:</label><br>
        <input name="complexity" type="number" id="complexity" placeholder="1-4">
        <br><br>
        <input type="submit" value="Create"></input>
        <input type="reset" value="Clear"></input>
    </form>
<?php
if (isset($_POST["count"]) && isset($_POST["length"]) && isset($_POST["complexity"])) {
    $count = $_POST["count"];
    $length = $_POST["length"];
    $complexity = $_POST["complexity"];

    // --- Creating passwords ---
    $generator = new Many_Passwords();
    $generator->set_complexity($complexity);
    $generator->set_number($length);
    $generator->set_password_count($count);

    $pass_arr = $generator->get_passwords();

    // --- Updating DB ---
    $db = new DB();
    $db->update_usr($user_id, $pass_arr);
    echo "Passwords successfully changed!<br>";
    
    // --- Printing ---
    echo "Here are they: <br>";
    foreach ($pass_arr as $el) {
        echo "$el<br>";
    }
}
// Printing other options
echo "<br>
    <a href='delete_usr.php?user_id=$user_id'>
    <font color=red>
    <i>Delete this user</i>
    </font>
    </a>";

?>
    
    <br><a href="select.php"><font color=green><i>Return to the table</i></font></a>
</body>
</html> 
