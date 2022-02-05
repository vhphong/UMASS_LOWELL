<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Bài3</title>
<script language="JavaScript">
    function hienthi(a)
    {
        document.pheptinh.manhinh.value+=a;
    }
    function tinh()
    {
        document.pheptinh.manhinh.value=eval(document.pheptinh.manhinh.value);
    }
    function xoa()
    {
        document.pheptinh.manhinh.value="";
    }
</script>
</head>
<body bgcolor="pink">
<form name="pheptinh">
<table width="300" height="250" align="center">
    <caption>Máy tính điện tử<br><input name="manhinh" type="text" size=43></caption>
<tr align="center">
    <td width="80" height="50"><input name"n_1" type="button" value="1" onClick="hienthi(this.value)" style="width:50px">
    <td width="80" height="50"><input name"n_2" type="button" value="2" onClick="hienthi(this.value)" style="width:50px">
    <td width="80" height="50"><input name"n_3" type="button" value="3" onClick="hienthi(this.value)" style="width:50px">
    <td width="80" height="50"><input name"cong" type="button" value="+" onClick="hienthi(this.value)" style="width:50px">
<tr align="center">    
    <td height="50"><input name"n_4" type="button" value="4" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"n_5" type="button" value="5" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"n_6" type="button" value="6" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"tru" type="button" value="-" onClick="hienthi(this.value)" style="width:50px">
<tr align="center">    
    <td height="50"><input name"n_7" type="button" value="7" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"n_8" type="button" value="8" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"n_9" type="button" value="9" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"nhan" type="button" value="*" onClick="hienthi(this.value)" style="width:50px">
<tr align="center">    
    <td height="50"><input name"c" type="button" value="C" onClick="xoa()" style="width:50px">
    <td><input name"n_0" type="button" value="0" onClick="hienthi(this.value)" style="width:50px">
    <td><input name"bang" type="button" value="=" onClick="tinh()" style="width:50px">
    <td><input name"chia" type="button" value="/" onClick="hienthi(this.value)" style="width:50px">
</table>    
<div align="center"><a href="index.php"> Trở về trang chu </a></div>
</form>
 </body>
</html>
