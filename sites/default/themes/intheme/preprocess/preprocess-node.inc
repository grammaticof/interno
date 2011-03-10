<?php
/**
 * @file
 * Contents of intheme_preprocess_node().
 */

// change the view mode.
if ($key = array_search('full-view', $vars['node_attributes']['class']))
	$vars['node_attributes']['class'][$key] = $vars['view_mode'].'-view';

if ($vars['node']->type == 'article') {
	
	$vars['display_submitted'] = FALSE;
	
	switch ($vars['view_mode']) {
		case 'firstpage':
			$vars['display_submitted'] = FALSE;
		break;
	
		// add 'first' 'second' 'third' class
		case 'teaser':
		
			if (!$vars['is_front']) {
				if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
					if ($vars['id'] == 1) {
						$vars['node_attributes']['class'][] = 'first';
						$vars['node_attributes']['class'][] = 'grid-14';
						$vars['node_attributes']['class'][] = 'alpha';
						$vars['node_attributes']['class'][] = 'omega';
					}
					elseif ($vars['id'] == 2) {
						$vars['node_attributes']['class'][] = 'second';
						$vars['node_attributes']['class'][] = 'grid-7';
						$vars['node_attributes']['class'][] = 'alpha';
						// $vars['node_attributes']['class'][] = 'pull-7';
					}
					elseif ($vars['id'] == 3) {
						$vars['node_attributes']['class'][] = 'third';
						$vars['node_attributes']['class'][] = 'grid-7';
						$vars['node_attributes']['class'][] = 'omega';
					}
					else {
						$vars['node_attributes']['class'][] = 'over';
						$vars['node_attributes']['class'][] = 'grid-14';
						$vars['node_attributes']['class'][] = 'alpha';
						$vars['node_attributes']['class'][] = 'omega';
					}
				}
			}
		break;
	}
}


