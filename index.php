<?PHP

error_reporting(E_ALL);
ob_start();

define('PATH_BASE',  dirname(__FILE__));
define('PATH_INC',   PATH_BASE.'/inc');
define('PATH_ADODB', PATH_INC.'/adodb5');

include(PATH_INC.'/conf.inc');
include(PATH_ADODB.'/adodb.inc.php');
include(PATH_INC.'/sql.inc');

$sql = new GotoSQLEngine();

$operation = '';
if(!empty($_GET['args']))
	$operation = $_GET['args'];

?>
