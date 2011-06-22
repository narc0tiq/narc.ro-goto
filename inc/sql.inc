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

	public function add_redirect($keyword, $url)
	{
		$q = 'INSERT INTO redirects (keyword, url) VALUES (?,?)';

		$resu = $this->db->Execute($q, array($keyword, $url));

		if(empty($resu))
		{
			$q = 'UPDATE redirects SET url = ? WHERE keyword = ?';

			$resu = $this->db->Execute($q, array($url, $keyword));

			if(!empty($resu))
				return true;

			return false;
		}
		else
			return true;
	}

	public function get_redirects($limit = null, $offset = null)
	{
		$limit += 0;
		$offset += 0;

		if(empty($this->db) and !$this->db_connect())
			die('Unable to connect to database');

		$q = 'SELECT keyword, url FROM redirects';
		if(!empty($limit))
			$q .= ' LIMIT '.$limit;
		if(!empty($offset))
			$q .= ' OFFSET '.$offset;

		$resu = $this->db->Execute($q);

		if(empty($resu))
			return array();
		else
			return $resu->GetAssoc();
	}

	public function delete_redirect($keyword)
	{
		$q = 'DELETE FROM redirects WHERE keyword = ?';

		$resu = $this->db->Execute($q, array($keyword));

		if(empty($resu))
			return false;
		else
			return true;
	}

}

?>
