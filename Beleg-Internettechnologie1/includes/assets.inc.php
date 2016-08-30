<?php
/** @file
 * Diese Datei enthält allgemeine Hilfsfunktionen.
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("../includes/template.class.php");

/// Ersetzt in der Vorlage (Templatedatei) alle Platzhalter (Keys) durch Werte (Values).
/// @param $template_file	Name der Templatedatei
/// @param $args			Array von Platzhaltern (Key) und stattdessen einzusetzenden Text (Value)
/// @return					Vorlage als String mit ersetzenden Plathaltern
function render($template_file, $args) {
    // Objekt erzeugen ($error wird bereits im Konstrukt definiert und ist hier nur optional)
    $template = new template("../templates/$template_file.html");
    // Datei einlesen
    $template->readtemplate();
    // Platzhalter ersetzen
    foreach ($args as $key => $value) {
        $template->replace($key, $value);
    }
    // Seite ausgeben
    return $template->parse();
}

function data_sanitizer($data) {
    $data = trim($data);
    $data = stripslashes($data);
    //$data = htmlspecialchars($data);
    return $data;
}

/** Gibt eine zum MIME-Type passende Dateierweiterung zurück.
 *
 * Quelle: http://wiki.selfhtml.org/wiki/PHP/Anwendung_und_Praxis/File_Upload#MIME-Type_erkennen
 *
 * @param type $mime_type
 * @return string|boolean
 */
function mime_to_ext($mime_type)
{
	$_mimetypes['audio/basic'] 			= 'au'; 	# *.snd 	Sound-Dateien
	$_mimetypes['audio/echospeech'] 		= 'es'; 	#		Echospeed-Dateien
	$_mimetypes['audio/tsplayer'] 			= 'tsi'; 	# 		TS-Player-Dateien
	$_mimetypes['audio/voxware'] 			= 'vox'; 	# 		Vox-Dateien
	$_mimetypes['audio/x-aiff'] 			= 'aif'; 	# *.aiff *.aifc AIFF-Sound-Dateien
	$_mimetypes['audio/x-dspeeh'] 			= 'dus'; 	# *.cht 	Sprachdateien
	$_mimetypes['audio/x-midi'] 			= 'mid'; 	# *.midi 	MIDI-Dateien
	$_mimetypes['audio/x-mpeg'] 			= 'mp2'; 	#		MPEG-Dateien
	$_mimetypes['audio/x-pn-realaudio'] 		= 'ram'; 	# *.ra 		RealAudio-Dateien
	$_mimetypes['audio/x-pn-realaudio-plugin'] 	= 'rpm'; 	# 		RealAudio-Plugin-Dateien
	$_mimetypes['audio/x-qt-stream'] 		= 'stream'; 	# 		Quicktime-Streaming-Dateien
	$_mimetypes['audio/x-wav'] 			= 'wav'; 	#		WAV-Dateien
	$_mimetypes['image/cis-cod'] 			= 'cod'; 	# 		CIS-Cod-Dateien
	$_mimetypes['image/cmu-raster'] 		= 'ras'; 	#		CMU-Raster-Dateien
	$_mimetypes['image/fif'] 			= 'fif'; 	# 		FIF-Dateien
	$_mimetypes['image/gif'] 			= 'gif'; 	#		GIF-Dateien
	$_mimetypes['image/ief'] 			= 'ief'; 	#		IEF-Dateien
	$_mimetypes['image/jpeg'] 			= 'jpg';     	# *.jpeg *.jpe 	JPEG-Dateien
	$_mimetypes['image/png'] 			= 'png'; 	# 		PNG-Dateien
	$_mimetypes['image/tiff'] 			= 'tif';        # *.tiff  	TIFF-Dateien
	$_mimetypes['image/vasa'] 			= 'mcf'; 	# 		Vasa-Dateien
	$_mimetypes['image/vnd.wap.wbmp'] 		= 'wbmp'; 	# 		Bitmap-Dateien (WAP)
	$_mimetypes['image/x-freehand'] 		= 'fh4'; 	# *.fh5 *.fhc 	Freehand-Dateien
	$_mimetypes['image/x-icon'] 			= 'ico'; 	# 		Icon-Dateien (z.B. Favoriten-Icons)
	$_mimetypes['image/x-portable-anymap'] 		= 'pnm'; 	# 		PBM Anymap Dateien
	$_mimetypes['image/x-portable-bitmap'] 		= 'pbm'; 	# 		PBM Bitmap Dateien
	$_mimetypes['image/x-portable-graymap'] 	= 'pgm'; 	# 		PBM Graymap Dateien
	$_mimetypes['image/x-portable-pixmap'] 		= 'ppm'; 	# 		PBM Pixmap Dateien
	$_mimetypes['image/x-rgb'] 			= 'rgb'; 	# 		RGB-Dateien
	$_mimetypes['image/x-windowdump'] 		= 'xwd'; 	# 		X-Windows Dump
	$_mimetypes['image/x-xbitmap'] 			= 'xbm'; 	# 		XBM-Dateien
	$_mimetypes['image/x-xpixmap'] 			= 'xpm'; 	# 		XPM-Dateien
	$_mimetypes['video/mpeg'] 			= 'mpeg'; 	# *.mpg *.mpe 	MPEG-Dateien
	$_mimetypes['video/quicktime'] 			= 'qt'; 	# *.mov 	Quicktime-Dateien
	$_mimetypes['video/vnd.vivo'] 			= 'viv'; 	# *.vivo 	Vivo-Dateien
	$_mimetypes['video/x-msvideo'] 			= 'avi'; 	# Microsoft AVI-Dateien
	$_mimetypes['video/x-sgi-movie'] 		= 'movie'; 	# Movie-Dateien

        ### hier proprietäre MIME-Types einfügen

	if (isset($_mimetypes[$mime_type]))
	{
		return $_mimetypes[$mime_type];
	}

	return false;

}

