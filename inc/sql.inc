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

		if(!empty($conf['db_debug']))
			$this->db->debug = true;
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

	public function get_redirect($keyword)
	{
		$q = 'SELECT keyword, url FROM redirects WHERE keyword = ?';

		$resu = $this->db->Execute($q, array($keyword));

		if(empty($resu))
			return array();
		else
			return $resu->GetAssoc();
	}

	public function users_table_exists()
	{
		if(empty($this->cache['tables']))
			$this->cache['tables'] = $this->db->MetaTables('TABLES');

		if(in_array('users', $this->cache['tables']))
			return true;
		else
			return false;
	}

	public function create_users_table()
	{
		$dict = NewDataDictionary($this->db);
		$fields = '
			username C(30) NOTNULL PRIMARY,
			password_hash C(40) NOTNULL';

		$sqlarray = $dict->CreateTableSQL('users', $fields);
		$resu = $dict->ExecuteSQLArray($sqlarray);

		if($resu > 0)
			return true;
		else
			return false;
	}

	public function get_users($limit = null, $offset = null)
	{
		$limit += 0;
		$offset += 0;

		$q = 'SELECT username, password_hash FROM users';
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

	public function add_user($username, $password_hash)
	{
		$q = 'INSERT INTO users (username, password_hash) VALUES (?,?)';

		$resu = $this->db->Execute($q, array($username, $password_hash));

		if(empty($resu))
		{
			$q = 'UPDATE redirects SET password_hash = ? WHERE username = ?';

			$resu = $this->db->Execute($q, array($password_hash, $username));

			if(!empty($resu))
				return true;

			return false;
		}
		else
			return true;
	}

	public function delete_user($username)
	{
		$q = 'DELETE FROM users WHERE username = ?';

		$resu = $this->db->Execute($q, array($username));

		if(empty($resu))
			return false;
		else
			return true;
	}

	public function get_user($username)
	{
		$q = 'SELECT username, password_hash FROM users WHERE username = ?';

		$resu = $this->db->Execute($q, array($username));

		if(empty($resu))
			return array();
		else
			return $resu->GetAssoc();
	}

}
?>
