<?php
/** @file
 * Diese Datei enthält die normalen Anwenderfunktionalitäten fürs Blog.
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("sidebar.inc.php");
include_once("assets.inc.php");
include_once("lib/Parsedown.php");

/// Speichert einen neuen Kommentar zu einem bestimmten Blogpost.
/// @param $post_id		ID des entspr. Blogposts
/// @param $comment		der zuspeichernde Kommentar
function post_comment($post_id, $comment) {
    $post_id = filename_sanitizer($post_id);
    if (is_null($post_id) or $post_id == '') { return; }
    $cname = sanitizer($comment['CNAME']);
    if (is_null($cname) or $cname == '') { return; }
    $ccontent = sanitizer($comment['CCONTENT']);
    if (is_null($ccontent) or $ccontent == '') { return; }

    $cemail = sanitizer($comment['CEMAIL']);

    $post = load_data_json($post_id);
    array_unshift($post->{'COMMENTS'}, array(
        'CDATE' => date("Y-m-d H:i"),
        'CNAME' => $cname,
        'CEMAIL' => $cemail,
        'CCONTENT' => $ccontent)
    );
    store_json($post);
}

/// Zeigt einen Blogpost + Kommentarbereich auf einer eigenen Seite an.
/// @param $post_id		ID des anzuzeigenden Blogposts
function get_postpage($post_id) {
    $post_id = filename_sanitizer($post_id);
    $headline = "IT1 Beleg - Post";

    if  (!is_null($post_id) and $post_id != '') {
        $post = load_data_json($post_id);
        $content = Parsedown::instance()->text($post->{'CONTENT'});
        $comments_list = build_comments_list($post->{'COMMENTS'});
        $comments = render("comments_part", array("COMMENTS_LIST" => $comments_list, 'POST-ID' => $post_id));
    } else {$post_id = '';}

    $blog_main = render("blog_main", array("POST-TITLE"=> $post->{'TITLE'},
		"POST-META_DATE"	=> $post->{'DATE'},
		"POST-META_CCOUNT"	=> count($post->{'COMMENTS'}),
        "POST-CONTENT"		=> $content . $comments,
        "POST-LINK"			=> ""));

    echo render("default", array(
        "HEADLINE" => $headline,
        "MAIN" => $blog_main,
        "SIDEBAR"=> sidebar(),
        "POST-ID" => $post_id,
        "PAGER" => ""
    ));
};

/// Gibt einen einzelnen Blogpost zurück.
/// @param $file		ID des anzuzeigenden Blogposts
/// @param $shortened	(OPTIONAL) gibt an, ob der Blogbeitrag gekürzt (=true) werden soll oder nicht (=false, Vorgabe)
/// @return				Blogeintrag (als HTML-Fragment)
function get_blogpost($file, $shortened=false) {
    if (is_null($file) or !!!count($file)) {
        $blog_main = render("blog_main", array("POST-TITLE"=> "Kein Blogpost vorhanden",
            "POST-META" => date("Y-m-d H:i"),
            "POST-CONTENT" => ""));
    } else {
		// Blogposts laden
        $post = load_data_json($file);

        // Blogbeitrag kürzen, falls gewünscht
        if ($shortened) {
            $cont = '';
            $lines = explode("\n", $post->{'CONTENT'});
            for ($i=0;$i<16 and $i<count($lines);$i++) {
                 $cont .= $lines[$i];
            }
            $post->{'CONTENT'} = $cont;
        }

        // Blogpostinhalt von Markdown in HTML übersetzen
        $content = Parsedown::instance()->text($post->{'CONTENT'});

        $post_link = render("continue_reading", array("POST-LINK" => "?post=$file"));
        $blog_main = render("blog_main", array("POST-TITLE"=> $post->{'TITLE'},
            "POST-META_DATE"	=> $post->{'DATE'},
            "POST-META_CCOUNT"	=> count($post->{'COMMENTS'}),
            "POST-CONTENT"		=> $content,
            "POST-LINK"			=> $post_link));
    }
    return $blog_main;
}

/// Gibt eine bestimmte Anzahl Blogposts zurück.
/// @param	$offset			Nr. des ersten zurückzugebenden Blogposts (aus der Liste aller Blogposts) (optional, Standardwert = 0)
/// @param	$posts_per_page	Anzahl der zurückzugebenden Blogposts (optional, Standardwert = 2)
/// @return					Liste aller Blogposts (als HTML-Fragment)
function get_some_blogposts($offset=0, $posts_per_page=2) {
    $files = get_data_filename();
    $blogposts = array();

    for ($i = $offset; $i<($offset+$posts_per_page) and $i<count($files); $i++) {
		array_push($blogposts, get_blogpost($files[$i], true));
    }

    return $blogposts;
}

/// Zeigt die Startseite an.
function get_startpage() {
	$offset = 0;
	$posts_per_page = 2;
	$prev_disabled = '';
	$next_disabled = '';

	$posts_count = get_posts_count();
	if (isset($_GET['offset'])) {
		$offset = $_GET['offset'] + 0;
	}
	if ($offset < 0) {
		$offset = 0;
	}
	if ($offset > $posts_count) {
		$offset = $posts_count;
	}

	// Pagination - vorige Seite (im Zweifel die 1.)
	if ($offset < $posts_per_page) {
		$prev_link = "?offset=0";
		$prev_disabled = 'hidden';
	} else {
		$prev_link = "?offset=" . ($offset - $posts_per_page);
	}

	// Pagination - nächste Seite (im Zweifel die letzte)
	if ($offset >= ($posts_count - $posts_per_page)) {
		$next_link = "?offset=" . ($posts_count - $posts_per_page);
		$next_disabled = 'hidden';
	} else {
		$next_link = "?offset=" . ($offset + $posts_per_page);
	}

    // startpage
    $headline = "IT1 Beleg";

	$blogposts = get_some_blogposts($offset, $posts_per_page);
    foreach($blogposts as $post) {
        $main .= $post;
    }

	$pager = render("pager", array(
		"PREV-DISABLED"	=> $prev_disabled,
		"PREV-LINK"		=> $prev_link,
		"NEXT-DISABLED"	=> $next_disabled,
		"NEXT-LINK"		=> $next_link
	));

    echo render("default", array(
		"HEADLINE" 		=> $headline,
		"MAIN" 			=> $main,
		"SIDEBAR" 		=> sidebar(),
		"POST-ID" 		=> '',
		"PAGER"			=> $pager
	));
};

/// Gibt eine Liste aller Kommentare eines bestimmten Blogposts zurück.
/// @param $comments	???
/// @return				Liste aller Kommentare des Blogposts (als HTML-Fragment)
function build_comments_list($comments) {
    $comments = (array)$comments;
    foreach ($comments as $comment) {
        $comments_list .= render('comments_list', array(
            'CNAME' => $comment->{'CNAME'},
            'CDATE' => $comment->{'CDATE'},
            'CCONTENT' => $comment->{'CCONTENT'}
        ));
    }
    return $comments_list;
}
?>
