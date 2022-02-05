<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Untitled Document</title>
</head>

<body>
<?php 
	$m=$_POST['txtma'];
	$n=$_POST['txtname'];
	$g=$_POST['txtgia'];
	$k=$_POST['txtkieu'];
	$ml=$_POST['txtml'];
	$gr=$_POST['txtgr'];
	$sp=$_POST['txtsp'];
	$h=$_POST['txthinhanh'];
	require("dbconnect.inc");
	$sql="UPDATE sanpham SET mahang='$m',tenhang='$n',giatien='$g',kieu='$k',maloai='$ml',sogr1sp='$gr',sosp1thung='$sp',hinhanh='$h' WHERE mahang='$m'";
	$result=mysql_query($sql,$link);
	if($result)
	{
?>
		<script language="javascript">
		window.alert("ban da sua thanh cong");
		window.location="index.php?action=10";
		</script>	
	<?php
	}
	else
	{
	?>
		<script language="javascript">
		window.alert("ban chua sua dc");
		window.location="tatcasp.php";
		</script>	
	<?php	
	}
	?>
</body>
</html>
