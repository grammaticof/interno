<div id="google-search">
  <script type="text/javascript" src="http://www.google.com/jsapi"></script>
<script type="text/javascript">
  google.load('search', '1');
  google.setOnLoadCallback(function() {
    google.search.CustomSearchControl.attachAutoCompletion(
      '005171206513133717924:kcnq9zomqqc',
      document.getElementById('as_q'),
      'cse-search-box');
  });
</script>
<form action="<?php print url('gsearch/result', array('absolute' => TRUE)); ?>" id="cse-search-box">
  <div>
    <input type="hidden" name="cx" value="005171206513133717924:kcnq9zomqqc" />
    <input type="hidden" name="cof" value="FORID:9" />
    <input type="hidden" name="ie" value="UTF-8" />
    <input type="text" name="as_q" id="as_q" autocomplete="off" size="20" />
    <input type="submit" name="sa" value="<?php print t('Search'); ?>" />
  </div>
</form>
<script type="text/javascript" src="http://www.google.com/cse/brand?form=cse-search-box&lang=it"></script>
</div>
