<?php
    error_reporting(0);
    highlight_file(__FILE__);

    $filename = $_GET['filename'];
    $content = $_POST['content'];

    if (isset($filename) && !preg_match('/index/i', $filename) && !preg_match('/:/', $filename)) {
        file_put_contents($filename, $content);
        unlink($filename);
    }