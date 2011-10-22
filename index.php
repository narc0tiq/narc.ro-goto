<?PHP

error_reporting(E_ALL);
ob_start();
session_start();

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

if(strpos($operation, '/') > 0)
	$operation = substr($operation, 0, strpos($operation, '/'));

if(!$sql->redirects_table_exists()
   and !$sql->create_redirects_table())
	die('Fatal error: could not create the redirects table.');

if(!$sql->users_table_exists()
   and !$sql->create_users_table())
	die('Fatal error: could not create the users table.');

if(strtolower(substr($operation, 0, 5)) == 'admin')
{
	include(PATH_INC.'/admin.inc');
	exit(0);
}
if(strtolower(substr($operation, 0, 4)) == 'list')
{
	include(PATH_INC.'/list.inc');
	exit(0);
}

$found = $sql->get_redirect($operation);

if(empty($found))
{
	header('HTTP/1.x 404 Not Found');
	echo fetch_header();
	die('<p style="color: #b00">Fatal error: No such redirect: "'.$operation.'"</p>');
}

header('Location: '.$found[$operation]);

?>
