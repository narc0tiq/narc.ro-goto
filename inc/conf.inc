<?PHP
// Configuration directives.
$conf = array();

$conf['db_is_file'] = true;
$conf['db_fname'] = PATH_BASE.'/goto.sqlite3.db';

$conf['db_dsn'] = 'sqlite3://'.$conf['db_fname'];
$conf['db_debug'] = false;

// Regex that redirect names must match. Should be the same as the one in .htaccess
$conf['filter_names'] = '/^[a-z0-9_-]{1,30}$/i';

// Regex that URLs must match.
$conf['filter_urls'] = '@^(https?|ftp|mumble|irc)://@i';

// How long to stay logged in to the admin panel?
$conf['max_login_secs'] = 300;

// Overriding the login requirement will make it possible to log in with ANY
//username/password! This should normally be set to false, unless you have a
//brand new install or did something stupid.
$conf['override_login'] = false;
?>
