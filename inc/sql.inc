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

	public function redirects_table_exists()
	{
		if(empty($this->cache['tables']))
			$this->cache['tables'] = $this->db->MetaTables('TABLES');

		if(in_array('redirects', $this->cache['tables']))
			return true;
		else
			return false;
	}

	public function create_redirects_table()
	{
		$dict = NewDataDictionary($this->db);
		$fields = '
			keyword C(30) NOTNULL PRIMARY,
			url C(1024) NOTNULL';

		$sqlarray = $dict->CreateTableSQL('redirects', $fields);
		$resu = $dict->ExecuteSQLArray($sqlarray);

		if($resu > 0)
			return true;
		else
			return false;
	}

}

?>
