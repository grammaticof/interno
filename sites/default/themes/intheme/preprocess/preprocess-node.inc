<?php
/**
 * @file
 * Contents of intheme_preprocess_node().
 */

// change the view mode.
if ($key = array_search('full-view', $vars['node_attributes']['class']))
	$vars['node_attributes']['class'][$key] = $vars['view_mode'].'-view';

switch ($vars['view_mode']) {
	case 'firstpage':
		$vars['display_submitted'] = FALSE;
	break;
}

