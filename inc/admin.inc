<?PHP

$errors = array();

if(empty($_SESSION['login_timestamp']) or
   ((time() - $_SESSION['login_timestamp']) > $conf['max_login_secs']))
{
	unset($_SESSION['login_timestamp']);
	unset($_SESSION['login_username']);

	if(!empty($_POST['username']))
	{
		if(empty($conf['override_login']))
		{
			$user = $sql->get_user($_POST['username']);
			$pw_hash = sha1($_POST['username'].' '.$_POST['password']);

			if(empty($user) or ($pw_hash != $user[$_POST['username']]))
				$errors[] = 'Invalid username/password combo!';
		}

		if(empty($errors))
		{
			$_SESSION['login_timestamp'] = time();

			// HACK: This is probably going to tie us to Apache...
			header('Location: '.$_SERVER['REQUEST_URI']);
		}
	}

	echo fetch_header();
	if(!empty($errors))
	{
		echo '<ul style="color: #b00; font-weight: bold">';
		foreach($errors as $e)
		{
			echo '<li>'.$e.'</li>';
		}
		echo '</ul>';
	}
?>
<form method="post">
	<div style="text-align: center">
		<label for="username">Username:</label> <input type="text" name="username" /><br/>
		<label for="password">Password:</label> <input type="password" name="password" /><br/>
		<input type="submit" value="Log in" />
	</div>
</form>
<?PHP
	die();
}
elseif(!empty($_POST['newusername']))
{
	if(!preg_match($conf['filter_names'], $_POST['newusername']))
		$errors[] = 'Bad name! Must match the regex: '.htmlentities($conf['filter_names']);

	if($_POST['newpassword'] != $_POST['newpassword2'])
		$errors[] = 'Password does not match the confirmation re-entry!';

	if(empty($errors))
	{
		$password_hash = sha1($_POST['newusername'].' '.$_POST['newpassword']);
		$sql->add_user($_POST['newusername'], $password_hash);

		// HACK: This is probably going to tie us to Apache...
		header('Location: '.$_SERVER['REQUEST_URI']);
	}
}
elseif(!empty($_POST['newname']))
{
	if(!preg_match($conf['filter_names'], $_POST['newname']))
		$errors[] = 'Bad name! Must match the regex: '.htmlentities($conf['filter_names']);

	if(!preg_match($conf['filter_urls'], $_POST['newurl']))
		$errors[] = 'Bad URL! Must match the regex: '.htmlentities($conf['filter_urls']);

	if(empty($errors))
	{
		$sql->add_redirect($_POST['newname'], $_POST['newurl']);

		// HACK: This is probably going to tie us to Apache...
		header('Location: '.$_SERVER['REQUEST_URI']);
	}
}
elseif(!empty($_GET['drop']))
{
	$action = $_SERVER['REQUEST_URI']; // HACK: see above
	$action = substr($action, 0, strpos($action, '?'));

	$keyword = htmlentities($_GET['drop']);
	echo fetch_header();
?>
<form method="post" action="<?PHP echo $action; ?>">
	<h2>Definitely delete the redirect "<?PHP echo $keyword; ?>"?</h2>
	<div style="text-align: center">
		<input type="submit" name="yes" value="Yes" />
		<input type="submit" name="no" value="No" />
	</div>
	<input type="hidden" name="drop" value="<?PHP echo $keyword; ?>" />
</form>
<?PHP
	die();
}
elseif(!empty($_POST['drop']) and !empty($_POST['yes']))
{
	if(preg_match($conf['filter_names'], $_POST['drop']))
		$sql->delete_redirect($_POST['drop']);

	// HACK: Still probably tying us to Apache...
	header('Location: '.$_SERVER['REQUEST_URI']);
}
elseif(!empty($_GET['dropuser']))
{
	$action = $_SERVER['REQUEST_URI']; // HACK: see above
	$action = substr($action, 0, strpos($action, '?'));

	$username = htmlentities($_GET['dropuser']);
	echo fetch_header();
?>
<form method="post" action="<?PHP echo $action; ?>">
	<h2>Definitely delete the user "<?PHP echo $username; ?>"?</h2>
	<div style="text-align: center">
		<input type="submit" name="yes" value="Yes" />
		<input type="submit" name="no" value="No" />
	</div>
	<input type="hidden" name="dropuser" value="<?PHP echo $username; ?>" />
</form>
<?PHP
	die();
}
elseif(!empty($_POST['dropuser']) and !empty($_POST['yes']))
{
	if(preg_match($conf['filter_names'], $_POST['dropuser']))
		$sql->delete_user($_POST['dropuser']);

	// HACK: Still probably tying us to Apache...
	header('Location: '.$_SERVER['REQUEST_URI']);
}

$redirects = $sql->get_redirects();

echo fetch_header();

if(!empty($errors))
{
	echo '<ul style="color: #b00; font-weight: bold">';
	foreach($errors as $e)
	{
		echo '<li>'.$e.'</li>';
	}
	echo '</ul>';
}
?>

<form method="post">
<table border="0px" cellpadding="0px" cellspacing="0px" style="width:90%; position: relative; left: 5%">
	<tr><th style="width: 20%">Short Name</th><th>URL</th></tr>
<?PHP
foreach($redirects as $keyword => $url)
{
	$keyword = htmlentities($keyword); $url = htmlentities($url);
	echo '<tr>
		<td style="padding: 4px"><tt>'.$keyword.'</tt> <a href="?drop='.$keyword.'">[del]</a></td>
		<td style="padding: 4px"><a href="'.$url.'">'.$url.'</a></td>
	</tr>'."\n";
}
?>
	<tr><td>
		<input type="text" name="newname"
			   value="<?PHP echo (empty($_POST['newname'])?'':htmlentities($_POST['newname']))?>"
			   style="width: 96%; position: relative; left: 2%"
		/>
	</td><td>
		<input type="text" name="newurl"
			   value="<?PHP echo (empty($_POST['newurl'])?'':htmlentities($_POST['newurl']))?>"
			   style="width: 79%; position: relative; left: 1%"
		/>
		<input type="submit" value="Add/Replace" style="width: 15%; position: relative; left: 1%" />
	</td></tr>
</table>
</form>

<?PHP

$users = $sql->get_users();

?>

<form method="post">
<table border="0px" cellpadding="0px" cellspacing="0px" style="width:200px; position: relative; left: 5%">
	<tr><th style="width: 20%">User Name</th></tr>
<?PHP
foreach($users as $username => $password_hash)
{
	$username = htmlentities($username);
	echo '<tr>
		<td style="padding: 4px"><tt>'.$username.'</tt> <a href="?dropuser='.$username.'">[del]</a></td>
	</tr>'."\n";
}
?>
	<tr><td>
		<input type="text" name="newusername"
			   value="<?PHP echo (empty($_POST['newusername'])?'':htmlentities($_POST['newusername']))?>"
			   style="width: 90%; position: relative; left: 5%"
		/>
		<br/>
		<input type="password" name="newpassword"
			   value="<?PHP echo (empty($_POST['newpassword'])?'':htmlentities($_POST['newpassword']))?>"
			   style="width: 90%; position: relative; left: 5%"
		/>
		<br/>
		<input type="password" name="newpassword2"
			   value="<?PHP echo (empty($_POST['newpassword2'])?'':htmlentities($_POST['newpassword2']))?>"
			   style="width: 90%; position: relative; left: 5%"
		/>
			   <br/>
		<input type="submit" value="Add/Replace" style="width: 90%; position: relative; left: 5%" />
	</td></tr>
</table>
</form>
