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
  return array(
		'item_list_no_div' => array(
			'variables' => array(
				'items' => NULL,
				'title' => NULL,
				'type' => 'ul',
			),
		),
	);
}

/**
 * Returns HTML for a list or nested list of items.
 *
 * @param $variables
 *   An associative array containing:
 *   - items: An array of items to be displayed in the list. If an item is a
 *     string, then it is used as is. If an item is an array, then the "data"
 *     element of the array is used as the contents of the list item. If an item
 *     is an array with a "children" element, those children are displayed in a
 *     nested list. All other elements are treated as attributes of the list
 *     item element.
 *   - title: The title of the list.
 *   - type: The type of list to return (e.g. "ul", "ol").
 *   - attributes: The attributes applied to the list element.
 */
function intheme_item_list_no_div($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];

  $attributes = $variables['attributes'];
  
  $output = '';
  
  
  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 0) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  
  $output .= '';

  return $output;
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
