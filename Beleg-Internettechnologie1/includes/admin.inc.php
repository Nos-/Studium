<?php
/** @file
 * Diese Datei enthält die Adminfunktionen fürs Blog
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("sidebar.inc.php");
include_once("assets.inc.php");

/// Zeigt Seite zum Anlegen eines neuen Blogposts an.
function get_new_post() {
    $headline = "IT1 Beleg - New Post";

    $arr = load_json("../templates/new_post.json");
    $blog_main = render("new_edit_post", array("POST-TITLE" => $arr->{"TITLE"},
        "POST-CONTENT" => $arr->{"CONTENT"}, "POST-ID" => ''));

    echo render("default", array(
        "HEADLINE" => $headline,
        "MAIN" => $blog_main,
        "SIDEBAR"=> admin_sidebar(),
        "POST-ID" => '',
        "PAGER" => ''
    ));
}

/// Zeigt Seite zum Bearbeiten eines Blogposts an.
/// @param $get		$_GET
function get_edit_post($get) {
    $headline = "IT1 Beleg - Edit Post";
    $id = filename_sanitizer($get['edit_post']);

    $arr = load_data_json($id);
    if (is_null($arr)) {
        header('Location: '. $_SERVER['SCRIPT_NAME'].'?admin&new_post');
    } else {
        $title = $arr->{'TITLE'};
        $content = $arr->{'CONTENT'};
        $blog_main = render("new_edit_post", array("POST-TITLE" => $title, "POST-CONTENT" => $content, "POST-ID" => $id ));
        echo render("default", array(
            "HEADLINE" => $headline,
            "MAIN" => $blog_main,
            "SIDEBAR"=> admin_sidebar(),
            "POST-ID" => $id,
            "PAGER" => ''
        ));
    }
}
/// get a list of all pictures
/// @return $picture_list   string
function get_all_pictures_list() {
	$blog_main = "";
    $files = get_picture_filename();

    for ($i = 0;$i<count($files); $i++) {

        $admin_ext = render("picture_admin_ext", array("ID" => $files[$i]));

        if (!!!($i % 3)) {
            if($i != 0) { $picture_list .= '</div>'; }
            $picture_list .= '<div class="row">';
        }
		$picture_list .= render("picture_part", array(
			"PICTURE-FILENAME"  => $files[$i],
			"PICTURE-INFO"      => $files[$i],
			"PICTURE-ACTIONS"   => $admin_ext
		));
    }
    if ( count($files)) {$picture_list .= '</div>';}
	return $picture_list;
}

/// Render Bilder Gallery
function get_picture_gallery() {
	$picture_modal = render("picture_modal");
	return render("picture_gallery", array("TITLE" => "Bildergallerie", 
		"PICTURES" => $picture_modal . get_all_pictures_list())
	);
}

/// Zeigt Seite zum Hochladen eines neuen Bildes an.
function get_upload_picture() {
    $headline = "IT1 Beleg - Upload Picture";

    $blog_main = render("upload_picture", array("PICTURE-ID" => "", "MAXFILESIZE" => MAX_UPLOADSIZE, "PICTURE-GALLERY" => get_picture_gallery()));

    echo render("default", array(
        "HEADLINE" => $headline,
        "MAIN" => $blog_main,
        "SIDEBAR"=> admin_sidebar(),
        "POST-ID" => '',
        "PAGER" => ''
    ));
}

function get_erase_post($id) {
    $id = filename_sanitizer($id);
    erase_post($id);
}

function get_erase_picture($id) {
    $id = filename_sanitizer($id);
    erase_picture($id);
}

/** Lädt Bilddateien auf den Server hoch. und gibt eine Erfolgs-/Fehlermeldung zurück.
 *
 * Die Datei wird ins Tempverz. hochgeladen und von dort ins, im $uploaddir hinterlegte, Verz. verschoben.
 *
 * @param   $post_filename  $_POST['upload_picture']
 * @param   $file           $_FILES
 * @return		(String) Erfolgs-/Fehlermeldung
 */
