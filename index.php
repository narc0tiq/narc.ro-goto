<?PHP

error_reporting(E_ALL);
ob_start();

include('inc/conf.inc');

$operation = '';
if(!empty($_GET['args']))
	$operation = $_GET['args'];

?>
