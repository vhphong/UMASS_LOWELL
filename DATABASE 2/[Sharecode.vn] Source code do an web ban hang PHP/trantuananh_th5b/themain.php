<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
</head>
<body>
<?php
	include("dbconnect.inc");
	$action=isset($_GET['action'])? $_GET['action']:"";
	switch($action)
	{
		case 1:
				include("dangnhap.php");
				break;
		case 2:
				include("dangky.php");
				break;
		case 3:
				include("capnhathanghoa.php");
				break;
		case 4:
				include("giohang.php");
				break;
		case 5:
				include("timkiem.php");
				break;
		case 6:
				include("maytinhdtu.php");
				break;
		case 8:
				include("linkthoat.php");
				break;
		case 10:
				include("thongtin.php");
				break;
	}

	if(isset($_GET['ml']))
	{
		include "loaisanpham.php";
	}	
	if(isset($_GET['chitiet']))
	{
		include "chitietsanpham.php";
	}
	if(isset($_SESSION['hang']))
	{
		include "giohang.php";
	}
	if(isset($_GET['sua']))
	{
		include"suathongtin.php";
	}
	if(isset($_GET['xoa']))
	{
		include"thucthixoa.php";
	}
	?>
</body>
</html>                                                                                                                                                                                           