<?PHP

//die('<pre>'.print_r($_SERVER, true));

$errors = array();

if(!empty($_POST['newname']))
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
