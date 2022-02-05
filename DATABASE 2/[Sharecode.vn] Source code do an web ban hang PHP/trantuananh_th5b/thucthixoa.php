<?php 
	if(isset($_GET['xoa']))
{
		include('dbconnect.inc');
		$mahang=$_GET['xoa'];
		$sql="delete from sanpham where mahang='$mahang'";
		echo"$sql";
		$result=mysql_query($sql);
	if($result)
	{
?>
		<script language="javascript">
		window.alert("ban da xoa thanh cong");
		window.location="index.php";
		</script>	
	<?php
	}
	else
	{
	?>
		<script language="javascript">
		window.alert("ban chua xoa dc");
		window.location="index.php";
		</script>	
	<?php	
	}
}
	?>