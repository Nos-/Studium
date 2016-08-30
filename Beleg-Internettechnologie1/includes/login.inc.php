<?php
/** @file
 * Diese Datei enthält die Anmeldefunktionalität für die Admin-Funktionen
 * 
 * @author PwnyTail <s70350@informatik.htw-dresden.de>
 * @author N. Schwirz <s70341@informatik.htw-dresden.de>
 */

include_once("sidebar.inc.php");
include_once("assets.inc.php");

/// validate cookie value
/// @param  cookie  $_COOKIE
/// @return         boolean
function validate_cookie(array $cookie) {
    if (isset($cookie['IT1_BELEG']) ){ //php < 5.6 : and isset($cookie['IT1_BELEG']['value'])) {
        $cookie['IT1_BELEG']['value'] = data_sanitizer($cookie['IT1_BELEG']['value']);
        return true;
    } else {
        return false;
    }
};

/// validate login credentials
/// @param user     string (e-mail)
/// @param passwd   string (password-hash)
/// @return          boolean
function validate_login($user, $passwd) {
    if (isset($user) and isset($passwd)) { // simple check credentials are set
        return setcookie("IT1_BELEG", "{user: $user, password: $passwd}", time() + 3600);;
    }
    return false;
};

/// process login credentials
/// sanitize credentials and validate
/// @param user     string (e-mail)
/// @param passwd   string (password-hash)
/// @return          boolean
function post_login($user, $passwd) {
    $user = data_sanitizer($user);
    $passwd = data_sanitizer($passwd);
    return validate_login($user, $passwd);
};

/// Zeigt den Loginseite an.
function get_login_screen () {
    $headline = "IT1 Beleg - Login";

    $blog_main = render("login", array());

    echo render("default", array("HEADLINE" => $headline, "MAIN" => $blog_main,
        "SIDEBAR"=> sidebar(), "POST-ID" => '', "PAGER" => ''));
};
?>
