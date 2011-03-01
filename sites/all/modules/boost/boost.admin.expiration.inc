<?php
// $Id: boost.admin.expiration.inc,v 1.1.2.2 2011/02/21 09:28:49 mikeytown2 Exp $

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
function boost_admin_expiration_settings() {

  $form['boost_ignore_flush'] = array(
    '#type' => 'checkbox',
    '#title' => t('Ignore a cache flush command if cron issued the request.'),
    '#default_value' => variable_get('boost_ignore_flush', BOOST_IGNORE_FLUSH),
    '#description' => t(''),
  );
  $form['boost_expire_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove old cache files on cron.'),
    '#default_value' => variable_get('boost_expire_cron', BOOST_EXPIRE_CRON),
    '#description' => t(''),
  );

  // reset htaccess on submit;
  $form['#submit'][] = 'boost_form_submit_handler';
  return system_settings_form($form);
}
