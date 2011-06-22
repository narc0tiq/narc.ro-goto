<?PHP
// Configuration directives.
$conf = array();

$conf['db_is_file'] = true;
$conf['db_fname'] = PATH_BASE.'/goto.sqlite.db';

//$conf['db_dsn'] = 'sqlite://'.urlencode($conf['db_fname']).'?debug';
$conf['db_dsn'] = 'sqlite://'.$conf['db_fname'];

// Regex that redirect names must match. Should be the same as the one in .htaccess
$conf['filter_names'] = '/^[a-z0-9_-]{1,30}$/i';

// Regex that URLs must match.
$conf['filter_urls'] = '@^(https?|ftp|mumble|irc)://@i';
?>
