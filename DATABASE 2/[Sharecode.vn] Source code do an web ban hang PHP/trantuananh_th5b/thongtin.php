<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Untitled Document</title>
</head>

<body>
<?php
require("dbconnect.inc");
$sql="select * from sanpham";
$result=mysql_query($sql);
?>
<table width="725" border="1" background="anhphp/theme8.jpg">
  <tr>
    <td width="65"><div align="left">Ma hang </div></td>
    <td width="100"><div align="left">Ten hang </div></td>
    <td width="80"><div align="left">Gia </div></td>
    <td width="80"><div align="left">Kieu</div></td>
    <td width="80"><div align="left">Ma loai </div></td>
    <td width="80"><div align="left">Hinhanh</div></td>
    <td width="80"><div align="left"></div></td>
  </tr>
<?php
while($rows=mysql_fetch_array($result))
{
?>
  <tr>
    <td><div align="left"><?php echo "$rows[0]";?></div></td>
    <td><div align="left"><?php echo "$rows[1]";?></div></td>
    <td><div align="left"><?php echo "$rows[2]";?></div></td>
    <td><div align="left"><?php echo "$rows[3]";?></div></td>
    <td><div align="left"><?php echo "$rows[4]";?></div></td>
    <td><div align="left"><?php echo "$rows[7]";?></div></td>
    <td><div align="left"><a href="/Thihocky/index.php?sua=<?php echo "$rows[0]";?>">Edit</a>&nbsp;&nbsp;<a href="/Thihocky/index.php?xoa=<?php echo "$rows[0]";?>">Del</a></div></td>
  </tr>
 <?php
 }
 ?>
</table>
</body>
</html>
