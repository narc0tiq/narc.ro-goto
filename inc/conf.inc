<?PHP
// Configuration directives.
$conf = array();

$conf['db_is_file'] = true;
$conf['db_fname'] = PATH_BASE.'/goto.sqlite.db';

//$conf['db_dsn'] = 'sqlite://'.urlencode($conf['db_fname']).'?debug';
$conf['db_dsn'] = 'sqlite://'.$conf['db_fname'];

?>
