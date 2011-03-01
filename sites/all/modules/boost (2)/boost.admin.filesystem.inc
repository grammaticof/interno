<?php
// $Id: boost.admin.filesystem.inc,v 1.1.2.3 2011/02/21 09:28:49 mikeytown2 Exp $

/**
 * @file
 * Admin page callbacks for the boost module.
 */

/**
 * Form builder; Configure boost settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function boost_admin_filesystem_settings() {

  $form['boost_root_cache_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Root cache directory'),
    '#default_value' => variable_get('boost_root_cache_dir', BOOST_ROOT_CACHE_DIR),
  );
  $form['boost_normal_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Normal cache directory'),
    '#default_value' => variable_get('boost_normal_dir', BOOST_NORMAL_DIR),
  );
  $form['boost_char'] = array(
    '#type' => 'textfield',
    '#title' => t('Character replacement for "?" in the URL'),
    '#default_value' => variable_get('boost_char', BOOST_CHAR),
  );

  // reset htaccess on submit;
  $form['#submit'][] = 'boost_form_submit_handler';
  return system_settings_form($form);
}
