//check.php : checks whether given UID with <TYPE> is on the server or not ( for that <DEVID>)
//client.txt : stores the list of registerd devices ( only their  DEVIDs)
//id.txt		: stores the  list  of registered UID with <TYPE>
//log.txt    : any debugging data or transaction is appended here
//startup.txt	: stores startup configurations
//startup.php  : used when a device boots up and it sets the configuration from 'startup.txt' // and execute  accordingly
//startupSet.php  : actually html which stores the response from user (server ) to file startup.txt ( interface)
//delete.php	: handles when DELETE mehod is given
//delete.txt		: stores data to be deleted by delete.php as "<TYPE>,<UID> [CRLF]"