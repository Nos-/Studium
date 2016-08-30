<?php
/** @file
 * Diese Datei enthält die Templateklasse.
 */

/** Template-Klasse
 * 
 * Quelle: http://www.it-academy.cc/article/1357/PHP:+OOP+Template+System.html
*/
class template {

    var $tmp_file; // Pfad zur Template Datei
    var $error; // Fehlermeldung
    var $content; // Inhalt des Templates

    /// Konstruktor
    function template($file, $error = "Template Datei nicht gefunden!") {

        // Variabeln auf Standardwerte setzen
        $this->tmp_file = $file;
        $this->error = $error;
        $this->content = "";

    }

    /// Template Datei einlesen
    function readtemplate() {

        $file = @fopen($this->tmp_file, "r");

        if(!$file) {

            echo $this->error;

        }
        else {

            // Datei einlesen
            while(!feof($file)) {

                $temp = fgets($file, 4096);
                $this->content .= $temp;

            }

        }

    }

    /// Platzhalter im Template ersetzen
    function replace($title, $value) {

        // Alle {TITLE} durch VALUE ersetzen
        $this->content = str_replace("{" . $title . "}", $value, $this->content);

    }

    /// Fertige Datei ausgeben
    function parse() {

        return $this->content;

    }

}
?>
