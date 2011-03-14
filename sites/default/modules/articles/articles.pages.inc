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

	// breadcrumb
	$breadcrumb = array();
	$tid_parents = array_reverse(taxonomy_get_parents_all($term->tid));
	foreach ($tid_parents as $i => $term_data)
		$breadcrumb[] = l($term_data->name, 'taxonomy/term/' . $term_data->tid);
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

	$nids = taxonomy_select_all_nodes($term->tid, FALSE, 15);

	if ($nids) {
		$nodes = node_load_multiple($nids);
		$build += node_view_multiple($nodes);

		/* PAGER
		$build['pager'] = array(
			'#theme' => 'pager',
			'#weight' => 5,
		);
		//*/
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

