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
	// drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);
	
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
		
		// adsense on top
		$build['adsense'] = array(
			'#markup' => theme('adsense_box'),
		);		
		$build += node_view_multiple($nodes);
		
		/* only the first one big */
		$first = TRUE;
		foreach ($nodes as $nid => $node) {
			if ($first) {
				$first = FALSE;
			
				if (!empty($node->field_media))
					$build['nodes'][$nid]['field_media'] = field_view_field('node', $nodes[$nid], 'field_media', 'full');
					$build['nodes'][$nid]['field_media']['#weight'] = 1;
			}
		}
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

/**
 * Generate the content feed for a taxonomy term.
 *
 * @param $term
 *   The taxonomy term.
 */
/*
function articles_term_feed($term) {
  $channel['link'] = url('taxonomy/term/' . $term->tid, array('absolute' => TRUE));
  $channel['title'] = variable_get('site_name', 'Drupal') . ' - ' . $term->name;
  // Only display the description if we have a single term, to avoid clutter and confusion.
  // HTML will be removed from feed description.
  $channel['description'] = check_markup($term->description, $term->format, '', TRUE);
  $nids = taxonomy_select_all_nodes($term->tid, FALSE, variable_get('feed_default_items', 10));

  node_feed($nids, $channel);
}
*/