/** gibt Dateinamensstrings bereinigt zurück.
 *
 * Quelle: http://wiki.selfhtml.org/wiki/PHP/Anwendung_und_Praxis/File_Upload#Dateinamen_anpassen
 *
 * @param type string   $s      String to be filtered, must be encoded utf-8
 * @param type boolean  $filter true->filter $s for use as filename and remove reserved expressions and signs for Windows, Linux, php, apache
 * @return string   (and boolean FALSE, if invalid or an error occoured)
 */
function filename_sanitizer($data, $filter=true) {
    ## Normalizer-class missing!
    if ( class_exists("Normalizer", $autoload = false)) {
        $data    = Normalizer::normalize( $data, Normalizer::FORM_D );
    }

    ## maps German (umlauts) and other European characters onto two characters before just removing diacritics
    $data    = preg_replace( '@\x{00c4}@u'    , "Ae",    $data );    // umlaut Ä => Ae
    $data    = preg_replace( '@\x{00d6}@u'    , "Oe",    $data );    // umlaut Ö => Oe
    $data    = preg_replace( '@\x{00dc}@u'    , "Ue",    $data );    // umlaut Ü => Ue
    $data    = preg_replace( '@\x{00e4}@u'    , "ae",    $data );    // umlaut ä => ae
    $data    = preg_replace( '@\x{00f6}@u'    , "oe",    $data );    // umlaut ö => oe
    $data    = preg_replace( '@\x{00fc}@u'    , "ue",    $data );    // umlaut ü => ue
    $data    = preg_replace( '@\x{00f1}@u'    , "ny",    $data );    // ñ => ny
    $data    = preg_replace( '@\x{00ff}@u'    , "yu",    $data );    // ÿ => yu

    ## maps special characters (characters with diacritics) on their base-character followed by the diacritical mark
    ## exmaple:  Ú => U´,  á => a`

    $data    = preg_replace( '@\pM@u'        , "",    $data );    // removes diacritics

    $data    = preg_replace( '@\x{00df}@u'    , "ss",    $data );    // maps German ß onto ss
    $data    = preg_replace( '@\x{00c6}@u'    , "Ae",    $data );    // Æ => Ae
    $data    = preg_replace( '@\x{00e6}@u'    , "ae",    $data );    // æ => ae
    $data    = preg_replace( '@\x{0132}@u'    , "Ij",    $data );    // ? => Ij
    $data    = preg_replace( '@\x{0133}@u'    , "ij",    $data );    // ? => ij
    $data    = preg_replace( '@\x{0152}@u'    , "Oe",    $data );    // Œ => Oe
    $data    = preg_replace( '@\x{0153}@u'    , "oe",    $data );    // œ => oe

    $data    = preg_replace( '@\x{00d0}@u'    , "D",    $data );    // Ð => D
    $data    = preg_replace( '@\x{0110}@u'    , "D",    $data );    // Ð => D
    $data    = preg_replace( '@\x{00f0}@u'    , "d",    $data );    // ð => d
    $data    = preg_replace( '@\x{0111}@u'    , "d",    $data );    // d => d
    $data    = preg_replace( '@\x{0126}@u'    , "H",    $data );    // H => H
    $data    = preg_replace( '@\x{0127}@u'    , "h",    $data );    // h => h
    $data    = preg_replace( '@\x{0131}@u'    , "i",    $data );    // i => i
    $data    = preg_replace( '@\x{0138}@u'    , "k",    $data );    // ? => k
    $data    = preg_replace( '@\x{013f}@u'    , "L",    $data );    // ? => L
    $data    = preg_replace( '@\x{0141}@u'    , "L",    $data );    // L => L
    $data    = preg_replace( '@\x{0140}@u'    , "l",    $data );    // ? => l
    $data    = preg_replace( '@\x{0142}@u'    , "l",    $data );    // l => l
    $data    = preg_replace( '@\x{014a}@u'    , "N",    $data );    // ? => N
    $data    = preg_replace( '@\x{0149}@u'    , "n",    $data );    // ? => n
    $data    = preg_replace( '@\x{014b}@u'    , "n",    $data );    // ? => n
    $data    = preg_replace( '@\x{00d8}@u'    , "O",    $data );    // Ø => O
    $data    = preg_replace( '@\x{00f8}@u'    , "o",    $data );    // ø => o
    $data    = preg_replace( '@\x{017f}@u'    , "s",    $data );    // ? => s
    $data    = preg_replace( '@\x{00de}@u'    , "T",    $data );    // Þ => T
    $data    = preg_replace( '@\x{0166}@u'    , "T",    $data );    // T => T
    $data    = preg_replace( '@\x{00fe}@u'    , "t",    $data );    // þ => t
    $data    = preg_replace( '@\x{0167}@u'    , "t",    $data );    // t => t

    // remove all non-ASCii characters
    $data    = preg_replace( '@[^\0-\x80]@u'  , "",     $data );

    $data = sanitizer($data);
    ## remove all reserved expressions and signs for Windows, Linux, php, apache
    if ($filter === true)
    {
	## avoid reserved expressions
	$_names = array( 'CON', 'PRN', 'AUX', 'NUL', 'COM1', 'COM2', 'COM3', 'COM4',
	  'COM5', 'COM6', 'COM7', 'COM8', 'COM9', 'LPT1', 'LPT2', 'LPT3', 'LPT4',
	  'LPT5', 'LPT6', 'LPT7', 'LPT8', 'LPT9');

	if (in_array(strtoupper($data), $_names, true)) return false;
    }

    ## possible errors in UTF8-regular-expressions
    if (empty($data)) return false;

    return $data;
}

