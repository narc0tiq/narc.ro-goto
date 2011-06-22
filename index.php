<?PHP

error_reporting(E_ALL);
ob_start();

define('PATH_BASE',  dirname(__FILE__));
define('PATH_INC',   PATH_BASE.'/inc');
define('PATH_ADODB', PATH_INC.'/adodb5');

include(PATH_INC.'/conf.inc');
include(PATH_ADODB.'/adodb.inc.php');
include(PATH_INC.'/sql.inc');
include(PATH_INC.'/strings.inc');

$sql = new GotoSQLEngine();

$operation = '';
if(!empty($_GET['args']))
	$operation = $_GET['args'];

if(!$sql->redirects_table_exists()
   and !$sql->create_redirects_table())
	die('Fatal error: could not create the redirects table.');

if(strtolower(substr($operation, 0, 5)) == 'admin')
{
	include(PATH_INC.'/admin.inc');
	exit(0);
}



?>
