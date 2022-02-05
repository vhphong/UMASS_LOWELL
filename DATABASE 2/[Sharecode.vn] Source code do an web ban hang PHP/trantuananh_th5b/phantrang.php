<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Untitled Document</title>
</head>

<body>
<?php
  //connect den server va co so du lieu
  mysql_connect("localhost","root","") or die(mysql_error());
  mysql_select_db("ngocngoc") or die(mysql_error());
  //-------------------------------------------------
  $qr=mysql_query("select * from sanpham");//query den bang co ten la: test trong CSDL
  $n_record=mysql_num_rows($qr);//so ban ghi cua bang
  $p=5;//so bang ghi trong 1 trang can hien thi
  
  //-------Ham tinh so trang-------------------------
  function num_page()
  {
    global $n_record;//lay bien toan cuc
    global $p;
    if($n_record%$p==0)
    {
      $n_page=$n_record/$p;
      return $n_page;
    }
    else
    {
      $n_page=($n_record-($n_record%$p))/$p+1;
      return $n_page;
    }
  }
  //-------------------------------------------------
  function view_page()
  {
    global $n_record;
    for($i=1;$i<=num_page();$i++)
    {
      echo "<a href='pages.php?n=".$i."'>".$i."</a><";
    }
    echo "<a href='pages.php?n=all'>All</a>";
  }
  //-------------------------------------------------
  echo "<br>";
  $n=$HTTP_GET_VARS['n'];//lay bien n tren trinh duyet
  $s=($n-1)*$p; //thu tu cua bang ghi tai trang thu n
  if ($n!='all')
  {
    $qr1=mysql_query("select * from test limit $s,$p") or die (mysql_error());
  }
  else
  {
    $qr1=mysql_query("select * from test");
  }
  //--------Hien thi bang-----------------------------
  view_page();
  echo "<table border=1 width=100%>";
  while($row=mysql_fetch_array($qr1))
  {
    echo "<tr>";
      echo "<td>".$row['id']."</td>";
      echo "<td>".$row['name']."</td>";
      echo "<td>".$row['address']."</td>";
    echo "</tr>";
  }
  echo "</table>";
  view_page();
?> 
</body>
</html>
