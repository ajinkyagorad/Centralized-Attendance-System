<?php
	if( !isset($_GET["DEVID"]) )
	{
		//if no device id given
		echo "No device ID given";
		exit();
	}
	
	//else  continue
	$devid=$_GET["DEVID"];
	
	//search if devid exits
	$client_filename="client.txt";		//file name for client data
	$client=fopen($client_filename,"r");	
	$clientData=explode(",",fread($client,filesize($client_filename)));		//get array of all filenames
	fclose($client);
	$clientExists=true;			//states whether devid registered or not , assigning  default value
	$newID="";							//variable for assigning new id if not registtered
	$newID= count($clientData)+1000;	//generate an ID in advance if needed
	$newIdAssigned=false;
		if( array_search($devid,$clientData) == false ) //if no match was found
		{
			$clientExists = false;	//client was not found => client must be asking for id
		
		}
		else{
			$clientExists=true;				//else client  exitst
		}
		
		//now send data from startup.txt to client // and userid if not registered
		{
			$startupFileName="startup.txt";
			$startupFile=fopen($startupFileName,"r");
			$startupData=fread($startupFile, filesize($startupFileName));
			fclose($startupFile);
			// now have the data
			if($clientExists==false)	//assign devid if client does not exist
			{
					//send device id too
					echo "DEVID=".$newID."\r\n";
					//also append it to client.txt file
					$client=fopen($client_filename,"a");
					fwrite($client,$newID.",");
					fclose($client);
					$newIdAssigned=True;
					
			}
			
			//send startup configuration
			//get  current  time and send
			$dataArray=preg_split("/$\R?^/m",$startupData);
			foreach($dataArray as $item)
			{
					if(strpos($item,"DATETIME")!==false)
					{
						date_default_timezone_set("Asia/Calcutta");		//set timezone to get time
						echo "DATETIME=".date("YmdHis")."\r\n";
					}
					else if(strpos($item,"NEW_DEVID")!==false )
					{
						if($newIdAssigned==false)
						{
							echo "DEVID=".$newID;
							$client=fopen($client_filename,"a");
							fwrite($client,$newID.",");
							fclose($client);
							$newIdAssigned=True;
						}
					}
					else
					{
						echo $item."\r\n";
					}
					
			}
		//now handle based on method
			//
		}
	
?>