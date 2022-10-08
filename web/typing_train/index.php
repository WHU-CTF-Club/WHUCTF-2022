<?php
    session_start();
    $_SESSION['count'] = $_SESSION['count'] ?? 0;
    if (isset($_GET['start'])) {
        $_SESSION['count'] = 0;
        $_SESSION['word'] = bin2hex(random_bytes(16));
    }
    if (isset($_GET['input'])){
        if ($_GET['input'] == $_SESSION['word']){
            $_SESSION['word'] = bin2hex(random_bytes(16));
            $_SESSION['count'] += 1;
        } else {
            $_SESSION['word'] = '错误！！！<a href="index.php?start">remake</a>';
        }
    }

    if ($_SESSION['count'] >= 6666) {
        echo $_ENV['FLAG'];
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>MaybeCTF Typing Train</title>

    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <h1 class="typing"><?php echo $_SESSION['word'] ?? '正确6666次即给flag<a href="index.php?start">开始</a>'?></h1>
    <form action="index.php">
        <input type="text" name="input" value=''>
    </form>
</html>

