<?php
$link= mysql_connect("localhost","root","") or die ("khong the ket noi duoc co so du lieu".mysql_error());
mysql_select_db("ngocngoc",$link) or die ("khong the ket noi duoc co so du lieu".mysql_error());
?>