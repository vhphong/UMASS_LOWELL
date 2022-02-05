<?php 
require("dbconnect.inc");
$sql= "select * from loaisp";
$result= mysql_query($sql);
?>
<table border = "0" cellspacing="0" cellpadding="5" width= "100%">
	<tr>
		<td>
			<center><marquee><font color="#FF33CC" size="+2"><b>San pham </b></font></marquee></center>
		</td>
	<tr>
<?php
	while($rows=mysql_fetch_array($result))
	{
?>
	<tr>
		<td>
			<a href="/Thihocky/index.php?ml=<?php echo $rows['maloai'];?>"><?php echo $rows['ten'];?></a>		
		</td>
	</tr>
<?php
	}
?>
</table>

