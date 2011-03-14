<?php

/**
 * @file
 * Starter template.php file for subthemes of Omega.
 */

/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */

/**
 * Implements hook_theme().
 */
function intheme_theme(&$existing, $type, $theme, $path) {
  $hooks = array();
  
  return $hooks;
}


/**
 * Returns HTML for a list of recent content.
 *
 * @param $variables
 *   An associative array containing:
 *   - nodes: An array of recent node objects.
 *
 * @ingroup themeable
 */
function intheme_node_recent_block($vars) {
  $rows = array();
  $output = '';

  foreach ($vars['nodes'] as $node)
    $rows[$node->nid] = l($node->title, 'node/'.$node->nid);
  
  $output = theme('item_list', array('items'=>$rows));
  
  return $output;
}
