<?php

/**
 * Alter taxonomy_term_page().
 * Menu callback; displays all nodes associated with a term.
 *
 * @param $term
 *	 The taxonomy term.
 * @return
 *	 The page content.
 */
function articles_term_page($term) {
	// Build breadcrumb based on the hierarchy of the term.
	$current = (object) array(
		'tid' => $term->tid,
	);
	
	// @todo This overrides any other possible breadcrumb and is a pure hard-coded
	//	 presumption. Make this behavior configurable per vocabulary or term.
	$breadcrumb = array();
	while ($parents = taxonomy_get_parents($current->tid)) {
		$current = array_shift($parents);
		$breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
	}
	$breadcrumb[] = l(t('Home'), NULL);
	$breadcrumb = array_reverse($breadcrumb);
	drupal_set_breadcrumb($breadcrumb);
	drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);

	$build = array();
	// Add term heading if the term has a description
	if (!empty($term->description)) {
		$build['term_heading'] = array(
			'#prefix' => '<div class="term-listing-heading">',
			'#suffix' => '</div>',
			'term' => taxonomy_term_view($term, 'full'),
		);
	}

	$nids = taxonomy_select_all_nodes($term->tid);
	
	if ($nids) {
		$nodes = node_load_multiple($nids);
		$build += node_view_multiple($nodes);
		$build['pager'] = array(
			'#theme' => 'pager',
			'#weight' => 5,
		);
	}
	else {
		$build['no_content'] = array(
			'#prefix' => '<p>',
			'#markup' => t('There is currently no content classified with this term.'),
			'#suffix' => '</p>',
		);
	}

	return $build;
}

