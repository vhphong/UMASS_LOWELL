<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Untitled Document</title>
</head>

<body >
<?php
include("dbconnect.inc");
$mahang=isset($_GET['sua'])? $_GET['sua']:"";
$sql="select * from sanpham where mahang='$mahang'";
$result=mysql_query($sql);
$rows=@mysql_fetch_array($result);
?>
<form id="form1" name="form1" method="post" action="thucthisua.php">
  <table width="205" border="1" align="center" background="anhphp/theme8.jpg">
  	<tr>
      <td width="195">Ma Hang</td>
	  <td><input name="txtma" type="text"  readonly="" value="<?php echo $rows['mahang'];?>" /></td>
    </tr>
	<tr>
      <td width="195">Ten Hang</td>
	  <td><input name="txtname" type="text" value="<?php echo $rows['tenhang'];?>" /></td>
    </tr>
    <tr>
      <td>Gia Tien</td>
	  <td><input name="txtgia" type="text" value="<?php echo $rows['giatien']; ?>" /></td>
    </tr>
    <tr>
      <td>Kieu</td>
	  <td><input name="txtkieu" type="text" value="<?php echo $rows['kieu'];?>" /></td>
    </tr>
    <tr>
      <td>Ma loai</td>
	  <td><input name="txtml" type="text" value="<?php echo $rows['kieu'];?>" /></td>
    </tr>
    <tr>
      <td>M&ocirc; t&#7843;</td>
	  <td><input name="txtgr" type="text" value="<?php echo $rows['sogr1sp'];?>" /></td>
    </tr>
    <tr>
      <td>Chi ti&#7871;t</td>
	  <td><input name="txtsp" type="text" value="<?php echo $rows['sosp1thung'];?>" /></td>
    </tr>
    <tr>
      <td>Hinh anh </td>
	  <td><input name="txthinhanh" type="text" value="<?php echo $rows['hinhanh'];?>" /></td>
    </tr>
    <tr>
      <td><label>
        <input name="Smsua" type="submit" value="Sua" />
      </label></td>
    </tr>
  </table>
</form>
</body>
</html>
