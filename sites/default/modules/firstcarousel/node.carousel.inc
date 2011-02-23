<?php


function node_page_carousel($node) {
	
	$limit = variable_get('firstcarousel_block_count', 4);
	
	$query = db_select('node', 'n');
	$query->innerJoin('users', 'u', 'u.uid = n.uid');
	$query->innerJoin('node_weight', 'nw', 'n.nid = nw.nid');
	$query->fields('n', array('nid', 'uid', 'title', 'created'));
	$query->fields('nw', array('weight'));
	$query->fields('u', array('name'));
	$query->condition('n.status', 1);
	$query->condition('n.type', 'article');
	$query->range(0, $limit + 1); // add 1 for the out of range node
	$query->orderBy('weight', 'ASC');
	$query->orderBy('created', 'DESC');
	
	$queue = $query->execute()->fetchAllAssoc('nid');
	
	drupal_add_js(array('firstcarousel' => array('limit' => $limit)), 'setting');
	
	return drupal_get_form('node_page_carousel_form', $node, $queue);
}

function node_page_carousel_form($form, &$form_state, $node, $queue) {

	// fix for the submit
	$module_path = drupal_get_path('module', 'firstcarousel');
	$form['#attached']['js'] = array('misc/jquery.cookie.js', $module_path . '/jquery.weightForm.js');
	$form['#attached']['css'] = array($module_path . '/firstcarousel.form.css');
	
	$form_state['current_nid'] = $node->nid;
	$form_state['node_queue'] = $queue;
	
	if (!empty($form_state['clicked_button']) && ($form_state['clicked_button']['#value'] == 'remove')) {
		$delete_nid = $form_state['clicked_button']['#array_parents'][1];
		unset($form_state['node_queue'][$delete_nid]);
	}
	
	$form['#tree'] = TRUE;
	
	$form['description'] = array(
		'#type' => 'item',
		'#title' => t('Choose the carousel articles:'),
	);
	
	$form['queue'] = array(
		'#theme' => 'firstcarousel_order',
		'#prefix' => '<div id="firstcarousel_order_wrapper">',
		'#suffix' => '</div>',
	);
	
	$clicked = isset($form_state['clicked_button']);

	$i = 0;
	foreach ($form_state['node_queue'] as $key => $values) {
		$form['queue'][$key]['title'] = array(
			'#markup' => $values->title,
		);
		$form['queue'][$key]['author'] = array(
			'#markup' => format_username($values),
		);
		$form['queue'][$key]['created'] = array(
			'#markup' => format_date($values->created),
		);
		$form['queue'][$key]['weight'] = array(
			'#type' => 'weight',
			'#title' => t('Weight for @title', array('@title' => $values->title)),
			'#title_display' => 'invisible',
			'#default_value' => $values->weight,
		);
		$form['queue'][$key]['remove'] = array(
			'#type' => 'checkbox',
			'#title' => '',
		);
		$form['queue'][$key]['position'] = array(
			'#markup' => ++$i,
		);
	}
	
	// add a textfield for adding nodes to the queue
	$form['add'] = array(
		'#type' => 'markup',
	);
	$form['add']['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Search a node'),
		'#autocomplete_path' => 'node/autocomplete',
		'#default_value' => $node->title,
	);
	$form['add']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Add node & save queue'),
		'#validate' => array('node_page_carousel_form_add_validate'),
		'#submit' => array('node_page_carousel_form_submit', 'node_page_carousel_form_add_submit', ),
	);
	
	// submit
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save queue'),
		'#disabled' => (empty($queue)) ? TRUE : FALSE,
	);
	return $form;
}

