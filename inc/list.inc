<?PHP

$redirects = $sql->get_redirects();

echo fetch_header();

?>
<table border="0px" cellpadding="0px" cellspacing="0px" style="width:90%; position: relative; left: 5%">
	<tr><th style="width: 20%">Short Name</th><th>Goes to URL</th></tr>
<?PHP
foreach($redirects as $keyword => $url)
{
	$keyword = htmlentities($keyword); $url = htmlentities($url);
	echo '<tr>
		<td style="padding: 4px"><tt><a href="/'.$keyword.'">'.$keyword.'</a></tt></td>
		<td style="padding: 4px"><a href="'.$url.'">'.$url.'</a></td>
	</tr>'."\n";
}
?>
</table>
<div style="padding-top: 20px; font-size: 0.7em"><a href="/favicon.ico">Favicon.ico</a> and other icons based on <a href="http://somerandomdude.com/work/bitcons/">Bitcons</a> by <a href="http://somerandomdude.com/">P.J. Onori</a>.</div>
</body></html>
