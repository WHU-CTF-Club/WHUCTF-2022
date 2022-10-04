<?php
    header("Set-Cookie:user=guest");
    $headers = getallheaders();
    if (stripos($headers['User-Agent'], 'hack') === false) {
        die('Please use <b>hack</b> browser');
    }
    echo 'Wow!!! You are really a hacker<br>';

    if ($_COOKIE['user'] != 'admin') {
        die('But Only <b>admin</b> can see<br>Do you want to try some <b>Cookie</b>?');
    }
    echo 'Wow!!! You get admin permission<br>';

    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        die('But please <b>POST</b> not <b>GET</b>');
    }

    echo "Wow!!! You find it!<br>".$_ENV['FLAG'];