/// Daten auf invalide Zeichen pruefen und entfernen
/// @param  $data   string
/// @return $data   modified string
function sanitizer($data) {
    $data = data_sanitizer($data);
//    $data = filename_sanitizer($data);
    $data = htmlspecialchars($data);
    return $data;
}

/// Daten Json-codiert in eine Datei speichern. Als Dateiname wird, falls gesetzt, das Attribut 'ID' des Übergabeparameters, ansonsten das aktuelle Datum, verwendet.
/// @param $arr		zu speichernde Daten
/// @return			Dateiname, in den gespeichert wurde
function store_json($arr) {
    $arr = (array)$arr;
    if (isset($arr['ID']) and $arr['ID'] != '') {
        $file = $arr['ID'];
    } else {
        $file = date("Y_m_d-H_i_s");	// Zeit als Datum-Uhrzeit (incl. Sek); Alternativ Timestamp mit "U"
        $arr['ID'] = $file;
    }
    $arr['DATE'] =  date("Y-m-d H:i");
    $json = json_encode($arr);
    //json_error();
    file_put_contents("../data/$file.json", $json, LOCK_EX);
    return $file;
}

/// Json-codierte Daten aus einer Datei einlesen und dekodieren.
/// @param $file	Name der einzulesenden Datei (ohne Pfad und Dateierw., welche automatisch ergänzt werden)
/// @return			Daten
function load_data_json($filename) {
    return load_json("../data/$filename.json");
}

