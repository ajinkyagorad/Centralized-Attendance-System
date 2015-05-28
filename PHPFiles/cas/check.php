<?php
	if(isset($_GET["METHOD"]))	$method=$_GET["METHOD"];
	if(isset($_GET["TYPE"]))$type=$_GET["TYPE"];
	if(isset($_GET["UID"]))$uid=$_GET["UID"];
	if(isset($_GET["DEVID"]))$devid=$_GET["DEVID"];
	if(isset($_GET["TIME"]))$time=$_GET["TIME"];
	if(isset($_GET["DATE"]))$date=$_GET["DATE"];
	if(isset($_GET["LAT"]))$lat=$_GET["LAT"];
	if(isset($_GET["LON"]))$lon=$_GET["LON"];
		print_r($_GET);
	$file=fopen("header.txt","w");
	foreach( getallheaders() as $name => $value)
	{
		fwrite($file, $name." : ".$value."\r\n");
	}
	fclose($file);
	
	//if(isset($_GET["TYPE"]))if($type=="RFID"|| $type=="FINGERPRINT")
	
	{
			//process
			$filename="id.txt";
			$file=fopen($filename,"r");
			$data=fread($file,filesize($filename));
			fclose($file);
			$rfid=explode(",",$data);
			$found=false;
			for( $i=0;$i<count($rfid);$i++)
			{
				//echo " checking with " . $rfid[$i]."\r\n";
				{	
				if($uid==$rfid[$i])
					$found=true;
					
				}
			}
			
			if($found==true)
			{
				echo " ID : ".$uid." id_found \r\n";
			}
			else
			{
				echo " ID : ".$uid."id_not_found\r\n";
			}
			/* debugging*/
			$file=fopen("htmlphpresp.txt","a");
			fwrite($file,"ID :  ".$uid."\r\n");
			
			fclose($file);
					
	}


?>
