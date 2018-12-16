# Bras_Moveo

Code source pour le bras MOVEO assemblé à robopoly.  
Le code permet de controler individuellement chaque moteur à l'aide d'une manette de ps3 ( dualshock 3 )  
Afin de mapper les boutons le code disponible ici peut être utile :   
https://theraspberryblonde.wordpress.com/2016/06/29/ps3-joystick-control-with-pygame/  
Le raspberry et l'arduino communiquent entre eux par serial. Par défaut via un cable usb.  
Le code va comme suit : un caractère est dédié à chaque moteur. '0' immmobilise le stepper, '1' le fait bouger dans un sens et '2' dans le sens inverse.   
Par exemple "102" fera bouger le premier et troisième moteur dans des sens opposés. 

/!\ Pour éteindre le raspberry appuyer simultanément sur start et select
