<?php
	session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Trang Chủ</title>
</head>
<body bgcolor="#FFFF33">
<table width="980" height="600" border="0" align="center"  class="body">
  <tr>
    <td   height="195" colspan="3"><img src="anhphp/banner.jpg" width="964" height="294"/></td>
  </tr>
  <tr>
    <td height="51" colspan="3"><?php include("header.php");?></td>
  </tr>
  <tr>
    <td width="150"><?php include("theleft.php");?></td>
    <td width="700"><?php include("themain.php");?></td>
    <td width="130"><?php include("theright.php");?></td>
  </tr>
</table>
</body>
</html>
