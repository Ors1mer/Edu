<?php
class DB {
    private $host = "localhost";
    private $user = "quick_brown_fox";
    private $pass = "jumped over the lazy dog";
    private $dbname = "passwordsDB";

    public function __construct() {
        try {
            $pdo = new PDO("mysql:host=$this->host; dbname=$this->dbname", $this->user, $this->pass);
            $this->db = $pdo;
        } catch (PDOException $err) {
            echo "Couldn't connect!<br>";
            echo $err->getMessage();
        }
    }

    public function insert($user, $pass_arr) {
        /* This function is used to insert a new user and his newly created passwords */
        // Insert user_id-user
        $user_insert = "INSERT INTO users (user_id, user)
                        VALUES (NULL, '$user')";
        $query = $this->db->prepare($user_insert);
        $query->execute();
        // Insert pass_id-password foreach pass in pass_arr
        
        foreach ($pass_arr as $pass) {
            $pass_insert = "INSERT INTO passwords (pass_id, password, user_id)
                            SELECT NULL, '$pass', user_id
                            FROM users WHERE user = '$user'";
            $query = $this->db->prepare($pass_insert);
            $query->execute();
        }
    }

    public function select() {
        /* This procedure prints the summary table (user & passwords) */
        $amount = $this->db->query("SELECT count(*) FROM users")->fetchColumn();
        echo "<h2>Found $amount users:</h2><br>";
        $users_data = $this->db->query("SELECT * FROM users")->fetchAll();

        foreach ($users_data as $row) {
            $user_id = $row["user_id"];
            $user = $row["user"];

            $get_amount = "SELECT count(*) FROM passwords WHERE user_id = '$user_id'";
            $amount = $this->db->query($get_amount)->fetchColumn();

            $passwords_select = "SELECT pass_id, password
                                 FROM passwords WHERE user_id = '$user_id'";
            $pass_data = $this->db->query($passwords_select)->fetchAll();
            echo "<a href='update_usr.php?user_id=$user_id&user=$user'><b>$user</b></a> ($amount) | ";

            foreach ($pass_data as $row) {
                $pass_id = $row["pass_id"];
                $pass = $row["password"];
                echo "<a href='update_pass.php?pass_id=$pass_id'>$pass</a> \t";
            }
            echo "<br><br>";
        }
    }

    public function update_usr($user_id, $pass_arr) {
        /* This function alters passwords of one specific user */
        // Delete old passwords
        $pass_delete = "DELETE FROM passwords WHERE user_id='$user_id'";
        $this->db->query($pass_delete);
        // Insert new ones
        foreach ($pass_arr as $pass) {
            $pass_insert = "INSERT INTO passwords (pass_id, password, user_id)
                            VALUES (NULL, '$pass', '$user_id')";
            $query = $this->db->prepare($pass_insert);
            $query->execute();
        }
    }

    public function delete_usr($user_id) {
        /* Deletes a user */
        // Delete user's passwords
        $pass_delete = "DELETE FROM passwords WHERE user_id='$user_id'";
        $this->db->query($pass_delete);
        // Delete user from table users
        $user_delete = "DELETE FROM users WHERE user_id='$user_id'";
        $this->db->query($user_delete);
    }

    public function update_pass($pass_id, $pass) {
        $update_pass = "UPDATE passwords SET password='$pass' WHERE pass_id='$pass_id'";
        $this->db->query($update_pass);
    }

    public function delete_pass($pass_id) {
        $delete_pass = "DELETE FROM passwords WHERE pass_id='$pass_id'";
        $this->db->query($delete_pass);    
    }
}
?>