/// Json-codierte Daten aus Pfad/Datei einlesen und dekodieren.
/// @param $file	Name der einzulesenden Datei (samt Pfad und Dateierweiterung)
/// @return			Daten
function load_json($file) {
    $json = file_get_contents($file);
    $arr = json_decode($json);
    //json_error();
    return $arr;
}

function json_error() {
    switch(json_last_error()) {
    case JSON_ERROR_NONE:
        echo ' - Keine Fehler';
        break;
    case JSON_ERROR_DEPTH:
        echo ' - Maximale Stacktiefe überschritten';
        break;
    case JSON_ERROR_STATE_MISMATCH:
        echo ' - Unterlauf oder Nichtübereinstimmung der Modi';
        break;
    case JSON_ERROR_CTRL_CHAR:
        echo ' - Unerwartetes Steuerzeichen gefunden';
        break;
    case JSON_ERROR_SYNTAX:
        echo ' - Syntaxfehler, ungültiges JSON';
        break;
    case JSON_ERROR_UTF8:
        echo ' - Missgestaltete UTF-8 Zeichen, möglicherweise fehlerhaft kodiert';
        break;
    default:
        echo ' - Unbekannter Fehler';
        break;
    }

}

/// Gibt eine Liste aller Dateien im Datenverzeichnis, sortiert nach dem Dateinamen, zurück.
/// @return		Dateinamensarray, sortiert nach Dateinamen
function get_data_filename() {
    $files = array();
    if ($handle = opendir('../data/')) {
        while (false !== ($entry = readdir($handle))) {
            if (!!!preg_match("/^(\.|\.\.)$/", $entry) and !!preg_match("/\.json$/",$entry)) {
                array_push($files, preg_replace('/\.json$/','',$entry));
            }
        }

        closedir($handle);
    }
    rsort($files);
    return $files;
}

/// Gibt eine Liste aller Dateien im Uploadverzeichnis, sortiert nach dem Dateinamen, zurück.
/// @return		Dateinamensarray, sortiert nach Dateinamen
function get_picture_filename() {
    $files = array();
    $handle = opendir('uploads/');
    if ($handle) {
        while (false !== ($entry = readdir($handle))) {
            if (!!!preg_match("/^(\.|\.\.)$/", $entry)) {
                array_push($files, $entry);
            }
        }

        closedir($handle);
    }
    rsort($files);
    return $files;
}

/// Gibt die Anzahl aller Blogposts zurück
/// @return		Anzahl aller Blogposts
function get_posts_count() {
	return count(get_data_filename());
}

/// Löscht Blogpost
/// @param      string
/// @return     boolean
function erase_post($id) {
    return unlink("../data/$id.json");
}

/// Löscht Bild
/// @param      string
/// @return     boolean
function erase_picture($id) {
    return unlink("uploads/$id");
}

?>
