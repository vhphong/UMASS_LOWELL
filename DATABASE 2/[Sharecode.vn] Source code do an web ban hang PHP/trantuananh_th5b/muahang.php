<?php
	session_start();
	session_register("hang");
	$muahang=$_GET['muahang'];
	if($_SESSION["hang"]["$muahang"])
	{
		$qty=$_SESSION["hang"]["$muahang"]+1;
	}
	else
	{
		$qty=1;
	}
	$_SESSION["hang"]["$muahang"]=$qty;
	?>
	<script language="javascript">
		window.alert('Ban da mua san pham nay');
		window.location="index.php";
	</script>

	
