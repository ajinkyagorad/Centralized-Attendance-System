<!DOCTYPE html>
<html>
	<body>
		<h1>Startup Setup</h1>
        <h3>
            <form action="" method ="post">
                <input type="radio" name="METHOD" value = "CHECK">Check : Normal mode<br>
                <input type="radio" name="METHOD" value = "ADD">Add: Register new user<br>
                <input type="radio" name="METHOD" value = "DELETE">Delete : Delete  existing user<br>
				<input type="text"	  name="TEXTLCD" value = "">Text to display on LCD<br>
				<input type="checkbox" name="DATETIME" value="TRUE">Set Date  Time<br>
				<input type="checkbox" name="NEW_DEVID" value="TRUE">Assign New Device ID<br>
                <input type="submit" name="StartupSetup" value = "Save Startup Settings">
				
            </form>
        </h3>
		<h1>Delete Setup</h1>
			<form action="" method = "post">
				<input type="radio" name="TYPE" value ="FINGERPRINT"> Fingerprint  Type<br>
				<input type="text" name="UID" value="">Enter UID to delete<br>
				<p>Add the data</p>
				<input type="submit" name="DeleteSetup" value="Append Delete Data">
			</form>
			
			<form action="" method = "post">
				<p>Following will clear 'delete.txt'</p>
				<input type="submit" name="ClearDeleteFile" value="Clear Delete Data">
			</form>
        <!--  now the process for sending assigned id and method-->
        <p>PHP will output </p>
        <?php
           if( isset($_POST["StartupSetup"]))
		   {
				   print_r($_POST);
				   $file=fopen("startup.txt","w");
					//write  configuration options in startup.txt
						if(isset($_POST["METHOD"]))
						{
							$methodData="METHOD=".$_POST["METHOD"]."\r\n";
							fwrite($file,$methodData);
						}
						if(isset($_POST["TEXTLCD"]))
						{
							if($_POST["TEXTLCD"]!="")
							{
								$textLcdData="TEXTLCD=".$_POST["TEXTLCD"]."\r\n";
								fwrite($file,$textLcdData);
							}
						}
						if(isset($_POST["DATETIME"]))
						{
							
							$dateTimeData="DATETIME\r\n";
							//$dateTimeData="DATETIME=".date("dmYHis");		//get time in dateMonthYearHourMinuteSecond format
							fwrite($file,$dateTimeData);
						}
						if(isset($_POST["NEW_DEVID"]))
						{
							$clrDevidData="NEW_DEVID\r\n";
							fwrite($file,$clrDevidData);
						}
				   fclose($file);
		   }
		   if( isset($_POST["DeleteSetup"]))
		   {
						//add 
						print_r($_POST);
						
						if(isset($_POST["TYPE"]) && isset($_POST["UID"]) )	//if both the data are given
						{
							$file=fopen("delete.txt","a");
							$data=$_POST["TYPE"].",".$_POST["UID"]."\r\n";
							fwrite($file,$data);
							fclose($file);
						}
						
		   }
		   if(isset($_POST["ClearDeleteFile"]))
		   {
						//Clear contents on delete file
						$file=fopen("delete.txt","w");
						ftruncate($file,0);	//truncate  file to zero length
						fclose($file);
		   }
        ?>
    </body>
</html>