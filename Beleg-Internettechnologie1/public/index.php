<?php
/** @file
 * Diese Datei enthält das Hauptscript, von dem alle anderen aufgerufen werden.
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("../includes/login.inc.php");
include_once("../includes/admin.inc.php");
include_once("../includes/userpages.inc.php");

// GLOBAL DEFINITIONS
define(ALLOWED_MIMETYPES, "/^image\//");      // mehrere Einträge können gemäß RegExp per "|" Oder-verknüpft werden
define(MAX_UPLOADSIZE, 2097152);              // 2 MB

// DEBUG INFORMATION
//error_reporting(E_ALL);     // Alle Fehler anzeigen
//foreach ($_POST as $key => $value) {
//    echo "POST: $key => $value |";
//}
//foreach ($_GET as $key => $value) {
//    echo "GET: $key => $value |";
//}
//foreach ($_COOKIE as $key => $value) {
//    echo "COOKIE: $key => $value |";
//}
//foreach ($_FILES as $key => $value) {
//    echo "FILES: $key => $value |";
//}
// END DEBUG INFORMATION

/// REQUEST METHOD POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    /// upload pictures
    if (isset($_POST['upload_picture'])) {
        if (validate_cookie($_COOKIE)) {
			header(post_upload_picture($_POST['upload_picture'], $_FILES));		// hochzuladendes Bild entgegennehmen und Erfolgs-/ Fehlermeldung zurückmelden
			get_upload_picture();				// Bilderhochlademaske/ -gallerie anzeigen
        } else {
            get_login_screen();
        }
    }

    /// new or edit post
    if ((isset($_POST['post_title']) and
      isset($_POST['post_content'])) or
      isset($_POST['post_id'])) {
        if (validate_cookie($_COOKIE)) {
            header('Location: '. $_SERVER['SCRIPT_NAME'].'?admin&edit_post='.post_post($_POST));
        } else {
            get_login_screen();
        }
    }

    /// login
    if (isset($_POST['login_name']) and isset($_POST['login_passwd'])) {
        if (post_login($_POST['login_name'], $_POST['login_passwd'])) {
            header('Location: '. $_SERVER['REQUEST_URI']);
        } else {
            header('Location: '. $_SERVER['SCRIPT_NAME']);
        }
    }

    /// comment
    if (isset($_POST['post']) and isset($_POST['comment_name']) and isset($_POST['comment_content'])) {
        post_comment($_POST['post'], array(
            "CNAME" => $_POST['comment_name'],
            "CEMAIL" => $_POST['comment_email'],
            "CCONTENT" => $_POST['comment_content']
        ));
        header('Location: '. $_SERVER['SCRIPT_NAME'].'?post='.$_POST['post']);
    }
}

/// REQUEST METHOD GET
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    if (isset($_GET['admin'])) {
        if (validate_cookie($_COOKIE)) {
            if (isset($_GET['new_post'])) {     get_new_post(); }
            elseif (isset($_GET['edit_post']) and
                $_GET['edit_post'] != '') {    get_edit_post($_GET);}
            elseif (isset($_GET['upload_picture'])) { get_upload_picture(); }
            elseif (isset($_GET['erase_post']) and
                $_GET['erase_post'] != '') {
                get_erase_post($_GET['erase_post']);
                header('Location: '. $_SERVER['SCRIPT_NAME'].'?admin&new_post');
            } elseif (isset($_GET['erase_picture']) and
                $_GET['erase_picture'] != '') {
                get_erase_picture($_GET['erase_picture']);
				get_upload_picture();
            } else { get_startpage(); }
        } else {
            get_login_screen();
        }
    } elseif (isset($_GET['post'])) {
        get_postpage($_GET['post']);
    } else {
        get_startpage();
    }
}
?>
