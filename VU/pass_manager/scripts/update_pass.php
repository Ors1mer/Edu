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
    $pass_id = $_GET["pass_id"];
?>
    <h2>Change password</h2>
    <form method=post>
        <label for="length">Length:</label><br>
        <input name="length" type="number" id="length" placeholder="8-256"><br>
        <label for="complexity">Complexity:</label><br>
        <input name="complexity" type="number" id="complexity" placeholder="1-4">
        <br><br>
        <input type="submit" value="Create"></input>
        <input type="reset" value="Clear"></input>
    </form>
<?php
if (isset($_POST["length"]) && isset($_POST["complexity"])) {
    $length = $_POST["length"];
    $complexity = $_POST["complexity"];

    // --- Creating password ---
    $generator = new Password();
    $generator->set_complexity($complexity);
    $generator->set_number($length);
    $generator->generate_password();

    $pass = $generator->get_password();

    // --- Updating DB ---
    $db = new DB();
    $db->update_pass($pass_id, $pass);
    echo "<br>Password's successfully changed!<br>";
    
    // --- Printing ---
    echo "Here it is: $pass<br>";

}
// Printing other options
echo "<br>
    <a href='delete_pass.php?pass_id=$pass_id'>
    <font color=red>
    <i>Delete this password</i>
    </font>
    </a>";

echo "<br><a href='select.php'><font color=green><i>Return to the table</i></font></a>";

?>
</body>
</html> 