function node_page_carousel_form_submit($form, &$form_state) {
	$tag = 'carousel';

	if (!empty($form_state['values']['queue'])) {
		
		// insert the data in the db {node_weight}.
		db_delete('node_weight')->condition('tag', $tag)->execute();
		
		// insert the data in the db {node_weight}.
		$query = db_insert('node_weight')->fields(array('nid', 'tag', 'weight'));
		foreach ($form_state['values']['queue'] as $nid => $data) {
			if (!$data['remove'])
				$query->values(array('nid'=>$nid, 'tag'=>$tag, 'weight'=>$data['weight']));
		}
		
		$query->execute();
	}
	
	drupal_set_message(t('Queue updated.'), 'form-status');
}

function node_page_carousel_form_add_validate($form, &$form_state) {
	$title = $form_state['values']['add']['title'];
	$tag = 'carousel';
	$nid = db_query_range('SELECT nid FROM {node} WHERE title = :title', 0, 1, array(':title' => $title))->fetchField();
	if (!$nid) {
		form_set_error('add][title', t('Enter a valid Article\'s title.'));
	}
	else {
		$exist = (bool) db_query_range('SELECT 1 FROM {node_weight} WHERE nid = :nid AND tag = :tag', 0, 1, array(':nid' => $nid, ':tag' => $tag))->fetchField();
		if ($exist)
			form_set_error('add][title', t('Article already in the queue.'));
		else
			$form_state['values']['add']['nid'] = $nid;
	}
}

function node_page_carousel_form_add_submit($form, &$form_state) {
	$tag = 'carousel';
	$values = array(
		'nid' => $form_state['values']['add']['nid'],
		'tag' => $tag,
		'weight' => 0,
	);

	$limit = variable_get('firstcarousel_block_count', 4);
	$check_max = (db_query('SELECT COUNT(nid) FROM {node_weight} WHERE tag = :tag', array(':tag'=>$tag))->fetchField() > $limit);
	
	if ($check_max)
		db_query('DELETE FROM {node_weight} WHERE tag = :tag ORDER BY weight DESC LIMIT 1', array(':tag' => $tag));
	
	db_insert('node_weight')->fields(array('nid','weight','tag'))->values($values)->execute();
	
	// clear the queue of messages.
	drupal_get_messages('form-status', TRUE);
	drupal_set_message(t('Articles %title added to the queue.', array('%title'=> $form_state['values']['add']['title'])), 'form-status');
}


/**
 * Returns a draggable table to reorder the nodes.
 *
 * @param $variables
 *	An associative array containing:
 *	- form: A render element representing the form.
 *
 * @ingroup themeable
 */
function theme_firstcarousel_order($variables) {
	$form = $variables['form'];
	$rows = array();
	
	foreach (element_children($form) as $key) {
		$row = array();
		$form[$key]['weight']['#attributes']['class'] = array('node-order-weight');
		if (is_numeric($key)) {
			$row[] = drupal_render($form[$key]['title']);
			$row[] = drupal_render($form[$key]['weight']);
			$row[] = drupal_render($form[$key]['author']);
			$row[] = drupal_render($form[$key]['created']);
			$row[] = drupal_render($form[$key]['remove']);
			$row[] = drupal_render($form[$key]['position']);
		}
		$rows[] = array('data' => $row, 'class' => array('draggable'));
	}
	
	$header = array(
		t('title'),
		t('Weight'),
		t('Author'),
		t('Post Date'),
		t('Remove'),
		t('Position'),
	);

	if (!count($rows)) {
		array_unshift($rows, array(array(
			'data' => t('There are currently no effects in this style. Add one by selecting an option below.'),
			'colspan' => 6,
		)));
	}

	$output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'firstcarousel-order')));
	drupal_add_tabledrag('firstcarousel-order', 'order', 'sibling', 'node-order-weight');
	return $output;
}

/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 */
function node_autocomplete($string = '') {
	$matches = array();
	if ($string) {
		$result = db_select('node')->fields('node', array('title'))->condition('title', '%'.db_like($string).'%', 'LIKE')->range(0, 10)->execute();
		foreach ($result as $node) {
			$matches[$node->title] = check_plain($node->title);
		}
	}

	drupal_json_output($matches);
}
