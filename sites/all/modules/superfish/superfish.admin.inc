<?php // $Id: superfish.admin.inc,v 1.2.2.1 2010/05/24 14:49:46 mehrpadin Exp $

/**
 * @file
 * Functions that are only called on the admin pages.
 */

/**
 * Overriding system settings form.
 */
function superfish_system_settings_form($form, $automatic_defaults = TRUE) {
  $form['actions']['#type'] = 'container';
  $form['actions']['#attributes']['class'][] = 'form-actions';
  $form['actions']['#weight'] = 100;
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  if ($automatic_defaults) {
    $form = _system_settings_form_automatic_defaults($form);
  }

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  $form['#submit'][] = 'system_settings_form_submit';
  // By default, render the form using theme_system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  return $form;
}

/**
 * Module settings form.
 */
function superfish_admin_settings() {
  $form['superfish_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of blocks'),
    '#multiple' => FALSE,
    '#options' => array(
      t('1'),
      t('2'),
      t('3'),
      t('4'),
      t('5'),
      t('6'),
      t('7'),
      t('8'),
      t('9'),
      t('10'),
      t('11'),
      t('12'),
      t('13'),
      t('14'),
      t('15'),
      t('16'),
      t('17'),
      t('18'),
      t('19'),
      t('20'),
      t('21'),
      t('22'),
      t('23'),
      t('24'),
      t('25'),
      t('26'),
      t('27'),
      t('28'),
      t('29'),
      t('30'),
      t('31'),
      t('32'),
      t('33'),
      t('34'),
      t('35'),
      t('36'),
      t('37'),
      t('38'),
      t('39'),
      t('40'),
    ),
    '#description' => t('The number of Superfish menu blocks.'),
    '#default_value' => variable_get('superfish_number', 2),
  );
  $form['superfish_hid'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable hoverIntent detection.'),
    '#default_value' => variable_get('superfish_hid', 1),
  );
  return superfish_system_settings_form($form, FALSE);
}