<?php		session_start();	
			require("dbconnect.inc");
			$maloai= isset($_GET["ml"])?$_GET["ml"]:"";
		
			if($maloai)
			{
				$sql= "select * from sanpham where maloai='$maloai' ";
				$result= @mysql_query($sql,$link);
?>
	<form id="form1" name="form1" method="post" action="">
  <table width="600" border="0" align="center">
   <?php
   	while($rows=mysql_fetch_array($result))
	{
   ?>
  <tr>
    <td align="center"><div align="center"><img src="/Thihocky/anhphp/<?php echo $rows['hinhanh']; ?>" width="120" height="120"></div></td>
    <td><div align="center"><?php echo $rows['tenhang']; ?></div></td>
    <td><div align="center"><a href="/Thihocky/index.php?chitiet=<?php echo $rows['mahang']; ?>">Xem chi tiet</a></div></td>
	<?php
	if(isset ($_SESSION['username']))
    {
	?>
	<td><div align="center"><a href="/Thihocky/muahang.php?muahang=<?php echo $rows['mahang'];?>">Mua hang</a></div></td>
	<?php
	}
	?>
   </tr>
  <?php
    }
  ?>
</table>
</form>
<?php
}
?>