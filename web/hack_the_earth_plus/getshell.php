<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Big Hacker</title>

    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <h1>Wow you get the first shell</h1>
    <h1>Can you get the other?</h1>
    <form action="getshell.php">
        <button class="bubbly-button" name="source">Get the source code</button>
    </form>
</body>
</html>

<?php
    error_reporting(0);
    if (isset($_GET['source'])) {
        highlight_file(__FILE__);
    }

    class Shell {
        public $cmd;
        function __construct($cmd) {
            $this->cmd = $cmd;
        }

        function __toString() {
            system($this->cmd);
        }
    }

    $addr1 = $_GET['addr1'];
    $addr2 = $_GET['addr2'];

    if ($addr1 && $addr2) {
        if ($addr1 !== $addr2 && md5($addr1) === md5($addr2)) {
            echo unserialize($_POST['class']);
        } else {
            echo "<script>alert('地址错误!!!')</script>";
        }
    }
?>


    