function post_upload_picture($post_filename, $file) {
//        // Error-Codes des Uploads (siehe http://www.php.net/manual/en/features.file-upload.errors.php)
//        UPLOAD_ERR_OK         = 0; // There is no error, the file uploaded with success.
//        UPLOAD_ERR_INI_SIZE   = 1; // The uploaded file exceeds the upload_max_filesize directive in php.ini.
//        UPLOAD_ERR_FORM_SIZE  = 2; // The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form.
//        UPLOAD_ERR_PARTIAL    = 3; // The uploaded file was only partially uploaded.
//        UPLOAD_ERR_NO_FILE    = 4; // No file was uploaded.
//        UPLOAD_ERR_NO_TMP_DIR = 6; // Missing a temporary folder. Introduced in PHP 4.3.10 and PHP 5.0.3.
//        UPLOAD_ERR_CANT_WRITE = 7; // Failed to write file to disk. Introduced in PHP 5.1.0.
//        UPLOAD_ERR_EXTENSION  = 8; // A PHP extension stopped the file upload. PHP does not provide a way to ascertain which extension caused the file upload to stop; examining the list of loaded extensions with phpinfo() may help. Introduced in PHP 5.2.0.

        $result	= "";
        $uploaderror = false;
        $uploadfile = filename_sanitizer(basename($post_filename)); 
        if ($uploadfile == '') {
            $uploadfile = "Namenlos";
        }

        $uploaddir = dirname($_SERVER['SCRIPT_FILENAME']) . DIRECTORY_SEPARATOR . "uploads" . DIRECTORY_SEPARATOR;
        $uploadfile = $uploaddir . $uploadfile;

        if (isset($file['datafile']['error'])) {
            if ($file['datafile']['error'] === UPLOAD_ERR_OK) {                                // Uploadfehler?
                if ($file['datafile']['size'] <= MAX_UPLOADSIZE) {           // Upload-Größe ok?
                    $image_info = getimagesize($file['datafile']['tmp_name'], $_imageinfo); // alternative Serverseitige Mimetypeermittlung; falls kein Bild, dann wird FALSE zurückgegeben
                    $mimetype = $image_info['mime'];

                    $realfileext = mime_to_ext($mimetype);
                    $uploadfile .= '.' . $realfileext;  // (korrigierte) Dateierweiterung an Namen anhängen
                    // Vorsicht vor: application/*, text/html|javascript|css|x-php
                    if (preg_match(ALLOWED_MIMETYPES, $mimetype)) {                    // erneute Mimetypeprüfung
                        if (move_uploaded_file($file['datafile']['tmp_name'], $uploadfile)) { // Dateiverschiebeoperat. erfolgreich?
                            $result = 'HTTP/1.1 200 OK';
                        } else {
                            $uploaderror = true;
                        }
                    } else {
                        $uploaderror = true;
                    }
                } else {
                    $uploaderror = true;
                }
            } else {
                $uploaderror = true;
            }
        } else {    // interner Fehler, da nicht mal das Error-Array existent
            $uploaderror = true;
        }
        if ($uploaderror) {
            $result = 'HTTP/1.1 204 No Content';
        }

        return $result;
};

/// Speichert einen Blogpost Json-formatiert in eine Datei.
/// @param $Post	der zu speichernden Blogpost (als Array)
/// @return 		ID des Blogposts
function post_post($post) {
    $title = sanitizer($post['post_title']);
    $content = data_sanitizer($post['post_content']);
    if (isset($post['post_id'])) {
        $id = filename_sanitizer($post['post_id']);
    } else {
        $id ='';
    }

    if ($id != '' and !is_null($data = load_data_json($id))) {
        $comments = $data->{'COMMENTS'};
    } else {
        $comments = array();
    }

    $id = store_json(array("TITLE" => $title, "CONTENT" => $content, "ID" => $id, "COMMENTS" => $comments, "DATE" => date()));
    return $id;
};
?>
