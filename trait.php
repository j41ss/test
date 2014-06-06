<?php
   trait H {
     function said() 
     {
       echo 'hello ';
     } 
     }
   trait W {
     function said2()
     {
       echo " world\n";
     } 
     }
   class Base2 {
     use H, W;
   }
   $a = new Base2();
   $a->said();
   $a->said2();






?>
