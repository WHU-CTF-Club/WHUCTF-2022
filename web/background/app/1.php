<?php
if (isset($_POST['Upload'])) {
    $files = $_FILES['uploaded']['name'];
    $target_path = "uploads/";
    $target_path = $target_path . basename( $files);
    $end = end(explode('.',$files));
    if(!move_uploaded_file($_FILES['uploaded']['tmp_name'], $target_path)) {
        echo '<pre>';
        echo "<script>alert('请选择文件');window.history.back(-1);</script>";
        echo '</pre>';
    } else {
        if(!(($_FILES['uploaded']['type'] == 'image/jpeg') || ($_FILES['uploaded']['type'] == 'image/png') || ($_FILES['uploaded']['type'] == 'image/gif'))){
            echo "<script>alert('哎呦~~你干嘛~~');window.history.back(-1);</script>";
        }
        else{
            $check = fopen($target_path,"r");
            $check_content = fread($check,filesize($target_path));
            if(strpos($check_content,'eval')){
                fclose($check);
                unlink($target_path);
                echo "<script>alert('哎呦~~你干嘛~~');window.history.back(-1);</script>";
            }
            else{
                fclose($check);
                $fp = fopen("upload.html","r");
                $str = fread($fp, filesize("upload.html"));
                $str = str_replace("{image}",$target_path,$str);
                $str = str_replace("{path}","已上传至".$target_path,$str);
                fclose($fp);
                $handle = fopen("upload.html","w");
                fwrite($handle,$str);
                fclose($handle);
                include("upload.html");
                $str = str_replace($target_path,"{image}",$str);
                $str = str_replace("已上传至".$target_path,"{path}",$str);
                $handle = fopen("upload.html","w");
                fwrite($handle,$str);
                fclose($handle);
            }
        }
        
    }
}
?>