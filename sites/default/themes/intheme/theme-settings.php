<?php
// $Id: theme-settings.php,v 1.3.2.3 2010/08/03 14:19:52 himerus Exp $

/**
 * @file
 * Theme settings for the Omega theme.
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function intheme_form_system_theme_settings_alter(&$form, &$form_state) {
  // Include any changes to the theme settings here.
  unset($form['omega_regions']['postscript']['omega_postscript_third_width']);
  unset($form['omega_regions']['postscript']['omega_postscript_third_prefix']);
  unset($form['omega_regions']['postscript']['omega_postscript_third_suffix']);
  unset($form['omega_regions']['postscript']['omega_postscript_fourth_width']);
  unset($form['omega_regions']['postscript']['omega_postscript_fourth_prefix']);
  unset($form['omega_regions']['postscript']['omega_postscript_fourth_suffix']);  
}
