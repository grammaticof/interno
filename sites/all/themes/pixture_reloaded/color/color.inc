<?php
// $Id: color.inc,v 1.8.2.11 2010/10/30 23:16:50 jmburnz Exp $
/*
 * @file color.inc
 * color.inc for Pixture Reloaded
 */
$info = array(
  // Fields
  'fields' => array(
    'base' => t('Base'),
    'link' => t('Links'),
    'top' => t('Header top'),
    'bottom' => t('Header bottom'),
    'text' => t('Text'),
    'blockh' => t('Block header'),
    'blockbg' => t('Block body'),
    'borders' => t('Borders'),
    'sticky' => t('Sticky teaser'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Girly Pink (default)'),
      'colors' => array(
        'base' => '#eb52c1',
        'link' => '#b21f88',
        'top' => '#b800a6',
        'bottom' => '#ff6bfe',
        'text' => '#555555',
        'blockh' => '#eb5ac3',
        'blockbg' => '#f9cbec',
        'borders' => '#f9cbec',
        'sticky' => '#f9cbec',
      ),
    ),
    'redcarpet' => array(
      'title' => t('Red Carpet'),
      'colors' => array(
        'base' => '#de8291',
        'link' => '#c55964',
        'top' => '#861509',
        'bottom' => '#f8306a',
        'text' => '#555555',
        'blockh' => '#DF8796',
        'blockbg' => '#F5D9DE',
        'borders' => '#F5D9DE',
        'sticky' => '#F5D9DE',
      ),
    ),
    'orangesunset' => array(
      'title' => t('Orange Sunset'),
      'colors' => array(
        'base' => '#f7b42b',
        'link' => '#8e6130',
        'top' => '#ec8c04',
        'bottom' => '#fade42',
        'text' => '#555555',
        'blockh' => '#F7B836',
        'blockbg' => '#FDE9C0',
        'borders' => '#FDE9C0',
        'sticky' => '#FDE9C0',
      ),
    ),
    'goldyellow' => array(
      'title' => t('Gold Yellow'),
      'colors' => array(
        'base' => '#d1bc00',
        'link' => '#6c7019',
        'top' => '#d5be01',
        'bottom' => '#f0fd58',
        'text' => '#555555',
        'blockh' => '#D3BF0D',
        'blockbg' => '#F1EBB3',
        'borders' => '#F1EBB3',
        'sticky' => '#F1EBB3',
      ),
    ),
    'sandstone' => array(
      'title' => t('Sandstone'),
      'colors' => array(
        'base' => '#d1681d',
        'link' => '#8b4513',
        'top' => '#D37029',
        'bottom' => '#d2691e',
        'text' => '#000000',
        'blockh' => '#D37029',
        'blockbg' => '#F1D2BC',
        'borders' => '#F1D2BC',
        'sticky' => '#F1D2BC',
      ),
    ),
    'caramelbrown' => array(
      'title' => t('Caramel Brown'),
      'colors' => array(
        'base' => '#d59648',
        'link' => '#865518',
        'top' => '#572e05',
        'bottom' => '#eb8919',
        'text' => '#555555',
        'blockh' => '#D79B51',
        'blockbg' => '#F2E0C8',
        'borders' => '#F2E0C8',
        'sticky' => '#F2E0C8',
      ),
    ),
    'earthbrown' => array(
      'title' => t('Earth Brown'),
      'colors' => array(
        'base' => '#cfb377',
        'link' => '#90712c',
        'top' => '#463406',
        'bottom' => '#e6bd5c',
        'text' => '#555555',
        'blockh' => '#D1B77E',
        'blockbg' => '#F1E8D6',
        'borders' => '#F1E8D6',
        'sticky' => '#F1E8D6',
      ),
    ),
    'olivegarden' => array(
      'title' => t('Olive Garden'),
      'colors' => array(
        'base' => '#afc94a',
        'link' => '#61751f',
        'top' => '#2d3701',
        'bottom' => '#d2f943',
        'text' => '#555555',
        'blockh' => '#B3CC53',
        'blockbg' => '#E7EFC9',
        'borders' => '#E7EFC9',
        'sticky' => '#E7EFC9',
      ),
    ),
    'forestgreen' => array(
      'title' => t('Forest Green'),
      'colors' => array(
        'base' => '#9bc068',
        'link' => '#3c7c41',
        'top' => '#0e3d0b',
        'bottom' => '#6beb37',
        'text' => '#555555',
        'blockh' => '#A0C370',
        'blockbg' => '#E1ECD2',
        'borders' => '#E1ECD2',
        'sticky' => '#E1ECD2',
      ),
    ),
    'teal' => array(
      'title' => t('Teal'),
      'colors' => array(
        'base' => '#83b49f',
        'link' => '#486156',
        'top' => '#174431',
        'bottom' => '#52bf90',
        'text' => '#555555',
        'blockh' => '#89B8A4',
        'blockbg' => '#DAE9E2',
        'borders' => '#DAE9E2',
        'sticky' => '#DAE9E2',
      ),
    ),
    'aquamarine' => array(
      'title' => t('Aquamarine'),
      'colors' => array(
        'base' => '#55c0e2',
        'link' => '#000000',
        'top' => '#085360',
        'bottom' => '#007e94',
        'text' => '#555555',
        'blockh' => '#5EC3E3',
        'blockbg' => '#CCECF6',
        'borders' => '#CCECF6',
        'sticky' => '#CCECF6',
      ),
    ),
    'oceanwater' => array(
      'title' => t('Ocean Water'),
      'colors' => array(
        'base' => '#7bc0ea',
        'link' => '#3561b1',
        'top' => '#025fb1',
        'bottom' => '#62c8fd',
        'text' => '#555555',
        'blockh' => '#82C3EB',
        'blockbg' => '#D8ECF9',
        'borders' => '#D8ECF9',
        'sticky' => '#D8ECF9',
      ),
    ),
    'deepblue' => array(
      'title' => t('Deep Blue'),
      'colors' => array(
        'base' => '#1C44A9',
        'link' => '#4b5cc3',
        'top' => '#062984',
        'bottom' => '#5283ff',
        'text' => '#555555',
        'blockh' => '#284EAD',
        'blockbg' => '#BBC7E5',
        'borders' => '#BBC7E5',
        'sticky' => '#BBC7E5',
      ),
    ),
    'graphite' => array(
      'title' => t('Graphite'),
      'colors' => array(
        'base' => '#9397d7',
        'link' => '#575dc1',
        'top' => '#091c3e',
        'bottom' => '#d0d6f6',
        'text' => '#555555',
        'blockh' => '#203254',
        'blockbg' => '#DFE0F3',
        'borders' => '#DFE0F3',
        'sticky' => '#DFE0F3',
      ),
    ),
    'violet' => array(
      'title' => t('Violet'),
      'colors' => array(
        'base' => '#ba90c6',
        'link' => '#935b9f',
        'top' => '#250c27',
        'bottom' => '#c271d0',
        'text' => '#555555',
        'blockh' => '#BE96C9',
        'blockbg' => '#EADEEE',
        'borders' => '#EADEEE',
        'sticky' => '#EADEEE',
      ),
    ),
    'purplehaze' => array(
      'title' => t('Purple Haze'),
      'colors' => array(
        'base' => '#b0a2f6',
        'link' => '#7958a7',
        'top' => '#25008f',
        'bottom' => '#c49eff',
        'text' => '#555555',
        'blockh' => '#B4A7F6',
        'blockbg' => '#E7E3FC',
        'borders' => '#E7E3FC',
        'sticky' => '#E7E3FC',
      ),
    ),
    'silver' => array(
      'title' => t('Silver'),
      'colors' => array(
        'base' => '#aaaeb1',
        'link' => '#4d637a',
        'top' => '#8c909b',
        'bottom' => '#eeecec',
        'text' => '#555555',
        'blockh' => '#AEB2B5',
        'blockbg' => '#E6E7E8',
        'borders' => '#E6E7E8',
        'sticky' => '#E6E7E8',
      ),
    ),
    'ash' => array(
      'title' => t('Ash'),
      'colors' => array(
        'base' => '#464849',
        'link' => '#2f416f',
        'top' => '#2a2b2d',
        'bottom' => '#5d6779',
        'text' => '#555555',
        'blockh' => '#4F5152',
        'blockbg' => '#C8C8C9',
        'borders' => '#C8C8C9',
        'sticky' => '#C8C8C9',
      ),
    ),
    'gothic' => array(
      'title' => t('Gothic'),
      'colors' => array(
        'base' => '#202020',
        'link' => '#11275f',
        'top' => '#000000',
        'bottom' => '#808080',
        'text' => '#000000',
        'blockh' => '#2B2B2B',
        'blockbg' => '#BDBDBD',
        'borders' => '#BDBDBD',
        'sticky' => '#BDBDBD',
      ),
    ),
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'colors.css',
  ),

  // Images to copy over
  'copy' => array(
    'images/bullet-round.png',
    'images/bullet-sm-arrow-right.png',
    'images/bullet-sm-arrow-down.png',
    'images/button.gif',
    'images/button-o.gif',
  ),

  // Coordinates of gradient (x, y, width, height)
  'gradients' => array(
    array(
      'dimension' => array(0,0,800,94),
      'direction' => 'vertical',
      'colors' => array('top', 'bottom'),
    ),
  ),

  // Color areas to fill (x, y, width, height)
  'fill' => array(
    'base' => array(0,0,800,570),
    'link' => array(240,530,40,40),
  ),

  // Coordinates of all the theme slices (x, y, width, height).
  'slices' => array(
    'images/header.png' => array(2,0,512,88),
    'images/header-tile.png' => array(792,0,8,88),
    'images/menu-tile.png' => array(792,0,8,32),
    'images/bg-footer.png' => array(792,0,8,88),
    'images/bg-footer-tile.png' => array(792,87,1,1),
    'images/bg-menu.png' => array(0,88,8,32),
    'images/bg-title.png' => array(20,130,10,10),
    'images/bg-wall.png' => array(792,120,8,408),
    'images/bg-bar-lite.png' => array(0,530,8,40),
    'images/bg-bar.png' => array(20,530,8,40),
    'images/bg-lbar-lite.png' => array(270,530,8,40),
    'images/bg-lbar.png' => array(250,530,8,40),
    'images/sf-hover-tile.png' => array(0,30,250,1),
  ),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files.
  'preview_image' => 'color/color-preview.png',
  'preview_css' => 'color/preview.css',

  // Base file for image generation
  'base_image' => 'color/base.png',
);