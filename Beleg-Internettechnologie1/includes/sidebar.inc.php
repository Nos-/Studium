<?php
/** @file
 * Diese Datei enthält die Sidebar-Funktionalität
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("assets.inc.php");

/// Gibt die Auflistung aller (bzw einer bestimmten Anzahl der aktuellsten) Blogposts (Titel, Metadaten, Link zur vollständigen Version etc, jedoch kein Inhalt) zurück.
/// @param		(bool)	$adminmode	(Optional) (De)Aktiviert zusätzliche Verwaltungsfunktionen für den Admin (Standardwert: false, also deaktiviert)
/// @param		(int)	$limit		(Optional) Begrenzt die Anzeige auf eine bestimmte Anzahl Blogposts (Standardwert: 0, also alle)
/// @return							Auflistung der letzten Blogposts (als HTML-Fragment)
function get_blogposts_list($limit = 0, $adminmode = false) {
    $files = get_data_filename();

	// alle Blogposts
    if ($limit == 0) {
		$limit = count($files);
	}

    for($i=0;$i < $limit and $i < count($files);$i++) {

		if (!(is_null($files[$i]) or !!!count($files[$i]))) {
			$post = load_data_json($files[$i]);

            if ($adminmode) {
                $admin_ext = render("admin_ext", array("ID" => $files[$i]));
            }
			$post_link = render("continue_reading", array("POST-LINK" => '?post='.$files[$i]));
			$blog_main .= render("blog_list", array("POST-TITLE"=> $post->{'TITLE'},
				"POST-META_DATE"	=> $post->{'DATE'},
				"POST-META_CCOUNT"	=> count($post->{'COMMENTS'}),
				"POST-CONTENT"		=> $content,
				"POST-ACTIONS"		=> $post_link . $admin_ext));
		}
    }
	return $blog_main;
}

/** Gibt die Sidebar (Seitenspalte am rechten Rand) zurück.
 * Die Sidebar enthält:
 * * (Kalender - noch nicht implementiert)
 * * eine Auflistung der neusten Blogposts (Titel etc., kein Inhalt)
 *
 * @return	Sidebar (als HTML-Fragment)
 */
function sidebar () {

	$blogpostslists = get_blogposts_list(10, false);

    return render("blog_sidebar", array(
        "SIDEBAR-CONTENT"=>$blogpostslists));
}

/** Gibt die Sidebar (Seitenspalte am rechten Rand) mit Admin Spezifikas zurück.
 * Die Sidebar enthält:
 * * (Kalender - noch nicht implementiert)
 * * eine Auflistung aller Blogposts (Titel etc., kein Inhalt, edit, erase)
 *
 * @return	Sidebar (als HTML-Fragment)
 */
function admin_sidebar () {

	$blogpostslists = render("modal");
	$blogpostslists .= get_blogposts_list(0, true);

    return render("blog_admin_sidebar", array(
        "SIDEBAR-CONTENT"=>$blogpostslists));
}
?>
