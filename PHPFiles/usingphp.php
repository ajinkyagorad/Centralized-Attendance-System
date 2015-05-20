<?php
	$id=$_GET["id"];
	$file=fopen("htmlphpresp.txt","a");
	fwrite($file,"RFID READ = ".$id."\r\n");
	fclose($file);
	//now check for id in file id.txt
	$file=fopen("id.txt","r");
	$data=explode(",",fread($file,filesize("id.txt")));
	$present=false;
	for ($index=0;$index<count($data);$index++)
	{
		if($id==$data[$index])$present=true;
	}
	if($present==true)
	{
		echo "YES, id : ".$id." is in list\r\n";
	}
	else{
		echo "NO, id : ".$id."was not found in the  list";
	}
	fclose($file);
	exit();
?>