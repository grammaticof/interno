<?php

// Add conditional stylesheets for IE
drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 8', '!IE' => FALSE), 'preprocess' => FALSE));
drupal_add_css(path_to_theme() . '/css/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));


// taxonomy class top
if (!$vars['is_front']) {
	// Add unique classes for each page and website section
	if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
		$tid = arg(2);
		
		// clean useless classes
		if ($key = array_search('page-taxonomy-term', $vars['classes_array']))
			unset($vars['classes_array'][$key]);
		if ($key = array_search('page-taxonomy-term-', $vars['classes_array']))
			unset($vars['classes_array'][$key]);
		if ($key = array_search('page-taxonomy-term-'.$tid, $vars['classes_array']))
			unset($vars['classes_array'][$key]);
		
		$term = taxonomy_term_load($tid);
		$vars['classes_array'][] = 'page-taxonomy-'.$term->vocabulary_machine_name;
		$vars['classes_array'][] = 'page-taxonomy-'.$term->vocabulary_machine_name.'-'.drupal_html_class($term->name);

		sort($vars['classes_array']);
	}
}



