<?php

interface PassGenerator {
    public function set_complexity($complexity);
    public function set_number($length);
    public function generate_password();
    public function get_password();
}

class Password implements PassGenerator {
    var $complexity,  $length;

    function set_complexity($complexity) {
       $this->complexity = $complexity; 
    }

    function set_number($length) {
        $this->length = $length;
    }

    function generate_password() {
        $numbers = range(0, 9);
        $numberscount = count($numbers);

        $uppercase = range('A', 'Z');
        $uppercount = count($uppercase);

        $lowercase = range('a', 'z');
        $lowercount = count($lowercase);

        $symbols = array_merge(range('!', '/'), range(':', '@'));
        $symbolscount = count($symbols);

        $this->password = '';
        for ($i = 0; $i < $this->length; $i++) {
            $rand = rand(1, $this->complexity);

            switch($rand) {
            case 1:
                // Choosing a random index of symbols list
                $sym = rand(0, $numberscount-1);
                // Appending the symbol to password
                $this->password = $this->password.$numbers[$sym];
                break;
            case 2:
                $sym = rand(0, $uppercount-1);
                $this->password = $this->password.$uppercase[$sym];
                break;
            case 3:
                $sym = rand(0, $lowercount-1);
                $this->password = $this->password.$lowercase[$sym];
                break;
            case 4:
                $sym = rand(0, $symbolscount-1);
                $this->password = $this->password.$symbols[$sym];
                break;
            }
        }
        return $this->password;
    }

    function get_password() {
        return $this->password; 
    }
}

class Many_Passwords extends Password  {
    var $n; // amount of passwords

    function set_password_count($n) {
        $this->n = $n; 
    }

    function get_passwords() {
        $this->pass_arr = [];
        
        for ($i = 0; $i < $this->n; $i++) {
            $this->pass_arr[] = $this->generate_password();
        }

        return $this->pass_arr; 
    }
}
?>
