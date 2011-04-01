<?php

switch ($vars['region']) {
	case 'menu':

		// override default menu.
		$vars['main_menu'] = '';
		
		// render the menus as nested ULs to style up some drop downs.
		$vars['menu_data'] = $menu = omega_menu_structure(menu_tree_page_data('main-menu', NULL, FALSE));
		
		// include pathauto
		module_load_include('inc', 'pathauto');
		// change the <li> class
		foreach ($menu as $mid => $data) {
			$title = pathauto_cleanstring($data['title']);
			unset($menu[$mid]);
			$menu[$title] = $data;

			/* superfish-nav hack
			if (!isset($menu[$title]['below'])) {
				$placeholder['holder'] = array(
					'href' => '#',
					'title' => '',
				);
				$menu[$title]['below'] = $placeholder;
			}
			//*/ /* end: superfish-nav hack */
		}
		
		$vars['main_menu'] = theme('links', array(
			'links' => $menu,
			'attributes' => array(
				'class' => array('links', 'main-menu sf-menu sf-navbar'),
			),
			'heading' => array(
				'text' => t('Main menu'),
				'level' => 'h2',
				'class' => array('element-invisible'),
			)
		));
		$vars['secondary_menu'] = FALSE;
		
	break;
}

