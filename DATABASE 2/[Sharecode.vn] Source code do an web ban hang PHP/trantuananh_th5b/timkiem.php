<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
</head>

<body>
<form id="form1" name="form1" method="post" action="">
  <div align="center">
    <table width="434" border="1">
      <tr>
        <td width="172"><label>
          <select name="select">
            <option>Lua chon</option>
            <option>Ten hang</option>
            <option>Gia tien</option>
          </select>
        </label></td>
        <td width="150"><label>
          <input type="text" name="txtselect" />
        </label></td>
        <td width="90"><label>
          <input type="submit" name="Submit" value="Tìm kiếm" />
        </label></td>
      </tr>
    </table>
  </div>
</form>
<div align="center">
  <?php
	if(isset($_POST['Submit']))
	{
		$a=$_POST['txtselect'];
		if(strlen($_POST['txtselect'])>0)
		{
			$selected=true;
		}
		else
		{
			$selected=false;
			echo"Ban chua nhap  ky tu";
		}
		if($selected)
		{
			require("dbconnect.inc");
			$sql="select * from sanpham where( tenhang LIKE '%$a%' || giatien LIKE '%$a%')"  ;
			$result= @mysql_query($sql,$link);
			if(@mysql_num_rows($result)!=0)
			{
			?>
  <table width="600" border="1">
    <tr>
      <td width="100"><div align="left">Ten hang </div></td>
      <td width="100"><div align="left">Gia tien </div></td>
      <td width="100"><div align="left">so gr/sp </div></td>
      <td width="100"><div align="left">So sp/thung </div></td>
      <td width="100"><div align="left">Kieu</div></td>
    </tr>
    <?php 
				 while($rows=mysql_fetch_array($result,MYSQL_NUM))
				 {
				 ?>
    <tr>
      <td><div align="left"><?php echo "$rows[1]"; ?></div></td>
      <td><div align="left"><?php echo "$rows[2]"; ?></div></td>
      <td><div align="left"><?php echo "$rows[5]"; ?></div></td>
      <td><div align="left"><?php echo "$rows[6]"; ?></div></td>
      <td><div align="left"><?php echo "$rows[3]"; ?></div></td>
    </tr>
    <?php
				}
				?>
    </table>
</div>
<p>
			   <?php
			 }
			else
			{
			?>
			<script language="javascript" >
			{
				window.alert("Sieu cho khong co san pham nay!");
			}
			</script>
			<?php
			}
					
		}
	}
?>
</body>
</html>

