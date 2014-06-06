<?php
declare(ticks=7);
function test()
{
  echo "hello\n";
}
register_tick_function('test');
$a = 'test';
$a();
?>


