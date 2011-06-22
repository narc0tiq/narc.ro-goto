<?PHP

final class GotoSQLEngine
{
	private $db = null;

	private $cache = array();

	public function __construct()
	{
		global $conf;

		if(empty($conf['db_dsn']))
			die('Fatal error: misconfiguration -- please set up a database connection string!');

		$this->db = ADONewConnection($conf['db_dsn']);

		if(empty($this->db))
			die('Fatal error: could not connect to database!');
	}


}

?>
